%option noyywrap
%{

#include <stdio.h>
#include <stdbool.h>
#include "header.h"

int     linenumber = 1;
symtab  *ptr;
bool    dumpTokens = false;

/* You need to define for all tokens in C--, here are some examples */
/* Reserved words */
#define RW_RETURN     0
#define RW_TYPEDEF    1
#define RW_IF         2
#define RW_ELSE       3
#define RW_INT        4
#define RW_FLOAT      5
#define RW_FOR        6
#define RW_VOID       7
#define RW_WHILE      8
const char *reserved_word_strings[] = {
  "RW_RETURN", "RW_TYPEDEF", "RW_IF", "RW_ELSE", "RW_INT",
  "RW_FLOAT", "RW_FOR", "RW_VOID", "RW_WHILE"
};

/* Constants and Comment */
#define CONST_INT     20
#define CONST_FLOAT   21
#define CONST_STRING  22
#define COMMENT       23

/* Identifiers */
#define IDENTIFIER    40

/* Symbols and Operators */
#define OP_ADD        61
#define OP_SUB        62
#define OP_MUL        63
#define OP_DIV        64
#define OP_LT         65
#define OP_GT         66
#define OP_LE         67
#define OP_GE         68
#define OP_EQ         69
#define OP_NE         70
#define OP_AND        71
#define OP_OR         72
#define OP_NOT        73
#define OP_ASSIGN     74

/* Separators */
#define MK_LBRACE     91
#define MK_RBRACE     92
#define MK_LBRACK     93
#define MK_RBRACK     94
#define MK_LPAREN     95
#define MK_RPAREN     96
#define MK_SEMICOL    97
#define MK_COMMA      98
#define MK_DOT        99

/* Error */
#define ERROR         110

%}

letter                [A-Za-z]
digit                 [0-9]
WS                    [ \t]+
newline               "\n"

/* Constants and Comment */
Int_constant          {digit}+
Float_constant        ({digit}+\.{digit}*|{digit}*\.{digit}+|{digit}+)([Ee]-?{digit}+)?
String_constant       \"[^"]*\"
comment               \/\*([^\*]|\*+[^\/\*])*(\*+)?\*\/
/* comment               \/\*([^\*]|\*+[^\/])*\*+\/ */

/* Identifiers */
ID                    {letter}({letter}|{digit}|"_")*

/* Symbols and Operators */
OP_add                "+"
OP_sub                "-"
OP_mul                "*"
OP_div                "/"
OP_lt                 "<"
OP_gt                 ">"
OP_le                 "<="
OP_ge                 ">="
OP_eq                 "=="
OP_ne                 "!="
OP_and                "&&"
OP_or                 "||"
OP_not                "!"
OP_assign             "="

/* Separators */
DL_lbrace             "{"
DL_rbrace             "}"
DL_lbrack             "["
DL_rbrack             "]"
DL_lparen             "("
DL_rparen             ")"
DL_comma              ","
DL_semicol            ";"
DL_dot                "."

/* Errors */
error                 .

%%

{WS}                  {}
{newline}             linenumber += 1;

{Int_constant}        {
                        if (dumpTokens) printf("CONST_INT\n");
                        return CONST_INT;
                      }
{Float_constant}      {
                        if (dumpTokens) printf("CONST_FLOAT\n");
                        return CONST_FLOAT;
                      }
{String_constant}     {
                        if (dumpTokens) printf("CONST_STRING\n");
                        return CONST_STRING;
                      }
{comment}             {
                        if (dumpTokens) printf("COMMENT\n");
                        printf("%s\n", yytext);
                        return COMMENT;
                      }

{ID}                  {
                        ptr = lookup(yytext);
                        if (ptr == NULL) {
                          if (strlen(yytext) > IDENTIFIER_MAX_LEN) {
                            fprintf(stderr, "[Error] Lexer: invalid identifier "
                                            "%s of length > 32 on line %d\n",
                                            yytext, linenumber);
                            return ERROR;
                          }
                          if (dumpTokens) printf("IDENTIFIER\n");
                          insert(yytext);
                          return IDENTIFIER;
                        } else if (ptr->isReservedWord) {
                          int tokenNumber = ptr->tokenNumber;
                          if (dumpTokens)
                            printf("%s\n", reserved_word_strings[tokenNumber]);
                          return tokenNumber;
                        } else {
                          if (dumpTokens) printf("IDENTIFIER\n");
                          ptr->counter++;
                          return IDENTIFIER;
                        }
                      }

