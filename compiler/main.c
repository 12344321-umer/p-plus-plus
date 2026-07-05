#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "semantic.h"

typedef struct Symbol Symbol;

/* Defined by Bison */
extern int   yyparse();
extern FILE *yyin;

/* AST root set by parser.y */
extern ASTNode *ast_root;

/* 
   Output modes
 */
typedef enum {
    MODE_ALL,
    MODE_TOKENS,
    MODE_AST,
    MODE_SYMBOLS,
    MODE_JSON
} OutputMode;


/* ══════════════════════════════════════════════════════
   OUTPUT COLLECTOR
══════════════════════════════════════════════════════ */
#define MAX_OUTPUT_LINES 256
#define MAX_LINE_LEN     1024

static char  output_lines[MAX_OUTPUT_LINES][MAX_LINE_LEN];
static int   output_count = 0;

static void collect_output(const char *line) {
    if (output_count < MAX_OUTPUT_LINES) {
        strncpy(output_lines[output_count], line, MAX_LINE_LEN - 1);
        output_lines[output_count][MAX_LINE_LEN - 1] = '\0';
        output_count++;
    }
}


/* ══════════════════════════════════════════════════════
   INTERPRETER
══════════════════════════════════════════════════════ */
typedef enum  { VAL_INT, VAL_FLOAT, VAL_STRING, VAL_BOOL, VAL_NULL } ValType;
typedef struct {
    ValType type;
    int     int_val;
    double  float_val;
    char    str_val[MAX_LINE_LEN];
} Value;

static Value make_null_val()          { Value v; v.type = VAL_NULL;  return v; }
static Value make_int_val(int n)      { Value v; v.type = VAL_INT;   v.int_val   = n; return v; }
static Value make_float_val(double d) { Value v; v.type = VAL_FLOAT; v.float_val = d; return v; }
static Value make_bool_val(int b)     { Value v; v.type = VAL_BOOL;  v.int_val   = b; return v; }
static Value make_string_val(const char *s) {
    Value v; v.type = VAL_STRING;
    strncpy(v.str_val, s, MAX_LINE_LEN - 1);
    v.str_val[MAX_LINE_LEN - 1] = '\0';
    return v;
}

/* ── Variable store with scope stack ── */
#define MAX_VARS   256
#define MAX_SCOPES  64

typedef struct {
    char  name[64];
    Value val;
    int   scope_depth;
} VarEntry;

static VarEntry var_store[MAX_VARS];
static int      var_count   = 0;
static int      scope_depth = 0;

static void interp_push_scope() { scope_depth++; }

static void interp_pop_scope() {
    int i = var_count - 1;
    while (i >= 0 && var_store[i].scope_depth == scope_depth)
        i--;
    var_count = i + 1;
    scope_depth--;
}

static void store_var(const char *name, Value val) {
    /* first look in current scope only */
    for (int i = var_count - 1; i >= 0; i--) {
        if (var_store[i].scope_depth < scope_depth) break;
        if (strcmp(var_store[i].name, name) == 0) {
            var_store[i].val = val;
            return;
        }
    }
    /* then look in outer scopes */
    for (int i = var_count - 1; i >= 0; i--) {
        if (strcmp(var_store[i].name, name) == 0) {
            var_store[i].val = val;
            return;
        }
    }
    /* not found anywhere — declare in current scope */
    if (var_count < MAX_VARS) {
        strncpy(var_store[var_count].name, name, 63);
        var_store[var_count].name[63]    = '\0';
        var_store[var_count].val         = val;
        var_store[var_count].scope_depth = scope_depth;
        var_count++;
    }
}

static void declare_var(const char *name, Value val) {
    if (var_count < MAX_VARS) {
        strncpy(var_store[var_count].name, name, 63);
        var_store[var_count].name[63]    = '\0';
        var_store[var_count].val         = val;
        var_store[var_count].scope_depth = scope_depth;
        var_count++;
    }
}

static Value lookup_var(const char *name) {
    for (int i = var_count - 1; i >= 0; i--) {
        if (strcmp(var_store[i].name, name) == 0)
            return var_store[i].val;
    }
    return make_null_val();
}


/* ── Function store ── */
#define MAX_FUNCS 64

typedef struct {
    char     name[64];
    ASTNode *params;
    ASTNode *body;
} FuncEntry;

static FuncEntry func_store[MAX_FUNCS];
static int       func_count = 0;

