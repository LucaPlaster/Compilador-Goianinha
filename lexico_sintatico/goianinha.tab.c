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
#line 1 "./lexico_sintatico/goianinha.y"

/**
 * Analisador Sintático para a Linguagem Goianinha
 * 
 * Este arquivo define a gramática da linguagem Goianinha e as ações semânticas
 * para construção da Árvore Sintática Abstrata (AST). É processado pelo Bison
 * para gerar o parser.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/arvore_sintatica.h"

struct NoArvore;

// Declarações de funções externas
extern int yylex();
extern int yylineno;
void yyerror(const char *s);

// Variável global que armazenará a raiz da AST
NoArvore* raiz_arvore_sintatica = NULL;

#line 96 "./lexico_sintatico/goianinha.tab.c"

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

#include "goianinha.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PROGRAMA = 3,                   /* PROGRAMA  */
  YYSYMBOL_TK_INT = 4,                     /* TK_INT  */
  YYSYMBOL_TK_CAR = 5,                     /* TK_CAR  */
  YYSYMBOL_RETORNE = 6,                    /* RETORNE  */
  YYSYMBOL_LEIA = 7,                       /* LEIA  */
  YYSYMBOL_ESCREVA = 8,                    /* ESCREVA  */
  YYSYMBOL_NOVALINHA = 9,                  /* NOVALINHA  */
  YYSYMBOL_SE = 10,                        /* SE  */
  YYSYMBOL_ENTAO = 11,                     /* ENTAO  */
  YYSYMBOL_SENAO = 12,                     /* SENAO  */
  YYSYMBOL_ENQUANTO = 13,                  /* ENQUANTO  */
  YYSYMBOL_EXECUTE = 14,                   /* EXECUTE  */
  YYSYMBOL_ID = 15,                        /* ID  */
  YYSYMBOL_STRINGCONST = 16,               /* STRINGCONST  */
  YYSYMBOL_CARCONST = 17,                  /* CARCONST  */
  YYSYMBOL_INTCONST = 18,                  /* INTCONST  */
  YYSYMBOL_MAIS = 19,                      /* MAIS  */
  YYSYMBOL_MENOS = 20,                     /* MENOS  */
  YYSYMBOL_MULT = 21,                      /* MULT  */
  YYSYMBOL_DIV = 22,                       /* DIV  */
  YYSYMBOL_IGUAL = 23,                     /* IGUAL  */
  YYSYMBOL_DIFERENTE = 24,                 /* DIFERENTE  */
  YYSYMBOL_MENOR = 25,                     /* MENOR  */
  YYSYMBOL_MAIOR = 26,                     /* MAIOR  */
  YYSYMBOL_MAIORIGUAL = 27,                /* MAIORIGUAL  */
  YYSYMBOL_MENORIGUAL = 28,                /* MENORIGUAL  */
  YYSYMBOL_ATRIBUICAO = 29,                /* ATRIBUICAO  */
  YYSYMBOL_OU = 30,                        /* OU  */
  YYSYMBOL_E = 31,                         /* E  */
  YYSYMBOL_ABREPAR = 32,                   /* ABREPAR  */
  YYSYMBOL_FECHAPAR = 33,                  /* FECHAPAR  */
  YYSYMBOL_ABRECHAVE = 34,                 /* ABRECHAVE  */
  YYSYMBOL_FECHACHAVE = 35,                /* FECHACHAVE  */
  YYSYMBOL_VIRGULA = 36,                   /* VIRGULA  */
  YYSYMBOL_PONTOVIRGULA = 37,              /* PONTOVIRGULA  */
  YYSYMBOL_38_ = 38,                       /* '!'  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_Programa = 40,                  /* Programa  */
  YYSYMBOL_DeclFuncVar = 41,               /* DeclFuncVar  */
  YYSYMBOL_DeclProg = 42,                  /* DeclProg  */
  YYSYMBOL_Tipo = 43,                      /* Tipo  */
  YYSYMBOL_DeclVar = 44,                   /* DeclVar  */
  YYSYMBOL_DeclFunc = 45,                  /* DeclFunc  */
  YYSYMBOL_ListaParametros = 46,           /* ListaParametros  */
  YYSYMBOL_ListaParametrosCont = 47,       /* ListaParametrosCont  */
  YYSYMBOL_Bloco = 48,                     /* Bloco  */
  YYSYMBOL_ListaDeclVar = 49,              /* ListaDeclVar  */
  YYSYMBOL_ListaComando = 50,              /* ListaComando  */
  YYSYMBOL_Comando = 51,                   /* Comando  */
  YYSYMBOL_Expr = 52,                      /* Expr  */
  YYSYMBOL_OrExpr = 53,                    /* OrExpr  */
  YYSYMBOL_AndExpr = 54,                   /* AndExpr  */
  YYSYMBOL_EqExpr = 55,                    /* EqExpr  */
  YYSYMBOL_DesigExpr = 56,                 /* DesigExpr  */
  YYSYMBOL_AddExpr = 57,                   /* AddExpr  */
  YYSYMBOL_MulExpr = 58,                   /* MulExpr  */
  YYSYMBOL_UnExpr = 59,                    /* UnExpr  */
  YYSYMBOL_PrimExpr = 60,                  /* PrimExpr  */
  YYSYMBOL_ListExpr = 61                   /* ListExpr  */
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
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   130

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  62
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  122

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   292


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
       2,     2,     2,    38,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    74,    74,    91,   100,   109,   121,   133,   138,   151,
     158,   171,   183,   187,   196,   203,   219,   231,   235,   249,
     253,   265,   270,   275,   280,   287,   292,   299,   304,   309,
     314,   319,   330,   334,   346,   351,   360,   365,   374,   379,
     384,   393,   398,   403,   408,   413,   422,   427,   432,   441,
     446,   451,   460,   465,   470,   479,   485,   491,   497,   503,
     509,   519,   524
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
  "\"end of file\"", "error", "\"invalid token\"", "PROGRAMA", "TK_INT",
  "TK_CAR", "RETORNE", "LEIA", "ESCREVA", "NOVALINHA", "SE", "ENTAO",
  "SENAO", "ENQUANTO", "EXECUTE", "ID", "STRINGCONST", "CARCONST",
  "INTCONST", "MAIS", "MENOS", "MULT", "DIV", "IGUAL", "DIFERENTE",
  "MENOR", "MAIOR", "MAIORIGUAL", "MENORIGUAL", "ATRIBUICAO", "OU", "E",
  "ABREPAR", "FECHAPAR", "ABRECHAVE", "FECHACHAVE", "VIRGULA",
  "PONTOVIRGULA", "'!'", "$accept", "Programa", "DeclFuncVar", "DeclProg",
  "Tipo", "DeclVar", "DeclFunc", "ListaParametros", "ListaParametrosCont",
  "Bloco", "ListaDeclVar", "ListaComando", "Comando", "Expr", "OrExpr",
  "AndExpr", "EqExpr", "DesigExpr", "AddExpr", "MulExpr", "UnExpr",
  "PrimExpr", "ListExpr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-98)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      82,   -98,   -98,    40,    30,    27,   -98,    17,   -98,    11,
      82,   -98,    82,    34,    18,    82,    53,     7,    63,    51,
     -98,    52,    82,   -98,    52,    43,    67,    14,    61,    73,
      76,    21,   -98,   -98,    -6,    43,   -98,    -6,   -98,    74,
       7,    75,    80,    83,    71,   -20,    77,    78,   -98,   -98,
      79,    17,   -98,   -98,    81,    84,    85,    86,    87,   -98,
      43,    43,    43,    39,    88,   -98,    92,   -98,   -98,   -98,
     -98,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    82,   -98,    82,   -98,   -98,   -98,   -98,
      93,    94,   -98,   -98,   -98,    33,   -98,    83,    71,   -20,
     -20,    77,    77,    77,    77,    78,    78,   -98,   -98,   -98,
     -98,   100,    99,   -98,    43,     7,     7,   -98,   104,   -98,
       7,   -98
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,     7,     8,     0,     0,     0,     1,     0,     2,    10,
      17,     6,    12,     0,     0,     5,     0,     0,     0,     0,
      13,    10,     5,     4,    10,     0,     0,     0,     0,     0,
       0,    57,    58,    59,     0,     0,    21,     0,    31,     0,
      19,     0,    32,    35,    37,    40,    45,    48,    51,    54,
      14,     0,     9,     3,     0,     0,     0,     0,     0,    27,
       0,     0,     0,     0,    57,    52,     0,    53,    16,    20,
      22,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    11,    17,    23,    24,    26,    25,
       0,     0,    33,    56,    61,     0,    60,    34,    36,    38,
      39,    41,    42,    43,    44,    46,    47,    49,    50,    15,
      18,     0,     0,    55,     0,     0,     0,    62,    28,    30,
       0,    29
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -98,   -98,     6,   -98,    -9,    49,   -98,   -98,    36,    -3,
      32,    89,   -97,   -25,   -98,    57,    58,    28,    15,    24,
      25,    46,   -98
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     8,     5,    14,    15,    19,    20,    38,
      17,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    95
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      55,    16,    58,    18,    11,    75,    76,    77,    78,    64,
      66,    32,    33,    25,    26,    27,    28,    29,   118,   119,
      30,    23,    31,   121,    32,    33,    35,    34,    53,    31,
      57,    32,    33,     7,    34,    90,    91,    92,    94,    35,
       6,    10,     9,    12,    36,    37,    35,    13,    84,    21,
      62,    10,    37,    63,    31,    22,    32,    33,    31,    34,
      32,    33,    64,    34,    32,    33,   113,    34,    24,   114,
      52,    35,    93,    54,    18,    35,    16,    37,    50,    35,
      65,    37,    56,    67,    51,    37,     1,     2,    13,   117,
     101,   102,   103,   104,    73,    74,    79,    80,    59,    81,
      82,    99,   100,   105,   106,    60,   107,   108,    61,    68,
      71,   115,    70,   116,    72,    83,   120,   110,    85,   109,
      63,    86,    87,    88,    89,    96,   111,   112,    97,    69,
      98
};

