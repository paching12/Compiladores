%{
#include <stdio.h>
#include <math.h>
#include "racional_cal.h"

// int yylex ();
void warning(char *s, char *t);
%}

%token racionalnum number fr
%left '+' '-'
%left '*' '/'
%% 
list:   
	| list'\n'
      | list exp '\n' { imprimirR( $2 ); }
	;
exp:  racionalnum { $$ = $1; }  
      | exp '+' exp { $$ = racionalSuma( $1, $3 ); }
      | exp '-' exp { $$ = racionalResta( $1, $3 ); }
      | exp '*' exp { $$ = racionalMultiplicar( $1, $3 ); }
      | exp '/' exp { $$ = racionalDividir( $1, $3 ); }
      
      | racionalnum '+' racionalnum { $$ = racionalSuma( $1, $3 ); }
      | racionalnum '-' racionalnum { $$ = racionalResta( $1, $3 ); }
      | racionalnum '*' racionalnum { $$ = racionalMultiplicar( $1, $3 ); }
      | racionalnum '/' racionalnum { $$ = racionalDividir( $1, $3 ); }
  ;
%%

#include <stdio.h>
#include <ctype.h>
char *progname;
int lineno = 1;

void warning(char *s, char *t){
	fprintf (stderr, "%s: %s", progname, s);
	if(t)
		fprintf (stderr, " %s", t);
	fprintf (stderr, "cerca de la linea %d\n", lineno);
}