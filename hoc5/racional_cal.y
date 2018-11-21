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
%token <sim> racionalnum var undef bltin PRINT IF ELSE WHILE
%type   <inst>  stmt asgn exp stmtlist cond while if end
%token op
%right	'='
%left	OR
%left	AND
%left	GT GE LT LE EQ NE
%left '+' '-'
%left '*' '/'
%left	UNARYMINUS NOT
%% 
list:   
      | list'\n'
      | list asgn '\n'  { code2(pop, STOP); return 1; }
      | list stmt '\n'	{ code(STOP); return 1; }
      | list exp '\n'   { code2(print, STOP); return 1;}
      ;
asgn : var '=' exp  {code3(varpush, (Inst)$1, assign); }
	;
stmt:     expr   { code(pop); }
	| PRINT expr    { code(prexpr); $$ = $2;} 
	| while cond stmt end {
		($1)[1] = (Inst)$3;     /* cuerpo de la iteración */ 
		($1)[2] = (Inst)$4; }   /* terminar si la condición no se cumple */
	| if cond stmt end {    /* proposición if que no emplea else */ 
		($1)[1] = (Inst)$3;     /* parte then */ 
		($1)[3] = (Inst)$4; }   /* terminar si la condición no se cumple */ 
	| if cond stmt end ELSE stmt end {  /* proposición if con parte else */
		($1)[1]   =   (Inst)$3;	/*  parte then  */
		($1)[2]   =   (Inst)$6;	/* parte else   */
		($1)[3]   =   (Inst)$7;   } /*   terminar si la condición no se cumple  */
	|   '{'   stmtlist   '}' {   $$  =  $2;   }
    ;
cond:'('   expr   ')'      {   code(STOP);  $$=  $2;   }
;
while:	WHILE   {   $$   =   code3(whilecode,STOP,STOP); }
	;
if:IF   { $$=code(ifcode); code3(STOP, STOP, STOP); }
	;
end:      /* nada */{ code(STOP); $$ = progp; }
	;
stmtlist: /* nada */	{ $$ = progp; }
	| stmtlist '\n' 
	| stmtlist stmt
	;
exp: 	racionalnum { code2(constpush, (Inst)$1); } 
	| asgn { } 
	| bltin  '(' exp ')' {
		code2(BLTIN, (Inst)$1->u.ptr);
	} 
	| var { code3(varpush, (Inst)$1, eval);}
  	| exp '+' exp {code(add);}
  	| exp '-' exp {code(sub);}
  	| exp '*' exp {code(mul);}
  	| exp '/' exp {code(divi);}
	| '(' exp ')' { $$ = $2 }
	|'-' expr %prec UNARYMINUS  { $$ = $2; code(negate); }
	|expr GT expr  { code(gt); }
	|expr GE expr  { code(ge); }
	|expr LT expr  { code(lt); }
	|expr LE expr  { code(le); }
	|expr EQ expr  { code (eq); }
	|expr NE expr  { code(ne); }
	|expr AND expr { code(and); }
	|expr OR expr  { code(or); }
	|NOT expr      { $$ = $2; code(not); }
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
