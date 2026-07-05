%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "semantic.h"

extern int line_count;
int yylex();
void yyerror(const char *msg);

/* The root of our AST — main.c will use this */
ASTNode *ast_root = NULL;
%}

/* 
   Value types tokens can carry
 */
%union {
    int        int_val;
    double     float_val;
    char      *str_val;
    ASTNode   *node;
}

/* 
   Token declarations
 */
%token SCENEONHA SCENEOFFHA
%token LOWKEY WARNABRO PHIRBRO
%token CHALBRO GHOSTED MISSKARA
%token WAPAS SPILLTEA
%token NUMYESKARAO FLOATYESKARAO
%token NOCAP CAP BASYAR KAAMKARO YEHLO KITNALAMBA
%token ASSIGN EQ PLUS MINUS MULTIPLY DIVIDE MODULO
%token AND OR NOT
%token LT GT LTE GTE
%token TERMINATOR SEPARATOR COMMA
%token LPAREN RPAREN

%token <int_val>   INT_NUM
%token <float_val> FLOAT_NUM
%token <float_val> SCIENTIFIC_NUM
%token <str_val>   STRING_LIT
%token <str_val>   ID

/* 
   Operator precedence (lowest to highest)
 */
%left OR
%left AND
%right NOT
%left PLUS MINUS
%left MULTIPLY DIVIDE MODULO

/* 
   Rule return types
 */
%type <node> program
%type <node> stmt_list
%type <node> stmt
%type <node> decl_stmt
%type <node> assign_stmt
%type <node> cond_stmt
%type <node> loop_stmt
%type <node> output_stmt
%type <node> return_stmt
%type <node> break_stmt
%type <node> continue_stmt
%type <node> func_decl
%type <node> func_call
%type <node> param_list
%type <node> arg_list
%type <node> condition
%type <node> expr
%type <node> term

%%

/* 
   Program root
 */
program
    : SCENEONHA stmt_list SCENEOFFHA
        {
            ASTNode *n = make_node(NODE_PROGRAM);
            n->left    = $2;
            ast_root   = n;
            $$ = n;
        }
    ;

/* 
   Statement list
 */
stmt_list
    : stmt stmt_list
        {
            ASTNode *n = make_node(NODE_STMT_LIST);
            n->left    = $1;
            n->next    = $2;
            $$ = n;
        }
    | stmt
        {
            ASTNode *n = make_node(NODE_STMT_LIST);
            n->left    = $1;
            n->next    = NULL;
            $$ = n;
        }
    ;

/* 
   All statement types
 */
stmt
    : decl_stmt     { $$ = $1; }
    | assign_stmt   { $$ = $1; }
    | cond_stmt     { $$ = $1; }
    | loop_stmt     { $$ = $1; }
    | output_stmt   { $$ = $1; }
    | return_stmt   { $$ = $1; }
    | break_stmt    { $$ = $1; }
    | continue_stmt { $$ = $1; }
    | func_decl     { $$ = $1; }
    | func_call     { $$ = $1; }
    ;

/* 
   numYesKarao x <- expr !!
   floatYesKarao x <- expr !!
 */
decl_stmt
    : NUMYESKARAO ID ASSIGN expr TERMINATOR
        {
            ASTNode *n  = make_node(NODE_DECL);
            n->str_val  = strdup($2);
            n->left     = $4;
            $$ = n;
        }
    | FLOATYESKARAO ID ASSIGN expr TERMINATOR
        {
            ASTNode *n  = make_node(NODE_DECL);
            n->str_val  = strdup($2);
            n->left     = $4;
            $$ = n;
        }
    ;

/* 
   x <- expr !!
 */
assign_stmt
    : ID ASSIGN expr TERMINATOR
        {
            ASTNode *n  = make_node(NODE_ASSIGN);
            n->str_val  = strdup($1);
            n->left     = $3;
            $$ = n;
        }
    ;

/* 
   lowkey (cond) basYar stmt_list yehLo
   lowkey (cond) basYar stmt_list warnaBro basYar stmt_list yehLo
   lowkey (cond) basYar stmt_list phirBro (cond) basYar stmt_list yehLo
 */
cond_stmt
    : LOWKEY LPAREN condition RPAREN BASYAR stmt_list YEHLO
        {
            ASTNode *n  = make_node(NODE_IF);
            n->left     = $3;
            n->right    = $6;
            $$ = n;
        }
    | LOWKEY LPAREN condition RPAREN BASYAR stmt_list WARNABRO BASYAR stmt_list YEHLO
        {
            ASTNode *n  = make_node(NODE_IF_ELSE);
            n->left     = $3;
            n->right    = $6;
            n->extra    = $9;
            $$ = n;
        }
    | LOWKEY LPAREN condition RPAREN BASYAR stmt_list PHIRBRO LPAREN condition RPAREN BASYAR stmt_list YEHLO
        {
            ASTNode *n  = make_node(NODE_IF_ELSEIF);
            n->left     = $3;   /* first condition (lowkey) */
            n->right    = $6;   /* first body (lowkey's body) */
            n->cond2    = $9;   /* second condition (phirBro) */
            n->extra    = $12;  /* second body (phirBro's body) */
            $$ = n;
        }
    ;

