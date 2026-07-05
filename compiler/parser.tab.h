/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SCENEONHA = 258,               /* SCENEONHA  */
    SCENEOFFHA = 259,              /* SCENEOFFHA  */
    LOWKEY = 260,                  /* LOWKEY  */
    WARNABRO = 261,                /* WARNABRO  */
    PHIRBRO = 262,                 /* PHIRBRO  */
    CHALBRO = 263,                 /* CHALBRO  */
    GHOSTED = 264,                 /* GHOSTED  */
    MISSKARA = 265,                /* MISSKARA  */
    WAPAS = 266,                   /* WAPAS  */
    SPILLTEA = 267,                /* SPILLTEA  */
    NUMYESKARAO = 268,             /* NUMYESKARAO  */
    FLOATYESKARAO = 269,           /* FLOATYESKARAO  */
    NOCAP = 270,                   /* NOCAP  */
    CAP = 271,                     /* CAP  */
    BASYAR = 272,                  /* BASYAR  */
    KAAMKARO = 273,                /* KAAMKARO  */
    YEHLO = 274,                   /* YEHLO  */
    KITNALAMBA = 275,              /* KITNALAMBA  */
    ASSIGN = 276,                  /* ASSIGN  */
    EQ = 277,                      /* EQ  */
    PLUS = 278,                    /* PLUS  */
    MINUS = 279,                   /* MINUS  */
    MULTIPLY = 280,                /* MULTIPLY  */
    DIVIDE = 281,                  /* DIVIDE  */
    MODULO = 282,                  /* MODULO  */
    AND = 283,                     /* AND  */
    OR = 284,                      /* OR  */
    NOT = 285,                     /* NOT  */
    LT = 286,                      /* LT  */
    GT = 287,                      /* GT  */
    LTE = 288,                     /* LTE  */
    GTE = 289,                     /* GTE  */
    TERMINATOR = 290,              /* TERMINATOR  */
    SEPARATOR = 291,               /* SEPARATOR  */
    COMMA = 292,                   /* COMMA  */
    LPAREN = 293,                  /* LPAREN  */
    RPAREN = 294,                  /* RPAREN  */
    INT_NUM = 295,                 /* INT_NUM  */
    FLOAT_NUM = 296,               /* FLOAT_NUM  */
    SCIENTIFIC_NUM = 297,          /* SCIENTIFIC_NUM  */
    STRING_LIT = 298,              /* STRING_LIT  */
    ID = 299                       /* ID  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 19 "parser.y"

    int        int_val;
    double     float_val;
    char      *str_val;
    ASTNode   *node;

#line 115 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
