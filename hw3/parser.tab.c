/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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
/* Tokens.  */
#define ID 258
#define CONST 259
#define VOID 260
#define INT 261
#define FLOAT 262
#define IF 263
#define ELSE 264
#define WHILE 265
#define FOR 266
#define TYPEDEF 267
#define OP_ASSIGN 268
#define OP_OR 269
#define OP_AND 270
#define OP_NOT 271
#define OP_EQ 272
#define OP_NE 273
#define OP_GT 274
#define OP_LT 275
#define OP_GE 276
#define OP_LE 277
#define OP_PLUS 278
#define OP_MINUS 279
#define OP_TIMES 280
#define OP_DIVIDE 281
#define MK_LB 282
#define MK_RB 283
#define MK_LPAREN 284
#define MK_RPAREN 285
#define MK_LBRACE 286
#define MK_RBRACE 287
#define MK_COMMA 288
#define MK_SEMICOLON 289
#define MK_DOT 290
#define ERROR 291
#define RETURN 292




/* Copy the first part of user declarations.  */
#line 4 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "header.h"

int linenumber = 1;
AST_NODE *prog;

extern int g_anyErrorOccur;
extern void printGV(AST_NODE *root, char* fileName);

int yylex();
int yyerror(char *mesg);

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



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 117 "parser.y"
{
	char *lexeme;
	CON_Type  *const1;
	AST_NODE  *node;
}
/* Line 193 of yacc.c.  */
#line 287 "parser.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 300 "parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  22
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   283

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  115
/* YYNRULES -- Number of states.  */
#define YYNSTATES  231

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    11,    14,    16,    25,
      34,    43,    51,    59,    67,    71,    73,    76,    79,    83,
      87,    91,    96,    98,    99,   102,   104,   106,   107,   110,
     112,   114,   116,   121,   126,   131,   135,   139,   141,   143,
     145,   149,   154,   157,   161,   166,   170,   174,   176,   180,
     184,   186,   188,   192,   194,   198,   200,   203,   207,   210,
     212,   216,   222,   232,   237,   243,   251,   257,   259,   262,
     266,   268,   269,   273,   275,   279,   281,   283,   287,   289,
     293,   295,   299,   301,   303,   305,   307,   309,   311,   313,
     314,   318,   320,   324,   326,   328,   330,   334,   336,   338,
     340,   344,   349,   354,   356,   359,   362,   367,   373,   379,
     381,   384,   387,   389,   392,   397
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      39,     0,    -1,    40,    -1,    -1,    40,    41,    -1,    41,
      -1,    48,    42,    -1,    42,    -1,    52,     3,    29,    43,
      30,    31,    47,    32,    -1,     3,     3,    29,    43,    30,
      31,    47,    32,    -1,     5,     3,    29,    43,    30,    31,
      47,    32,    -1,    52,     3,    29,    30,    31,    47,    32,
      -1,     3,     3,    29,    30,    31,    47,    32,    -1,     5,
       3,    29,    30,    31,    47,    32,    -1,    43,    33,    44,
      -1,    44,    -1,    52,     3,    -1,     3,     3,    -1,    52,
       3,    45,    -1,     3,     3,    45,    -1,    27,    46,    28,
      -1,    45,    27,    71,    28,    -1,    71,    -1,    -1,    48,
      60,    -1,    60,    -1,    48,    -1,    -1,    48,    49,    -1,
      49,    -1,    50,    -1,    51,    -1,    12,    52,    53,    34,
      -1,    12,     3,    53,    34,    -1,    12,     5,    53,    34,
      -1,    52,    58,    34,    -1,     3,    58,    34,    -1,     6,
      -1,     7,    -1,     3,    -1,    53,    33,     3,    -1,    53,
      33,     3,    54,    -1,     3,    54,    -1,    27,    55,    28,
      -1,    54,    27,    55,    28,    -1,    55,    23,    56,    -1,
      55,    24,    56,    -1,    56,    -1,    56,    25,    57,    -1,
      56,    26,    57,    -1,    57,    -1,     4,    -1,    29,    55,
      30,    -1,    59,    -1,    58,    33,    59,    -1,     3,    -1,
       3,    54,    -1,     3,    13,    65,    -1,    60,    61,    -1,
      61,    -1,    31,    47,    32,    -1,    10,    29,    70,    30,
      61,    -1,    11,    29,    62,    34,    69,    34,    62,    30,
      61,    -1,    76,    13,    65,    34,    -1,     8,    29,    70,
      30,    61,    -1,     8,    29,    70,    30,    61,     9,    61,
      -1,     3,    29,    69,    30,    34,    -1,    34,    -1,    37,
      34,    -1,    37,    65,    34,    -1,    63,    -1,    -1,    63,
      33,    64,    -1,    64,    -1,     3,    13,    65,    -1,    65,
      -1,    66,    -1,    65,    14,    66,    -1,    67,    -1,    66,
      15,    67,    -1,    71,    -1,    71,    68,    71,    -1,    17,
      -1,    21,    -1,    22,    -1,    18,    -1,    19,    -1,    20,
      -1,    70,    -1,    -1,    70,    33,    65,    -1,    65,    -1,
      71,    72,    73,    -1,    73,    -1,    23,    -1,    24,    -1,
      73,    74,    75,    -1,    75,    -1,    25,    -1,    26,    -1,
      29,    65,    30,    -1,    24,    29,    65,    30,    -1,    16,
      29,    65,    30,    -1,     4,    -1,    24,     4,    -1,    16,
       4,    -1,     3,    29,    69,    30,    -1,    24,     3,    29,
      69,    30,    -1,    16,     3,    29,    69,    30,    -1,    76,
      -1,    24,    76,    -1,    16,    76,    -1,     3,    -1,     3,
      77,    -1,    77,    27,    71,    28,    -1,    27,    71,    28,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   171,   171,   172,   175,   179,   185,   189,   195,   202,
     210,   218,   224,   231,   240,   244,   251,   256,   262,   268,
     275,   279,   285,   291,   296,   303,   308,   313,   319,   324,
     331,   335,   341,   347,   353,   361,   367,   376,   380,   386,
     390,   395,   400,   406,   412,   417,   422,   428,   434,   440,
     446,   453,   460,   467,   472,   479,   483,   488,   495,   500,
     509,   515,   520,   526,   533,   539,   545,   550,   555,   560,
     567,   573,   578,   583,   596,   602,   609,   613,   620,   625,
     633,   638,   645,   650,   655,   660,   665,   670,   678,   684,
     689,   694,   701,   706,   713,   717,   723,   728,   735,   740,
     747,   753,   757,   762,   768,   774,   781,   788,   794,   801,
     807,   811,   818,   823,   831,   836
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
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
  "global_decl_list", "global_decl", "function_decl", "param_list",
  "param", "dim_fn", "expr_null", "block", "decl_list", "decl",
  "type_decl", "var_decl", "type", "id_list", "dim_decl", "cexpr",
  "mcexpr", "cfactor", "init_id_list", "init_id", "stmt_list", "stmt",
  "assign_expr_list", "nonempty_assign_expr_list", "assign_expr",
  "relop_expr", "relop_term", "relop_factor", "rel_op", "relop_expr_list",
  "nonempty_relop_expr_list", "expr", "add_op", "term", "mul_op", "factor",
  "var_ref", "dim_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    39,    40,    40,    41,    41,    42,    42,
      42,    42,    42,    42,    43,    43,    44,    44,    44,    44,
      45,    45,    46,    46,    47,    47,    47,    47,    48,    48,
      49,    49,    50,    50,    50,    51,    51,    52,    52,    53,
      53,    53,    53,    54,    54,    55,    55,    55,    56,    56,
      56,    57,    57,    58,    58,    59,    59,    59,    60,    60,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      62,    62,    63,    63,    64,    64,    65,    65,    66,    66,
      67,    67,    68,    68,    68,    68,    68,    68,    69,    69,
      70,    70,    71,    71,    72,    72,    73,    73,    74,    74,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    76,    76,    77,    77
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     2,     1,     8,     8,
       8,     7,     7,     7,     3,     1,     2,     2,     3,     3,
       3,     4,     1,     0,     2,     1,     1,     0,     2,     1,
       1,     1,     4,     4,     4,     3,     3,     1,     1,     1,
       3,     4,     2,     3,     4,     3,     3,     1,     3,     3,
       1,     1,     3,     1,     3,     1,     2,     3,     2,     1,
       3,     5,     9,     4,     5,     7,     5,     1,     2,     3,
       1,     0,     3,     1,     3,     1,     1,     3,     1,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     0,
       3,     1,     3,     1,     1,     1,     3,     1,     1,     1,
       3,     4,     4,     1,     2,     2,     4,     5,     5,     1,
       2,     2,     1,     2,     4,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,    37,    38,     0,     0,     2,     5,     7,
       0,    29,    30,    31,     0,    55,     0,    53,     0,     0,
       0,     0,     1,     4,     6,    28,    55,     0,     0,     0,
       0,    56,     0,    36,     0,    39,     0,     0,     0,     0,
      35,   112,   103,     0,     0,     0,    57,    76,    78,    80,
      93,    97,   109,    51,     0,     0,    47,    50,     0,     0,
       0,    15,     0,     0,    55,    54,     0,     0,    42,     0,
      33,    34,    32,     0,     0,     0,    89,   113,   112,   105,
       0,   111,   112,   104,     0,   110,     0,     0,     0,    82,
      85,    86,    87,    83,    84,    94,    95,     0,     0,    98,
      99,     0,     0,     0,     0,    43,     0,     0,    17,    27,
       0,     0,    16,     0,    27,     0,    40,    27,     0,     0,
      91,     0,    88,     0,    89,     0,    89,     0,   100,    77,
      79,    81,    92,    96,    52,    45,    46,    48,    49,    23,
      19,   112,     0,     0,     0,    27,    67,     0,     0,    26,
       0,    25,    59,     0,    27,    14,    18,    44,     0,    27,
      41,     0,    27,   115,   106,     0,     0,     0,   102,     0,
     101,     0,    22,     0,    89,     0,     0,    71,     0,    68,
       0,    12,    24,   112,    58,     0,     0,    13,     0,    11,
       0,    90,   114,   108,   107,    20,     0,     0,     0,     0,
     112,     0,    70,    73,    75,    60,    69,     0,     9,    10,
       8,    21,     0,     0,     0,     0,    89,     0,    63,    66,
      64,    61,    74,     0,    72,     0,    71,    65,     0,     0,
      62
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    60,    61,   140,   171,   148,
     149,    11,    12,    13,   150,    36,    31,    55,    56,    57,
      16,    17,   151,   152,   201,   202,   203,   120,    47,    48,
      97,   121,   122,    49,    98,    50,   101,    51,    52,    77
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -136
static const yytype_int16 yypact[] =
{
     153,    19,    23,  -136,  -136,   197,     7,   153,  -136,  -136,
     153,  -136,  -136,  -136,    36,   103,    47,  -136,    63,    69,
      69,    69,  -136,  -136,  -136,  -136,   118,   130,    83,    62,
      18,    87,   141,  -136,    58,   107,   136,   149,   191,    68,
    -136,   189,  -136,    33,    38,    83,   139,   178,  -136,   157,
     201,  -136,  -136,  -136,    62,    78,   203,  -136,   198,   166,
     105,  -136,   210,    62,    57,  -136,   175,   113,    87,   237,
    -136,  -136,  -136,   211,   177,    83,    83,   214,   190,  -136,
      83,  -136,   193,  -136,    83,  -136,    75,    83,    83,  -136,
    -136,  -136,  -136,  -136,  -136,  -136,  -136,    83,    83,  -136,
    -136,    83,   138,    62,    62,  -136,    62,    62,   216,   117,
     213,   202,   216,   143,   117,   215,   107,   117,   217,   162,
     139,   219,   218,    83,    83,    81,    83,   125,  -136,   178,
    -136,   207,   201,  -136,  -136,   203,   203,  -136,  -136,    83,
     220,    56,   221,   223,   224,   117,  -136,    16,   222,   117,
     141,    20,  -136,   232,   117,  -136,   220,  -136,   225,   117,
      87,   226,   117,  -136,  -136,    83,   168,   229,  -136,   230,
    -136,   227,   207,    83,    83,    83,    83,    93,   231,  -136,
      -1,  -136,    20,   194,  -136,    83,   233,  -136,   234,  -136,
     235,   139,  -136,  -136,  -136,  -136,   171,   238,   181,   182,
     123,   228,   236,  -136,   139,  -136,  -136,    15,  -136,  -136,
    -136,  -136,   239,    20,    20,    83,    83,    93,  -136,  -136,
     247,  -136,   139,   240,  -136,    20,    93,  -136,   241,    20,
    -136
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -136,  -136,  -136,   254,   260,    43,   161,   152,  -136,   -99,
     126,    -9,  -136,  -136,     4,   212,   -23,   -19,   131,   132,
      -8,   243,   127,  -135,    51,  -136,    64,   -28,   192,   195,
    -136,  -116,    61,   -70,  -136,   180,  -136,   179,   -41,  -136
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      46,    25,    81,    85,    14,   119,    27,    22,   167,    21,
     169,    14,    68,    87,    14,   158,   184,    86,   161,    41,
      42,    58,    15,   183,     3,     4,    18,   131,   142,    87,
     143,   144,    43,   206,    62,   102,    78,    79,    62,    26,
      44,    82,    83,    62,   113,    45,   178,   184,    59,   218,
     179,   145,   125,   166,   146,   186,   127,   147,   197,    64,
     188,    58,    80,   190,     3,     4,    53,    84,   153,   172,
      28,    58,    35,   153,     3,     4,   153,    67,   220,   221,
      32,    33,    74,    75,    29,   174,    41,    42,    66,    87,
     227,    54,    34,   160,   230,    87,   200,    42,    73,    43,
     223,   103,   104,   196,   153,   128,   105,    44,   153,    43,
     153,   168,    45,   153,    63,    62,    28,    44,   153,   180,
     141,   153,    45,     3,     4,   142,    10,   143,   144,     5,
      29,    28,    30,    10,    29,   110,   215,   191,   111,    87,
      25,   153,    27,   115,    64,    29,   111,    39,   145,   204,
      75,   146,    76,    87,   147,   170,     1,   207,     2,     3,
       4,   103,   104,    32,    40,     5,   103,   104,   134,    69,
      70,   157,   153,   153,    89,    90,    91,    92,    93,    94,
      95,    96,    69,    71,   153,    95,    96,   222,   153,   204,
     163,    95,    96,    88,    95,    96,   192,   109,   204,   211,
      19,   108,    20,     3,     4,    58,   114,   118,     3,     4,
     111,   213,   214,   112,   165,   165,    75,    75,    76,   124,
      75,    75,   126,   174,    69,    72,    99,   100,   106,   107,
      95,    96,    37,    38,   135,   136,   198,   199,   137,   138,
     116,   123,   117,   139,   154,   185,   159,   173,   162,   164,
     175,   165,   176,   177,   181,   195,   225,   187,   189,   193,
     194,    23,   216,   205,   156,   208,   209,   210,   212,   217,
      24,   229,   155,   219,   226,    65,   182,   228,   132,   129,
     133,   224,     0,   130
};

