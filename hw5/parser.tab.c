/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "header.h"
#include "symbolTable.h"
int linenumber = 1;
AST_NODE *prog;
int yylex();
int yyerror(char *mesg);

extern int g_anyErrorOccur;

static inline AST_NODE* makeSibling(AST_NODE *a, AST_NODE *b)
{
    while (a->rightSibling) {
        a = a->rightSibling;
    }
    if (b == NULL) {
        return a;
    }
    b = b->leftmostSibling;
    a->rightSibling = b;

    b->leftmostSibling = a->leftmostSibling;
    b->parent = a->parent;
    while (b->rightSibling) {
        b = b->rightSibling;
        b->leftmostSibling = a->leftmostSibling;
        b->parent = a->parent;
    }
    return b;
}

static inline AST_NODE* makeChild(AST_NODE *parent, AST_NODE *child)
{
    if (child == NULL) {
        return parent;
    }
    if (parent->child) {
        makeSibling(parent->child, child);
    } else {
        child = child->leftmostSibling;
        parent->child = child;
        while (child) {
            child->parent = parent;
            child = child->rightSibling;
        }
    }
    return parent;
}

static AST_NODE* makeFamily(AST_NODE *parent, int childrenCount, ...)
{
    va_list childrenList;
    va_start(childrenList, childrenCount);
    AST_NODE* child = va_arg(childrenList, AST_NODE*);
    makeChild(parent, child);
    AST_NODE* tmp = child;
    int index = 1;
    for (index = 1; index < childrenCount; ++index) {
        child = va_arg(childrenList, AST_NODE*);
        tmp = makeSibling(tmp, child);
    }
    va_end(childrenList);
    return parent;
}

static inline AST_NODE* makeIDNode(char *lexeme, IDENTIFIER_KIND idKind)
{
    AST_NODE* identifier = Allocate(IDENTIFIER_NODE);
    identifier->semantic_value.identifierSemanticValue.identifierName = lexeme;
    identifier->semantic_value.identifierSemanticValue.kind = idKind;
    identifier->semantic_value.identifierSemanticValue.symbolTableEntry = NULL;
    return identifier;
}

static inline AST_NODE* makeStmtNode(STMT_KIND stmtKind)
{
    AST_NODE* stmtNode = Allocate(STMT_NODE);
    stmtNode->semantic_value.stmtSemanticValue.kind = stmtKind;
    return stmtNode;
}

static inline AST_NODE* makeDeclNode(DECL_KIND declKind)
{
    AST_NODE* declNode = Allocate(DECLARATION_NODE);
    declNode->semantic_value.declSemanticValue.kind = declKind;
    return declNode;
}

static inline AST_NODE* makeExprNode(EXPR_KIND exprKind, int operationEnumValue)
{
    AST_NODE* exprNode = Allocate(EXPR_NODE);
    exprNode->semantic_value.exprSemanticValue.isConstEval = 0;
    exprNode->semantic_value.exprSemanticValue.kind = exprKind;
    if (exprKind == BINARY_OPERATION) {
        exprNode->semantic_value.exprSemanticValue.op.binaryOp = operationEnumValue;
    } else if (exprKind == UNARY_OPERATION) {
        exprNode->semantic_value.exprSemanticValue.op.unaryOp = operationEnumValue;
    } else {
        printf("Error in static inline AST_NODE* makeExprNode(EXPR_KIND exprKind, int operationEnumValue)\n");
    }
    return exprNode;
}


#line 179 "parser.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    CONST = 259,
    VOID = 260,
    INT = 261,
    FLOAT = 262,
    IF = 263,
    ELSE = 264,
    WHILE = 265,
    FOR = 266,
    TYPEDEF = 267,
    OP_ASSIGN = 268,
    OP_OR = 269,
    OP_AND = 270,
    OP_NOT = 271,
    OP_EQ = 272,
    OP_NE = 273,
    OP_GT = 274,
    OP_LT = 275,
    OP_GE = 276,
    OP_LE = 277,
    OP_PLUS = 278,
    OP_MINUS = 279,
    OP_TIMES = 280,
    OP_DIVIDE = 281,
    MK_LB = 282,
    MK_RB = 283,
    MK_LPAREN = 284,
    MK_RPAREN = 285,
    MK_LBRACE = 286,
    MK_RBRACE = 287,
    MK_COMMA = 288,
    MK_SEMICOLON = 289,
    MK_DOT = 290,
    ERROR = 291,
    RETURN = 292
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 114 "parser.y"

	char *lexeme;
	CON_Type  *const1;
	AST_NODE  *node;

#line 275 "parser.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */



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
typedef yytype_uint8 yy_state_t;

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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  19
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   234

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  112
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  201