static void store_func(const char *name, ASTNode *params, ASTNode *body) {
    for (int i = 0; i < func_count; i++) {
        if (strcmp(func_store[i].name, name) == 0) {
            func_store[i].params = params;
            func_store[i].body   = body;
            return;
        }
    }
    if (func_count < MAX_FUNCS) {
        strncpy(func_store[func_count].name, name, 63);
        func_store[func_count].name[63] = '\0';
        func_store[func_count].params   = params;
        func_store[func_count].body     = body;
        func_count++;
    }
}

static FuncEntry *lookup_func(const char *name) {
    for (int i = 0; i < func_count; i++) {
        if (strcmp(func_store[i].name, name) == 0)
            return &func_store[i];
    }
    return NULL;
}


/* forward declaration */
static Value evaluate(ASTNode *node);

/* ── value_to_str — forward declared so eval_binop can use it ── */
static void value_to_str(Value v, char *buf, int buf_size);

/* ══════════════════════════════════════════════════════
   eval_binop — handles math AND string concatenation
══════════════════════════════════════════════════════ */
static Value eval_binop(const char *op, Value left, Value right) {

    /* string concatenation — ^+ with at least one string side */
    if (strcmp(op, "^+") == 0 &&
        (left.type == VAL_STRING || right.type == VAL_STRING)) {
        char lbuf[MAX_LINE_LEN];
        char rbuf[MAX_LINE_LEN];
        char result[MAX_LINE_LEN * 2];
        value_to_str(left,  lbuf, MAX_LINE_LEN);
        value_to_str(right, rbuf, MAX_LINE_LEN);
        snprintf(result, sizeof(result), "%s%s", lbuf, rbuf);
        return make_string_val(result);
    }

    int    is_float = (left.type == VAL_FLOAT || right.type == VAL_FLOAT);
    double l = (left.type  == VAL_FLOAT) ? left.float_val  : (double)left.int_val;
    double r = (right.type == VAL_FLOAT) ? right.float_val : (double)right.int_val;

    double result = 0;
    if      (strcmp(op, "^+") == 0) result = l + r;
    else if (strcmp(op, "^-") == 0) result = l - r;
    else if (strcmp(op, "^*") == 0) result = l * r;
    else if (strcmp(op, "^/") == 0) result = (r != 0) ? l / r : 0;
    else if (strcmp(op, "^%") == 0) result = (r != 0) ? (int)l % (int)r : 0;

    if (is_float) return make_float_val(result);
    return make_int_val((int)result);
}

/* ══════════════════════════════════════════════════════
   eval_condition — handles numeric AND string comparison
══════════════════════════════════════════════════════ */
static int eval_condition(ASTNode *node) {
    if (!node) return 0;
    const char *op = node->str_val;

    if (strcmp(op, "aurBhai") == 0)
        return eval_condition(node->left) && eval_condition(node->right);
    if (strcmp(op, "yaBhai") == 0)
        return eval_condition(node->left) || eval_condition(node->right);
    if (strcmp(op, "nahi") == 0)
        return !eval_condition(node->left);

    Value left  = evaluate(node->left);
    Value right = evaluate(node->right);

    /* string comparison */
    if (left.type == VAL_STRING || right.type == VAL_STRING) {
        char lbuf[MAX_LINE_LEN], rbuf[MAX_LINE_LEN];
        value_to_str(left,  lbuf, MAX_LINE_LEN);
        value_to_str(right, rbuf, MAX_LINE_LEN);
        if (strcmp(op, "==?") == 0) return strcmp(lbuf, rbuf) == 0;
        if (strcmp(op, "<")   == 0) return strcmp(lbuf, rbuf) <  0;
        if (strcmp(op, ">")   == 0) return strcmp(lbuf, rbuf) >  0;
        return 0;
    }

    /* numeric comparison */
    double l = (left.type  == VAL_FLOAT) ? left.float_val  : (double)left.int_val;
    double r = (right.type == VAL_FLOAT) ? right.float_val : (double)right.int_val;

    if (strcmp(op, "==?") == 0) return l == r;
    if (strcmp(op, "<")   == 0) return l <  r;
    if (strcmp(op, ">")   == 0) return l >  r;
    if (strcmp(op, "<=")  == 0) return l <= r;
    if (strcmp(op, ">=")  == 0) return l >= r;
    return 0;
}