static const yytype_int8 yycheck[] =
{
      25,    10,    27,    12,     7,    25,    26,    27,    28,    15,
      35,    17,    18,     6,     7,     8,     9,    10,   115,   116,
      13,    15,    15,   120,    17,    18,    32,    20,    22,    15,
      16,    17,    18,     3,    20,    60,    61,    62,    63,    32,
       0,    34,    15,    32,    37,    38,    32,    36,    51,    15,
      29,    34,    38,    32,    15,    37,    17,    18,    15,    20,
      17,    18,    15,    20,    17,    18,    33,    20,    15,    36,
      21,    32,    33,    24,    83,    32,    85,    38,    15,    32,
      34,    38,    15,    37,    33,    38,     4,     5,    36,   114,
      75,    76,    77,    78,    23,    24,    19,    20,    37,    21,
      22,    73,    74,    79,    80,    32,    81,    82,    32,    35,
      30,    11,    37,    14,    31,    36,    12,    85,    37,    83,
      32,    37,    37,    37,    37,    33,    33,    33,    71,    40,
      72
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,    40,    41,    43,     0,     3,    42,    15,
      34,    48,    32,    36,    44,    45,    43,    49,    43,    46,
      47,    15,    37,    41,    15,     6,     7,     8,     9,    10,
      13,    15,    17,    18,    20,    32,    37,    38,    48,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      15,    33,    44,    41,    44,    52,    15,    16,    52,    37,
      32,    32,    29,    32,    15,    60,    52,    60,    35,    50,
      37,    30,    31,    23,    24,    25,    26,    27,    28,    19,
      20,    21,    22,    36,    48,    37,    37,    37,    37,    37,
      52,    52,    52,    33,    52,    61,    33,    54,    55,    56,
      56,    57,    57,    57,    57,    58,    58,    59,    59,    47,
      49,    33,    33,    33,    36,    11,    14,    52,    51,    51,
      12,    51
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    41,    41,    41,    42,    43,    43,    44,
      44,    45,    46,    46,    47,    47,    48,    49,    49,    50,
      50,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    52,    52,    53,    53,    54,    54,    55,    55,
      55,    56,    56,    56,    56,    56,    57,    57,    57,    58,
      58,    58,    59,    59,    59,    60,    60,    60,    60,    60,
      60,    61,    61
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     5,     4,     0,     2,     1,     1,     3,
       0,     4,     0,     1,     2,     4,     4,     0,     5,     1,
       2,     1,     2,     3,     3,     3,     3,     2,     6,     8,
       6,     1,     1,     3,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     2,     2,     1,     4,     3,     1,     1,     1,
       3,     1,     3
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
  case 2: /* Programa: DeclFuncVar DeclProg  */
#line 75 "./lexico_sintatico/goianinha.y"
    {
        raiz_arvore_sintatica = construir_no_arvore(NO_PROGRAMA, yylineno, NULL, 0, 
                                                     TIPO_VAZIO, 2, (yyvsp[-1].no), (yyvsp[0].no));
        (yyval.no) = raiz_arvore_sintatica;
    }
#line 1231 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 3: /* DeclFuncVar: Tipo ID DeclVar PONTOVIRGULA DeclFuncVar  */
#line 92 "./lexico_sintatico/goianinha.y"
    {
        // Cria nó para declaração de variável(is)
        NoArvore* no_atual = construir_no_arvore(NO_DECL_VAR, yylineno, (yyvsp[-3].texto), 0, 
                                                  (yyvsp[-4].no)->tipo_var, 1, (yyvsp[-2].no));
        // Se houver mais declarações, cria uma lista
        (yyval.no) = (yyvsp[0].no) ? construir_no_arvore(NO_LISTA, yylineno, NULL, 0, 
                                       TIPO_DESCONHECIDO, 2, no_atual, (yyvsp[0].no)) : no_atual;
    }
#line 1244 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 4: /* DeclFuncVar: Tipo ID DeclFunc DeclFuncVar  */
#line 101 "./lexico_sintatico/goianinha.y"
    {
        // Cria nó para declaração de função
        NoArvore* no_atual = construir_no_arvore(NO_FUNCAO, yylineno, (yyvsp[-2].texto), 0, 
                                                  (yyvsp[-3].no)->tipo_var, 1, (yyvsp[-1].no));
        // Se houver mais declarações, cria uma lista
        (yyval.no) = (yyvsp[0].no) ? construir_no_arvore(NO_LISTA, yylineno, NULL, 0, 
                                       TIPO_DESCONHECIDO, 2, no_atual, (yyvsp[0].no)) : no_atual;
    }
#line 1257 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 5: /* DeclFuncVar: %empty  */
#line 110 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = NULL;  // Não há declarações
    }
