%option noyywrap
%{
#include <stdio.h>
#include <stdlib.h>
#include "racional_cal.h"
#include "y.tab.h"
void RmWs(char* str);
extern YYSTYPE yylval;
%}
/* Add your Flex definitions here              */
/* Some definitions are already provided to you*/
op [-+*/()=]
ws [ \t]+
digits [0-9]
var [a-zA-z][a-zA-Z0-9]*
number (0|[1-9]+{digits}*)
im [i]
fr [+]
racionalnum {ws}*[-]*{ws}*{number}{ws}*{fr}{ws}*{number}{ws}*

%%
{var} {
	Symbol *s;
	lookup(yytext);
	if ((s=lookup(yytext)) == 0 )
		s= install(yytext,undef,0.0);
	yylval.sim = s;
	return s->tipo == undef ? var: s -> tipo;
}

{racionalnum} {
 int num, den;
 RmWs(yytext); 
 sscanf(yytext,"%d %d", &num, &den); 
 yylval.sim=install("",racionalnum,creaRacional(num, den, (double)((double)num/(double)den), 1));
 return racionalnum;}

{op} |
\n {
	return *yytext;}
{ws} { /* Do nothing */ } 
. { /* Do nothing */ }

%%
/* function provided to student to remove */
/* all the whitespaces from a string.     */
/* input :       a string of chars        */
/* output:       nothing                  */
/* side effect:  whitespace in the        */
/*               original string removed  */
/* return value: none                     */
void RmWs(char* str) {
  int i = 0, j = 0;
  char temp[strlen(str) + 1];
  strcpy(temp, str);
  while (temp[i] != '\0') {
    while (temp[i] == ' ')
      i++;
    str[j] = temp[i];
    i++;
    j++;
  }
 str[j] = '\0';
}

