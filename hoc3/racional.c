// #include <stdio.h>
#include "racional.h"
#include <stdlib.h>

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
	int nvonum = (r -> num * s -> den) + (s -> num * r -> den);
	int nvoden = r -> den * s -> den;
	Racional *nvo = creaRacional(nvonum, nvoden, (double)((double)nvonum/(double)nvoden), 1 );
	return nvo; 
}
Racional* racionalResta(Racional *r, Racional *s){
	int nvonum = (r -> num * s -> den) - (s -> num * r -> den);
	int nvoden = r -> den * s -> den;
	Racional *nvo = creaRacional(nvonum, nvoden,(double)((double)nvonum/(double)nvoden), 1 );
	return nvo; 
}
Racional* racionalMultiplicar(Racional *r, Racional *s){
	int nvonum = r -> num * s -> num;
	int nvoden = r -> den * s -> den;
	Racional *nvo = creaRacional(nvonum, nvoden,(double)((double)nvonum/(double)nvoden), 1 );
	return nvo; 
}

Racional* racionalDividir(Racional *r, Racional *s){
	int nvonum = r -> num * s -> den;
	int nvoden = r -> den * s -> num;
	Racional *nvo = creaRacional(nvonum, nvoden,(double)((double)nvonum/(double)nvoden), 1 );
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