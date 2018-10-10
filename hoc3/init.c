#include "racional.h"
#include "hoc.h"
#include "y.tab.h"
#include <math.h>

//extern double Log(), Log10(), Sqrt(), Exp( ) , integer ( ) ;
extern integer();
static struct {         /* Constantes */ char *name; double cval;
} consts[] = {
"PI",    3.14159265358979323846,
"E",     2.71828182845904523536,
"GAMMA", 0.57721566490153286060,  /* Euler */
"DEG",  57.29577951308232087680,  /* grado/radian */
"PHI",   1.6180339887498948*820,  /* proporcion dorada */
0,       0
};

static struct {	/*	Predefinidos */
char *name;
double	(*func)();
} builtins[] =	{
"sin",	sin,
"cos" ,	cos,
"atan",	atan,
"log", log,
"log10", log10,
"exp", exp,
"sqrt",	sqrt,   /*	verifica rango */
"int" ,	integer,
//"abs",	fabs,
0,	0
};

init( )  /* instalar constantes y predefinidos en la tabla */
{
int i;
Symbol *s;
RacionalAP * r;
for (i = 0; consts[i].name; i++) {
	r = creaRacional( 0, 1, consts[i].cval, 0 );
	installR(consts[i].name, VAR, r );
} // end for

for (i = 0; builtins[i].name; i++) {
	r = creaRacional( 0, 1, 0.0, 0 );
	s = installR(builtins[i].name, BLTIN, r);
	s->u.ptr = builtins[i].func;
}
}