#line 1265 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 6: /* DeclProg: PROGRAMA Bloco  */
#line 122 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = construir_no_arvore(NO_BLOCO, yylineno, strdup("programa"), 0, 
                                 TIPO_VAZIO, 1, (yyvsp[0].no));
    }
#line 1274 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 7: /* Tipo: TK_INT  */
#line 134 "./lexico_sintatico/goianinha.y"
    { 
        (yyval.no) = construir_no_arvore(NO_IDENTIFICADOR, yylineno, strdup("int"), 0, 
                                 TIPO_INTEIRO, 0); 
    }
#line 1283 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 8: /* Tipo: TK_CAR  */
#line 139 "./lexico_sintatico/goianinha.y"
    { 
        (yyval.no) = construir_no_arvore(NO_IDENTIFICADOR, yylineno, strdup("car"), 0, 
                                 TIPO_CARACTERE, 0); 
    }
#line 1292 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 9: /* DeclVar: VIRGULA ID DeclVar  */
#line 152 "./lexico_sintatico/goianinha.y"
    {
        NoArvore* no_id = construir_no_arvore(NO_IDENTIFICADOR, yylineno, (yyvsp[-1].texto), 0, 
                                               TIPO_DESCONHECIDO, 0);
        (yyval.no) = construir_no_arvore(NO_LISTA, yylineno, NULL, 0, 
                                 TIPO_DESCONHECIDO, 2, no_id, (yyvsp[0].no));
    }
