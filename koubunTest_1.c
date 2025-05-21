/*****  koubun.c  ******************************************/

#include "global_0.h"

void expr();		/* E := T{(+|-)T} */
void term();		/* T := F{(*|/|DIV|MOD)F} */
void factor();		/* F := i|n|(E) */
void stmt();
void assign();
int match(int t);	/* check token with syantax element and get next token */

int lookahead;		/* next token */

/*** parse and translates expression list into postfix notation ***/
void parse()	/*** P := E;{E;} ***/
{
        
	lookahead = lexan();		/* get token from lexical analyzer */
	
	while (lookahead != DONE){
          stmt();
          match(';');
	  
	}
	emit(DONE, NONE);
	return;
}

void expr()	/*** E := T{(+|-)T} ***/
{
	int t;
	if (lookahead == '-') 
        {
          match('-');
          term();
          emit(MINUS, NONE); 
        } 
        else 
        {
          term();
        }
	while(1)
		switch(lookahead){
			case '+': case '-':
				t = lookahead;
				match(lookahead); term(); emit(t, NONE);
				continue;
			default:
				return;
	}
}

void term()	/*** T := F{(*|/|DIV|MOD)F} ***/
{
	int t;
	
	factor();
	while(1)
		switch(lookahead){
			case '*': case '/': case DIV : case MOD :
				t = lookahead;
				match(lookahead);factor(); emit(t, NONE);
				continue;
			default:
				return;
		}
}

void factor()	/*** F := i|n|(E) ***/
{
	switch(lookahead){
		case ID:
			emit(ID,tokenval); match(ID);  break;
		case NUM:
			emit(NUM, tokenval); match(NUM); break;
		case '(':
			 match('('); expr(); match(')'); break;
		default:
			error("syntax error");
	}
}
void stmt() /***文 ::= 代入文 ***/
{
  assign();
  return;
}

void assign() /*** 代入文 ::= 変数"="式 ***/
{
  int tv = tokenval; 
  match(ID); 
  emit(ID, tv); 
  match('=');
  expr(); 
  emit('=', NONE); 
  return;
}
int match(int t)	/*** check token with syantax element and get next token ***/
{
	if(lookahead == t) lookahead = lexan();
	else error("syntax error");
	return 0;
}




