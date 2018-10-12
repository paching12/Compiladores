%{
#include <stdio.h>
#include <math.h>
#include "racional_cal.h"

void yyerror (char *s);
int yylex ();
void warning(char *s, char *t);
%}

%union{
  Racional *racional;
  int integer;
}
%token <integer> NUMBER
%type <racional> fraccion 
%left '+' '-'
%left '*' '/'
%% 
list:   
	| list'\n'
      | list exp '\n'
	;
exp:  fraccion
      | fraccion '+' fraccion
  ;
fraccion: NUMBER 'v' NUMBER {
      // printf("%s\n", "Creo que vi un linda racional" );
    }
  ;
%%

#include <stdio.h>
#include <ctype.h>
char *progname;
int lineno = 1;

void main (int argc, char *argv[]){
	progname=argv[0];
  	yyparse ();
}
int yylex (){
  	int c;
  	while ((c = getchar ()) == ' ' || c == '\t')  
  		;
 	if (c == EOF)                            
    		return 0;
  	if ( isdigit (c) ) {
      		ungetc (c, stdin);
      		scanf ("%d", &yylval);
	      return NUMBER;
    	}
  	if(c == '\n')
		lineno++;
  	return c;                                
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