#line 1303 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 10: /* DeclVar: %empty  */
#line 159 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = NULL;  // Não há mais variáveis
    }
#line 1311 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 11: /* DeclFunc: ABREPAR ListaParametros FECHAPAR Bloco  */
#line 172 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = construir_no_arvore(NO_FUNCAO, yylineno, NULL, 0, 
                                 TIPO_DESCONHECIDO, 2, (yyvsp[-2].no), (yyvsp[0].no));
    }
#line 1320 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 12: /* ListaParametros: %empty  */
#line 184 "./lexico_sintatico/goianinha.y"
    { 
        (yyval.no) = NULL;  // Sem parâmetros
    }
#line 1328 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 13: /* ListaParametros: ListaParametrosCont  */
#line 188 "./lexico_sintatico/goianinha.y"
    { 
        (yyval.no) = (yyvsp[0].no); 
    }
#line 1336 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 14: /* ListaParametrosCont: Tipo ID  */
#line 197 "./lexico_sintatico/goianinha.y"
    {
        NoArvore* no_id = construir_no_arvore(NO_IDENTIFICADOR, yylineno, (yyvsp[0].texto), 0, 
                                               (yyvsp[-1].no)->tipo_var, 0);
        (yyval.no) = construir_no_arvore(NO_LISTA, yylineno, strdup("lista_params"), 0, 
                                 TIPO_DESCONHECIDO, 1, no_id);
    }
