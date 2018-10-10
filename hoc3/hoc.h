#include <string.h>
#include <stdio.h>

typedef struct Symbol { /* entrada de la tabla de s�mbolos */
	char   *name;
	short   type;   /* VAR, BLTIN, UNDEF */
	union {
		RacionalAP val;	       /* si es VAR */
		double  (*ptr)();      /* s� es BLTIN */
	} u;
	struct Symbol   *next;  /* para ligarse a otro */ 
} Symbol;

Symbol *installR(char *s,int t, RacionalAP r), *lookup(char *s);