#define YYUNDEFTOK  2
#define YYMAXUTOK   292


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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
      35,    36,    37
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   168,   168,   169,   172,   176,   182,   186,   192,   199,
     204,   211,   217,   222,   226,   232,   237,   243,   247,   253,
     258,   263,   268,   273,   278,   283,   287,   293,   297,   303,
     308,   316,   323,   327,   331,   337,   341,   345,   349,   354,
     358,   363,   368,   373,   378,   383,   388,   394,   399,   405,
     409,   415,   419,   423,   429,   433,   441,   445,   450,   455,
     460,   465,   470,   475,   479,   484,   491,   496,   501,   505,
     511,   517,   523,   529,   533,   540,   544,   551,   555,   561,
     565,   569,   573,   577,   581,   588,   593,   598,   602,   608,
     612,   618,   622,   628,   632,   638,   642,   648,   652,   657,
     662,   667,   674,   681,   686,   693,   700,   704,   709,   716,
     720,   728,   732
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "CONST", "VOID", "INT", "FLOAT",
  "IF", "ELSE", "WHILE", "FOR", "TYPEDEF", "OP_ASSIGN", "OP_OR", "OP_AND",
  "OP_NOT", "OP_EQ", "OP_NE", "OP_GT", "OP_LT", "OP_GE", "OP_LE",
  "OP_PLUS", "OP_MINUS", "OP_TIMES", "OP_DIVIDE", "MK_LB", "MK_RB",
  "MK_LPAREN", "MK_RPAREN", "MK_LBRACE", "MK_RBRACE", "MK_COMMA",
  "MK_SEMICOLON", "MK_DOT", "ERROR", "RETURN", "$accept", "program",
  "global_decl_list", "global_decl", "function_decl", "function_head",
  "opt_param_list", "param_list", "param", "dim_fn", "expr_null", "block",
  "decl_list", "decl", "type_decl", "var_decl", "type", "id_list",
  "dim_decl", "cexpr", "mcexpr", "cfactor", "init_id_list", "init_id",
  "stmt_list", "stmt", "assign_expr_list", "nonempty_assign_expr_list",
  "test", "assign_expr", "relop_expr", "relop_term", "relop_factor",
  "rel_op", "relop_expr_list", "nonempty_relop_expr_list", "expr",
  "add_op", "term", "mul_op", "factor", "var_ref", "dim_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292
};
# endif

