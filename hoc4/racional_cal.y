%{
#include <stdio.h>
#include <math.h>
#include "racional_cal.h"
#define MSDOS
#define code2(c1, c2)     code(c1); code(c2);
#define code3(c1, c2, c3) code(c1); code(c2); code(c3);
void yyerror (char *s);
//int yylex ();
void warning(char *s, char *t);
void execerror(char *s, char *t);
void fpecatch(int e);
extern void init();
%}
%union{
	Symbol *sim;
	Inst *inst;
	RacionalAP racional_;

}
%token <sim> racionalnum var undef bltin
%token op
%left '+' '-'
%left '*' '/'
%% 
list:   
      | list'\n'
      | list asigna '\n'  { code2(pop, STOP); return 1; }
      | list exp '\n'   { code2(print, STOP); return 1;}
      ;
asigna : var '=' exp  {code3(varpush, (Inst)$1, assign); }
	;
exp: 	racionalnum { code2(constpush, (Inst)$1); } 
	| asigna { } 
	| bltin  '(' exp ')' {
		code2(BLTIN, (Inst)$1->u.ptr);
	} 
	| var { code3(varpush, (Inst)$1, eval);}
  	| exp '+' exp {code(add);}
  	| exp '-' exp {code(sub);}
  	| exp '*' exp {code(mul);}
  	| exp '/' exp {code(divi);}
	| '(' exp ')' 
  ;
%%

#include <stdio.h>
#include <ctype.h>
#include <signal.h>
#include <setjmp.h>

jmp_buf begin;

char *progname;
int lineno = 1;

void main (int argc, char *argv[])
{
	
	progname=argv[0];
	init();
	setjmp(begin);
	signal(SIGFPE, fpecatch);
  	for(initcode(); yyparse (); initcode())
		execute(prog);
	// return 0;
}

void execerror(char *s, char *t)
{
	warning(s, t);
	longjmp(begin, 0);
}

void fpecatch(int e)
{
	execerror("excepcion de punto flotante", (char *)0);
}

void yyerror (char *s) {
	warning(s, (char *) 0);
}
void warning(char *s, char *t){
	fprintf (stderr, "%s: %s", progname, s);
	if(t)
		fprintf (stderr, " %s", t);
	fprintf (stderr, "cerca de la linea %d\n", lineno);
}