static const yytype_int16 yycheck[] =
{
      28,    10,    43,    44,     0,    75,    14,     0,   124,     5,
     126,     7,    35,    14,    10,   114,   151,    45,   117,     3,
       4,     3,     3,     3,     6,     7,     3,    97,     8,    14,
      10,    11,    16,    34,    30,    54,     3,     4,    34,     3,
      24,     3,     4,    39,    63,    29,   145,   182,    30,    34,
      34,    31,    80,   123,    34,   154,    84,    37,   174,     3,
     159,     3,    29,   162,     6,     7,     4,    29,   109,   139,
      13,     3,     3,   114,     6,     7,   117,    34,   213,   214,
      33,    34,    39,    27,    27,    29,     3,     4,    30,    14,
     225,    29,    29,   116,   229,    14,     3,     4,    30,    16,
     216,    23,    24,   173,   145,    30,    28,    24,   149,    16,
     151,    30,    29,   154,    27,   111,    13,    24,   159,   147,
       3,   162,    29,     6,     7,     8,     0,    10,    11,    12,
      27,    13,    29,     7,    27,    30,    13,   165,    33,    14,
     149,   182,   150,    30,     3,    27,    33,    29,    31,   177,
      27,    34,    29,    14,    37,    30,     3,   185,     5,     6,
       7,    23,    24,    33,    34,    12,    23,    24,    30,    33,
      34,    28,   213,   214,    17,    18,    19,    20,    21,    22,
      23,    24,    33,    34,   225,    23,    24,   215,   229,   217,
      28,    23,    24,    15,    23,    24,    28,    31,   226,    28,
       3,     3,     5,     6,     7,     3,    31,    30,     6,     7,
      33,    30,    30,     3,    33,    33,    27,    27,    29,    29,
      27,    27,    29,    29,    33,    34,    25,    26,    25,    26,
      23,    24,    20,    21,   103,   104,   175,   176,   106,   107,
       3,    27,    31,    27,    31,    13,    31,    27,    31,    30,
      29,    33,    29,    29,    32,    28,     9,    32,    32,    30,
      30,     7,    34,    32,   112,    32,    32,    32,    30,    33,
      10,    30,   111,    34,    34,    32,   149,   226,    98,    87,
     101,   217,    -1,    88
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     6,     7,    12,    39,    40,    41,    42,
      48,    49,    50,    51,    52,     3,    58,    59,     3,     3,
       5,    52,     0,    41,    42,    49,     3,    58,    13,    27,
      29,    54,    33,    34,    29,     3,    53,    53,    53,    29,
      34,     3,     4,    16,    24,    29,    65,    66,    67,    71,
      73,    75,    76,     4,    29,    55,    56,    57,     3,    30,
      43,    44,    52,    27,     3,    59,    30,    43,    54,    33,
      34,    34,    34,    30,    43,    27,    29,    77,     3,     4,
      29,    76,     3,     4,    29,    76,    65,    14,    15,    17,
      18,    19,    20,    21,    22,    23,    24,    68,    72,    25,
      26,    74,    55,    23,    24,    28,    25,    26,     3,    31,
      30,    33,     3,    55,    31,    30,     3,    31,    30,    71,
      65,    69,    70,    27,    29,    65,    29,    65,    30,    66,
      67,    71,    73,    75,    30,    56,    56,    57,    57,    27,
      45,     3,     8,    10,    11,    31,    34,    37,    47,    48,
      52,    60,    61,    76,    31,    44,    45,    28,    47,    31,
      54,    47,    31,    28,    30,    33,    71,    69,    30,    69,
      30,    46,    71,    27,    29,    29,    29,    29,    47,    34,
      65,    32,    60,     3,    61,    13,    47,    32,    47,    32,
      47,    65,    28,    30,    30,    28,    71,    69,    70,    70,
       3,    62,    63,    64,    65,    32,    34,    65,    32,    32,
      32,    28,    30,    30,    30,    13,    34,    33,    34,    34,
      61,    61,    65,    69,    64,     9,    34,    61,    62,    30,
      61
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

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
#line 171 "parser.y"
    { (yyval.node)=Allocate(PROGRAM_NODE); makeChild((yyval.node),(yyvsp[(1) - (1)].node)); prog=(yyval.node);;}
    break;

  case 3:
#line 172 "parser.y"
    { (yyval.node)=Allocate(PROGRAM_NODE); prog=(yyval.node);;}
    break;

  case 4:
#line 176 "parser.y"
    {
                        (yyval.node) = makeSibling((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
                    ;}
    break;

  case 5:
#line 180 "parser.y"
    {
                        (yyval.node) = (yyvsp[(1) - (1)].node);
                    ;}
    break;

  case 6:
#line 186 "parser.y"
    {
                    (yyval.node) = makeSibling(makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[(1) - (2)].node)), (yyvsp[(2) - (2)].node));
                ;}
    break;

  case 7:
#line 190 "parser.y"
    {
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                ;}
    break;

  case 8:
#line 196 "parser.y"
    {
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* parameterList = Allocate(PARAM_LIST_NODE);
                        makeChild(parameterList, (yyvsp[(4) - (8)].node));
                        makeFamily((yyval.node), 4, (yyvsp[(1) - (8)].node), makeIDNode((yyvsp[(2) - (8)].lexeme), NORMAL_ID), parameterList, (yyvsp[(7) - (8)].node));
                    ;}
    break;

  case 9:
#line 203 "parser.y"
    {
                        /*TODO*/
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* parameterList = Allocate(PARAM_LIST_NODE);
                        makeChild(parameterList, (yyvsp[(4) - (8)].node));
                        makeFamily((yyval.node), 4, makeIDNode((yyvsp[(1) - (8)].lexeme), NORMAL_ID), makeIDNode((yyvsp[(2) - (8)].lexeme), NORMAL_ID), parameterList, (yyvsp[(7) - (8)].node));
                    ;}
    break;

  case 10:
#line 211 "parser.y"
    {
                        /*TODO*/
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* parameterList = Allocate(PARAM_LIST_NODE);
                        makeChild(parameterList, (yyvsp[(4) - (8)].node));
                        makeFamily((yyval.node), 4, makeIDNode("void", NORMAL_ID), makeIDNode((yyvsp[(2) - (8)].lexeme), NORMAL_ID), parameterList, (yyvsp[(7) - (8)].node));
                    ;}
    break;

  case 11:
#line 219 "parser.y"
    {
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* emptyParameterList = Allocate(PARAM_LIST_NODE);
                        makeFamily((yyval.node), 4, (yyvsp[(1) - (7)].node), makeIDNode((yyvsp[(2) - (7)].lexeme), NORMAL_ID), emptyParameterList, (yyvsp[(6) - (7)].node));
                    ;}
    break;

  case 12:
#line 225 "parser.y"
    {
                        /*TODO*/
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* emptyParameterList = Allocate(PARAM_LIST_NODE);
                        makeFamily((yyval.node), 4, makeIDNode((yyvsp[(1) - (7)].lexeme), NORMAL_ID), makeIDNode((yyvsp[(2) - (7)].lexeme), NORMAL_ID), emptyParameterList, (yyvsp[(6) - (7)].node));
                    ;}
    break;

  case 13:
#line 232 "parser.y"
    {
                        /*TODO*/
                        (yyval.node) = makeDeclNode(FUNCTION_DECL);
                        AST_NODE* emptyParameterList = Allocate(PARAM_LIST_NODE);
                        makeFamily((yyval.node), 4, makeIDNode("void", NORMAL_ID), makeIDNode((yyvsp[(2) - (7)].lexeme), NORMAL_ID), emptyParameterList, (yyvsp[(6) - (7)].node));
                    ;}
    break;

  case 14:
#line 241 "parser.y"
    {
                    (yyval.node) = makeSibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                ;}
    break;

  case 15:
#line 245 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                ;}
    break;

  case 16:
#line 252 "parser.y"
    {
                    (yyval.node) = makeDeclNode(FUNCTION_PARAMETER_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[(1) - (2)].node), makeIDNode((yyvsp[(2) - (2)].lexeme), NORMAL_ID));
                ;}
    break;

  case 17:
#line 257 "parser.y"
    {
                    (yyval.node) = makeDeclNode(FUNCTION_PARAMETER_DECL);
                    makeFamily((yyval.node), 2, makeIDNode((yyvsp[(1) - (2)].lexeme), NORMAL_ID), makeIDNode((yyvsp[(2) - (2)].lexeme), NORMAL_ID));
                ;}
    break;

  case 18:
#line 263 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeDeclNode(FUNCTION_PARAMETER_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[(1) - (3)].node), makeChild(makeIDNode((yyvsp[(2) - (3)].lexeme), ARRAY_ID), (yyvsp[(3) - (3)].node))); 
                ;}
    break;

  case 19:
#line 269 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeDeclNode(FUNCTION_PARAMETER_DECL);
                    makeFamily((yyval.node), 2, makeIDNode((yyvsp[(1) - (3)].lexeme), NORMAL_ID), makeChild(makeIDNode((yyvsp[(2) - (3)].lexeme), ARRAY_ID), (yyvsp[(3) - (3)].node))); 
                ;}
    break;

  case 20:
#line 276 "parser.y"
    {
                    (yyval.node) = (yyvsp[(2) - (3)].node);
                ;}
    break;

  case 21:
#line 280 "parser.y"
    {
                    (yyval.node) = makeSibling((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node));
                ;}
    break;

  case 22:
#line 286 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[(1) - (1)].node);                    
                ;}
    break;

  case 23:
#line 291 "parser.y"
    {
                    (yyval.node) = Allocate(NUL_NODE); 
                ;}
    break;

  case 24:
#line 297 "parser.y"
    {
                        /*TODO*/
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeFamily((yyval.node), 2, makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[(1) - (2)].node)), 
                                          makeChild(Allocate(STMT_LIST_NODE), (yyvsp[(2) - (2)].node)));
                    ;}
    break;

  case 25:
#line 304 "parser.y"
    {
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeChild((yyval.node), makeChild(Allocate(STMT_LIST_NODE), (yyvsp[(1) - (1)].node)));
                    ;}
    break;

  case 26:
#line 309 "parser.y"
    {
                        (yyval.node) = Allocate(BLOCK_NODE);
                        makeChild((yyval.node), makeChild(Allocate(VARIABLE_DECL_LIST_NODE), (yyvsp[(1) - (1)].node)));
                    ;}
    break;

  case 27:
#line 313 "parser.y"
    {
                        /*TODO*/
                        (yyval.node) = Allocate(BLOCK_NODE);
                    ;}
    break;

  case 28:
#line 320 "parser.y"
    {
                        /*TODO*/
                        (yyval.node) = makeSibling((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
                ;}
    break;

  case 29:
#line 325 "parser.y"
    {
                        /*TODO*/
                        (yyval.node) = (yyvsp[(1) - (1)].node);
                ;}
    break;

  case 30:
#line 332 "parser.y"
    {
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                ;}
    break;

  case 31:
#line 336 "parser.y"
    {
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                ;}
    break;

  case 32:
#line 342 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeDeclNode(TYPE_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[(2) - (4)].node), (yyvsp[(3) - (4)].node));
                ;}
    break;

  case 33:
#line 348 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeDeclNode(TYPE_DECL);
                    makeFamily((yyval.node), 2, makeIDNode((yyvsp[(2) - (4)].lexeme), NORMAL_ID), (yyvsp[(3) - (4)].node));
                ;}
    break;

  case 34:
