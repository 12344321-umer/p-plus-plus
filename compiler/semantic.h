#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"

/* 
   Variable types
 */
typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_BOOL,
    TYPE_UNKNOWN
} VarType;


/* 
   A single variable entry
 */
typedef struct Symbol {
    char          *name;
    VarType        type;
    int            line;
    struct Symbol *next;
} Symbol;


/* 
   A single scope — one per block (if body, while body, function, etc.)
 */
typedef struct Scope {
    Symbol      *head;      // variables declared in this scope
    struct Scope *parent;   // the scope above this one
} Scope;


/* 
   The symbol table is now a scope stack
 */
typedef struct {
    Scope *current;         // the innermost active scope
    int    error_count;
} SymbolTable;


/* 
   Public API
 */
SymbolTable *create_symbol_table  ();
void         destroy_symbol_table (SymbolTable *table);

/* Scope management */
void    push_scope (SymbolTable *table);
void    pop_scope  (SymbolTable *table);

/* Symbol operations */
int     declare_symbol (SymbolTable *table, const char *name, VarType type, int line);
Symbol *lookup_symbol  (SymbolTable *table, const char *name);

/* Analysis entry point */
int  analyze            (ASTNode *root, SymbolTable *table);
void print_symbol_table (SymbolTable *table);

/* Collect all symbols across all scopes for JSON output */
Symbol *collect_all_symbols (SymbolTable *table);

#endif