#line 1347 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 15: /* ListaParametrosCont: Tipo ID VIRGULA ListaParametrosCont  */
#line 204 "./lexico_sintatico/goianinha.y"
    {
        NoArvore* no_id = construir_no_arvore(NO_IDENTIFICADOR, yylineno, (yyvsp[-2].texto), 0, 
                                               (yyvsp[-3].no)->tipo_var, 0);
        (yyval.no) = construir_no_arvore(NO_LISTA, yylineno, NULL, 0, 
                                 TIPO_DESCONHECIDO, 2, no_id, (yyvsp[0].no));
    }
#line 1358 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 16: /* Bloco: ABRECHAVE ListaDeclVar ListaComando FECHACHAVE  */
#line 220 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = construir_no_arvore(NO_BLOCO, yylineno, NULL, 0, 
                                 TIPO_VAZIO, 2, (yyvsp[-2].no), (yyvsp[-1].no));
    }
#line 1367 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 17: /* ListaDeclVar: %empty  */
#line 232 "./lexico_sintatico/goianinha.y"
    { 
        (yyval.no) = NULL;  // Sem declarações locais
    }
#line 1375 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 18: /* ListaDeclVar: Tipo ID DeclVar PONTOVIRGULA ListaDeclVar  */
#line 236 "./lexico_sintatico/goianinha.y"
    {
        NoArvore* no_decl = construir_no_arvore(NO_DECL_VAR, yylineno, (yyvsp[-3].texto), 0, 
                                                 (yyvsp[-4].no)->tipo_var, 1, (yyvsp[-2].no));
        (yyval.no) = (yyvsp[0].no) ? construir_no_arvore(NO_LISTA, yylineno, NULL, 0, 
                                      TIPO_DESCONHECIDO, 2, no_decl, (yyvsp[0].no)) : no_decl;
    }
#line 1386 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 19: /* ListaComando: Comando  */
#line 250 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = (yyvsp[0].no);
    }