#line 354 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeDeclNode(TYPE_DECL);
                    makeFamily((yyval.node), 2, makeIDNode("void", NORMAL_ID), (yyvsp[(3) - (4)].node));
                ;}
    break;

  case 35:
#line 362 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeDeclNode(VARIABLE_DECL);
                    makeFamily((yyval.node), 2, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node));
                ;}
    break;

  case 36:
#line 369 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeDeclNode(VARIABLE_DECL);
                    makeFamily((yyval.node), 2, makeIDNode((yyvsp[(1) - (3)].lexeme), NORMAL_ID), (yyvsp[(2) - (3)].node));
                ;}
    break;

  case 37:
#line 377 "parser.y"
    {
                    (yyval.node) = makeIDNode("int", NORMAL_ID);  
                ;}
    break;

  case 38:
#line 381 "parser.y"
    {
                    (yyval.node) = makeIDNode("float", NORMAL_ID);
                ;}
    break;

  case 39:
#line 387 "parser.y"
    {
                    (yyval.node) = makeIDNode((yyvsp[(1) - (1)].lexeme), NORMAL_ID);
                ;}
    break;

  case 40:
#line 391 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeSibling((yyvsp[(1) - (3)].node), makeIDNode((yyvsp[(3) - (3)].lexeme), NORMAL_ID));
                ;}
    break;

  case 41:
