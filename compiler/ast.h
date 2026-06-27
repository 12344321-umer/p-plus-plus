#ifndef AST_H
#define AST_H

/* 
   All the node types our AST can have
 */
typedef enum {
    NODE_PROGRAM,        // root: sceneOnHa ... sceneOffHa
    NODE_STMT_LIST,      // list of statements
    NODE_DECL,           // numYesKarao x <- 5 !!
    NODE_ASSIGN,         // x <- expr !!
    NODE_IF,             // lowkey (cond) basYar ...
    NODE_IF_ELSE,        // lowkey ... warnaBro ...
    NODE_IF_ELSEIF,      // lowkey ... phirBro ...
    NODE_WHILE,          // chalBro (cond) basYar ...
    NODE_PRINT,          // spillTea expr !!
    NODE_RETURN,         // wapas expr !!
    NODE_BREAK,          // ghosted !!
    NODE_CONTINUE,       // missKara !!
    NODE_BINOP,          // expr ^+ expr
    NODE_CONDITION,      // expr ==? expr  /  expr < expr  etc.
    NODE_INT_LIT,        // 42
    NODE_FLOAT_LIT,      // 3.14
    NODE_STRING_LIT,     // "hello"
    NODE_BOOL_LIT,       // noCap / cap
    NODE_IDENTIFIER,     // variable name
} NodeType;


/* 
   A single node in the tree
 */
typedef struct ASTNode {
    NodeType type;

    /* Literal values (only one is used per node) */
    int     int_val;
    double  float_val;
    char   *str_val;     // string literals AND identifier names AND operators

    /* Children */
    struct ASTNode *left;    // left child  (condition, expr, etc.)
    struct ASTNode *right;   // right child
    struct ASTNode *extra;   // third child (for if-elseif / if-else chains)
    struct ASTNode *next;    // next sibling in a statement list

} ASTNode;


/* 
   Constructor helpers  (defined in ast.c)
 */
ASTNode *make_node      (NodeType type);
ASTNode *make_int       (int val);
ASTNode *make_float     (double val);
ASTNode *make_string    (const char *val);
ASTNode *make_bool      (int val);          // 1 = noCap, 0 = cap
ASTNode *make_ident     (const char *name);
ASTNode *make_binop     (const char *op, ASTNode *left, ASTNode *right);
ASTNode *make_condition (const char *op, ASTNode *left, ASTNode *right);

/* 
   Utility  (defined in ast.c)
 */
void print_ast  (ASTNode *node, int depth);   // pretty-print the tree
void free_ast   (ASTNode *node);              // free all memory

#endif 
