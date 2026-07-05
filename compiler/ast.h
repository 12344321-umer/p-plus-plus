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
    NODE_FUNC_DECL,      // kaamKaro funcName ::: params ::: basYar body yehLo
    NODE_FUNC_CALL,      // funcName ::: args ::: !!
    NODE_PARAM_LIST,     // linked list of parameter names
    NODE_ARG_LIST,       // linked list of argument expressions
    NODE_STR_LEN,        // gintiBata varName
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
    struct ASTNode *left;    // left child  (condition, expr, params, etc.)
    struct ASTNode *right;   // right child (body, args, etc.)
    struct ASTNode *extra;   // third child (for if-elseif / if-else chains)
    struct ASTNode *cond2;   // second condition (phirBro's own condition, for if-elseif)
    struct ASTNode *next;    // next sibling in a list

} ASTNode;


/* 
   Constructor helpers  (defined in ast.c)
 */
ASTNode *make_node      (NodeType type);
ASTNode *make_int       (int val);
ASTNode *make_float     (double val);
ASTNode *make_string    (const char *val);
ASTNode *make_bool      (int val);
ASTNode *make_ident     (const char *name);
ASTNode *make_binop     (const char *op, ASTNode *left, ASTNode *right);
ASTNode *make_condition (const char *op, ASTNode *left, ASTNode *right);
ASTNode *make_func_decl (const char *name, ASTNode *params, ASTNode *body);
ASTNode *make_func_call (const char *name, ASTNode *args);
ASTNode *make_param     (const char *name);
ASTNode *make_arg       (ASTNode *expr);

/* 
   Utility  (defined in ast.c)
 */
void print_ast  (ASTNode *node, int depth);
void free_ast   (ASTNode *node);

#endif