/* ══════════════════════════════════════════════════════
   value_to_str
══════════════════════════════════════════════════════ */
static void value_to_str(Value v, char *buf, int buf_size) {
    switch (v.type) {
        case VAL_INT:
            snprintf(buf, buf_size, "%d", v.int_val);
            break;
        case VAL_FLOAT:
            snprintf(buf, buf_size, "%g", v.float_val);
            break;
        case VAL_BOOL:
            snprintf(buf, buf_size, "%s", v.int_val ? "noCap" : "cap");
            break;
        case VAL_STRING: {
            const char *s = v.str_val;
            if (s[0] == '"') {
                strncpy(buf, s + 1, buf_size - 1);
                buf[buf_size - 1] = '\0';
                int len = strlen(buf);
                if (len > 0 && buf[len - 1] == '"')
                    buf[len - 1] = '\0';
            } else {
                strncpy(buf, s, buf_size - 1);
                buf[buf_size - 1] = '\0';
            }
            break;
        }
        default:
            snprintf(buf, buf_size, "null");
            break;
    }
}

#define BREAK_SIGNAL    1
#define CONTINUE_SIGNAL 2
#define RETURN_SIGNAL   3
static int   control_signal = 0;
static Value return_value;

static Value evaluate(ASTNode *node) {
    if (!node) return make_null_val();

    switch (node->type) {

        case NODE_INT_LIT:    return make_int_val(node->int_val);
        case NODE_FLOAT_LIT:  return make_float_val(node->float_val);
        case NODE_BOOL_LIT:   return make_bool_val(node->int_val);
        case NODE_STRING_LIT: return make_string_val(node->str_val);
        case NODE_IDENTIFIER: return lookup_var(node->str_val);

        case NODE_BINOP: {
            Value left  = evaluate(node->left);
            Value right = evaluate(node->right);
            return eval_binop(node->str_val, left, right);
        }

        case NODE_DECL: {
            Value val = evaluate(node->left);
            declare_var(node->str_val, val);
            return val;
        }

        case NODE_ASSIGN: {
            Value val = evaluate(node->left);
            store_var(node->str_val, val);
            return val;
        }

        case NODE_PRINT: {
            Value val = evaluate(node->left);
            char  buf[MAX_LINE_LEN];
            value_to_str(val, buf, MAX_LINE_LEN);
            collect_output(buf);
            return make_null_val();
        }

        case NODE_STMT_LIST: {
            ASTNode *cur = node;
            while (cur) {
                if (control_signal) break;
                evaluate(cur->left);
                cur = cur->next;
            }
            return make_null_val();
        }

        case NODE_IF: {
            if (eval_condition(node->left)) {
                interp_push_scope();
                evaluate(node->right);
                interp_pop_scope();
            }
            return make_null_val();
        }

        case NODE_IF_ELSE: {
            if (eval_condition(node->left)) {
                interp_push_scope();
                evaluate(node->right);
                interp_pop_scope();
            } else {
                interp_push_scope();
                evaluate(node->extra);
                interp_pop_scope();
            }
            return make_null_val();
        }

        /* lowkey (cond) ... phirBro (cond2) ...
           Only run the phirBro branch if the first condition was
           false AND the phirBro's own condition is true. If neither
           condition holds, do nothing — matches how if/elseif works
           in every other language. */
        case NODE_IF_ELSEIF: {
            if (eval_condition(node->left)) {
                interp_push_scope();
                evaluate(node->right);
                interp_pop_scope();
            } else if (eval_condition(node->cond2)) {
                interp_push_scope();
                evaluate(node->extra);
                interp_pop_scope();
            }
            return make_null_val();
        }

        case NODE_WHILE: {
            while (eval_condition(node->left)) {
                control_signal = 0;
                interp_push_scope();
                evaluate(node->right);
                interp_pop_scope();
                if (control_signal == BREAK_SIGNAL)  break;
                if (control_signal == RETURN_SIGNAL) break;
            }
            if (control_signal != RETURN_SIGNAL)
                control_signal = 0;
            return make_null_val();
        }

        case NODE_BREAK:
            control_signal = BREAK_SIGNAL;
            return make_null_val();

        case NODE_CONTINUE:
            control_signal = CONTINUE_SIGNAL;
            return make_null_val();

        case NODE_RETURN: {
            return_value   = evaluate(node->left);
            control_signal = RETURN_SIGNAL;
            return return_value;
        }

        case NODE_FUNC_DECL:
            store_func(node->str_val, node->left, node->right);
            return make_null_val();

        case NODE_FUNC_CALL: {
            FuncEntry *fn = lookup_func(node->str_val);
            if (!fn) {
                fprintf(stderr, "Runtime Error: undefined function '%s'\n",
                        node->str_val);
                return make_null_val();
            }
            interp_push_scope();
            ASTNode *param = fn->params;
            ASTNode *arg   = node->left;
            while (param && arg) {
                Value val = evaluate(arg->left);
                declare_var(param->str_val, val);
                param = param->next;
                arg   = arg->next;
            }
            int saved_signal = control_signal;
            control_signal   = 0;
            evaluate(fn->body);
            Value result     = (control_signal == RETURN_SIGNAL)
                               ? return_value
                               : make_null_val();
            control_signal   = saved_signal;
            interp_pop_scope();
            return result;
        }

        /* gintiBata varName — returns string length as int */
        case NODE_STR_LEN: {
            Value val = lookup_var(node->str_val);
            char  buf[MAX_LINE_LEN];
            value_to_str(val, buf, MAX_LINE_LEN);
            return make_int_val((int)strlen(buf));
        }

        case NODE_PROGRAM:
            return evaluate(node->left);

        default:
            return make_null_val();
    }
}


