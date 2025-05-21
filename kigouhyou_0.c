/*****  kigouhyou.c  **************************/

#include "global_0.h"

#define STRMAX 999	/* size of lexemes array */

char lexemes[STRMAX];	/* array of lexical names */
int lastchar = -1;	/* last used position in lexemes */
int lastentry = 0;	/* last used position in symbol table */

int lookup(char s[])	/* returns position of entry for s */
{
	int p;
	for(p = lastentry; p > 0; p = p-1)
		if(strcmp(symtable[p].lexptr, s) == 0) return p;
	return 0;
}

int insert(char s[], int tok, int loc)	/* returns position of entry for s */
{
	int len;
	len = strlen(s);	/* strlen computes length of s */
	if(lastentry + 1 >= SYMMAX) {error("symbol table full"); /*??*/}
	if(lastchar + len + 1 >= STRMAX) {error("lexemes array full"); /*??*/}
	lastentry = lastentry + 1;
	symtable[lastentry].token = tok;
	symtable[lastentry].lexptr = &lexemes[lastchar + 1];
	symtable[lastentry].location = loc;
	lastchar = lastchar +len +1;
	strcpy(symtable[lastentry].lexptr, s);
	return lastentry;
}