#line 1394 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 20: /* ListaComando: Comando ListaComando  */
#line 254 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = construir_no_arvore(NO_LISTA, yylineno, NULL, 0, 
                                 TIPO_DESCONHECIDO, 2, (yyvsp[-1].no), (yyvsp[0].no));
    }
#line 1403 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 21: /* Comando: PONTOVIRGULA  */
#line 266 "./lexico_sintatico/goianinha.y"
    {
        // Comando vazio
        (yyval.no) = NULL;
    }
#line 1412 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 22: /* Comando: Expr PONTOVIRGULA  */
#line 271 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = construir_no_arvore(NO_COMANDO, yylineno, strdup("expr"), 0, 
                                 TIPO_VAZIO, 1, (yyvsp[-1].no));
    }
#line 1421 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 23: /* Comando: RETORNE Expr PONTOVIRGULA  */
#line 276 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = construir_no_arvore(NO_COMANDO, yylineno, strdup("retorne"), 0, 
                                 TIPO_VAZIO, 1, (yyvsp[-1].no));
    }
#line 1430 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 24: /* Comando: LEIA ID PONTOVIRGULA  */
#line 281 "./lexico_sintatico/goianinha.y"
    {
        NoArvore* no_id = construir_no_arvore(NO_IDENTIFICADOR, yylineno, (yyvsp[-1].texto), 0, 
                                               TIPO_DESCONHECIDO, 0);
        (yyval.no) = construir_no_arvore(NO_COMANDO, yylineno, strdup("leia"), 0, 
                                 TIPO_VAZIO, 1, no_id);
    }
#line 1441 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 25: /* Comando: ESCREVA Expr PONTOVIRGULA  */
#line 288 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = construir_no_arvore(NO_COMANDO, yylineno, strdup("escreva"), 0, 
                                 TIPO_VAZIO, 1, (yyvsp[-1].no));
    }
#line 1450 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 26: /* Comando: ESCREVA STRINGCONST PONTOVIRGULA  */
#line 293 "./lexico_sintatico/goianinha.y"
    {
        NoArvore* no_string = construir_no_arvore(NO_CONSTANTE, yylineno, (yyvsp[-1].texto), 0, 
                                                   TIPO_CARACTERE, 0);
        (yyval.no) = construir_no_arvore(NO_COMANDO, yylineno, strdup("escreva_string"), 0, 
                                 TIPO_VAZIO, 1, no_string);
    }
#line 1461 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 27: /* Comando: NOVALINHA PONTOVIRGULA  */
#line 300 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = construir_no_arvore(NO_COMANDO, yylineno, strdup("novalinha"), 0, 
                                 TIPO_VAZIO, 0);
    }
#line 1470 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 28: /* Comando: SE ABREPAR Expr FECHAPAR ENTAO Comando  */
#line 305 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = construir_no_arvore(NO_COMANDO, yylineno, strdup("se"), 0, 
                                 TIPO_VAZIO, 2, (yyvsp[-3].no), (yyvsp[0].no));
    }
#line 1479 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 29: /* Comando: SE ABREPAR Expr FECHAPAR ENTAO Comando SENAO Comando  */
#line 310 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = construir_no_arvore(NO_COMANDO, yylineno, strdup("se_senao"), 0, 
                                 TIPO_VAZIO, 3, (yyvsp[-5].no), (yyvsp[-2].no), (yyvsp[0].no));
    }
#line 1488 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 30: /* Comando: ENQUANTO ABREPAR Expr FECHAPAR EXECUTE Comando  */
#line 315 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = construir_no_arvore(NO_COMANDO, yylineno, strdup("enquanto"), 0, 
                                 TIPO_VAZIO, 2, (yyvsp[-3].no), (yyvsp[0].no));
    }
#line 1497 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 31: /* Comando: Bloco  */
#line 320 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = (yyvsp[0].no);
    }
#line 1505 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 32: /* Expr: OrExpr  */
#line 331 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = (yyvsp[0].no);
    }