{OP_add}              {
                        if (dumpTokens) printf("OP_ADD\n");
                        return OP_ADD;
                      }
{OP_sub}              {
                        if (dumpTokens) printf("OP_SUB\n");
                        return OP_SUB;
                      }
{OP_mul}              {
                        if (dumpTokens) printf("OP_MUL\n");
                        return OP_MUL;
                      }
{OP_div}              {
                        if (dumpTokens) printf("OP_DIV\n");
                        return OP_DIV;
                      }
{OP_lt}               {
                        if (dumpTokens) printf("OP_LT\n");
                        return OP_LT;
                      }
{OP_gt}               {
                        if (dumpTokens) printf("OP_GT\n");
                        return OP_GT;
                      }
{OP_le}               {
                        if (dumpTokens) printf("OP_LE\n");
                        return OP_LE;
                      }
{OP_ge}               {
                        if (dumpTokens) printf("OP_GE\n");
                        return OP_GE;
                      }
{OP_eq}               {
                        if (dumpTokens) printf("OP_EQ\n");
                        return OP_EQ;
                      }
{OP_ne}               {
                        if (dumpTokens) printf("OP_NE\n");
                        return OP_NE;
                      }
{OP_and}              {
                        if (dumpTokens) printf("OP_AND\n");
                        return OP_AND;
                      }
{OP_or}               {
                        if (dumpTokens) printf("OP_OR\n");
                        return OP_OR;
                      }
{OP_not}              {
                        if (dumpTokens) printf("OP_NOT\n");
                        return OP_NOT;
                      }
{OP_assign}           {
                        if (dumpTokens) printf("OP_ASSIGN\n");
                        return OP_ASSIGN;
                      }

{DL_lbrace}           {
                        if (dumpTokens) printf("MK_LBRACE\n");
                        return MK_LBRACE;
                      }
{DL_rbrace}           {
                        if (dumpTokens) printf("MK_RBRACE\n");
                        return MK_RBRACE;
                      }
{DL_lbrack}           {
                        if (dumpTokens) printf("MK_LBRACK\n");
                        return MK_LBRACK;
                      }
{DL_rbrack}           {
                        if (dumpTokens) printf("MK_RBRACK\n");
                        return MK_RBRACK;
                      }
{DL_lparen}           {
                        if (dumpTokens) printf("MK_LPAREN\n");
                        return MK_LPAREN;
                      }
{DL_rparen}           {
                        if (dumpTokens) printf("MK_RPAREN\n");
                        return MK_RPAREN;
                      }
{DL_comma}            {
                        if (dumpTokens) printf("MK_COMMA\n");
                        return MK_COMMA;
                      }
{DL_semicol}          {
                        if (dumpTokens) printf("MK_SEMICOL\n");
                        return MK_SEMICOL;
                      }
{DL_dot}              {
                        if (dumpTokens) printf("MK_DOT\n");
                        return MK_DOT;
                      }

<<EOF>>               return EOF;

{error}               {
                        fprintf(stderr, "[Error] Lexer: unrecognized token %s "
                                        "on line %d\n", yytext, linenumber);
                        return ERROR;
                      }

%%

int main(int argc, char **argv) {
  setvbuf(stdout, NULL, _IONBF, 0);

  insertReservedWord("return", RW_RETURN);
  insertReservedWord("typedef", RW_TYPEDEF);
  insertReservedWord("if", RW_IF);
  insertReservedWord("else", RW_ELSE);
  insertReservedWord("int", RW_INT);
  insertReservedWord("float", RW_FLOAT);
  insertReservedWord("for", RW_FOR);
  insertReservedWord("void", RW_VOID);
  insertReservedWord("while", RW_WHILE);

  argc--; ++argv;
  if (argc > 0) {
    char *filename = NULL;
    for (int i = 0; i < argc; ++i) {
      if (strcmp(argv[i], "--dump-tokens") == 0) {
        dumpTokens = true;
      } else if (filename) {
        printf("usage: ./scanner [--dump-tokens] input-file\n");
        return -1;
      } else {
        filename = argv[i];
      }
    }
    yyin = fopen(filename, "r");
  } else {
    yyin = stdin;
  }
  int token;
  while ((token = yylex()) != EOF) {
    if (token == ERROR)
      return -1;
  }
  printf("\nFrequency of identifiers:\n");
  printIdentifierFrequencies();
}

