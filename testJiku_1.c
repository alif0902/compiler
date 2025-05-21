/*****  jiku.c  *****************************/

#include "global_0.h"

char lexbuf[BSIZE];
int  lineno = 1;
int  tokenval = NONE;

/*** lexical analyzer ***/
int  lexan()      
{
	int t;
	while(1){
		t = getchar();
		if(t==' '||t=='\t')
		     ;		/* strip out white space */
		else if (t == '\n')
		     lineno = lineno + 1;
		else if (isdigit(t)){	/* t is a digit*/
			ungetc(t, stdin);
			scanf("%d", &tokenval);		/* read value */
			return NUM;
		}
		else if (isalpha(t)) {	/* t is a letter */
			int p, b = 0;
			while (isalnum(t)) {	/* t is alphanumeric */
				lexbuf[b]=t;
				t = getchar();
				b = b + 1;
				if (b >= BSIZE) error("lexical_buffer overflow");
			}
			lexbuf[b] = EOS;
			if (t != EOF) ungetc(t, stdin);
			p = lookup(lexbuf);
			if (p == 0) p =insert(lexbuf, ID, NONE);	/* insert new identifier */
			tokenval = p;
			return symtable[p].token;
		}
		else if(t == EOF)
			return DONE;
		else {
            if(t=='='||t=='+'||t=='-'||t=='*'||t=='/'||t=='('||t==')'||t==';'){
                tokenval = NONE;
			    return t;
            }
			else{
                error("illegal character");
                return t;
            }
		}
	}
}
