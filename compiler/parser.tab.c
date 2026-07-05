/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

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

#line 86 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SCENEONHA = 3,                  /* SCENEONHA  */
  YYSYMBOL_SCENEOFFHA = 4,                 /* SCENEOFFHA  */
  YYSYMBOL_LOWKEY = 5,                     /* LOWKEY  */
  YYSYMBOL_WARNABRO = 6,                   /* WARNABRO  */
  YYSYMBOL_PHIRBRO = 7,                    /* PHIRBRO  */
  YYSYMBOL_CHALBRO = 8,                    /* CHALBRO  */
  YYSYMBOL_GHOSTED = 9,                    /* GHOSTED  */
  YYSYMBOL_MISSKARA = 10,                  /* MISSKARA  */
  YYSYMBOL_WAPAS = 11,                     /* WAPAS  */
  YYSYMBOL_SPILLTEA = 12,                  /* SPILLTEA  */
  YYSYMBOL_NUMYESKARAO = 13,               /* NUMYESKARAO  */
  YYSYMBOL_FLOATYESKARAO = 14,             /* FLOATYESKARAO  */
  YYSYMBOL_NOCAP = 15,                     /* NOCAP  */
  YYSYMBOL_CAP = 16,                       /* CAP  */
  YYSYMBOL_BASYAR = 17,                    /* BASYAR  */
  YYSYMBOL_KAAMKARO = 18,                  /* KAAMKARO  */
  YYSYMBOL_YEHLO = 19,                     /* YEHLO  */
  YYSYMBOL_KITNALAMBA = 20,                /* KITNALAMBA  */
  YYSYMBOL_ASSIGN = 21,                    /* ASSIGN  */
  YYSYMBOL_EQ = 22,                        /* EQ  */
  YYSYMBOL_PLUS = 23,                      /* PLUS  */
  YYSYMBOL_MINUS = 24,                     /* MINUS  */
  YYSYMBOL_MULTIPLY = 25,                  /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 26,                    /* DIVIDE  */
  YYSYMBOL_MODULO = 27,                    /* MODULO  */
  YYSYMBOL_AND = 28,                       /* AND  */
  YYSYMBOL_OR = 29,                        /* OR  */
  YYSYMBOL_NOT = 30,                       /* NOT  */
  YYSYMBOL_LT = 31,                        /* LT  */
  YYSYMBOL_GT = 32,                        /* GT  */
  YYSYMBOL_LTE = 33,                       /* LTE  */
  YYSYMBOL_GTE = 34,                       /* GTE  */
  YYSYMBOL_TERMINATOR = 35,                /* TERMINATOR  */
  YYSYMBOL_SEPARATOR = 36,                 /* SEPARATOR  */
  YYSYMBOL_COMMA = 37,                     /* COMMA  */
  YYSYMBOL_LPAREN = 38,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 39,                    /* RPAREN  */
  YYSYMBOL_INT_NUM = 40,                   /* INT_NUM  */
  YYSYMBOL_FLOAT_NUM = 41,                 /* FLOAT_NUM  */
  YYSYMBOL_SCIENTIFIC_NUM = 42,            /* SCIENTIFIC_NUM  */
  YYSYMBOL_STRING_LIT = 43,                /* STRING_LIT  */
  YYSYMBOL_ID = 44,                        /* ID  */
  YYSYMBOL_YYACCEPT = 45,                  /* $accept  */
  YYSYMBOL_program = 46,                   /* program  */
  YYSYMBOL_stmt_list = 47,                 /* stmt_list  */
  YYSYMBOL_stmt = 48,                      /* stmt  */
  YYSYMBOL_decl_stmt = 49,                 /* decl_stmt  */
  YYSYMBOL_assign_stmt = 50,               /* assign_stmt  */
  YYSYMBOL_cond_stmt = 51,                 /* cond_stmt  */
  YYSYMBOL_loop_stmt = 52,                 /* loop_stmt  */
  YYSYMBOL_output_stmt = 53,               /* output_stmt  */
  YYSYMBOL_return_stmt = 54,               /* return_stmt  */
  YYSYMBOL_break_stmt = 55,                /* break_stmt  */
  YYSYMBOL_continue_stmt = 56,             /* continue_stmt  */
  YYSYMBOL_func_decl = 57,                 /* func_decl  */
  YYSYMBOL_func_call = 58,                 /* func_call  */
  YYSYMBOL_param_list = 59,                /* param_list  */
  YYSYMBOL_arg_list = 60,                  /* arg_list  */
  YYSYMBOL_condition = 61,                 /* condition  */
  YYSYMBOL_expr = 62,                      /* expr  */
  YYSYMBOL_term = 63                       /* term  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  25
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   166

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  55
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  128

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   299


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    84,    84,    97,   104,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   134,   141,   154,   169,   176,
     184,   199,   212,   224,   236,   246,   257,   261,   272,   276,
     286,   290,   302,   306,   319,   320,   321,   322,   323,   324,
     325,   326,   334,   335,   336,   337,   338,   339,   346,   347,
     348,   349,   350,   351,   352,   353
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SCENEONHA",
  "SCENEOFFHA", "LOWKEY", "WARNABRO", "PHIRBRO", "CHALBRO", "GHOSTED",
  "MISSKARA", "WAPAS", "SPILLTEA", "NUMYESKARAO", "FLOATYESKARAO", "NOCAP",
  "CAP", "BASYAR", "KAAMKARO", "YEHLO", "KITNALAMBA", "ASSIGN", "EQ",
  "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "MODULO", "AND", "OR", "NOT",
  "LT", "GT", "LTE", "GTE", "TERMINATOR", "SEPARATOR", "COMMA", "LPAREN",
  "RPAREN", "INT_NUM", "FLOAT_NUM", "SCIENTIFIC_NUM", "STRING_LIT", "ID",
  "$accept", "program", "stmt_list", "stmt", "decl_stmt", "assign_stmt",
  "cond_stmt", "loop_stmt", "output_stmt", "return_stmt", "break_stmt",
  "continue_stmt", "func_decl", "func_call", "param_list", "arg_list",
  "condition", "expr", "term", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-31)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      16,     0,    32,     1,    12,   -11,    20,    57,    57,    -8,
       7,    22,   -19,    70,     0,   -31,   -31,   -31,   -31,   -31,
     -31,   -31,   -31,   -31,   -31,   -31,     5,     5,   -31,   -31,
     -31,   -31,    34,   -31,   -31,   -31,   -31,   -31,    95,   -31,
     100,    55,    66,    53,    57,    18,   -31,   -31,     5,    -2,
      83,    24,   -31,    57,    57,    57,    57,    57,   -31,   -31,
      57,    57,   -13,   113,    56,   -30,   136,   -31,     5,     5,
      73,    57,    57,    57,    57,    57,    75,   -31,   -31,   -31,
     -31,   -31,   118,   131,    77,   -31,    -7,   -31,   -31,    60,
      57,   -31,    74,     0,   136,   136,   136,   136,   136,     0,
     -31,   -31,     0,    86,    68,   -31,   136,     9,    94,   109,
       0,   -31,   112,    93,   -31,   -31,   -31,   114,     0,     5,
     -31,   115,    36,   -31,   129,     0,   128,   -31
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,     1,     0,     0,    24,    25,
      52,    53,     0,    48,    49,    50,    51,    54,     0,    47,
       0,     0,     0,     0,     0,     0,     2,     3,     0,     0,
       0,     0,    55,     0,     0,     0,     0,     0,    23,    22,
       0,     0,     0,     0,     0,     0,    32,    41,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    42,    43,    44,
      45,    46,     0,     0,     0,    30,     0,    17,    29,     0,
       0,    39,    40,     0,    34,    35,    36,    37,    38,     0,
      15,    16,     0,     0,     0,    28,    33,     0,     0,     0,
       0,    31,     0,     0,    18,    21,    27,     0,     0,     0,
      26,     0,     0,    19,     0,     0,     0,    20
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -31,   -31,   -14,   -31,   -31,   -31,   -31,   -31,   -31,   -31,
     -31,   -31,   -31,   -31,   -31,   -31,   -26,    -4,    27
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    86,    65,    49,    50,    39
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      47,    51,    44,    38,    40,     3,    89,    90,     4,     5,
       6,     7,     8,     9,    10,   112,   113,    45,    11,     1,
      30,    31,    67,    84,    28,    32,    68,    69,   114,   103,
     104,    85,    25,    30,    31,    48,    41,    70,    32,    26,
      63,    66,    91,    92,    12,    33,    34,    35,    36,    37,
      27,    42,    68,    69,    64,    29,    82,    83,    33,    34,
      35,    36,    37,    76,    68,    69,    43,    94,    95,    96,
      97,    98,    30,    31,    46,   124,    60,    32,    52,   107,
      77,    78,    79,    80,    81,   108,   106,    61,   109,    62,
      93,    88,    99,   122,   102,   105,   117,    33,    34,    35,
      36,    37,    68,   110,   121,    71,    53,    54,    55,    56,
      57,   126,   111,   115,    72,    73,    74,    75,    53,    54,
      55,    56,    57,    53,    54,    55,    56,    57,   116,   118,
      58,   119,     0,   120,   123,    59,    53,    54,    55,    56,
      57,    53,    54,    55,    56,    57,   125,   127,    87,     0,
       0,     0,     0,   100,    53,    54,    55,    56,    57,    53,
      54,    55,    56,    57,     0,     0,   101
};

static const yytype_int8 yycheck[] =
{
      14,    27,    21,     7,     8,     5,    36,    37,     8,     9,
      10,    11,    12,    13,    14,     6,     7,    36,    18,     3,
      15,    16,    48,    36,    35,    20,    28,    29,    19,    36,
      37,    44,     0,    15,    16,    30,    44,    39,    20,    38,
      44,    45,    68,    69,    44,    40,    41,    42,    43,    44,
      38,    44,    28,    29,    36,    35,    60,    61,    40,    41,
      42,    43,    44,    39,    28,    29,    44,    71,    72,    73,
      74,    75,    15,    16,     4,    39,    21,    20,    44,    93,
      53,    54,    55,    56,    57,    99,    90,    21,   102,    36,
      17,    35,    17,   119,    17,    35,   110,    40,    41,    42,
      43,    44,    28,    17,   118,    22,    23,    24,    25,    26,
      27,   125,    44,    19,    31,    32,    33,    34,    23,    24,
      25,    26,    27,    23,    24,    25,    26,    27,    19,    17,
      35,    38,    -1,    19,    19,    35,    23,    24,    25,    26,
      27,    23,    24,    25,    26,    27,    17,    19,    35,    -1,
      -1,    -1,    -1,    35,    23,    24,    25,    26,    27,    23,
      24,    25,    26,    27,    -1,    -1,    35
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    46,     5,     8,     9,    10,    11,    12,    13,
      14,    18,    44,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,     0,    38,    38,    35,    35,
      15,    16,    20,    40,    41,    42,    43,    44,    62,    63,
      62,    44,    44,    44,    21,    36,     4,    47,    30,    61,
      62,    61,    44,    23,    24,    25,    26,    27,    35,    35,
      21,    21,    36,    62,    36,    60,    62,    61,    28,    29,
      39,    22,    31,    32,    33,    34,    39,    63,    63,    63,
      63,    63,    62,    62,    36,    44,    59,    35,    35,    36,
      37,    61,    61,    17,    62,    62,    62,    62,    62,    17,
      35,    35,    17,    36,    37,    35,    62,    47,    47,    47,
      17,    44,     6,     7,    19,    19,    19,    47,    17,    38,
      19,    47,    61,    19,    39,    17,    47,    19
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    47,    47,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    49,    49,    50,    51,    51,
      51,    52,    53,    54,    55,    56,    57,    57,    58,    58,
      59,    59,    60,    60,    61,    61,    61,    61,    61,    61,
      61,    61,    62,    62,    62,    62,    62,    62,    63,    63,
      63,    63,    63,    63,    63,    63
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     5,     5,     4,     7,    10,
      13,     7,     3,     3,     2,     2,     8,     7,     5,     4,
       1,     3,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     3,     3,     3,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: SCENEONHA stmt_list SCENEOFFHA  */
