#include <stdio.h>
#include <stdlib.h>
#include "racional_cal.h"
// int main() { return yyparse(); }
// int yyerror(const char* s) { 
//   printf("%s\n", s); 
//   return 0; 
// }
Racional *creaRacional(int num, int den, double dec, int type){
   Racional *nvo;
   if(den==0)
	return (Racional *)NULL;
   nvo=(Racional *)malloc(sizeof(Racional));
   if(!nvo){
	puts("no hay memoria para crear Racional ");
        return (Racional *)NULL;
   }  
   nvo->num=num;
   nvo->den=den;
   nvo->dec=dec;
   nvo->type=type;
   return nvo;
}
void asignar(Racional *r, int num, int den){
   r -> num = num; r -> den = den;
}
int numerador(Racional *r){ return r ->num; }
int denominador(Racional *r){ return r ->den; }
Racional* racionalSuma(Racional *r, Racional *s){
	
	Racional *nvo;
	if( r -> type == 0 || s -> type == 0 )
		nvo = creaRacional(1, 1, (double)(r -> dec + s -> dec), 0 );
	else {
		int nvonum = (r -> num * s -> den) + (s -> num * r -> den);
		int nvoden = r -> den * s -> den;
		nvo = creaRacional(nvonum, nvoden, (double)((double)nvonum/(double)nvoden), 1 );
	} // end else

	return nvo; 
}
Racional* racionalResta(Racional *r, Racional *s){
	Racional * nvo;
	if( r -> type == 0 || s -> type == 0 )
		nvo = creaRacional(1, 1, (double)(r -> dec - s -> dec), 0 );
	else {
		
		int nvonum = (r -> num * s -> den) - (s -> num * r -> den);
		int nvoden = r -> den * s -> den;
		nvo = creaRacional(nvonum, nvoden,(double)((double)nvonum/(double)nvoden), 1 );

	} // end else
	return nvo; 
}
Racional* racionalMultiplicar(Racional *r, Racional *s){
	Racional * nvo;
	if( r -> type == 0 || s -> type == 0 )
		nvo = creaRacional(1, 1, (double)(r -> dec * s -> dec), 0 );
	else {
		int nvonum = r -> num * s -> num;
		int nvoden = r -> den * s -> den;
		nvo = creaRacional(nvonum, nvoden,(double)((double)nvonum/(double)nvoden), 1 );
	} // end else
	return nvo; 
}

Racional* racionalDividir(Racional *r, Racional *s){
	Racional *nvo;
	if( r -> type == 0 || s -> type == 0 ){
		if( s -> dec != 0 )
			nvo = creaRacional(1, 1, (double)(r -> dec / s -> dec), 0 );
		else
			printf("Divisón sobre cero .-.\n");
	} else {
		int nvonum = r -> num * s -> den;
		int nvoden = r -> den * s -> num;
		nvo = creaRacional(nvonum, nvoden,(double)((double)nvonum/(double)nvoden), 1 );
	} // end else
	return nvo; 
}

int esIgual(Racional *r, Racional *s){
	return (r -> num * s -> den) == (r -> den * s -> num);
}

double convertirRacionalDouble( Racional * r ) {
	int n = numerador( r );
	int d = denominador( r );
	return ( d != 0 ) ? ( (double) n/d ) : 0;
} // end convertirRacionalDouble

void imprimirR(void *r){
	Racional *p = (Racional*)r;
	if( p -> type == 1 )
		printf("(%d / %d) = (%0.2lf)\n", p -> num, p -> den, p -> dec);
	else
		printf("= %0.2lf\n", p -> dec);
}

Racional *copiar(Racional *r){
	return creaRacional(r -> num, r -> den,(double)((double)r -> num/(double)r -> den), r -> type);
}