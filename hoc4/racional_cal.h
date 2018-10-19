#include <string.h>

struct racional {
	int num, den, type;
	double dec;
};
typedef struct racional Racional;
typedef struct racional* RacionalAP;
typedef struct Symbol 
{
	char *nombre;
	short tipo;
	union
	{
		RacionalAP val;
		double (*ptr)();		
	}u;
	struct Symbol *sig; 
}Symbol;
Symbol *install(),*lookup();

/*  prototypes of the provided functions */ 
typedef union Datum {   /* tipo de la pila del intérprete */
RacionalAP  val;
Symbol  *sim; } Datum; 

extern Datum pop();
typedef int (*Inst)();  /* instrucción de máquina */ 

#define STOP    (Inst) 0
extern	Inst prog[];
extern	eval(), add(), sub(), mul(), divi();
extern	assign(), BLTIN(), varpush(), constpush(), print();

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

/*  prototypes of the provided functions */ 
/* define the return type of FLEX */