#line 85 "parser.y"
        {
            ASTNode *n = make_node(NODE_PROGRAM);
            n->left    = (yyvsp[-1].node);
            ast_root   = n;
            (yyval.node) = n;
        }
#line 1225 "parser.tab.c"
    break;

  case 3: /* stmt_list: stmt stmt_list  */
#line 98 "parser.y"
        {
            ASTNode *n = make_node(NODE_STMT_LIST);
            n->left    = (yyvsp[-1].node);
            n->next    = (yyvsp[0].node);
            (yyval.node) = n;
        }
#line 1236 "parser.tab.c"
    break;

  case 4: /* stmt_list: stmt  */
#line 105 "parser.y"
        {
            ASTNode *n = make_node(NODE_STMT_LIST);
            n->left    = (yyvsp[0].node);
            n->next    = NULL;
            (yyval.node) = n;
        }
#line 1247 "parser.tab.c"
    break;

  case 5: /* stmt: decl_stmt  */
#line 117 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1253 "parser.tab.c"
    break;

  case 6: /* stmt: assign_stmt  */
#line 118 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1259 "parser.tab.c"
    break;

  case 7: /* stmt: cond_stmt  */
#line 119 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1265 "parser.tab.c"
    break;

  case 8: /* stmt: loop_stmt  */