/* ══════════════════════════════════════════════════════
   JSON helpers
══════════════════════════════════════════════════════ */
static void json_escape(const char *s) {
    if (!s) { printf("null"); return; }
    printf("\"");
    while (*s) {
        if      (*s == '"')  printf("\\\"");
        else if (*s == '\\') printf("\\\\");
        else if (*s == '\n') printf("\\n");
        else if (*s == '\r') printf("\\r");
        else if (*s == '\t') printf("\\t");
        else                 printf("%c", *s);
        s++;
    }
    printf("\"");
}

static void ast_to_json(ASTNode *node) {
    if (!node) { printf("null"); return; }
    printf("{");
    printf("\"type\":");
    switch (node->type) {
        case NODE_PROGRAM:     printf("\"Program\"");    break;
        case NODE_STMT_LIST:   printf("\"StmtList\"");   break;
        case NODE_DECL:        printf("\"VarDecl\"");    break;
        case NODE_ASSIGN:      printf("\"Assign\"");     break;
        case NODE_IF:          printf("\"If\"");         break;
        case NODE_IF_ELSE:     printf("\"IfElse\"");     break;
        case NODE_IF_ELSEIF:   printf("\"IfElseIf\"");   break;
        case NODE_WHILE:       printf("\"While\"");      break;
        case NODE_PRINT:       printf("\"Print\"");      break;
        case NODE_RETURN:      printf("\"Return\"");     break;
        case NODE_BREAK:       printf("\"Break\"");      break;
        case NODE_CONTINUE:    printf("\"Continue\"");   break;
        case NODE_BINOP:       printf("\"BinOp\"");      break;
        case NODE_CONDITION:   printf("\"Condition\"");  break;
        case NODE_INT_LIT:     printf("\"IntLit\"");     break;
        case NODE_FLOAT_LIT:   printf("\"FloatLit\"");   break;
        case NODE_STRING_LIT:  printf("\"StringLit\"");  break;
        case NODE_BOOL_LIT:    printf("\"BoolLit\"");    break;
        case NODE_IDENTIFIER:  printf("\"Identifier\""); break;
        case NODE_FUNC_DECL:   printf("\"FuncDecl\"");   break;
        case NODE_FUNC_CALL:   printf("\"FuncCall\"");   break;
        case NODE_PARAM_LIST:  printf("\"ParamList\"");  break;
        case NODE_ARG_LIST:    printf("\"ArgList\"");    break;
        case NODE_STR_LEN:     printf("\"StrLen\"");     break;
        default:               printf("\"Unknown\"");    break;
    }
    if (node->str_val) {
        printf(",\"value\":"); json_escape(node->str_val);
    } else if (node->type == NODE_INT_LIT) {
        printf(",\"value\":%d", node->int_val);
    } else if (node->type == NODE_FLOAT_LIT) {
        printf(",\"value\":%g", node->float_val);
    } else if (node->type == NODE_BOOL_LIT) {
        printf(",\"value\":\"%s\"", node->int_val ? "noCap" : "cap");
    }
    if (node->left)  { printf(",\"left\":");  ast_to_json(node->left);  }
    if (node->right) { printf(",\"right\":"); ast_to_json(node->right); }
    if (node->cond2) { printf(",\"cond2\":"); ast_to_json(node->cond2); }
    if (node->extra) { printf(",\"extra\":"); ast_to_json(node->extra); }
    if (node->next)  { printf(",\"next\":");  ast_to_json(node->next);  }
    printf("}");
}

