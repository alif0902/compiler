/*****  code.c  ********************************/

#include "global_0.h"

int lastloc = -1;		


void emit(int t, int tval)	
{
	switch(t){
		case '+': case '-': case '*': case '/': case '=':
			printf("%c\n", t); break;	
		case DIV: 
            printf("DIV\n"); break;
		case MOD: 
            printf("MOD\n"); break;
		case MINUS: 
            printf("MINUS\n"); break;
		case NUM:
			printf("%d\n", tval); break;
		case ID:
			printf("%s\n", symtable[tval].lexptr); break;
		case DONE:
			printf("DONE\n"); break;
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
			printf("%d\n", PUSH); printf("%d\n", tval); break;
		case LVALUE:
			if(symtable[tval].location == NONE) symtable[tval].location = ++lastloc;
			printf("%d\n", LVALUE); 
            printf("%d\n", symtable[tval].location); 
            break; 
		case RVALUE:
			if(symtable[tval].location == NONE) error("location is not allocated");
            printf("%d\n", RVALUE); 
            printf("%d\n", symtable[tval].location); 
            break; 
		case STORE:
            printf("%d\n", STORE); 
            break; 
		case DONE:
            printf("%d\n", DONE); 
            break;
		default:
			error("illegal token");
	}
}