#line 120 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1271 "parser.tab.c"
    break;

  case 9: /* stmt: output_stmt  */
#line 121 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1277 "parser.tab.c"
    break;

  case 10: /* stmt: return_stmt  */
#line 122 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1283 "parser.tab.c"
    break;

  case 11: /* stmt: break_stmt  */
#line 123 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1289 "parser.tab.c"
    break;

  case 12: /* stmt: continue_stmt  */
#line 124 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1295 "parser.tab.c"
    break;

  case 13: /* stmt: func_decl  */
#line 125 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1301 "parser.tab.c"
    break;

  case 14: /* stmt: func_call  */
#line 126 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1307 "parser.tab.c"
    break;

  case 15: /* decl_stmt: NUMYESKARAO ID ASSIGN expr TERMINATOR  */
#line 135 "parser.y"
        {
            ASTNode *n  = make_node(NODE_DECL);
            n->str_val  = strdup((yyvsp[-3].str_val));
            n->left     = (yyvsp[-1].node);
            (yyval.node) = n;
        }
#line 1318 "parser.tab.c"
    break;

  case 16: /* decl_stmt: FLOATYESKARAO ID ASSIGN expr TERMINATOR  */
#line 142 "parser.y"
        {
            ASTNode *n  = make_node(NODE_DECL);
            n->str_val  = strdup((yyvsp[-3].str_val));
            n->left     = (yyvsp[-1].node);
            (yyval.node) = n;
        }
