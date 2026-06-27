 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"

/* 
   Create a fresh symbol table
 */
SymbolTable *create_symbol_table() {
    SymbolTable *table = (SymbolTable *)malloc(sizeof(SymbolTable));
    if (!table) {
        fprintf(stderr, "Error: out of memory\n");
        exit(1);
    }
    table->head        = NULL;
    table->error_count = 0;
    return table;
}


/* 
   Free all memory used by the symbol table
 */
void destroy_symbol_table(SymbolTable *table) {
    if (!table) return;
    Symbol *cur = table->head;
    while (cur) {
        Symbol *next = cur->next;
        if (cur->name) free(cur->name);
        free(cur);
        cur = next;
    }
    free(table);
}


/* 
   Add a new variable to the symbol table
   Returns 0 on success, -1 if duplicate
 */
int declare_symbol(SymbolTable *table, const char *name, VarType type, int line) {
    /* Check for duplicate */
    if (lookup_symbol(table, name)) {
        fprintf(stderr, "Semantic Error [line %d]: '%s' already declared\n", line, name);
        table->error_count++;
        return -1;
    }

    Symbol *sym  = (Symbol *)malloc(sizeof(Symbol));
    sym->name    = strdup(name);
    sym->type    = type;
    sym->line    = line;
    sym->next    = table->head;   // prepend to list
    table->head  = sym;
    return 0;
}


/* 
   Look up a variable by name
   Returns the Symbol or NULL if not found
 */
Symbol *lookup_symbol(SymbolTable *table, const char *name) {
    Symbol *cur = table->head;
    while (cur) {
        if (strcmp(cur->name, name) == 0) return cur;
        cur = cur->next;
    }
    return NULL;
}


/* 
   Print the full symbol table
 */
void print_symbol_table(SymbolTable *table) {
    printf("\n========== Symbol Table ==========\n");
    printf("%-15s %-10s %-5s\n", "Name", "Type", "Line");
    printf("----------------------------------\n");
    Symbol *cur = table->head;
    while (cur) {
        const char *type_str;
        switch (cur->type) {
            case TYPE_INT:     type_str = "int";     break;
            case TYPE_FLOAT:   type_str = "float";   break;
            case TYPE_STRING:  type_str = "string";  break;
            case TYPE_BOOL:    type_str = "bool";    break;
            default:           type_str = "unknown"; break;
        }
        printf("%-15s %-10s %-5d\n", cur->name, type_str, cur->line);
        cur = cur->next;
    }
    printf("==================================\n\n");
}


/* 
   Internal: track whether we are inside
   a loop (for break/continue validation)
 */
static int loop_depth = 0;


/* 
   Internal: analyze a single expression
   node and check all identifiers in it
 */
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
            analyze_expr(node->left,  table);
            analyze_expr(node->right, table);
            break;

        case NODE_CONDITION:
            analyze_expr(node->left,  table);
            analyze_expr(node->right, table);
            break;

        /* literals are always fine */
        case NODE_INT_LIT:
        case NODE_FLOAT_LIT:
        case NODE_STRING_LIT:
        case NODE_BOOL_LIT:
            break;

        default:
            break;
    }
}


/* 
   Internal: analyze a statement list
 */
static void analyze_stmts(ASTNode *node, SymbolTable *table);

static void analyze_stmt(ASTNode *node, SymbolTable *table) {
    if (!node) return;

    switch (node->type) {

        /* numYesKarao x <- expr !! */
        case NODE_DECL: {
            VarType t = TYPE_UNKNOWN;
            if (node->left) {
                if      (node->left->type == NODE_INT_LIT)    t = TYPE_INT;
                else if (node->left->type == NODE_FLOAT_LIT)  t = TYPE_FLOAT;
                else if (node->left->type == NODE_STRING_LIT) t = TYPE_STRING;
                else if (node->left->type == NODE_BOOL_LIT)   t = TYPE_BOOL;
                else if (node->left->type == NODE_IDENTIFIER) {
                    /* type inferred from rhs identifier */
                    Symbol *s = lookup_symbol(table, node->left->str_val);
                    if (s) t = s->type;
                }
            }
            declare_symbol(table, node->str_val, t, 0);
            analyze_expr(node->left, table);
            break;
        }

        /* x <- expr !! */
        case NODE_ASSIGN:
            if (!lookup_symbol(table, node->str_val)) {
                fprintf(stderr,
                    "Semantic Error: assignment to undeclared variable '%s'\n",
                    node->str_val);
                table->error_count++;
            }
            analyze_expr(node->left, table);
            break;

        /* spillTea expr !! */
        case NODE_PRINT:
            analyze_expr(node->left, table);
            break;

        /* wapas expr !! */
        case NODE_RETURN:
            analyze_expr(node->left, table);
            break;

        /* ghosted !! */
        case NODE_BREAK:
            if (loop_depth == 0) {
                fprintf(stderr,
                    "Semantic Error: 'ghosted' (break) used outside of a loop\n");
                table->error_count++;
            }
            break;

        /* missKara !! */
        case NODE_CONTINUE:
            if (loop_depth == 0) {
                fprintf(stderr,
                    "Semantic Error: 'missKara' (continue) used outside of a loop\n");
                table->error_count++;
            }
            break;

        /* lowkey (cond) basYar stmts */
        case NODE_IF:
            analyze_expr (node->left,  table);   // condition
            analyze_stmts(node->right, table);   // body
            break;

        /* lowkey ... warnaBro ... */
        case NODE_IF_ELSE:
            analyze_expr (node->left,  table);
            analyze_stmts(node->right, table);   // then branch
            analyze_stmts(node->extra, table);   // else branch
            break;

        /* lowkey ... phirBro ... */
        case NODE_IF_ELSEIF:
            analyze_expr (node->left,  table);
            analyze_stmts(node->right, table);   // then branch
            analyze_stmt (node->extra, table);   // elseif chain
            break;

        /* chalBro (cond) basYar stmts */
        case NODE_WHILE:
            analyze_expr(node->left, table);     // condition
            loop_depth++;
            analyze_stmts(node->right, table);   // body
            loop_depth--;
            break;

        default:
            break;
    }
}


/* 
   Walk a statement list node
 */
static void analyze_stmts(ASTNode *node, SymbolTable *table) {
    if (!node) return;

    if (node->type == NODE_STMT_LIST) {
        analyze_stmt (node->left, table);   // current statement
        analyze_stmts(node->next, table);   // rest of list
    } else {
        analyze_stmt(node, table);
    }
}


/* 
   Public entry point
 */
int analyze(ASTNode *root, SymbolTable *table) {
    if (!root) return 0;

    /* root should be NODE_PROGRAM */
    if (root->type == NODE_PROGRAM) {
        analyze_stmts(root->left, table);
    }

    return table->error_count;
}
