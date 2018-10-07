%option noyywrap
%{
#include "hoc.h"
#include "racional.h"
#include "y.tab.h"

void RmWs(char* str);
extern YYSTYPE yylval;
%}
/* Add your Flex definitions here              */
/* Some definitions are already provided to you*/
op [-+*/()=]
ws [ \t]+
digits [0-9]
letters [A-Za-z]+
number (0|[1-9]+{digits}*)
sub [n]
fr [+]
racionalnum {ws}*{sub}?{ws}*{number}{ws}*{fr}{ws}*{number}{ws}*
NUMBER {ws}*{sub}?{ws}*{digits}+{ws}*[\.]?{ws}*{digits}*{ws}*
%%
{letters} {
  RmWs(yytext);
  Symbol *s;
  // int c;
  // char sbuf[200], *p=sbuf;
  // do {
  //   *p++=c;
  //   printf("%s\n", sbuf );
  // } while ( ( c=getchar())!=EOF && isalnum(c) );
  if( ( s = lookup(yytext) ) == (Symbol *) NULL )
    s = install( yytext, INDEF, 0.0 );

  yylval.sym=s;
  if(s->type == INDEF){
    // printf(":%s\n", "nueva" );
    return VAR;
  }
  else {
    return s->type;
  }
}
{NUMBER} {
  RmWs(yytext);
  sscanf(yytext, "%lf", &yylval.val);
  return NUMBER;
}
{racionalnum} {
 int num, den;
 RmWs(yytext); 
 printf("(%s)", yytext);
 sscanf(yytext,"%d %d", &num, &den); 
 yylval.racionales=creaRacional(num, den);
 return racionalnum;}
{op} |
\n {return *yytext;}
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

