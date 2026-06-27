 #ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"

/* 
   Variable types we support in P++
 */
typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_BOOL,
    TYPE_UNKNOWN
} VarType;


/* 
   A single entry in the symbol table
   (one row per declared variable)
 */
typedef struct Symbol {
    char        *name;      // variable name
    VarType      type;      // its type
    int          line;      // line it was declared on
    struct Symbol *next;    // next entry (linked list)
} Symbol;


/* 
   The symbol table itself
 */
typedef struct {
    Symbol *head;           // first symbol in the list
    int     error_count;    // how many semantic errors found
} SymbolTable;


/* 
   Public API  (defined in semantic.c)
 */

// Create and destroy
SymbolTable *create_symbol_table  ();
void         destroy_symbol_table (SymbolTable *table);

// Symbol operations
int     declare_symbol  (SymbolTable *table, const char *name, VarType type, int line);
Symbol *lookup_symbol   (SymbolTable *table, const char *name);

// Run full semantic analysis on the AST
// Returns number of errors found (0 = clean)
int analyze (ASTNode *root, SymbolTable *table);

// Print the symbol table (for debugging / playground output)
void print_symbol_table (SymbolTable *table);

#endif
