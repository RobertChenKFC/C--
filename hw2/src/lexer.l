%option noyywrap
%{

#include <stdio.h>
#include "header.h"

int     linenumber;
symtab  *ptr;

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
Float_constant        ({digit}+\.{digit}*|{digit}*\.{digit}+|{digit}+)([Ee]-?{digit})?
/* TODO: implemented escape? */
String_constant       \"[^"]*\"
comment               \/\*([^\*]|\*+[^\/\*])*(\*+)?\*\/

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

{Int_constant}        return CONST_INT;
{Float_constant}      return CONST_FLOAT;
{String_constant}     return CONST_STRING;
{comment}             {
                        printf("%s\n", yytext);
                        return COMMENT;
                      }

{ID}                  {
                        // DEBUG
                        //printf("Identifier %s is found!\n", yytext);

                        ptr = lookup(yytext);
                        if (ptr == NULL) {
                          insert(yytext);
                          return IDENTIFIER;
                        } else if (ptr->isReservedWord) {
                          // DEBUG
                          //printf("The identifier is a reserved word!\n");

                          return ptr->tokenNumber;
                        } else {
                          ptr->counter++;
                          return IDENTIFIER;
                        }
                      }

{OP_add}              return OP_ADD;
{OP_sub}              return OP_SUB;
{OP_mul}              return OP_MUL;
{OP_div}              return OP_DIV;
{OP_lt}               return OP_LT;
{OP_gt}               return OP_GT;
{OP_le}               return OP_LE;
{OP_ge}               return OP_GE;
{OP_eq}               return OP_EQ;
{OP_ne}               return OP_NE;
{OP_and}              return OP_AND;
{OP_or}               return OP_OR;
{OP_not}              return OP_NOT;
{OP_assign}           return OP_ASSIGN;

{DL_lbrace}           return MK_LBRACE;
{DL_rbrace}           return MK_RBRACE;
{DL_lbrack}           return MK_LBRACK;
{DL_rbrack}           return MK_RBRACK;
{DL_lparen}           return MK_LPAREN;
{DL_rparen}           return MK_RPAREN;
{DL_comma}            return MK_COMMA;
{DL_semicol}          return MK_SEMICOL;

<<EOF>>               return EOF;

{error}               {
                        printf("[Error] Lexer: unrecognized token %s\n", yytext);
                        return ERROR;
                      }

%%

int main(int argc, char **argv) {
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
  if (argc > 0)
    yyin = fopen(argv[0], "r");
  else
    yyin = stdin;
  int token;
  while ((token = yylex()) != EOF) {
    if (token == ERROR)
      return -1;
  }
  printIdentifierFrequencies();
}