#line 1329 "parser.tab.c"
    break;

  case 17: /* assign_stmt: ID ASSIGN expr TERMINATOR  */
#line 155 "parser.y"
        {
            ASTNode *n  = make_node(NODE_ASSIGN);
            n->str_val  = strdup((yyvsp[-3].str_val));
            n->left     = (yyvsp[-1].node);
            (yyval.node) = n;
        }
#line 1340 "parser.tab.c"
    break;

  case 18: /* cond_stmt: LOWKEY LPAREN condition RPAREN BASYAR stmt_list YEHLO  */
#line 170 "parser.y"
        {
            ASTNode *n  = make_node(NODE_IF);
            n->left     = (yyvsp[-4].node);
            n->right    = (yyvsp[-1].node);
            (yyval.node) = n;
        }
#line 1351 "parser.tab.c"
    break;

  case 19: /* cond_stmt: LOWKEY LPAREN condition RPAREN BASYAR stmt_list WARNABRO BASYAR stmt_list YEHLO  */
#line 177 "parser.y"
        {
            ASTNode *n  = make_node(NODE_IF_ELSE);
            n->left     = (yyvsp[-7].node);
            n->right    = (yyvsp[-4].node);
            n->extra    = (yyvsp[-1].node);
            (yyval.node) = n;
        }
#line 1363 "parser.tab.c"
    break;

  case 20: /* cond_stmt: LOWKEY LPAREN condition RPAREN BASYAR stmt_list PHIRBRO LPAREN condition RPAREN BASYAR stmt_list YEHLO  */
#line 185 "parser.y"
        {
            ASTNode *n  = make_node(NODE_IF_ELSEIF);
            n->left     = (yyvsp[-10].node);   /* first condition (lowkey) */
            n->right    = (yyvsp[-7].node);   /* first body (lowkey's body) */
            n->cond2    = (yyvsp[-4].node);   /* second condition (phirBro) */
            n->extra    = (yyvsp[-1].node);  /* second body (phirBro's body) */
            (yyval.node) = n;
        }