static void symbols_to_json(SymbolTable *table) {
    printf("[");
    Symbol *all   = collect_all_symbols(table);
    Symbol *cur   = all;
    int     first = 1;
    while (cur) {
        if (!first) printf(",");
        first = 0;
        const char *type_str;
        switch (cur->type) {
            case TYPE_INT:    type_str = "int";     break;
            case TYPE_FLOAT:  type_str = "float";   break;
            case TYPE_STRING: type_str = "string";  break;
            case TYPE_BOOL:   type_str = "bool";    break;
            default:          type_str = "unknown"; break;
        }
        printf("{\"name\":\"%s\",\"type\":\"%s\",\"line\":%d}",
               cur->name, type_str, cur->line);
        cur = cur->next;
    }
    cur = all;
    while (cur) {
        Symbol *next = cur->next;
        free(cur);
        cur = next;
    }
    printf("]");
}

static void output_to_json() {
    printf("[");
    for (int i = 0; i < output_count; i++) {
        if (i > 0) printf(",");
        json_escape(output_lines[i]);
    }
    printf("]");
}


/* ══════════════════════════════════════════════════════
   Entry point
══════════════════════════════════════════════════════ */
int main(int argc, char *argv[]) {

    char       *filename = NULL;
    OutputMode  mode     = MODE_ALL;

    for (int i = 1; i < argc; i++) {
        if      (strcmp(argv[i], "--tokens")  == 0) mode = MODE_TOKENS;
        else if (strcmp(argv[i], "--ast")     == 0) mode = MODE_AST;
        else if (strcmp(argv[i], "--symbols") == 0) mode = MODE_SYMBOLS;
        else if (strcmp(argv[i], "--json")    == 0) mode = MODE_JSON;
        else                                        filename = argv[i];
    }

    if (filename) {
        yyin = fopen(filename, "r");
        if (!yyin) {
            fprintf(stderr, "Error: cannot open file '%s'\n", filename);
            return 1;
        }
    } else {
        yyin = stdin;
    }

    int parse_result = yyparse();
    if (filename) fclose(yyin);

    /* ── JSON mode ── */
    if (mode == MODE_JSON) {
        SymbolTable *table      = create_symbol_table();
        int          sem_errors = 0;

        if (ast_root)
            sem_errors = analyze(ast_root, table);

        if (parse_result == 0 && sem_errors == 0 && ast_root)
            evaluate(ast_root);

        printf("{");
        printf("\"parseOk\":%s",    parse_result == 0 ? "true" : "false");
        printf(",\"semErrors\":%d", sem_errors);
        printf(",\"output\":");     output_to_json();
        printf(",\"ast\":");        ast_to_json(ast_root);
        printf(",\"symbols\":");    symbols_to_json(table);
        printf("}\n");

        destroy_symbol_table(table);
        free_ast(ast_root);
        return (parse_result == 0 && sem_errors == 0) ? 0 : 1;
    }

    /* ── Human-readable modes ── */
    if (parse_result != 0) {
        fprintf(stderr, "\nParsing failed.\n");
        return 1;
    }

    printf("\n✓ Parsing successful!\n");

    SymbolTable *table      = create_symbol_table();
    int          sem_errors = analyze(ast_root, table);

    if (mode == MODE_ALL || mode == MODE_AST) {
        printf("\n========== Abstract Syntax Tree ==========\n");
        print_ast(ast_root, 0);
    }

    if (mode == MODE_ALL || mode == MODE_SYMBOLS) {
        print_symbol_table(table);
    }

    if (sem_errors > 0) {
        fprintf(stderr, "\n✗ Semantic analysis failed with %d error(s).\n",
                sem_errors);
    } else {
        printf("✓ Semantic analysis passed.\n\n");
    }

    destroy_symbol_table(table);
    free_ast(ast_root);
    return sem_errors > 0 ? 1 : 0;
}