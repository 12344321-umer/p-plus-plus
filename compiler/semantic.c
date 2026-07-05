#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"


/* ══════════════════════════════════════
   SCOPE MANAGEMENT
══════════════════════════════════════ */

static Scope *create_scope(Scope *parent) {
    Scope *s  = (Scope *)malloc(sizeof(Scope));
    s->head   = NULL;
    s->parent = parent;
    return s;
}

static void destroy_scope(Scope *s) {
    if (!s) return;
    Symbol *cur = s->head;
    while (cur) {
        Symbol *next = cur->next;
        if (cur->name) free(cur->name);
        free(cur);
        cur = next;
    }
    free(s);
}

SymbolTable *create_symbol_table() {
    SymbolTable *table  = (SymbolTable *)malloc(sizeof(SymbolTable));
    table->error_count  = 0;
    table->current      = create_scope(NULL); // global scope
    return table;
}

void destroy_symbol_table(SymbolTable *table) {
    if (!table) return;
    Scope *cur = table->current;
    while (cur) {
        Scope *parent = cur->parent;
        destroy_scope(cur);
        cur = parent;
    }
    free(table);
}

/* Enter a new inner scope */
void push_scope(SymbolTable *table) {
    table->current = create_scope(table->current);
}

/* Leave the current scope and go back to the parent */
void pop_scope(SymbolTable *table) {
    if (!table->current || !table->current->parent) return;
    Scope *old      = table->current;
    table->current  = old->parent;
    destroy_scope(old);
}


/* ══════════════════════════════════════
   SYMBOL OPERATIONS
══════════════════════════════════════ */

/*
   Declare a variable in the CURRENT scope only.
   It is fine to shadow a variable from an outer scope.
*/
int declare_symbol(SymbolTable *table, const char *name, VarType type, int line) {
    /* check for duplicate in current scope only */
    Symbol *cur = table->current->head;
    while (cur) {
        if (strcmp(cur->name, name) == 0) {
            fprintf(stderr,
                "Semantic Error [line %d]: '%s' already declared in this scope\n",
                line, name);
            table->error_count++;
            return -1;
        }
        cur = cur->next;
    }

    Symbol *sym  = (Symbol *)malloc(sizeof(Symbol));
    sym->name    = strdup(name);
    sym->type    = type;
    sym->line    = line;
    sym->next    = table->current->head;
    table->current->head = sym;
    return 0;
}

/*
   Look up a variable by walking from the current scope
   upward through all parent scopes.
*/
Symbol *lookup_symbol(SymbolTable *table, const char *name) {
    Scope *scope = table->current;
    while (scope) {
        Symbol *cur = scope->head;
        while (cur) {
            if (strcmp(cur->name, name) == 0) return cur;
            cur = cur->next;
        }
        scope = scope->parent;
    }
    return NULL;
}

/*
   Collect every symbol across all scopes into a flat
   linked list — used for the JSON symbol table output.
   Caller must free the list nodes (not the names).
*/
Symbol *collect_all_symbols(SymbolTable *table) {
    Symbol *result = NULL;
    Scope  *scope  = table->current;
    while (scope) {
        Symbol *cur = scope->head;
        while (cur) {
            Symbol *copy  = (Symbol *)malloc(sizeof(Symbol));
            copy->name    = cur->name;   // borrow the pointer
            copy->type    = cur->type;
            copy->line    = cur->line;
            copy->next    = result;
            result        = copy;
            cur           = cur->next;
        }
        scope = scope->parent;
    }
    return result;
}


/* ══════════════════════════════════════
   PRINT (debug / human-readable mode)
══════════════════════════════════════ */
void print_symbol_table(SymbolTable *table) {
    printf("\n========== Symbol Table ==========\n");
    printf("%-15s %-10s %-5s\n", "Name", "Type", "Line");
    printf("----------------------------------\n");

    Scope *scope = table->current;
    int    depth = 0;
    while (scope) {
        Symbol *cur = scope->head;
        while (cur) {
            const char *type_str;
            switch (cur->type) {
                case TYPE_INT:    type_str = "int";     break;
                case TYPE_FLOAT:  type_str = "float";   break;
                case TYPE_STRING: type_str = "string";  break;
                case TYPE_BOOL:   type_str = "bool";    break;
                default:          type_str = "unknown"; break;
            }
            printf("%-15s %-10s %-5d  (scope depth %d)\n",
                   cur->name, type_str, cur->line, depth);
            cur = cur->next;
        }
        scope = scope->parent;
        depth++;
    }
    printf("==================================\n\n");
}


/* ══════════════════════════════════════
   SEMANTIC ANALYSIS
══════════════════════════════════════ */
static int loop_depth = 0;

