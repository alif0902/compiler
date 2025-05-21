/*****  global.h  ************************************/

#include <stdio.h>	/* load i/o routines */
#include <ctype.h>	/* load charactertest routines */
#include <stdlib.h>
#include <string.h>

/*** constant values ***/
#define BSIZE  128	/* buffer size */
#define NONE   -1
#define EOS    '\0'	/* end of string */
#define SYMMAX 100	/* size of symbol table */

/*** tokens ***/
#define NUM    256
#define ID     257
#define DIV    258
#define MOD    259
#define MINUS  260
#define DONE   261	/* end of codes */

/*** stuck operator codes ***/
#define PUSH   384
#define POP    385
#define RVALUE 386
#define LVALUE 387
#define STORE  388

/*** type definitions ***/
struct entry {		/* form of symbol table entry */
	char *lexptr;		/* pointer to lexical name */
	int  token;		/* token taype */
	int  location;		/* memory location */
};

/*** variables ***/
int tokenval;		/* value of token attribute */
int lineno;		/* line no. of source_prog. */

/*** array ***/
struct entry symtable[SYMMAX];	/* symbol table */

/*** functions ***/
void init();		/* loads keywords into symtable */
int lookup(char s[]);	/* returns position of entry for s */
int insert(char s[], int tok, int loc);		/* returns position of entry for s */
int error(char *m);	/* generates all error message */
int lexan();    	/* lexical analyzer */
void parse();		/* parser */
void emit(int t, int tval);	/* generates output */
void gencode(int t, int tval);	/* generates object_code */
