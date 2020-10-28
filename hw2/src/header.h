#ifndef HEADER_H
#define HEADER_H

#include <stdbool.h>

typedef struct symtab {
	char lexeme[33];
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