/* 
   chalBro (cond) basYar stmt_list yehLo
 */
loop_stmt
    : CHALBRO LPAREN condition RPAREN BASYAR stmt_list YEHLO
        {
            ASTNode *n  = make_node(NODE_WHILE);
            n->left     = $3;
            n->right    = $6;
            $$ = n;
        }
    ;

/* 
   spillTea expr !!
 */
output_stmt
    : SPILLTEA expr TERMINATOR
        {
            ASTNode *n = make_node(NODE_PRINT);
            n->left    = $2;
            $$ = n;
        }
    ;

/* 
   wapas expr !!
 */
return_stmt
    : WAPAS expr TERMINATOR
        {
            ASTNode *n = make_node(NODE_RETURN);
            n->left    = $2;
            $$ = n;
        }
    ;

/* 
   ghosted !!
 */
break_stmt
    : GHOSTED TERMINATOR
        {
            $$ = make_node(NODE_BREAK);
        }
    ;

/* 
   missKara !!
 */
continue_stmt
    : MISSKARA TERMINATOR
        {
            $$ = make_node(NODE_CONTINUE);
        }
    ;

/* 
   kaamKaro funcName ::: param1, param2 ::: basYar body yehLo
   kaamKaro funcName ::: ::: basYar body yehLo   (no params)
 */
func_decl
    : KAAMKARO ID SEPARATOR param_list SEPARATOR BASYAR stmt_list YEHLO
        {
            $$ = make_func_decl($2, $4, $7);
        }
    | KAAMKARO ID SEPARATOR SEPARATOR BASYAR stmt_list YEHLO
        {
            $$ = make_func_decl($2, NULL, $6);
        }
    ;

/* 
   funcName ::: arg1, arg2 ::: !!
   funcName ::: ::: !!            (no args)
 */
func_call
    : ID SEPARATOR arg_list SEPARATOR TERMINATOR
        {
            $$ = make_func_call($1, $3);
        }
    | ID SEPARATOR SEPARATOR TERMINATOR
        {
            $$ = make_func_call($1, NULL);
        }
    ;

/*
   param_list: params separated by commas
*/
param_list
    : ID
        {
            $$ = make_param($1);
        }
    | param_list COMMA ID
        {
            ASTNode *p = make_param($3);
            $1->next   = p;
            $$ = $1;
        }
    ;

/*
   arg_list: args separated by commas
*/
arg_list
    : expr
        {
            $$ = make_arg($1);
        }
    | arg_list COMMA expr
        {
            ASTNode *a = make_arg($3);
            $1->next   = a;
            $$ = $1;
        }
    ;

/* 
   Conditions
   aurBhai = and   |   yaBhai = or   |   nahi = not
 */
condition
    : expr EQ  expr              { $$ = make_condition("==?",     $1, $3); }
    | expr LT  expr              { $$ = make_condition("<",        $1, $3); }
    | expr GT  expr              { $$ = make_condition(">",        $1, $3); }
    | expr LTE expr              { $$ = make_condition("<=",       $1, $3); }
    | expr GTE expr              { $$ = make_condition(">=",       $1, $3); }
    | condition AND condition    { $$ = make_condition("aurBhai",  $1, $3); }
    | condition OR  condition    { $$ = make_condition("yaBhai",   $1, $3); }
    | NOT condition              { $$ = make_condition("nahi",     $2, NULL); }
    ;

/* 
   Expressions
   ^+ = add   ^- = subtract   ^* = multiply   ^/ = divide   ^% = modulo
 */
expr
    : expr PLUS     term { $$ = make_binop("^+", $1, $3); }
    | expr MINUS    term { $$ = make_binop("^-", $1, $3); }
    | expr MULTIPLY term { $$ = make_binop("^*", $1, $3); }
    | expr DIVIDE   term { $$ = make_binop("^/", $1, $3); }
    | expr MODULO   term { $$ = make_binop("^%", $1, $3); }
    | term               { $$ = $1;                        }
    ;

/* 
   Terms — includes gintiBata for string length
 */
term
    : INT_NUM        { $$ = make_int($1);    }
    | FLOAT_NUM      { $$ = make_float($1);  }
    | SCIENTIFIC_NUM { $$ = make_float($1);  }
    | STRING_LIT     { $$ = make_string($1); }
    | NOCAP          { $$ = make_bool(1);    }
    | CAP            { $$ = make_bool(0);    }
    | ID             { $$ = make_ident($1);  }
    | KITNALAMBA ID
        {
            ASTNode *n = make_node(NODE_STR_LEN);
            n->str_val = strdup($2);
            $$ = n;
        }
    ;

%%

/* 
   Error handler
 */
void yyerror(const char *msg) {
    fprintf(stderr,
        "Syntax Error [line %d]: %s (near '%s')\n",
        line_count, msg, "?");
}