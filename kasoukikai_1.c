/*****  kasoukikai.c  *******************************************/

#include <stdio.h>  /* load i/o routines */
#include <stdlib.h>

/*** constant values ***/
#define MAXINST 999	/* size of instruction_memory */
#define MAXDATA 100	/* size of data_memory */
#define MAXSTACK 100	/* size of stack */

/*** arithmetic operator codes ***/
#define DIV    258
#define MOD    259
#define MINUS  260

/*** dummy code for end of object_codes ***/
#define DONE   261

/*** stuck operator codes ***/
#define PUSH   384
#define POP    385
#define RVALUE 386
#define LVALUE 387
#define STORE  388

/*** variables ***/
int ip;		/* instruction pointer */
int top;	/* stack top */
int op;		/* operator */
int oprnd;	/* operand (value or location) */
int oprnd1;	/* first operand */
int oprnd2;	/* second operand */
int inst;	/* instruction */
int maxloc = 0;	/* max used location of data_memory */

/*** arrays ***/
int instmem[MAXINST];	/* instruction_memory */
int datamem[MAXDATA];	/* data_memory */
int stack[MAXSTACK];	/* stack */

/*** functions ***/
void loadinst(void);	/* read and store object_codes into instruction_memory */
void checkloc(int);	/* check location */
void push(int);
int pop(void);
void error(char *);	/* generates all error message */
void printdmem(void);	/* print data_memory */

int main(void)
{
	loadinst();
	ip = 0; //new
	top = -1; //new
	while(1) {
		op = instmem[ip++];
		switch(op) {	/* execution according to operator */
			case '+': oprnd2 = pop(); oprnd1 = pop(); push(oprnd1 + oprnd2); continue;//new
			case '-': oprnd2 = pop(); oprnd1 = pop(); push(oprnd1 - oprnd2); continue;//new
			case '*': oprnd2 = pop(); oprnd1 = pop(); push(oprnd1 * oprnd2); continue;//new
			case '/': oprnd2 = pop(); oprnd1 = pop(); push(oprnd1 / oprnd2); continue;//new
			case DIV: oprnd2 = pop(); oprnd1 = pop(); push(oprnd1 / oprnd2); continue;//new
			case MOD: oprnd2 = pop(); oprnd1 = pop(); push(oprnd1 % oprnd2); continue;//new
			case MINUS: oprnd1 = pop(); push(oprnd1 * -1); continue;//new
			case POP: pop(); continue;//new
			case PUSH: oprnd = instmem[ip++]; push(oprnd); continue;//new
			case RVALUE: oprnd = instmem[ip++]; checkloc(oprnd); push(datamem[oprnd]); continue;//new
			case LVALUE: oprnd = instmem[ip++]; checkloc(oprnd); push(oprnd); continue;//new
			case STORE: oprnd2 = pop(); oprnd1 = pop(); datamem[oprnd1] = oprnd2; continue;//new
			case DONE: printdmem(); exit(0);	/* succsessful termination *///new
		}
	}
}

/*** read and store object_codes into instruction_memory ***/
void loadinst()	
{
	int i = 0;
	scanf("%d", &inst);
	instmem[i] = inst;
	while(inst != DONE) {
		i++;
		if(i > MAXINST) error("instruction memory overflow");
		scanf("%d", &inst);
		instmem[i] = inst;
	}
	return;
}

/*** check location and gets max location of data_memory ***/
void checkloc(int l)	
{
	if(l < 0 || l > MAXDATA) error("wrong location"); 
	if(l > maxloc) maxloc = l;
	return;
}

/*** push v ***/
void push(int v)	
{
	top++;
	if(top > MAXSTACK) error("stack overflow"); 
	stack[top] = v;//new
	return;	
}

/*** pop ***/
int pop()		
{
	int v;
	if(top < 0) error("stack is empty"); 
	v = stack[top];//new
	top--;
	return v;	
}

/*** generates all error message ***/
void error(char *m)  
{
	fprintf(stderr, "ip %d: %s\n", ip-1, m);
	exit(1);	/* unsucsessful termination */
}

/*** print values in data_memory ***/
void printdmem()	
{
	int i;
	for(i = 0; i <= maxloc; i++) 
		printf("datamem[%d]: %d \n", i, datamem[i]);
	return;
}