#line 396 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeSibling((yyvsp[(1) - (4)].node), makeChild(makeIDNode((yyvsp[(3) - (4)].lexeme), ARRAY_ID), (yyvsp[(4) - (4)].node)));     
                ;}
    break;

  case 42:
#line 401 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeChild(makeIDNode((yyvsp[(1) - (2)].lexeme), ARRAY_ID), (yyvsp[(2) - (2)].node));
                ;}
    break;

  case 43:
#line 407 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[(2) - (3)].node); 
                ;}
    break;

  case 44:
#line 413 "parser.y"
    {
                    (yyval.node) = makeSibling((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node));
                ;}
    break;

  case 45:
#line 418 "parser.y"
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_ADD);
                    makeFamily((yyval.node), 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                ;}
    break;

  case 46:
#line 423 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_SUB);
                    makeFamily((yyval.node), 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                ;}
    break;

  case 47:
#line 429 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                ;}
    break;

  case 48:
#line 435 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_MUL);
                    makeFamily((yyval.node), 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                ;}
    break;

  case 49:
#line 441 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_DIV);
                    makeFamily((yyval.node), 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                ;}
    break;

  case 50:
#line 447 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                ;}
    break;

  case 51:
#line 454 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = Allocate(CONST_VALUE_NODE);
                    (yyval.node)->semantic_value.const1=(yyvsp[(1) - (1)].const1);
                    
                ;}
    break;

  case 52:
#line 461 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[(2) - (3)].node);
                ;}
    break;

  case 53:
#line 468 "parser.y"
    {
                        /*TODO*/
                        (yyval.node) = (yyvsp[(1) - (1)].node); 
                    ;}
    break;

  case 54:
#line 473 "parser.y"
    {
                        /*TODO*/
                        (yyval.node) = makeSibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                    ;}
    break;

  case 55:
#line 480 "parser.y"
    {
                    (yyval.node) = makeIDNode((yyvsp[(1) - (1)].lexeme), NORMAL_ID);
                ;}
    break;

  case 56:
#line 484 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeChild(makeIDNode((yyvsp[(1) - (2)].lexeme), ARRAY_ID), (yyvsp[(2) - (2)].node));
                ;}
    break;

  case 57:
#line 489 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeChild(makeIDNode((yyvsp[(1) - (3)].lexeme), WITH_INIT_ID), (yyvsp[(3) - (3)].node));
                ;}
    break;

  case 58:
#line 496 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeSibling((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
                ;}
    break;

  case 59:
#line 501 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                ;}
    break;

  case 60:
#line 510 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[(2) - (3)].node);
                ;}
    break;

  case 61:
#line 516 "parser.y"
    {
                    (yyval.node) = makeStmtNode(WHILE_STMT);
                    makeFamily((yyval.node), 2, (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node));
                ;}
    break;

  case 62:
#line 521 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeStmtNode(FOR_STMT);
                    makeFamily((yyval.node), 4, (yyvsp[(3) - (9)].node), (yyvsp[(5) - (9)].node), (yyvsp[(7) - (9)].node), (yyvsp[(9) - (9)].node));
                ;}
    break;

  case 63:
#line 527 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeStmtNode(ASSIGN_STMT);
                    makeFamily((yyval.node), 2, (yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node));
                ;}
    break;

  case 64:
#line 534 "parser.y"
    {
                    (yyval.node) = makeStmtNode(IF_STMT);
                    makeFamily((yyval.node), 3, (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node), Allocate(NUL_NODE));
                ;}
    break;

  case 65:
#line 540 "parser.y"
    {
                    (yyval.node) = makeStmtNode(IF_STMT);
                    makeFamily((yyval.node), 3, (yyvsp[(3) - (7)].node), (yyvsp[(5) - (7)].node), (yyvsp[(7) - (7)].node));
                ;}
    break;

  case 66:
#line 546 "parser.y"
    {
                    (yyval.node) = makeStmtNode(FUNCTION_CALL_STMT);
                    makeFamily((yyval.node), 2, makeIDNode((yyvsp[(1) - (5)].lexeme), NORMAL_ID), (yyvsp[(3) - (5)].node));
                ;}
    break;

  case 67:
#line 551 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = Allocate(NUL_NODE);
                ;}
    break;

  case 68:
#line 556 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeStmtNode(RETURN_STMT); 
                ;}
    break;

  case 69:
#line 561 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeChild(makeStmtNode(RETURN_STMT), (yyvsp[(2) - (3)].node));
                ;}
    break;

  case 70:
#line 568 "parser.y"
    {
                        /*TODO*/
                        (yyval.node) = makeChild(Allocate(NONEMPTY_ASSIGN_EXPR_LIST_NODE), (yyvsp[(1) - (1)].node));
                     ;}
    break;

  case 71:
#line 573 "parser.y"
    {
                         (yyval.node) = Allocate(NUL_NODE); 
                     ;}
    break;

  case 72:
#line 579 "parser.y"
    {
                                        /*TODO*/
                                        (yyval.node) = makeSibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                                    ;}
    break;

  case 73:
#line 584 "parser.y"
    {
                                        /*TODO*/
                                        (yyval.node) = (yyvsp[(1) - (1)].node);
                                    ;}
    break;

  case 74:
#line 597 "parser.y"
    {
                        /*TODO*/
                        (yyval.node) = makeStmtNode(ASSIGN_STMT);
                        makeFamily((yyval.node), 2, makeIDNode((yyvsp[(1) - (3)].lexeme), NORMAL_ID), (yyvsp[(3) - (3)].node));
                    ;}
    break;

  case 75:
#line 603 "parser.y"
    {
                        /*TODO*/
                        (yyval.node) = (yyvsp[(1) - (1)].node);
                    ;}
    break;

  case 76:
#line 610 "parser.y"
    {
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                ;}
    break;

  case 77:
#line 614 "parser.y"
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_OR);
                    makeFamily((yyval.node), 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                ;}
    break;

  case 78:
#line 621 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                ;}
    break;

  case 79:
#line 626 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_AND);
                    makeFamily((yyval.node), 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                ;}
    break;

  case 80:
#line 634 "parser.y"
    {
                        /*TODO*/
                        (yyval.node) = (yyvsp[(1) - (1)].node);
                    ;}
    break;

  case 81:
#line 639 "parser.y"
    {
                        /*TODO*/
                        (yyval.node) = makeFamily((yyvsp[(2) - (3)].node), 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); 
                    ;}
    break;

  case 82:
#line 646 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_EQ);
                ;}
    break;

  case 83:
#line 651 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_GE);
                ;}
    break;

  case 84:
#line 656 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_LE);
                ;}
    break;

  case 85:
#line 661 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_NE);
                ;}
    break;

  case 86:
#line 666 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_GT);
                ;}
    break;

  case 87:
#line 671 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_LT);
                ;}
    break;

  case 88:
