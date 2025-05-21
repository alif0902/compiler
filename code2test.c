/*****  code.c  ********************************/
#include "global_0.h"

int lastloc = -1;     // last used location of data memory
int max_loc = 0;

/*** generates output for intermediate code ***/
void gencode(int t, int tval)
{
    switch(t) {
        case '+': case '-': case '*': case '/': 
        case DIV: case MOD: case MINUS:
            printf("%d\n", t);
            break;

        case NUM:
            printf("%d\n", PUSH);
            printf("%d\n", tval);
            break;

        case LVALUE:
            if (symtable[tval].location == NONE)
                symtable[tval].location = ++lastloc;

            printf("%d\n", LVALUE);
            printf("%d\n", symtable[tval].location);

            if (symtable[tval].location > max_loc)
                max_loc = symtable[tval].location;
            break;

        case RVALUE:
            if (symtable[tval].location == NONE)
                error("location is not allocated");

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
            error("illegal token in gencode");
    }
}
