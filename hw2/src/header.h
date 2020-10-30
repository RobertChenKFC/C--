#ifndef HEADER_H
#define HEADER_H

#include <stdbool.h>

#define IDENTIFIER_MAX_LEN 32

typedef struct symtab {
	char lexeme[IDENTIFIER_MAX_LEN + 1];
	struct symtab *front;
	struct symtab *back;
	int line;
  union {
    int counter;
    int tokenNumber;
  };
  bool isReservedWord;
} symtab;

symtab *lookup(char *name);
void   insert(char *name);
void   insertReservedWord(char *string, int tokenNumber);
void   printSymTab();
void   printIdentifierFrequencies();

#endif // HEADER_H

