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
    node->next      = NULL;
    return node;
}

/* 
Constructors
 */
ASTNode *make_int(int val) {
    ASTNode *n  = make_node(NODE_INT_LIT);
    n->int_val  = val;
    return n;
}

ASTNode *make_float(double val) {
    ASTNode *n   = make_node(NODE_FLOAT_LIT);
    n->float_val = val;
    return n;
}

ASTNode *make_string(const char *val) {
    ASTNode *n  = make_node(NODE_STRING_LIT);
    n->str_val  = strdup(val);
    return n;
}

ASTNode *make_bool(int val) {
    ASTNode *n  = make_node(NODE_BOOL_LIT);
    n->int_val  = val;   // 1 = noCap (true), 0 = cap (false)
    return n;
}

ASTNode *make_ident(const char *name) {
    ASTNode *n  = make_node(NODE_IDENTIFIER);
    n->str_val  = strdup(name);
    return n;
}

ASTNode *make_binop(const char *op, ASTNode *left, ASTNode *right) {
    ASTNode *n  = make_node(NODE_BINOP);
    n->str_val  = strdup(op);
    n->left     = left;
    n->right    = right;
    return n;
}

ASTNode *make_condition(const char *op, ASTNode *left, ASTNode *right) {
    ASTNode *n  = make_node(NODE_CONDITION);
    n->str_val  = strdup(op);
    n->left     = left;
    n->right    = right;
    return n;
}

/* 
   Pretty-print the AST
   depth controls the indentation level
 */
void print_ast(ASTNode *node, int depth) {
    if (!node) return;

    /* indent */
    for (int i = 0; i < depth; i++) printf("  ");

    switch (node->type) {
        case NODE_PROGRAM:
            printf("Program\n");
            print_ast(node->left, depth + 1);   // stmt_list
            break;

        case NODE_STMT_LIST:
            print_ast(node->left, depth);        // first stmt
            print_ast(node->next, depth);        // rest of list
            break;

        case NODE_DECL:
            printf("VarDecl [%s]\n", node->str_val);
            print_ast(node->left, depth + 1);   // initial value expr
            break;

        case NODE_ASSIGN:
            printf("Assign [%s]\n", node->str_val);
            print_ast(node->left, depth + 1);   // expr
            break;

        case NODE_IF:
            printf("If\n");
            for (int i = 0; i < depth + 1; i++) printf("  ");
            printf("Condition:\n");
            print_ast(node->left,  depth + 2);  // condition
            for (int i = 0; i < depth + 1; i++) printf("  ");
            printf("Body:\n");
            print_ast(node->right, depth + 2);  // body
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
            printf("ElseIf:\n");
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

        case NODE_BREAK:
            printf("Break\n");
            break;

        case NODE_CONTINUE:
            printf("Continue\n");
            break;

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

        case NODE_INT_LIT:
            printf("Int [%d]\n", node->int_val);
            break;

        case NODE_FLOAT_LIT:
            printf("Float [%g]\n", node->float_val);
            break;

        case NODE_STRING_LIT:
            printf("String [%s]\n", node->str_val);
            break;

        case NODE_BOOL_LIT:
            printf("Bool [%s]\n", node->int_val ? "noCap" : "cap");
            break;

        case NODE_IDENTIFIER:
            printf("Identifier [%s]\n", node->str_val);
            break;

        default:
            printf("Unknown node\n");
    }

    /* sibling traversal for stmt lists */
    if (node->type != NODE_STMT_LIST)
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
    free_ast(node->next);

    if (node->str_val) free(node->str_val);
    free(node);
} 
