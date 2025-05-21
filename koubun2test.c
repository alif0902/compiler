/*****  koubun_2.c  ******************************************/

#include "global_0.h"

void expr();     /* E := T {(+|-) T} */
void term();     /* T := F {(*|/|DIV|MOD) F} */
void factor();   /* F := i | n | (E) */
void stmt();
void assign();
int match(int t); /* Check token with syntax element and get next token */

int lookahead;  /* Next token */

/*** Parse and translate expression list into postfix notation ***/
void parse() /* P := E; {E;} */
{
    lookahead = lexan();  /* Get token from lexical analyzer */
    while (lookahead != DONE) {
        stmt();
        match(';');
    }
    gencode(DONE, NONE);
    return;
}

void expr() /* E := T {(+|-) T} */
{
    int t;
    if (lookahead == '-') {
        match('-');
        term();
        gencode(MINUS, NONE);
    } else {
        term();
    }

    while (1) {
        switch (lookahead) {
            case '+':
            case '-':
                t = lookahead;
                match(t);
                term();
                gencode(t, NONE);
                continue;
            default:
                return;
        }
    }
}

void term() /* T := F {(*|/|DIV|MOD) F} */
{
    int t;
    factor();
    while (1) {
        switch (lookahead) {
            case '*':
            case '/':
            case DIV:
            case MOD:
                t = lookahead;
                match(t);
                factor();
                gencode(t, NONE);
                continue;
            default:
                return;
        }
    }
}

void factor() /* F := i | n | (E) */
{
    switch (lookahead) {
        case ID:
            gencode(RVALUE, tokenval);
            match(ID);
            break;
        case NUM:
            gencode(NUM, tokenval);
            match(NUM);
            break;
        case '(':
            match('(');
            expr();
            match(')');
            break;
        default:
            error("syntax error");
    }
}

void stmt()
{
    assign();
    return;
}

void assign()
{
    int tv = tokenval;
    match(ID);
    gencode(LVALUE, tv);
    match('=');
    expr();
    gencode(STORE, NONE);
    return;
}

int match(int t) /* Check token with syntax element and get next token */
{
    if (lookahead == t)
        lookahead = lexan();
    else
        error("syntax error");
    return 0;
}
