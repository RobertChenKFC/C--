#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include"header.h"

#define TABLE_SIZE	512

symtab     *hash_table[TABLE_SIZE];
size_t     number_of_entries = 0;
extern int linenumber;

int HASH(char * str){
	int idx=0;
	while(*str){
		idx = idx << 1;
		idx+=*str;
		str++;
	}	
	return (idx & (TABLE_SIZE-1));
}

/*returns the symbol table entry if found else NULL*/

symtab * lookup(char *name){
	int hash_key;
	symtab* symptr;
	if(!name)
		return NULL;
	hash_key=HASH(name);
	symptr=hash_table[hash_key];

	while(symptr){
		if(!(strcmp(name,symptr->lexeme)))
			return symptr;
		symptr=symptr->front;
	}
	return NULL;
}


void insert(char *name){
	int hash_key;
	symtab* ptr;
	symtab* symptr=(symtab*)malloc(sizeof(symtab));	

	hash_key=HASH(name);
	ptr=hash_table[hash_key];

	if(ptr==NULL){
		/*first entry for this hash_key*/
		hash_table[hash_key]=symptr;
		symptr->front=NULL;
		symptr->back=symptr;
	}
	else{
		symptr->front=ptr;
		ptr->back=symptr;
		symptr->back=symptr;
		hash_table[hash_key]=symptr;	
	}

  ++number_of_entries;

	strcpy(symptr->lexeme,name);
	symptr->line=linenumber;
	symptr->counter=1;
  symptr->isReservedWord = false;
}

void insertReservedWord(char *string, int tokenNumber) {
  insert(string);
  --number_of_entries;
  symtab *symptr = lookup(string);
  symptr->tokenNumber = tokenNumber;
  symptr->isReservedWord = true;
}

void printSym(symtab* ptr) 
{
	    printf(" Name = %s \n", ptr->lexeme);
	    printf(" References = %d \n", ptr->counter);
}

void printSymTab() {
  int i;
  printf("----- Symbol Table ---------\n");
  for (i=0; i<TABLE_SIZE; i++) {
    symtab* symptr;
    symptr = hash_table[i];
    while (symptr != NULL) {
      if (!symptr->isReservedWord) {
        printf("====>  index = %d \n", i);
        printSym(symptr);
      }
      symptr=symptr->front;
    }
  }
}

typedef struct {
  const char *id;
  int freq;
} id_and_freq;

int qsort_cmp(const void *pa, const void *pb) {
  const id_and_freq *a = (const id_and_freq*)pa, *b = (const id_and_freq*)pb;
  return strcmp(a->id, b->id);
}

void printIdentifierFrequencies() {
  id_and_freq *ids = malloc(number_of_entries * sizeof(id_and_freq));

  size_t idx = 0;
  for (int i = 0; i < TABLE_SIZE; ++i) {
    symtab *symptr = hash_table[i];
    while (symptr != NULL) {
      if (!symptr->isReservedWord) {
        ids[idx].id = symptr->lexeme;
        ids[idx++].freq = symptr->counter;
      }
      symptr = symptr->front;
    }
  }

  qsort(ids, number_of_entries, sizeof(id_and_freq), qsort_cmp);
  for (size_t i = 0; i < number_of_entries; ++i)
    printf("%-32s %d\n", ids[i].id, ids[i].freq);

  free(ids);
}