#line 679 "parser.y"
    {
                        /*TODO*/
                        (yyval.node) = makeChild(Allocate(NONEMPTY_RELOP_EXPR_LIST_NODE), (yyvsp[(1) - (1)].node));
                    ;}
    break;

  case 89:
#line 684 "parser.y"
    {
                        (yyval.node) = Allocate(NUL_NODE);
                    ;}
    break;

  case 90:
#line 690 "parser.y"
    {
                                    /*TODO*/
                                    (yyval.node) = makeSibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                                ;}
    break;

  case 91:
#line 695 "parser.y"
    {
                                    /*TODO*/
                                    (yyval.node) = (yyvsp[(1) - (1)].node);
                                ;}
    break;

  case 92:
#line 702 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeFamily((yyvsp[(2) - (3)].node), 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); 
                ;}
    break;

  case 93:
#line 707 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                ;}
    break;

  case 94:
#line 714 "parser.y"
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_ADD);
                ;}
    break;

  case 95:
#line 718 "parser.y"
    {
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_SUB);
                ;}
    break;

  case 96:
#line 724 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeFamily((yyvsp[(2) - (3)].node), 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                ;}
    break;

  case 97:
#line 729 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                ;}
    break;

  case 98:
#line 736 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_MUL);
                ;}
    break;

  case 99:
#line 741 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeExprNode(BINARY_OPERATION, BINARY_OP_DIV);
                ;}
    break;

  case 100:
#line 748 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[(2) - (3)].node);
                ;}
    break;

  case 101:
#line 754 "parser.y"
    {
                    (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE), (yyvsp[(3) - (4)].node)); 
                ;}
    break;

  case 102:
#line 758 "parser.y"
    {   
                    /*TODO*/
                    (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION), (yyvsp[(3) - (4)].node)); 
                ;}
    break;

  case 103:
#line 763 "parser.y"
    {
                    (yyval.node) = Allocate(CONST_VALUE_NODE);
                    (yyval.node)->semantic_value.const1=(yyvsp[(1) - (1)].const1);
                ;}
    break;

  case 104:
#line 769 "parser.y"
    {
                    AST_NODE *const_node = Allocate(CONST_VALUE_NODE);
                    const_node->semantic_value.const1 = (yyvsp[(2) - (2)].const1);
                    (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE), const_node);
                ;}
    break;

  case 105:
#line 775 "parser.y"
    {
                    /*TODO*/
                    AST_NODE *const_node = Allocate(CONST_VALUE_NODE);
                    const_node->semantic_value.const1 = (yyvsp[(2) - (2)].const1);
                    (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION), const_node);
                ;}
    break;

  case 106:
#line 782 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeStmtNode(FUNCTION_CALL_STMT);
                    makeFamily((yyval.node), 2, makeIDNode((yyvsp[(1) - (4)].lexeme), NORMAL_ID), (yyvsp[(3) - (4)].node));
                ;}
    break;

  case 107:
#line 789 "parser.y"
    {
                    AST_NODE *function_node = makeStmtNode(FUNCTION_CALL_STMT);
                    makeFamily(function_node, 2, makeIDNode((yyvsp[(2) - (5)].lexeme), NORMAL_ID), (yyvsp[(4) - (5)].node));
                    (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE), function_node);
                ;}
    break;

  case 108:
#line 795 "parser.y"
    {
                    /*TODO*/
                    AST_NODE *function_node = makeStmtNode(FUNCTION_CALL_STMT);
                    makeFamily(function_node, 2, makeIDNode((yyvsp[(2) - (5)].lexeme), NORMAL_ID), (yyvsp[(4) - (5)].node));
                    (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION), function_node);
                ;}
    break;

  case 109:
#line 802 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[(1) - (1)].node);
                ;}
    break;

  case 110:
#line 808 "parser.y"
    {
                    (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_NEGATIVE), (yyvsp[(2) - (2)].node));
                ;}
    break;

  case 111:
#line 812 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeChild(makeExprNode(UNARY_OPERATION, UNARY_OP_LOGICAL_NEGATION), (yyvsp[(2) - (2)].node));
                ;}
    break;

  case 112:
#line 819 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeIDNode((yyvsp[(1) - (1)].lexeme), NORMAL_ID);
                ;}
    break;

  case 113:
#line 824 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeChild(makeIDNode((yyvsp[(1) - (2)].lexeme), ARRAY_ID), (yyvsp[(2) - (2)].node));
                ;}
    break;

  case 114:
#line 832 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = makeSibling((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node));
                ;}
    break;

  case 115:
#line 837 "parser.y"
    {
                    /*TODO*/
                    (yyval.node) = (yyvsp[(2) - (3)].node);
                ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2635 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 844 "parser.y"


#include "lex.yy.c"
int main (int argc, char *argv[]) {
    yyin = fopen(argv[1],"r");
    yyparse();
    printf("%s\n", "Parsing completed. No errors found.");
    printGV(prog, argv[2]);
} /* main */


int yyerror (char *mesg) {
    printf("%s\t%d\t%s\t%s\n", "Error found in Line ", linenumber, "next token: ", yytext );
    exit(1);
} 

