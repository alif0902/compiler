/*****  syokika.c  *******************************/

#include "global_0.h"

struct entry keywords[] ={	/* keywords */
	{"div",	DIV,	NONE},
	{"mod",	MOD,	NONE},
	{0,	0,	0},
};

void init()	/* stores keywords into symtable */
{
	struct entry *p;
	for(p = keywords; p->token; p++)
	insert(p->lexptr, p->token, p->location);
}
