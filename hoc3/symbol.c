#include <math.h>
#include  "racional.h" 
#include  "hoc.h" 
#include  "y.tab.h"

static Symbol *symlist=0;    /* tabla de simbolos: lista ligada */

Symbol *lookup(char *s)    /* encontrar s en la tabla de s�mbolos */
{
	Symbol  *sp;
	for (sp = symlist; sp != (Symbol *)0; sp = sp->next) 
		if (strcmp(sp->name, s)== 0) 
			return sp;
	return 0;      /* 0 ==> no se encontr� */ 
}


Symbol *installR(char *s,int t, RacionalAP r) /* instalar s en la tabla de s�mbolos */
{
	Symbol *sp;
	char *emalloc();
	sp = (Symbol *) emalloc(sizeof(Symbol));
	sp->name = emalloc(strlen(s)+ 1) ; /* +1 para '\0' */
	strcpy(sp->name, s);
	sp->type = t;
	sp->u.val = r;
	sp->next  =  symlist;   /*  poner al frente de la lista   */
	symlist =  sp; 
        return sp; 
}


char  *emalloc(unsigned n)	/*   revisar el regreso desde malloc  */
{
char *p,   *malloc();
	p = malloc(n); 
	if(p == 0)
		execerror("out of memory", (char  *)  0); 
	return p; 
}