#define YYPACT_NINF (-137)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-110)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     151,  -137,    25,  -137,  -137,   173,    62,   151,  -137,  -137,
      16,   151,  -137,  -137,  -137,    65,  -137,    82,    82,  -137,
    -137,   126,  -137,  -137,    63,   141,  -137,    38,   148,   150,
      41,    74,  -137,    97,   112,     8,   108,   115,  -137,   108,
     140,  -137,  -137,   120,   126,   128,     9,  -137,    11,    14,
     112,   146,   180,  -137,   147,   160,  -137,  -137,  -137,     8,
      75,   162,  -137,     8,    31,  -137,    38,    19,  -137,   112,
     169,   112,   112,   170,    57,  -137,   112,  -137,    68,  -137,
     112,  -137,    18,   112,   112,  -137,  -137,  -137,  -137,  -137,
    -137,  -137,  -137,   112,   112,  -137,  -137,   112,   100,     8,
       8,  -137,     8,     8,   103,   108,    64,   171,   172,   174,
      19,  -137,    85,   167,    19,   115,    71,  -137,   185,   176,
     166,   112,   116,   146,   175,   177,   112,   112,    27,   112,
      45,  -137,   180,  -137,   166,   160,  -137,  -137,   162,   162,
    -137,  -137,  -137,   112,   118,   118,   118,   179,  -137,    20,
    -137,    71,   132,  -137,   112,  -137,   122,  -137,  -137,   112,
     149,   178,  -137,   182,  -137,   183,    67,   184,  -137,   146,
     186,   168,   187,  -137,  -137,  -137,    21,  -137,   146,  -137,
    -137,  -137,   181,   112,    71,    71,   112,   118,  -137,  -137,
     146,   197,  -137,   188,  -137,    71,   118,  -137,   189,    71,
    -137
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,    34,     0,    32,    33,     0,     0,     2,     5,     7,
       0,     0,    26,    27,    28,     0,    10,     0,     0,     1,
       4,    12,     6,    25,    51,     0,    49,    35,     0,     0,
       0,    11,    14,     0,     0,     0,    52,     0,    31,    38,
       0,    30,    29,     0,     0,    15,   109,   100,     0,     0,
       0,    53,    73,    75,    77,    90,    94,   106,    47,     0,
       0,    43,    46,     0,    51,    50,    36,    24,    13,    20,
      16,     0,    86,   110,   109,   102,     0,   108,   109,   101,
       0,   107,     0,     0,     0,    79,    82,    83,    84,    80,
      81,    91,    92,     0,     0,    95,    96,     0,     0,     0,
       0,    39,     0,     0,     0,    37,    34,     0,     0,     0,
      24,    63,     0,     0,    23,     0,    22,    55,     0,     0,
      19,     0,     0,    88,     0,    85,     0,    86,     0,    86,
       0,    97,    74,    76,    78,    89,    93,    48,    41,    42,
      44,    45,    40,    86,     0,     0,    67,     0,    64,     0,
       8,    21,   109,    54,     0,    17,     0,   112,   103,     0,
       0,     0,    99,     0,    98,     0,   109,     0,    70,    72,
       0,     0,    66,    69,    56,    65,     0,    18,    87,   111,
     105,   104,     0,     0,     0,     0,    86,     0,    59,    62,
      71,    60,    57,     0,    68,     0,    67,    61,     0,     0,
      58
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -137,  -137,  -137,   200,   198,  -137,  -137,  -137,   190,  -137,
    -137,   107,   -61,    -8,  -137,  -137,     3,   203,   -14,   -40,
      92,    91,  -137,   191,   104,  -112,    28,  -137,    78,  -136,
     -34,   142,   143,  -137,  -122,  -137,   -60,  -137,   135,  -137,
     129,   -47,  -137
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    10,    30,    31,    32,    70,
     119,   113,    11,    12,    13,    14,    15,    28,    36,    60,
      61,    62,    25,    26,   116,   117,   171,   172,   167,   168,
     123,    52,    53,    93,   124,   125,    54,    94,    55,    97,
      56,    57,    73
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      51,    77,    81,    23,   153,   161,   114,   163,    18,   120,
     173,   122,    58,    39,    74,    75,    82,    78,    79,    98,
     118,   165,   106,   104,    33,     3,     4,   107,    16,   108,
     109,     5,    83,   134,    83,    83,    71,    59,    72,   153,
      76,    83,   128,    80,    34,    21,   130,    33,   131,   114,
     110,   194,   105,   111,   175,   188,   112,   162,    35,    83,
     173,   156,    19,   118,   193,    35,   160,   118,    24,   118,
     115,    43,   191,   192,   152,   164,    34,  -109,   149,   107,
     183,   108,   109,   197,    71,    27,   127,   200,    46,    47,
      35,    71,    -9,   143,    71,    71,    72,   129,    99,   100,
      45,    48,   110,   101,   118,   111,    23,    44,   112,    49,
     169,   169,   169,   115,    50,    46,    47,   115,    64,   148,
     176,   166,    47,    99,   100,   178,    99,   100,    48,     1,
     137,   142,     3,     4,    48,    63,    49,   118,   118,    91,
      92,    50,    49,    66,   157,    91,    92,    50,   118,   190,
     177,    67,   118,   169,     1,    69,     2,     3,     4,    71,
      83,   143,   169,     5,    85,    86,    87,    88,    89,    90,
      91,    92,    91,    92,    37,    38,     1,   179,    17,     3,
       4,    40,    41,    40,    42,    95,    96,   102,   103,    91,
      92,   138,   139,   140,   141,    84,   121,   126,   154,   150,
     144,   145,   186,   146,   155,   158,   195,    20,   180,    22,
     159,   174,   181,   182,   184,   189,   185,   147,   151,   199,
     187,    29,   196,   170,   198,   132,   136,   133,    65,   135,
       0,     0,     0,     0,    68
};