static void analyze_expr(ASTNode *node, SymbolTable *table) {
    if (!node) return;
    switch (node->type) {

        case NODE_IDENTIFIER:
            if (!lookup_symbol(table, node->str_val)) {
                fprintf(stderr,
                    "Semantic Error: undeclared variable '%s'\n",
                    node->str_val);
                table->error_count++;
            }
            break;

        case NODE_BINOP:
        case NODE_CONDITION:
            analyze_expr(node->left,  table);
            analyze_expr(node->right, table);
            break;

        case NODE_INT_LIT:
        case NODE_FLOAT_LIT:
        case NODE_STRING_LIT:
        case NODE_BOOL_LIT:
            break;

        default:
            break;
    }
}

static void analyze_stmts(ASTNode *node, SymbolTable *table);

static void analyze_stmt(ASTNode *node, SymbolTable *table) {
    if (!node) return;

    switch (node->type) {

        case NODE_DECL: {
            VarType t = TYPE_UNKNOWN;
            if (node->left) {
                if      (node->left->type == NODE_INT_LIT)    t = TYPE_INT;
                else if (node->left->type == NODE_FLOAT_LIT)  t = TYPE_FLOAT;
                else if (node->left->type == NODE_STRING_LIT) t = TYPE_STRING;
                else if (node->left->type == NODE_BOOL_LIT)   t = TYPE_BOOL;
                else if (node->left->type == NODE_IDENTIFIER) {
                    Symbol *s = lookup_symbol(table, node->left->str_val);
                    if (s) t = s->type;
                }
            }
            declare_symbol(table, node->str_val, t, 0);
            analyze_expr(node->left, table);
            break;
        }

        /* kaamKaro funcName ::: params ::: basYar body */
case NODE_FUNC_DECL: {
    /* push a scope for the function body */
    push_scope(table);

    /* declare each parameter as a variable in that scope */
    ASTNode *param = node->left;
    while (param) {
        declare_symbol(table, param->str_val, TYPE_UNKNOWN, 0);
        param = param->next;
    }

    /* analyze the body with params in scope */
    analyze_stmts(node->right, table);

    pop_scope(table);
    break;
}

/* funcName ::: args ::: !! */
case NODE_FUNC_CALL: {
    /* analyze each argument expression */
    ASTNode *arg = node->left;
    while (arg) {
        analyze_expr(arg->left, table);
        arg = arg->next;
    }
    break;
}

        case NODE_ASSIGN:
            if (!lookup_symbol(table, node->str_val)) {
                fprintf(stderr,
                    "Semantic Error: assignment to undeclared variable '%s'\n",
                    node->str_val);
                table->error_count++;
            }
            analyze_expr(node->left, table);
            break;

        case NODE_PRINT:
            analyze_expr(node->left, table);
            break;

        case NODE_RETURN:
            analyze_expr(node->left, table);
            break;

        case NODE_BREAK:
            if (loop_depth == 0) {
                fprintf(stderr,
                    "Semantic Error: 'ghosted' used outside of a loop\n");
                table->error_count++;
            }
            break;

        case NODE_CONTINUE:
            if (loop_depth == 0) {
                fprintf(stderr,
                    "Semantic Error: 'missKara' used outside of a loop\n");
                table->error_count++;
            }
            break;

        /* if — new scope for the body */
        case NODE_IF:
            analyze_expr(node->left, table);
            push_scope(table);
            analyze_stmts(node->right, table);
            pop_scope(table);
            break;

        /* if-else — separate scopes for each branch */
        case NODE_IF_ELSE:
            analyze_expr(node->left, table);
            push_scope(table);
            analyze_stmts(node->right, table);
            pop_scope(table);
            push_scope(table);
            analyze_stmts(node->extra, table);
            pop_scope(table);
            break;

        /* if-elseif — both conditions checked, both bodies analyzed as stmt lists */
        case NODE_IF_ELSEIF:
            analyze_expr(node->left, table);
            push_scope(table);
            analyze_stmts(node->right, table);
            pop_scope(table);

            analyze_expr(node->cond2, table);
            push_scope(table);
            analyze_stmts(node->extra, table);
            pop_scope(table);
            break;

        /* while — new scope for the body */
        case NODE_WHILE:
            analyze_expr(node->left, table);
            loop_depth++;
            push_scope(table);
            analyze_stmts(node->right, table);
            pop_scope(table);
            loop_depth--;
            break;

        default:
            break;
    }
}

static void analyze_stmts(ASTNode *node, SymbolTable *table) {
    if (!node) return;
    if (node->type == NODE_STMT_LIST) {
        analyze_stmt (node->left, table);
        analyze_stmts(node->next, table);
    } else {
        analyze_stmt(node, table);
    }
}

int analyze(ASTNode *root, SymbolTable *table) {
    if (!root) return 0;
    if (root->type == NODE_PROGRAM)
        analyze_stmts(root->left, table);
    return table->error_count;
}