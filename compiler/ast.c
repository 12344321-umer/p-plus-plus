#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

/* 
   Internal helper: allocate a blank node
 */
ASTNode *make_node(NodeType type) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Error: out of memory\n");
        exit(1);
    }
    node->type      = type;
    node->int_val   = 0;
    node->float_val = 0.0;
    node->str_val   = NULL;
    node->left      = NULL;
    node->right     = NULL;
    node->extra     = NULL;
    node->cond2     = NULL;
    node->next      = NULL;
    return node;
}

/* 
   Existing constructors
 */
ASTNode *make_int(int val) {
    ASTNode *n = make_node(NODE_INT_LIT);
    n->int_val = val;
    return n;
}

ASTNode *make_float(double val) {
    ASTNode *n   = make_node(NODE_FLOAT_LIT);
    n->float_val = val;
    return n;
}

ASTNode *make_string(const char *val) {
    ASTNode *n = make_node(NODE_STRING_LIT);
    n->str_val = strdup(val);
    return n;
}

ASTNode *make_bool(int val) {
    ASTNode *n = make_node(NODE_BOOL_LIT);
    n->int_val = val;
    return n;
}

ASTNode *make_ident(const char *name) {
    ASTNode *n = make_node(NODE_IDENTIFIER);
    n->str_val = strdup(name);
    return n;
}

ASTNode *make_binop(const char *op, ASTNode *left, ASTNode *right) {
    ASTNode *n = make_node(NODE_BINOP);
    n->str_val = strdup(op);
    n->left    = left;
    n->right   = right;
    return n;
}

ASTNode *make_condition(const char *op, ASTNode *left, ASTNode *right) {
    ASTNode *n = make_node(NODE_CONDITION);
    n->str_val = strdup(op);
    n->left    = left;
    n->right   = right;
    return n;
}

/* 
   New constructors for functions
 */

/*
   kaamKaro funcName ::: param1 ::: basYar body
   str_val = function name
   left    = param list (linked via next)
   right   = body (stmt_list)
*/
ASTNode *make_func_decl(const char *name, ASTNode *params, ASTNode *body) {
    ASTNode *n = make_node(NODE_FUNC_DECL);
    n->str_val = strdup(name);
    n->left    = params;
    n->right   = body;
    return n;
}

/*
   funcName ::: arg1 ::: !!
   str_val = function name
   left    = arg list (linked via next)
*/
ASTNode *make_func_call(const char *name, ASTNode *args) {
    ASTNode *n = make_node(NODE_FUNC_CALL);
    n->str_val = strdup(name);
    n->left    = args;
    return n;
}

/*
   A single parameter — just stores its name
   str_val = param name
   next    = next param
*/
ASTNode *make_param(const char *name) {
    ASTNode *n = make_node(NODE_PARAM_LIST);
    n->str_val = strdup(name);
    return n;
}

/*
   A single argument — stores the expression
   left = the expression
   next = next argument
*/
ASTNode *make_arg(ASTNode *expr) {
    ASTNode *n = make_node(NODE_ARG_LIST);
    n->left    = expr;
    return n;
}


/* 
   Pretty-print the AST
 */