static const yytype_int16 yycheck[] =
{
      34,    48,    49,    11,   116,   127,    67,   129,     5,    69,
     146,    71,     4,    27,     3,     4,    50,     3,     4,    59,
      67,   143,     3,    63,    21,     6,     7,     8,     3,    10,
      11,    12,    14,    93,    14,    14,    27,    29,    29,   151,
      29,    14,    76,    29,    13,    29,    80,    44,    30,   110,
      31,   187,    66,    34,    34,    34,    37,    30,    27,    14,
     196,   121,     0,   110,   186,    27,   126,   114,     3,   116,
      67,    30,   184,   185,     3,    30,    13,    13,   112,     8,
      13,    10,    11,   195,    27,     3,    29,   199,     3,     4,
      27,    27,    29,    29,    27,    27,    29,    29,    23,    24,
       3,    16,    31,    28,   151,    34,   114,    33,    37,    24,
     144,   145,   146,   110,    29,     3,     4,   114,     3,    34,
     154,     3,     4,    23,    24,   159,    23,    24,    16,     3,
      30,    28,     6,     7,    16,    27,    24,   184,   185,    23,
      24,    29,    24,     3,    28,    23,    24,    29,   195,   183,
      28,    31,   199,   187,     3,    27,     5,     6,     7,    27,
      14,    29,   196,    12,    17,    18,    19,    20,    21,    22,
      23,    24,    23,    24,    33,    34,     3,    28,     5,     6,
       7,    33,    34,    33,    34,    25,    26,    25,    26,    23,
      24,    99,   100,   102,   103,    15,    27,    27,    13,    32,
      29,    29,    34,    29,    28,    30,     9,     7,    30,    11,
      33,    32,    30,    30,    30,    34,    30,   110,   114,    30,
      33,    18,    34,   145,   196,    83,    97,    84,    37,    94,
      -1,    -1,    -1,    -1,    44
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     5,     6,     7,    12,    39,    40,    41,    42,
      43,    50,    51,    52,    53,    54,     3,     5,    54,     0,
      41,    29,    42,    51,     3,    60,    61,     3,    55,    55,
      44,    45,    46,    54,    13,    27,    56,    33,    34,    56,
      33,    34,    34,    30,    33,     3,     3,     4,    16,    24,
      29,    68,    69,    70,    74,    76,    78,    79,     4,    29,
      57,    58,    59,    27,     3,    61,     3,    31,    46,    27,
      47,    27,    29,    80,     3,     4,    29,    79,     3,     4,
      29,    79,    68,    14,    15,    17,    18,    19,    20,    21,
      22,    23,    24,    71,    75,    25,    26,    77,    57,    23,
      24,    28,    25,    26,    57,    56,     3,     8,    10,    11,
      31,    34,    37,    49,    50,    54,    62,    63,    79,    48,
      74,    27,    74,    68,    72,    73,    27,    29,    68,    29,
      68,    30,    69,    70,    74,    76,    78,    30,    58,    58,
      59,    59,    28,    29,    29,    29,    29,    49,    34,    68,
      32,    62,     3,    63,    13,    28,    74,    28,    30,    33,
      74,    72,    30,    72,    30,    72,     3,    66,    67,    68,
      66,    64,    65,    67,    32,    34,    68,    28,    68,    28,
      30,    30,    30,    13,    30,    30,    34,    33,    34,    34,
      68,    63,    63,    72,    67,     9,    34,    63,    64,    30,
      63
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    38,    39,    39,    40,    40,    41,    41,    42,    43,
      43,    44,    44,    45,    45,    46,    46,    47,    47,    48,
      48,    49,    49,    49,    49,    50,    50,    51,    51,    52,
      52,    53,    54,    54,    54,    55,    55,    55,    55,    56,
      56,    57,    57,    57,    58,    58,    58,    59,    59,    60,
      60,    61,    61,    61,    62,    62,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    64,    64,    65,    65,
      66,    67,    67,    68,    68,    69,    69,    70,    70,    71,
      71,    71,    71,    71,    71,    72,    72,    73,    73,    74,
      74,    75,    75,    76,    76,    77,    77,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    79,
      79,    80,    80
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     2,     1,     7,     2,
       2,     1,     0,     3,     1,     2,     3,     3,     4,     1,
       0,     2,     1,     1,     0,     2,     1,     1,     1,     4,
       4,     3,     1,     1,     1,     1,     3,     4,     2,     3,
       4,     3,     3,     1,     3,     3,     1,     1,     3,     1,
       3,     1,     2,     3,     2,     1,     3,     5,     9,     4,
       5,     7,     5,     1,     2,     3,     1,     0,     3,     1,
       1,     3,     1,     1,     3,     1,     3,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     0,     3,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     3,     4,     4,
       1,     2,     2,     4,     5,     5,     1,     2,     2,     1,
       2,     4,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 2:
#line 168 "parser.y"
                                   { (yyval.node)=Allocate(PROGRAM_NODE);  makeChild((yyval.node),(yyvsp[0].node)); prog=(yyval.node);}
#line 1603 "parser.tab.c"
    break;

  case 3:
#line 169 "parser.y"
                  { (yyval.node)=Allocate(PROGRAM_NODE); prog=(yyval.node);}
#line 1609 "parser.tab.c"
    break;

  case 4:
#line 173 "parser.y"
                    {
                        (yyval.node) = makeSibling((yyvsp[-1].node), (yyvsp[0].node));
                    }
#line 1617 "parser.tab.c"
    break;

  case 5:
#line 177 "parser.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 1625 "parser.tab.c"
    break;

  case 6:
#line 183 "parser.y"
                {
                    (yyval.node) = makeSibling(makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[-1].node)), (yyvsp[0].node));
                }
#line 1633 "parser.tab.c"
    break;

  case 7:
#line 187 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1641 "parser.tab.c"
    break;

  case 8:
#line 193 "parser.y"
                    {
                        (yyval.node) = (yyvsp[-6].node);
                        makeChild((yyval.node), (yyvsp[-4].node));
                        makeChild((yyval.node), (yyvsp[-1].node));
                    }
#line 1651 "parser.tab.c"
    break;

  case 9:
#line 200 "parser.y"
                    {
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        makeFamily((yyval.node), 2, (yyvsp[-1].node), makeIDNode((yyvsp[0].lexeme), NORMAL_ID));
                    }
