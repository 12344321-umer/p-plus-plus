 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "semantic.h"

/* Defined by Bison */
extern int   yyparse();
extern FILE *yyin;

/* AST root set by parser.y */
extern ASTNode *ast_root;

/* 
   Output modes
 */
typedef enum {
    MODE_ALL,       // tokens + AST + symbol table (default)
    MODE_TOKENS,    // lexer output only
    MODE_AST,       // AST only
    MODE_SYMBOLS,   // symbol table only
    MODE_JSON       // JSON output (for web playground)
} OutputMode;


/* 
   JSON helpers (for the web playground)
 */
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

    /* type label */
    printf("\"type\":");
    switch (node->type) {
        case NODE_PROGRAM:     printf("\"Program\"");     break;
        case NODE_STMT_LIST:   printf("\"StmtList\"");    break;
        case NODE_DECL:        printf("\"VarDecl\"");     break;
        case NODE_ASSIGN:      printf("\"Assign\"");      break;
        case NODE_IF:          printf("\"If\"");          break;
        case NODE_IF_ELSE:     printf("\"IfElse\"");      break;
        case NODE_IF_ELSEIF:   printf("\"IfElseIf\"");    break;
        case NODE_WHILE:       printf("\"While\"");       break;
        case NODE_PRINT:       printf("\"Print\"");       break;
        case NODE_RETURN:      printf("\"Return\"");      break;
        case NODE_BREAK:       printf("\"Break\"");       break;
        case NODE_CONTINUE:    printf("\"Continue\"");    break;
        case NODE_BINOP:       printf("\"BinOp\"");       break;
        case NODE_CONDITION:   printf("\"Condition\"");   break;
        case NODE_INT_LIT:     printf("\"IntLit\"");      break;
        case NODE_FLOAT_LIT:   printf("\"FloatLit\"");    break;
        case NODE_STRING_LIT:  printf("\"StringLit\"");   break;
        case NODE_BOOL_LIT:    printf("\"BoolLit\"");     break;
        case NODE_IDENTIFIER:  printf("\"Identifier\"");  break;
        default:               printf("\"Unknown\"");     break;
    }

    /* value */
    if (node->str_val) {
        printf(",\"value\":"); json_escape(node->str_val);
    } else if (node->type == NODE_INT_LIT) {
        printf(",\"value\":%d", node->int_val);
    } else if (node->type == NODE_FLOAT_LIT) {
        printf(",\"value\":%g", node->float_val);
    } else if (node->type == NODE_BOOL_LIT) {
        printf(",\"value\":\"%s\"", node->int_val ? "noCap" : "cap");
    }

    /* children */
    if (node->left) {
        printf(",\"left\":");
        ast_to_json(node->left);
    }
    if (node->right) {
        printf(",\"right\":");
        ast_to_json(node->right);
    }
    if (node->extra) {
        printf(",\"extra\":");
        ast_to_json(node->extra);
    }
    if (node->next) {
        printf(",\"next\":");
        ast_to_json(node->next);
    }

    printf("}");
}

static void symbols_to_json(SymbolTable *table) {
    printf("[");
    Symbol *cur   = table->head;
    int     first = 1;
    while (cur) {
        if (!first) printf(",");
        first = 0;
        const char *type_str;
        switch (cur->type) {
            case TYPE_INT:    type_str = "int";    break;
            case TYPE_FLOAT:  type_str = "float";  break;
            case TYPE_STRING: type_str = "string"; break;
            case TYPE_BOOL:   type_str = "bool";   break;
            default:          type_str = "unknown";break;
        }
        printf("{\"name\":\"%s\",\"type\":\"%s\",\"line\":%d}",
               cur->name, type_str, cur->line);
        cur = cur->next;
    }
    printf("]");
}


/* 
   Entry point
 */
int main(int argc, char *argv[]) {

    /* defaults */
    char       *filename = NULL;
    OutputMode  mode     = MODE_ALL;

    /* parse arguments */
    for (int i = 1; i < argc; i++) {
        if      (strcmp(argv[i], "--tokens")  == 0) mode = MODE_TOKENS;
        else if (strcmp(argv[i], "--ast")     == 0) mode = MODE_AST;
        else if (strcmp(argv[i], "--symbols") == 0) mode = MODE_SYMBOLS;
        else if (strcmp(argv[i], "--json")    == 0) mode = MODE_JSON;
        else                                        filename = argv[i];
    }

    /* open input file */
    if (filename) {
        yyin = fopen(filename, "r");
        if (!yyin) {
            fprintf(stderr, "Error: cannot open file '%s'\n", filename);
            return 1;
        }
    } else {
        yyin = stdin;
    }

    /* run the parser (which runs the lexer internally) */
    int parse_result = yyparse();

    if (filename) fclose(yyin);

    /* ── JSON mode: used by the web playground ── */
    if (mode == MODE_JSON) {
        SymbolTable *table = create_symbol_table();
        int sem_errors     = 0;

        if (ast_root)
            sem_errors = analyze(ast_root, table);

        printf("{");
        printf("\"parseOk\":%s",   parse_result == 0 ? "true" : "false");
        printf(",\"semErrors\":%d", sem_errors);
        printf(",\"ast\":");
        ast_to_json(ast_root);
        printf(",\"symbols\":");
        symbols_to_json(table);
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

    SymbolTable *table     = create_symbol_table();
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
