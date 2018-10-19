#include "racional_cal.h"
#include "y.tab.h"
#include <stdlib.h>
#include <stdio.h>
static Symbol *simlista = 0;
Symbol *lookup(s)
	char *s;
{
	
	Symbol *sp;
	for (sp = simlista; sp != (Symbol *) 0; sp = sp->sig)
		if(strcmp(sp->nombre,s)==0)
			return sp;
		// else
		// 	printf("No encontramos a %s con %s\n", s, sp->nombre );

	return 0;
}
Symbol *install(char *s,int t, RacionalAP r) /* instalar s en la tabla de símbolos */
{
	Symbol *sp;
	char *emalloc();
	sp = (Symbol *) emalloc(sizeof(Symbol));
	sp->nombre = emalloc(strlen(s)+ 1) ; /* +1 para '\0' */
	strcpy(sp->nombre, s);
	sp->tipo = t;
	sp->u.val = r;
	sp->sig  =  simlista;   /*  poner al frente de la lista   */
	simlista =  sp; 
        return sp; 
}
char * emalloc(n)
	unsigned n;
{
	void *p = NULL;
	p = malloc(n);
	return p;
}
	

