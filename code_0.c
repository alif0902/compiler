/*****  code.c  ********************************/

#include "global_0.h"

int lastloc = -1;		/* last used location of data_momory */

/*** generates output ***/
void emit(int t, int tval)	
{
	switch(t){
		case '+': case '-': case '*': case '/': case DIV: case MOD: case MINUS: case '=':
			printf("%d\n", t); break;	/* output internal code (decimal number) */
		case MINUS: 
			printf("MINUS\n"); break;
		case NUM:
			printf("%d\n", tval); break;
		case ID:
			printf("%s\n", symtable[tval].lexptr); break;
		case DONE:
			printf("%d\n", t); break;
		default:
			printf("token %d, tokenval %d\n", t, tval);
	}
}

/*
/*** generates object_code ***/
void gencode(int t, int tval)  
{
	switch(t){
		case '+': case '-': case '*': case '/': case DIV: case MOD: case MINUS:
			printf("%d\n", t); break;
		case NUM:
			printf("%d\n", PUSH); /*??*/; break;
		case LVALUE:
			if(symtable[tval].location == NONE) symtable[tval].location = ++lastloc;
			/*??*/; /*??*/;	break;
		case RVALUE:
			if(symtable[tval].location > lastloc) error("location is not allocated");
			/*??*/; /*??*/; break;
		case STORE:
			/*??*/; break;
		case DONE:
			/*??*/; break;
		default:
			error("illegal token");
	}
}
