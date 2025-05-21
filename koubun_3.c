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
void parse() 
/*** P := E;{E;} ***/ 
{ 
    lookahead = lexan();  
    while (lookahead != DONE){ 
        stmt(); 
        if(match(';') == 1){ 
        error("';' is expected"); 
        }  
        
    } 
    gencode(DONE, NONE);  
    return; 
}

void expr() 
{ 
    int t; 
    if(lookahead == '-'){       
        match('-'); 
        term(); 
        gencode(MINUS, NONE); 
    } else { 
        term(); 
    } 
    while(1){ 
        switch(lookahead){ 
           case '+': case '-': 
            t = lookahead; 
            match(lookahead); 
            term(); 
            gencode(t, NONE); 
            continue; 
          case ';': case ')':
            return;
        default:
            error("syntax error: '+', '-', ')' or ';' is expected");
            skiptoken('E');
            return; 
        } 
    } 
}



void term() /*** T := F{(*|/|DIV|MOD)F} ***/ 
{ 
    int t; 
    factor(); 
    while(1) {
        switch(lookahead){ 
            case '*': case '/': case DIV: case MOD: 
                t = lookahead; 
                match(lookahead); 
                factor(); 
                gencode(t, NONE); 
                continue;
            case '+': case '-': case ')': case ';': 
                return;
            default: 
                error("syntax error: '*', '/', 'DIV', 'MOD', '+', '-', ')' or ';' is expected");
                skiptoken('T'); 
                return; 
        } 
    } 
}


void factor() /*** F := i|n|(E) ***/ 
{ 
   switch(lookahead){ 
      case ID: 
            gencode(RVALUE, tokenval); match(ID); break; 
      case NUM: 
            gencode(NUM, tokenval); match(NUM); break; 
      case '(': 
            match('('); expr(); match(')'); break; 
      default:            
            error("syntax error 'ID', 'NUM' or '(' is expected"); 
            skiptoken('F');
    } 
}

void stmt() /***文 ::= 代入文 ***/
{
  assign();
  return;
}

void assign(){ 
    int tv = tokenval; 
    if(match(ID) == 1){ 
        error("ID is expected"); 
        skiptoken('A'); 
        return; 
    } 
    gencode(LVALUE, tv);  

    if(match('=') == 1){ 
        error("'=' is expected"); 
        return; 
    }           
    expr();              
    gencode(STORE, NONE); 
    return; 
}

int match(int t)	/*** check token with syantax element and get next token ***/
{
	if(lookahead == t) 
        lookahead = lexan();
	else 
        error("syntax error");
	return 0;
}

//  (for KADAI 22)
void skiptoken(int n)	/*** skip tokens until follow(N) ***/
{
	int l;
	l = lookahead;
	switch(n) {
		case 'S': case 'A':
			while(l!=';' && l!=DONE) l = lexan();
			break;		
		case 'E': 
			while(l!=';' && l!=DONE && l!=')') l = lexan();
			break;		
		case 'T': 
			while(l!=';' && l!=DONE && l!=')' && l!='+' && l!='-') l = lexan();
			break;		
		case 'F': 
			while(l!=';' && l!=DONE && l!=')' && l!='+' && l!='-' && l!='*'
                  && l!='/' && l!=DIV && l!=MOD) l = lexan();
			break;		
		default:
			error("illegal nonterminal syambol in skiptken()"); exit(1);
	}
	lookahead = l;
	return;
}