void print_ast(ASTNode *node, int depth) {
    if (!node) return;

    for (int i = 0; i < depth; i++) printf("  ");

    switch (node->type) {
        case NODE_PROGRAM:
            printf("Program\n");
            print_ast(node->left, depth + 1);
            break;

        case NODE_STMT_LIST:
            print_ast(node->left, depth);
            print_ast(node->next, depth);
            break;

        case NODE_DECL:
            printf("VarDecl [%s]\n", node->str_val);
            print_ast(node->left, depth + 1);
            break;

        case NODE_ASSIGN:
            printf("Assign [%s]\n", node->str_val);
            print_ast(node->left, depth + 1);
            break;

        case NODE_IF:
            printf("If\n");
            for (int i = 0; i < depth + 1; i++) printf("  ");
            printf("Condition:\n");
            print_ast(node->left,  depth + 2);
            for (int i = 0; i < depth + 1; i++) printf("  ");
            printf("Body:\n");
            print_ast(node->right, depth + 2);
            break;

        case NODE_IF_ELSE:
            printf("IfElse\n");
            for (int i = 0; i < depth + 1; i++) printf("  ");
            printf("Condition:\n");
            print_ast(node->left,  depth + 2);
            for (int i = 0; i < depth + 1; i++) printf("  ");
            printf("Then:\n");
            print_ast(node->right, depth + 2);
            for (int i = 0; i < depth + 1; i++) printf("  ");
            printf("Else:\n");
            print_ast(node->extra, depth + 2);
            break;

        case NODE_IF_ELSEIF:
            printf("IfElseIf\n");
            for (int i = 0; i < depth + 1; i++) printf("  ");
            printf("Condition:\n");
            print_ast(node->left,  depth + 2);
            for (int i = 0; i < depth + 1; i++) printf("  ");
            printf("Then:\n");
            print_ast(node->right, depth + 2);
            for (int i = 0; i < depth + 1; i++) printf("  ");
            printf("ElseIfCondition:\n");
            print_ast(node->cond2, depth + 2);
            for (int i = 0; i < depth + 1; i++) printf("  ");
            printf("ElseIfBody:\n");
            print_ast(node->extra, depth + 2);
            break;

        case NODE_WHILE:
            printf("WhileLoop\n");
            for (int i = 0; i < depth + 1; i++) printf("  ");
            printf("Condition:\n");
            print_ast(node->left,  depth + 2);
            for (int i = 0; i < depth + 1; i++) printf("  ");
            printf("Body:\n");
            print_ast(node->right, depth + 2);
            break;

        case NODE_PRINT:
            printf("Print\n");
            print_ast(node->left, depth + 1);
            break;

        case NODE_RETURN:
            printf("Return\n");
            print_ast(node->left, depth + 1);
            break;

        case NODE_BREAK:    printf("Break\n");    break;
        case NODE_CONTINUE: printf("Continue\n"); break;

        case NODE_BINOP:
            printf("BinOp [%s]\n", node->str_val);
            print_ast(node->left,  depth + 1);
            print_ast(node->right, depth + 1);
            break;

        case NODE_CONDITION:
            printf("Condition [%s]\n", node->str_val);
            print_ast(node->left,  depth + 1);
            print_ast(node->right, depth + 1);
            break;

        case NODE_INT_LIT:    printf("Int [%d]\n",    node->int_val);  break;
        case NODE_FLOAT_LIT:  printf("Float [%g]\n",  node->float_val); break;
        case NODE_STRING_LIT: printf("String [%s]\n", node->str_val);  break;
        case NODE_BOOL_LIT:   printf("Bool [%s]\n",   node->int_val ? "noCap" : "cap"); break;
        case NODE_IDENTIFIER: printf("Identifier [%s]\n", node->str_val); break;

        /* function declaration */
        case NODE_FUNC_DECL:
            printf("FuncDecl [%s]\n", node->str_val);
            for (int i = 0; i < depth + 1; i++) printf("  ");
            printf("Params:\n");
            print_ast(node->left,  depth + 2);
            for (int i = 0; i < depth + 1; i++) printf("  ");
            printf("Body:\n");
            print_ast(node->right, depth + 2);
            break;

        /* function call */
        case NODE_FUNC_CALL:
            printf("FuncCall [%s]\n", node->str_val);
            for (int i = 0; i < depth + 1; i++) printf("  ");
            printf("Args:\n");
            print_ast(node->left, depth + 2);
            break;

        /* param list node */
        case NODE_PARAM_LIST:
            printf("Param [%s]\n", node->str_val);
            print_ast(node->next, depth);
            break;

        /* arg list node */
        case NODE_ARG_LIST:
            print_ast(node->left, depth);
            print_ast(node->next, depth);
            break;

        default:
            printf("Unknown node\n");
    }

    if (node->type != NODE_STMT_LIST &&
        node->type != NODE_PARAM_LIST &&
        node->type != NODE_ARG_LIST)
        print_ast(node->next, depth);
}

/* 
   Free all memory used by the tree
 */
void free_ast(ASTNode *node) {
    if (!node) return;
    free_ast(node->left);
    free_ast(node->right);
    free_ast(node->extra);
    free_ast(node->cond2);
    free_ast(node->next);
    if (node->str_val) free(node->str_val);
    free(node);
}