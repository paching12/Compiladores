%{

#include "racional.h"
#include "hoc.h"
#include <math.h>
#define MSDOS

void yyerror (char *s);
// int yylex ();
void warning(char *s, char *t);
void execerror(char *s, char *t);
void fpecatch();
extern double Pow(double, double);
// typedef double (*apf)(double);
// static struct {		Predefinidos 
// char *name;

// double	(*func)();
// } builtins_[] =	{
// "sin",	sin,
// "cos" ,	cos,
// "atan",	atan,
// "log", log,
// "log10", log10,
// "exp", exp,
// "sqrt",	sqrt,   /*	verifica rango */
// "int" ,	integer,
// //"abs",	fabs,
// 0,	0
// };

%}
%union {
	double val;
	char * bltin;
	Symbol *sym;
	RacionalAP racional_;
}

%token <racional_> racionalnum 
%token <val> NUMBER
%token <sym> VAR BLTIN INDEF
%type <racional_> asgn expr

%right '='
%left '+' '-'
%left '*' '/'
%left UNARYMINUS
%right '^'

%% /* A continuación las reglas gramaticales y las acciones */
list:   
	| list '\n'
	| list asgn '\n' { printf("%s\n", "assing" ); }
	| list expr '\n'  { imprimirR( $2 );}
	| list error '\n' { yyerrok; } 
	;
asgn:	VAR '=' expr {$$=$1->u.val=$3; $1->type=VAR;}
	;
expr: VAR { if($1->type == INDEF)
				execerror("variable no definida ",$1->name);
			$$=$1->u.val;
	      }
	| asgn
	| BLTIN  '(' expr ')' {
		printf("sen() = %lf\n",sin( $3 -> dec ) );
		$$= creaRacional( 1,1,(*($1->u.ptr))( $3 -> dec ), 0 ); 
	}
    | '(' expr ')'	{ $$ = $2;}
	//| '-' expr %prec UNARYMINUS { $$= -$2; }

	| racionalnum { 
		if($1 -> den == 0.0)
			execerror("division por cero", "");
		$$ = $1; 
	}
      | expr '+' expr { $$ = racionalSuma( $1, $3 ); }
      | expr '-' expr { $$ = racionalResta( $1, $3 ); }
      | expr '*' expr { $$ = racionalMultiplicar( $1, $3 ); }
      | expr '/' expr { $$ = racionalDividir( $1, $3 ); }
	;
%%

#include <stdio.h>
#include <ctype.h>
#include <signal.h>
#include <setjmp.h>

jmp_buf begin;

char *progname;
int lineno = 1;

int main (int argc, char *argv[]){
	progname=argv[0];
	init();
	setjmp(begin);
	signal(SIGFPE, fpecatch);
  	yyparse ();
}

void execerror(char *s, char *t){
	warning(s, t);
	longjmp(begin, 0);
}

void fpecatch(){
	execerror("excepcion de punto flotante", (char *)0);
}

// apf busca(){

// }//end busca
void yyerror (char *s)  /* Llamada por yyparse ante un error */
{
	warning(s, (char *) 0);
}

void warning(char *s, char *t)
{
	fprintf (stderr, "%s: %s", progname, s);
	if(t)
		fprintf (stderr, " %s", t);
	fprintf (stderr, "cerca de la linea %d\n", lineno);
}