#line 1513 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 33: /* Expr: ID ATRIBUICAO Expr  */
#line 335 "./lexico_sintatico/goianinha.y"
    {
        NoArvore* no_id = construir_no_arvore(NO_IDENTIFICADOR, yylineno, (yyvsp[-2].texto), 0, 
                                               TIPO_DESCONHECIDO, 0);
        (yyval.no) = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup("="), 0, 
                                 TIPO_DESCONHECIDO, 2, no_id, (yyvsp[0].no));
    }
#line 1524 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 34: /* OrExpr: OrExpr OU AndExpr  */
#line 347 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup("ou"), 0, 
                                 TIPO_DESCONHECIDO, 2, (yyvsp[-2].no), (yyvsp[0].no));
    }
#line 1533 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 35: /* OrExpr: AndExpr  */
#line 352 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = (yyvsp[0].no);
    }
#line 1541 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 36: /* AndExpr: AndExpr E EqExpr  */
#line 361 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup("e"), 0, 
                                 TIPO_DESCONHECIDO, 2, (yyvsp[-2].no), (yyvsp[0].no));
    }
#line 1550 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 37: /* AndExpr: EqExpr  */
#line 366 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = (yyvsp[0].no);
    }
#line 1558 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 38: /* EqExpr: EqExpr IGUAL DesigExpr  */
#line 375 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup("=="), 0, 
                                 TIPO_DESCONHECIDO, 2, (yyvsp[-2].no), (yyvsp[0].no));
    }
#line 1567 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 39: /* EqExpr: EqExpr DIFERENTE DesigExpr  */
#line 380 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup("!="), 0, 
                                 TIPO_DESCONHECIDO, 2, (yyvsp[-2].no), (yyvsp[0].no));
    }
#line 1576 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 40: /* EqExpr: DesigExpr  */
#line 385 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = (yyvsp[0].no);
    }
#line 1584 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 41: /* DesigExpr: DesigExpr MENOR AddExpr  */
#line 394 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup("<"), 0, 
                                 TIPO_DESCONHECIDO, 2, (yyvsp[-2].no), (yyvsp[0].no));
    }
#line 1593 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 42: /* DesigExpr: DesigExpr MAIOR AddExpr  */
#line 399 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup(">"), 0, 
                                 TIPO_DESCONHECIDO, 2, (yyvsp[-2].no), (yyvsp[0].no));
    }
#line 1602 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 43: /* DesigExpr: DesigExpr MAIORIGUAL AddExpr  */
#line 404 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup(">="), 0, 
                                 TIPO_DESCONHECIDO, 2, (yyvsp[-2].no), (yyvsp[0].no));
    }
#line 1611 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 44: /* DesigExpr: DesigExpr MENORIGUAL AddExpr  */
#line 409 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup("<="), 0, 
                                 TIPO_DESCONHECIDO, 2, (yyvsp[-2].no), (yyvsp[0].no));
    }
#line 1620 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 45: /* DesigExpr: AddExpr  */
#line 414 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = (yyvsp[0].no);
    }
#line 1628 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 46: /* AddExpr: AddExpr MAIS MulExpr  */
#line 423 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup("+"), 0, 
                                 TIPO_DESCONHECIDO, 2, (yyvsp[-2].no), (yyvsp[0].no));
    }
#line 1637 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 47: /* AddExpr: AddExpr MENOS MulExpr  */
#line 428 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup("-"), 0, 
                                 TIPO_DESCONHECIDO, 2, (yyvsp[-2].no), (yyvsp[0].no));
    }
#line 1646 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 48: /* AddExpr: MulExpr  */
#line 433 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = (yyvsp[0].no);
    }
#line 1654 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 49: /* MulExpr: MulExpr MULT UnExpr  */
#line 442 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup("*"), 0, 
                                 TIPO_DESCONHECIDO, 2, (yyvsp[-2].no), (yyvsp[0].no));
    }
#line 1663 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 50: /* MulExpr: MulExpr DIV UnExpr  */
#line 447 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup("/"), 0, 
                                 TIPO_DESCONHECIDO, 2, (yyvsp[-2].no), (yyvsp[0].no));
    }