#line 1376 "parser.tab.c"
    break;

  case 21: /* loop_stmt: CHALBRO LPAREN condition RPAREN BASYAR stmt_list YEHLO  */
#line 200 "parser.y"
        {
            ASTNode *n  = make_node(NODE_WHILE);
            n->left     = (yyvsp[-4].node);
            n->right    = (yyvsp[-1].node);
            (yyval.node) = n;
        }
#line 1387 "parser.tab.c"
    break;

  case 22: /* output_stmt: SPILLTEA expr TERMINATOR  */
#line 213 "parser.y"
        {
            ASTNode *n = make_node(NODE_PRINT);
            n->left    = (yyvsp[-1].node);
            (yyval.node) = n;
        }
#line 1397 "parser.tab.c"
    break;

  case 23: /* return_stmt: WAPAS expr TERMINATOR  */
#line 225 "parser.y"
        {
            ASTNode *n = make_node(NODE_RETURN);
            n->left    = (yyvsp[-1].node);
            (yyval.node) = n;
        }
#line 1407 "parser.tab.c"
    break;

  case 24: /* break_stmt: GHOSTED TERMINATOR  */
#line 237 "parser.y"
        {
            (yyval.node) = make_node(NODE_BREAK);
        }
#line 1415 "parser.tab.c"
    break;

  case 25: /* continue_stmt: MISSKARA TERMINATOR  */
#line 247 "parser.y"
        {
            (yyval.node) = make_node(NODE_CONTINUE);
        }
#line 1423 "parser.tab.c"
    break;

  case 26: /* func_decl: KAAMKARO ID SEPARATOR param_list SEPARATOR BASYAR stmt_list YEHLO  */
#line 258 "parser.y"
        {
            (yyval.node) = make_func_decl((yyvsp[-6].str_val), (yyvsp[-4].node), (yyvsp[-1].node));
        }
#line 1431 "parser.tab.c"
    break;

  case 27: /* func_decl: KAAMKARO ID SEPARATOR SEPARATOR BASYAR stmt_list YEHLO  */
#line 262 "parser.y"
        {
            (yyval.node) = make_func_decl((yyvsp[-5].str_val), NULL, (yyvsp[-1].node));
        }
#line 1439 "parser.tab.c"
    break;

  case 28: /* func_call: ID SEPARATOR arg_list SEPARATOR TERMINATOR  */
#line 273 "parser.y"
        {
            (yyval.node) = make_func_call((yyvsp[-4].str_val), (yyvsp[-2].node));
        }
#line 1447 "parser.tab.c"
    break;

  case 29: /* func_call: ID SEPARATOR SEPARATOR TERMINATOR  */
#line 277 "parser.y"
        {
            (yyval.node) = make_func_call((yyvsp[-3].str_val), NULL);
        }
#line 1455 "parser.tab.c"
    break;

  case 30: /* param_list: ID  */
#line 287 "parser.y"
        {
            (yyval.node) = make_param((yyvsp[0].str_val));
        }
#line 1463 "parser.tab.c"
    break;

  case 31: /* param_list: param_list COMMA ID  */
#line 291 "parser.y"
        {
            ASTNode *p = make_param((yyvsp[0].str_val));
            (yyvsp[-2].node)->next   = p;
            (yyval.node) = (yyvsp[-2].node);
        }
#line 1473 "parser.tab.c"
    break;

  case 32: /* arg_list: expr  */
#line 303 "parser.y"
        {
            (yyval.node) = make_arg((yyvsp[0].node));
        }
#line 1481 "parser.tab.c"
    break;

  case 33: /* arg_list: arg_list COMMA expr  */
#line 307 "parser.y"
        {
            ASTNode *a = make_arg((yyvsp[0].node));
            (yyvsp[-2].node)->next   = a;
            (yyval.node) = (yyvsp[-2].node);
        }
#line 1491 "parser.tab.c"
    break;

  case 34: /* condition: expr EQ expr  */