#line 1660 "parser.tab.c"
    break;

  case 10:
#line 205 "parser.y"
                    {
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* voidNode = makeIDNode("void", NORMAL_ID);
                        makeFamily((yyval.node), 2, voidNode, makeIDNode((yyvsp[0].lexeme), NORMAL_ID));
                    }
#line 1670 "parser.tab.c"
    break;

  case 11:
#line 212 "parser.y"
                    {
                        (yyval.node) = Allocate(PARAM_LIST_NODE);
                        makeChild((yyval.node), (yyvsp[0].node));
                    }
#line 1679 "parser.tab.c"
    break;

  case 12:
#line 217 "parser.y"
                    {
                        (yyval.node) = Allocate(PARAM_LIST_NODE);
                    }
#line 1687 "parser.tab.c"
    break;

  case 13:
#line 223 "parser.y"
                {
                    (yyval.node) = makeSibling((yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1695 "parser.tab.c"
    break;

  case 14:
#line 227 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1703 "parser.tab.c"
    break;

  case 15:
#line 233 "parser.y"
                {
                    (yyval.node) = makeDeclNode(FUNCTION_PARAMETER_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[-1].node), makeIDNode((yyvsp[0].lexeme), NORMAL_ID));
                }
#line 1712 "parser.tab.c"
    break;

  case 16:
#line 238 "parser.y"
                {
                    (yyval.node) = makeDeclNode(FUNCTION_PARAMETER_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), makeChild(makeIDNode((yyvsp[-1].lexeme), ARRAY_ID), (yyvsp[0].node)));
                }
#line 1721 "parser.tab.c"
    break;

  case 17:
#line 244 "parser.y"
                {
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 1729 "parser.tab.c"
    break;

  case 18:
#line 248 "parser.y"
                {
                    (yyval.node) = makeSibling((yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 1737 "parser.tab.c"
    break;

  case 19:
#line 254 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1745 "parser.tab.c"
    break;

  case 20:
#line 258 "parser.y"
                {
                    (yyval.node) = Allocate(NUL_NODE);
                }
#line 1753 "parser.tab.c"
    break;

  case 21:
#line 264 "parser.y"
                    {
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeFamily((yyval.node), 2, makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[-1].node)), makeChild(Allocate(STMT_LIST_NODE), (yyvsp[0].node)));
                    }
#line 1762 "parser.tab.c"
    break;

  case 22:
#line 269 "parser.y"
                    {
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeChild((yyval.node), makeChild(Allocate(STMT_LIST_NODE), (yyvsp[0].node)));
                    }
#line 1771 "parser.tab.c"
    break;

  case 23:
#line 274 "parser.y"
                    {
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeChild((yyval.node), makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[0].node)));
                    }
#line 1780 "parser.tab.c"
    break;

  case 24:
#line 278 "parser.y"
                    {
                        (yyval.node) = Allocate(BLOCK_NODE);
                    }
#line 1788 "parser.tab.c"
    break;

  case 25:
#line 284 "parser.y"
                {
                    (yyval.node) = makeSibling((yyvsp[-1].node), (yyvsp[0].node));
                }
#line 1796 "parser.tab.c"
    break;

  case 26:
#line 288 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1804 "parser.tab.c"
    break;

  case 27:
#line 294 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1812 "parser.tab.c"
    break;

  case 28:
#line 298 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1820 "parser.tab.c"
    break;

  case 29:
#line 304 "parser.y"
                {
                    (yyval.node) = makeDeclNode(TYPE_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[-1].node));
                }
#line 1829 "parser.tab.c"
    break;

  case 30:
#line 309 "parser.y"
                {
                    (yyval.node) = makeDeclNode(TYPE_DECL);
                    AST_NODE* voidNode = makeIDNode("void", NORMAL_ID);
                    makeFamily((yyval.node), 2, voidNode, (yyvsp[-1].node));
                }
#line 1839 "parser.tab.c"
    break;

  case 31:
#line 317 "parser.y"
                {
                    (yyval.node) = makeDeclNode(VARIABLE_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[-1].node));
                }
#line 1848 "parser.tab.c"
    break;

  case 32:
#line 324 "parser.y"
                {
                    (yyval.node) = makeIDNode("int", NORMAL_ID);
                }
#line 1856 "parser.tab.c"
    break;

  case 33:
#line 328 "parser.y"
                {
                    (yyval.node) = makeIDNode("float", NORMAL_ID);
                }
#line 1864 "parser.tab.c"
    break;

  case 34:
#line 332 "parser.y"
                {
                    (yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID); 
                }
#line 1872 "parser.tab.c"
    break;

  case 35:
#line 338 "parser.y"
                {
                    (yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID);
                }
#line 1880 "parser.tab.c"
    break;

  case 36:
#line 342 "parser.y"
                {
                    (yyval.node) = makeSibling((yyvsp[-2].node), makeIDNode((yyvsp[0].lexeme), NORMAL_ID));
                }
#line 1888 "parser.tab.c"
    break;

  case 37:
#line 346 "parser.y"
                {
                    (yyval.node) = makeSibling((yyvsp[-3].node), makeChild(makeIDNode((yyvsp[-1].lexeme), ARRAY_ID), (yyvsp[0].node)));
                }
#line 1896 "parser.tab.c"
    break;

  case 38:
#line 350 "parser.y"
                {
                    (yyval.node) = makeChild(makeIDNode((yyvsp[-1].lexeme), ARRAY_ID), (yyvsp[0].node));
                }
#line 1904 "parser.tab.c"
    break;

  case 39:
#line 355 "parser.y"
                {
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 1912 "parser.tab.c"
    break;

  case 40:
#line 359 "parser.y"
                {
                    (yyval.node) = makeSibling((yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 1920 "parser.tab.c"
    break;

  case 41:
#line 364 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_ADD);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1929 "parser.tab.c"
    break;

  case 42:
#line 369 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_SUB);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1938 "parser.tab.c"
    break;

  case 43:
#line 374 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1946 "parser.tab.c"
    break;

  case 44:
#line 379 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_MUL);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1955 "parser.tab.c"
    break;

  case 45:
#line 384 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_DIV);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 1964 "parser.tab.c"
    break;

  case 46:
#line 389 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 1972 "parser.tab.c"
    break;

  case 47:
#line 395 "parser.y"
                {
                    (yyval.node) = Allocate(CONST_VALUE_NODE);
                    (yyval.node)->semantic_value.const1 = (yyvsp[0].const1);
                }
#line 1981 "parser.tab.c"
    break;

  case 48:
#line 400 "parser.y"
                {
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 1989 "parser.tab.c"
    break;

  case 49:
#line 406 "parser.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 1997 "parser.tab.c"
    break;

  case 50:
#line 410 "parser.y"
                    {
                        (yyval.node) = makeSibling((yyvsp[-2].node), (yyvsp[0].node));
                    }
#line 2005 "parser.tab.c"
    break;

  case 51:
#line 416 "parser.y"
                {
                    (yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID);
                }
#line 2013 "parser.tab.c"
    break;

  case 52:
#line 420 "parser.y"
                {
                    (yyval.node) = makeChild(makeIDNode((yyvsp[-1].lexeme), ARRAY_ID), (yyvsp[0].node));
                }
#line 2021 "parser.tab.c"
    break;

  case 53:
#line 424 "parser.y"
                {
                    (yyval.node) = makeChild(makeIDNode((yyvsp[-2].lexeme), WITH_INIT_ID), (yyvsp[0].node));
                }
#line 2029 "parser.tab.c"
    break;

  case 54:
#line 430 "parser.y"
                {
                    (yyval.node) = makeSibling((yyvsp[-1].node), (yyvsp[0].node));
                }
#line 2037 "parser.tab.c"
    break;

  case 55:
#line 434 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2045 "parser.tab.c"
    break;

  case 56:
#line 442 "parser.y"
                {
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 2053 "parser.tab.c"
    break;

  case 57:
#line 446 "parser.y"
                {
                    (yyval.node) = makeStmtNode(WHILE_STMT);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2062 "parser.tab.c"
    break;

  case 58:
#line 451 "parser.y"
                {
                    (yyval.node) = makeStmtNode(FOR_STMT);
                    makeFamily((yyval.node), 4, (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2071 "parser.tab.c"
    break;

  case 59:
#line 456 "parser.y"
                {
                    (yyval.node) = makeStmtNode(ASSIGN_STMT);
                    makeFamily((yyval.node), 2, (yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 2080 "parser.tab.c"
    break;

  case 60:
#line 461 "parser.y"
                {
                    (yyval.node) = makeStmtNode(IF_STMT);
                    makeFamily((yyval.node), 3, (yyvsp[-2].node), (yyvsp[0].node), Allocate(NUL_NODE));
                }
#line 2089 "parser.tab.c"
    break;

  case 61:
#line 466 "parser.y"
                {
                    (yyval.node) = makeStmtNode(IF_STMT);
                    makeFamily((yyval.node), 3, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2098 "parser.tab.c"
    break;

  case 62:
#line 471 "parser.y"
                {
                    (yyval.node) = makeStmtNode(FUNCTION_CALL_STMT);
                    makeFamily((yyval.node), 2, makeIDNode((yyvsp[-4].lexeme), NORMAL_ID), (yyvsp[-2].node));
                }
#line 2107 "parser.tab.c"
    break;

  case 63:
#line 476 "parser.y"
                {
                    (yyval.node) = Allocate(NUL_NODE);
                }
#line 2115 "parser.tab.c"
    break;

  case 64:
#line 480 "parser.y"
                {
                    (yyval.node) = makeStmtNode(RETURN_STMT);
                    makeChild((yyval.node), Allocate(NUL_NODE));
                }
#line 2124 "parser.tab.c"
    break;

  case 65:
#line 485 "parser.y"
                {
                    (yyval.node) = makeStmtNode(RETURN_STMT);
                    makeChild((yyval.node), (yyvsp[-1].node));
                }
#line 2133 "parser.tab.c"
    break;

  case 66:
#line 492 "parser.y"
                     {
                        (yyval.node) = makeChild(Allocate(NONEMPTY_ASSIGN_EXPR_LIST_NODE), (yyvsp[0].node));
                     }
#line 2141 "parser.tab.c"
    break;

  case 67:
#line 496 "parser.y"
                     {
                         (yyval.node) = Allocate(NUL_NODE);
                     }
#line 2149 "parser.tab.c"
    break;

  case 68:
#line 502 "parser.y"
                                    {
                                        (yyval.node) = makeSibling((yyvsp[-2].node), (yyvsp[0].node));
                                    }
#line 2157 "parser.tab.c"
    break;

  case 69:
#line 506 "parser.y"
                                    {
                                        (yyval.node) = (yyvsp[0].node);
                                    }
#line 2165 "parser.tab.c"
    break;

  case 70:
#line 512 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2173 "parser.tab.c"
    break;

  case 71:
#line 518 "parser.y"
                    {
                        //TODO: for simpler implementation, use ASSIGN_STMT for now
                        (yyval.node) = makeStmtNode(ASSIGN_STMT);
                        makeFamily((yyval.node), 2, makeIDNode((yyvsp[-2].lexeme), NORMAL_ID), (yyvsp[0].node));
                    }
#line 2183 "parser.tab.c"
    break;

  case 72:
#line 524 "parser.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 2191 "parser.tab.c"
    break;

  case 73:
#line 530 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2199 "parser.tab.c"
    break;

  case 74:
#line 534 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_OR);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2208 "parser.tab.c"
    break;

  case 75:
#line 541 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2216 "parser.tab.c"
    break;

  case 76:
#line 545 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_AND);
                    makeFamily((yyval.node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2225 "parser.tab.c"
    break;

  case 77:
#line 552 "parser.y"
                    {
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 2233 "parser.tab.c"
    break;

  case 78:
#line 556 "parser.y"
                    {
                        (yyval.node) = makeFamily((yyvsp[-1].node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                    }
#line 2241 "parser.tab.c"
    break;

  case 79:
#line 562 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_EQ);
                }
#line 2249 "parser.tab.c"
    break;

  case 80:
#line 566 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_GE);
                }
#line 2257 "parser.tab.c"
    break;

  case 81:
#line 570 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_LE);
                }
#line 2265 "parser.tab.c"
    break;

  case 82:
#line 574 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_NE);
                }
#line 2273 "parser.tab.c"
    break;

  case 83:
#line 578 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_GT);
                }
#line 2281 "parser.tab.c"
    break;

  case 84:
#line 582 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_LT);
                }
#line 2289 "parser.tab.c"
    break;

  case 85:
#line 589 "parser.y"
                    {
                        (yyval.node) = makeChild(Allocate(NONEMPTY_RELOP_EXPR_LIST_NODE), (yyvsp[0].node));
                    }
#line 2297 "parser.tab.c"
    break;

  case 86:
#line 593 "parser.y"
                    {
                        (yyval.node) = Allocate(NUL_NODE);
                    }
#line 2305 "parser.tab.c"
    break;

  case 87:
#line 599 "parser.y"
                                {
                                    (yyval.node) = makeSibling((yyvsp[-2].node), (yyvsp[0].node));
                                }
#line 2313 "parser.tab.c"
    break;

  case 88:
#line 603 "parser.y"
                                {
                                    (yyval.node) = (yyvsp[0].node);
                                }
#line 2321 "parser.tab.c"
    break;

  case 89:
#line 609 "parser.y"
                {
                    (yyval.node) = makeFamily((yyvsp[-1].node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2329 "parser.tab.c"
    break;

  case 90:
#line 613 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2337 "parser.tab.c"
    break;

  case 91:
#line 619 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_ADD);
                }
#line 2345 "parser.tab.c"
    break;

  case 92:
#line 623 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_SUB);
                }
#line 2353 "parser.tab.c"
    break;

  case 93:
#line 629 "parser.y"
                {
                    (yyval.node) = makeFamily((yyvsp[-1].node), 2, (yyvsp[-2].node), (yyvsp[0].node));
                }
#line 2361 "parser.tab.c"
    break;

  case 94:
#line 633 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2369 "parser.tab.c"
    break;

  case 95:
#line 639 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_MUL);
                }
#line 2377 "parser.tab.c"
    break;

  case 96:
#line 643 "parser.y"
                {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_DIV);
                }
#line 2385 "parser.tab.c"
    break;

  case 97:
#line 649 "parser.y"
                {
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 2393 "parser.tab.c"
    break;

  case 98:
#line 653 "parser.y"
                {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE);
                    makeChild((yyval.node), (yyvsp[-1].node));
                }
#line 2402 "parser.tab.c"
    break;

  case 99:
#line 658 "parser.y"
                {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION);
                    makeChild((yyval.node), (yyvsp[-1].node));
                }
#line 2411 "parser.tab.c"
    break;

  case 100:
#line 663 "parser.y"
                {
                    (yyval.node) = Allocate(CONST_VALUE_NODE);
                    (yyval.node)->semantic_value.const1=(yyvsp[0].const1);
                }
#line 2420 "parser.tab.c"
    break;

  case 101:
#line 668 "parser.y"
                {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE);
                    AST_NODE *constNode = Allocate(CONST_VALUE_NODE);
                    constNode->semantic_value.const1 = (yyvsp[0].const1);
                    makeChild((yyval.node), constNode);
                }
#line 2431 "parser.tab.c"
    break;

  case 102:
#line 675 "parser.y"
                {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION);
                    AST_NODE *constNode = Allocate(CONST_VALUE_NODE);
                    constNode->semantic_value.const1 = (yyvsp[0].const1);
                    makeChild((yyval.node), constNode);
                }
#line 2442 "parser.tab.c"
    break;

  case 103:
#line 682 "parser.y"
                {
                    (yyval.node) = makeStmtNode(FUNCTION_CALL_STMT);
                    makeFamily((yyval.node), 2, makeIDNode((yyvsp[-3].lexeme), NORMAL_ID), (yyvsp[-1].node));
                }
#line 2451 "parser.tab.c"
    break;

  case 104:
#line 687 "parser.y"
                {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE);
                    AST_NODE* functionCallNode = makeStmtNode(FUNCTION_CALL_STMT);
                    makeFamily(functionCallNode, 2, makeIDNode((yyvsp[-3].lexeme), NORMAL_ID), (yyvsp[-1].node));
                    makeChild((yyval.node), functionCallNode);
                }
#line 2462 "parser.tab.c"
    break;

  case 105:
#line 694 "parser.y"
                {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION);
                    AST_NODE* functionCallNode = makeStmtNode(FUNCTION_CALL_STMT);
                    makeFamily(functionCallNode, 2, makeIDNode((yyvsp[-3].lexeme), NORMAL_ID), (yyvsp[-1].node));
                    makeChild((yyval.node), functionCallNode);
                }
#line 2473 "parser.tab.c"
    break;

  case 106:
#line 701 "parser.y"
                {
                    (yyval.node) = (yyvsp[0].node);
                }
#line 2481 "parser.tab.c"
    break;

  case 107:
#line 705 "parser.y"
                {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE);
                    makeChild((yyval.node), (yyvsp[0].node));
                }
#line 2490 "parser.tab.c"
    break;

  case 108:
#line 710 "parser.y"
                {
                    (yyval.node) = makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION);
                    makeChild((yyval.node), (yyvsp[0].node));
                }
#line 2499 "parser.tab.c"
    break;

  case 109:
#line 717 "parser.y"
                {
                    (yyval.node) = makeIDNode((yyvsp[0].lexeme), NORMAL_ID);
                }
#line 2507 "parser.tab.c"
    break;

  case 110:
#line 721 "parser.y"
                {
                    (yyval.node) = makeIDNode((yyvsp[-1].lexeme), ARRAY_ID);
                    makeChild((yyval.node),(yyvsp[0].node));
                }
#line 2516 "parser.tab.c"
    break;

  case 111:
#line 729 "parser.y"
                {
                    (yyval.node) = makeSibling((yyvsp[-3].node), (yyvsp[-1].node));
                }
#line 2524 "parser.tab.c"
    break;

  case 112:
#line 733 "parser.y"
                {
                    (yyval.node) = (yyvsp[-1].node);
                }
#line 2532 "parser.tab.c"
    break;


#line 2536 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 739 "parser.y"


#include "lex.yy.c"
#include "codegen.h"
main (argc, argv)
int argc;
char *argv[];
  {
     yyin = fopen(argv[1],"r");
     yyparse();
     // printGV(prog, NULL);

     initializeSymbolTable();

     semanticAnalysis(prog);

     symbolTableEnd();
     if (!g_anyErrorOccur) {
        printf("Parsing completed. No errors found.\n");
        CodegenProgramNode(prog);
     }
  } /* main */


int yyerror (mesg)
char *mesg;
  {
  printf("%s\t%d\t%s\t%s\n", "Error found in Line ", linenumber, "next token: ", yytext );
  exit(1);
  }