#line 1672 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 51: /* MulExpr: UnExpr  */
#line 452 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = (yyvsp[0].no);
    }
#line 1680 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 52: /* UnExpr: MENOS PrimExpr  */
#line 461 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup("negacao"), 0, 
                                 TIPO_DESCONHECIDO, 1, (yyvsp[0].no));
    }
#line 1689 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 53: /* UnExpr: '!' PrimExpr  */
#line 466 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup("!"), 0, 
                                 TIPO_DESCONHECIDO, 1, (yyvsp[0].no));
    }
#line 1698 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 54: /* UnExpr: PrimExpr  */
#line 471 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = (yyvsp[0].no);
    }
#line 1706 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 55: /* PrimExpr: ID ABREPAR ListExpr FECHAPAR  */
#line 480 "./lexico_sintatico/goianinha.y"
    {
        // Chamada de função com argumentos
        (yyval.no) = construir_no_arvore(NO_EXPRESSAO, yylineno, (yyvsp[-3].texto), 0, 
                                 TIPO_DESCONHECIDO, 1, (yyvsp[-1].no));
    }
#line 1716 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 56: /* PrimExpr: ID ABREPAR FECHAPAR  */
#line 486 "./lexico_sintatico/goianinha.y"
    {
        // Chamada de função sem argumentos
        (yyval.no) = construir_no_arvore(NO_EXPRESSAO, yylineno, (yyvsp[-2].texto), 0, 
                                 TIPO_DESCONHECIDO, 0);
    }
#line 1726 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 57: /* PrimExpr: ID  */
#line 492 "./lexico_sintatico/goianinha.y"
    {
        // Variável ou identificador
        (yyval.no) = construir_no_arvore(NO_IDENTIFICADOR, yylineno, (yyvsp[0].texto), 0, 
                                 TIPO_DESCONHECIDO, 0);
    }
#line 1736 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 58: /* PrimExpr: CARCONST  */
#line 498 "./lexico_sintatico/goianinha.y"
    {
        // Constante de caractere
        (yyval.no) = construir_no_arvore(NO_CONSTANTE, yylineno, (yyvsp[0].texto), 0, 
                                 TIPO_CARACTERE, 0);
    }
#line 1746 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 59: /* PrimExpr: INTCONST  */
#line 504 "./lexico_sintatico/goianinha.y"
    {
        // Constante inteira
        (yyval.no) = construir_no_arvore(NO_CONSTANTE, yylineno, (yyvsp[0].texto), 0, 
                                 TIPO_INTEIRO, 0);
    }
#line 1756 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 60: /* PrimExpr: ABREPAR Expr FECHAPAR  */
#line 510 "./lexico_sintatico/goianinha.y"
    {
        // Expressão entre parênteses
        (yyval.no) = (yyvsp[-1].no);
    }
#line 1765 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 61: /* ListExpr: Expr  */
#line 520 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = construir_no_arvore(NO_LISTA, yylineno, strdup("args"), 0, 
                                 TIPO_DESCONHECIDO, 1, (yyvsp[0].no));
    }
#line 1774 "./lexico_sintatico/goianinha.tab.c"
    break;

  case 62: /* ListExpr: ListExpr VIRGULA Expr  */
#line 525 "./lexico_sintatico/goianinha.y"
    {
        (yyval.no) = construir_no_arvore(NO_LISTA, yylineno, NULL, 0, 
                                 TIPO_DESCONHECIDO, 2, (yyvsp[-2].no), (yyvsp[0].no));
    }
#line 1783 "./lexico_sintatico/goianinha.tab.c"
    break;


#line 1787 "./lexico_sintatico/goianinha.tab.c"

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

#line 531 "./lexico_sintatico/goianinha.y"


/**
 * Função de tratamento de erros sintáticos.
 * Chamada automaticamente pelo parser quando encontra um erro.
 */
void yyerror(const char *s) {
    fprintf(stderr, "ERRO: Erro sintático na linha %d\n", yylineno);
    exit(1);
}