#line 319 "parser.y"
                                 { (yyval.node) = make_condition("==?",     (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1497 "parser.tab.c"
    break;

  case 35: /* condition: expr LT expr  */
#line 320 "parser.y"
                                 { (yyval.node) = make_condition("<",        (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1503 "parser.tab.c"
    break;

  case 36: /* condition: expr GT expr  */
#line 321 "parser.y"
                                 { (yyval.node) = make_condition(">",        (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1509 "parser.tab.c"
    break;

  case 37: /* condition: expr LTE expr  */
#line 322 "parser.y"
                                 { (yyval.node) = make_condition("<=",       (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1515 "parser.tab.c"
    break;

  case 38: /* condition: expr GTE expr  */
#line 323 "parser.y"
                                 { (yyval.node) = make_condition(">=",       (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1521 "parser.tab.c"
    break;

  case 39: /* condition: condition AND condition  */
#line 324 "parser.y"
                                 { (yyval.node) = make_condition("aurBhai",  (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1527 "parser.tab.c"
    break;

  case 40: /* condition: condition OR condition  */
#line 325 "parser.y"
                                 { (yyval.node) = make_condition("yaBhai",   (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1533 "parser.tab.c"
    break;

  case 41: /* condition: NOT condition  */
#line 326 "parser.y"
                                 { (yyval.node) = make_condition("nahi",     (yyvsp[0].node), NULL); }
#line 1539 "parser.tab.c"
    break;

  case 42: /* expr: expr PLUS term  */
#line 334 "parser.y"
                         { (yyval.node) = make_binop("^+", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1545 "parser.tab.c"
    break;

  case 43: /* expr: expr MINUS term  */
#line 335 "parser.y"
                         { (yyval.node) = make_binop("^-", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1551 "parser.tab.c"
    break;

  case 44: /* expr: expr MULTIPLY term  */
#line 336 "parser.y"
                         { (yyval.node) = make_binop("^*", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1557 "parser.tab.c"
    break;

  case 45: /* expr: expr DIVIDE term  */
#line 337 "parser.y"
                         { (yyval.node) = make_binop("^/", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1563 "parser.tab.c"
    break;

  case 46: /* expr: expr MODULO term  */
#line 338 "parser.y"
                         { (yyval.node) = make_binop("^%", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1569 "parser.tab.c"
    break;

  case 47: /* expr: term  */
#line 339 "parser.y"
                         { (yyval.node) = (yyvsp[0].node);                        }
#line 1575 "parser.tab.c"
    break;

  case 48: /* term: INT_NUM  */
#line 346 "parser.y"
                     { (yyval.node) = make_int((yyvsp[0].int_val));    }
#line 1581 "parser.tab.c"
    break;

  case 49: /* term: FLOAT_NUM  */
#line 347 "parser.y"
                     { (yyval.node) = make_float((yyvsp[0].float_val));  }
#line 1587 "parser.tab.c"
    break;

  case 50: /* term: SCIENTIFIC_NUM  */
#line 348 "parser.y"
                     { (yyval.node) = make_float((yyvsp[0].float_val));  }
#line 1593 "parser.tab.c"
    break;

  case 51: /* term: STRING_LIT  */
#line 349 "parser.y"
                     { (yyval.node) = make_string((yyvsp[0].str_val)); }
#line 1599 "parser.tab.c"
    break;

  case 52: /* term: NOCAP  */
#line 350 "parser.y"
                     { (yyval.node) = make_bool(1);    }
#line 1605 "parser.tab.c"
    break;

  case 53: /* term: CAP  */
#line 351 "parser.y"
                     { (yyval.node) = make_bool(0);    }
#line 1611 "parser.tab.c"
    break;

  case 54: /* term: ID  */
#line 352 "parser.y"
                     { (yyval.node) = make_ident((yyvsp[0].str_val));  }
#line 1617 "parser.tab.c"
    break;

  case 55: /* term: KITNALAMBA ID  */
#line 354 "parser.y"
        {
            ASTNode *n = make_node(NODE_STR_LEN);
            n->str_val = strdup((yyvsp[0].str_val));
            (yyval.node) = n;
        }
#line 1627 "parser.tab.c"
    break;


#line 1631 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 361 "parser.y"


/* 
   Error handler
 */
void yyerror(const char *msg) {
    fprintf(stderr,
        "Syntax Error [line %d]: %s (near '%s')\n",
        line_count, msg, "?");
}
