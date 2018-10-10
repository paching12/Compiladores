#include <stdio.h>

struct racional {
	int num, den, type;
	double dec;
};

typedef struct racional Racional;
typedef struct racional* RacionalAP;
/*  prototypes of the provided functions */ 
Racional *creaRacional(int num, int den, double dec, int type  );
void asignar(Racional *r, int num, int den);
int numerador(Racional *r);
int denominador(Racional *r);
Racional* racionalSuma(Racional *r, Racional *s);
Racional* racionalResta(Racional *r, Racional *s);
Racional* racionalMultiplicar(Racional *r, Racional *s);
Racional* racionalDividir(Racional *r, Racional *s);
int esIgual(Racional *r, Racional *s);
double convertirRacionalDouble( Racional * r );
void imprimirR(void *r);
Racional *copiar(Racional *r);

