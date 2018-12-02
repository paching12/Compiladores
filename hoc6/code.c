#include "racional_cal.h" 
#include "y.tab.h"
#define NSTACK  256
static  Datum  stack[NSTACK];  /* la pila */
static  Datum   *stackp;       /* siguiente lugar libre en la pila */
#define NPROG   2000
Inst    prog[NPROG];    /* la máquina */
Inst    *progp;         /* siguiente lugar libre para la generación de código */
Inst    *pc;	/* contador de programa durante la ejecución */


initcode()      /* inicialización para la generación de código */ {
stackp = stack;
progp = prog;
}

push(d)	/*  meter d en la pila  */
Datum d; 
{
if (stackp >= &stack[NSTACK])
execerror("stack overflow", (char *) 0);
*stackp++ = d;
}

Datum pop( )     /* sacar y retornar de la pila el elemento del tope */
{
if (stackp <= stack)
execerror("stack underflow", (char *) 0);
return  *--stackp;
}

pop1( )     /* sacar y retornar de la pila el elemento del tope */
{
if (stackp <= stack)
execerror("stack underflow", (char *) 0);
	--stackp;
}

Inst   *code(Inst f) /*   instalar una instrucción u operando   */
{
Inst *oprogp = progp;
	if (progp >= &prog [ NPROG ])
		execerror("program too big", (char *) 0);
	*progp++ = f;
	return oprogp;
}

execute(Inst *p)	/*   ejecución con la máquina   */
{
for  (pc  =  p;   *pc != STOP; ) 
	(*(*pc++))();
}
constpush( )	/* meter una constante a la pila  */
{
Datum d;
d.val  =  ((Symbol  *)*pc++)->u.val;
push(d);

}

varpush()	/* meter una variable a la pila   */
{
Datum d;
d.sim  =  (Symbol   *)(*pc++);
push(d);
}
forcode() {
Datum d;
Inst *savepc = pc;
execute(savepc+4); // Inicializacion
execute(*((Inst  **)(savepc)));//condicion
d=pop();
printf("%lf",d.val->dec);
while(d.val->dec){
		
	execute(*((Inst  **)(savepc+2)));//cuerpo

	execute(*((Inst  **)(savepc+1)));//incremento
	
	execute(*((Inst  **)(savepc)));//condicion
	d=pop();
}
pc  =  *((Inst  **)(savepc+3));   
// while(d.val->dec) {
// execute(*((Inst  **)(savepc))); //asignacion;
// 	execute(savepc+4);
// 	d=pop();
// }

}
whilecode() {
Datum d;
Inst  *savepc  = pc;	/*  cuerpo de la iteración  */
execute(savepc+2);     /*   condición   */ 
d  =  pop(); 
while   (d.val->dec)   {
execute(*((Inst  **)(savepc)));     /*  cuerpo  */
execute(savepc+2);
d  = pop(); 
} 
pc  =  *((Inst  **)(savepc+1));     /*   siguiente proposición   */
}


ifcode()
{
Datum d;
Inst  *savepc  = pc;	/* parte then */
execute(savepc+3);	/*  condición   */
d  =  pop(); 
imprimirR(d.val);
if(d.val->dec)
	execute(*((Inst **)(savepc)));
else if (*((Inst **)(savepc+1)))
execute(*(( Inst  **) (savepc+1)));
pc = *((Inst **)(savepc+2));
}



eval( )	/*  evaluar una variable en la pila   */
{
Datum  d;
d   =  pop();
if   (d.sim->tipo   ==   undef)
execerror("undefined variable",   
d.sim->nombre); 
d.val   =  d.sim->u.val; push(d);
}




add( )	/*   sumar los dos elementos superiores de la pila   */
{
Datum d1,   d2; 
d2  =  pop(); 
d1   =  pop(); 
d1.val = racionalSuma(d1.val, d2.val); push(d1); 
}

sub()
{
Datum d1,  d2; 
d2  = pop(); 
d1  = pop(); 
d1.val = racionalResta(d1.val, d2.val);
push(d1);
}

mul()
{
Datum d1, d2;
d2 = pop(); 
d1 = pop(); 
d1.val = racionalMultiplicar(d1.val, d2.val); 
push(d1);
}


divi( )
{
Datum d1, d2;
d2 = pop();
d1 = pop(); 
d1.val = racionalDividir(d1.val, d2.val);
push(d1);
}

gt() {
Datum d1,  d2,d3;
d2 = pop();
d1 = pop();
d3.val = creaRacional(0, 1, 0.0, 0);
d3.val->dec =   (double)(d1.val->dec  > d2.val->dec);
push(d3);
}

lt()
{
Datum d1,  d2,d3;
d2 = pop();
d1 = pop();
d3.val = creaRacional(0, 1, 0.0, 0);
d3.val->dec  =   (double)(d1.val->dec  < d2.val->dec);
push(d3);
}

ge( ) {
Datum d1,  d2,d3;
d2  = pop();
d1  = pop();
d3.val = creaRacional(0, 1, 0.0, 0);
d3.val->dec   =   (double)(d1.val->dec  >= d2.val->dec);
push(d3) ;
}

le() {
Datum d1,  d2,d3;
d2   =  pop();
d1   =  pop();
d3.val = creaRacional(0, 1, 0.0, 0);
d3.val->dec  =   (double)(d1.val->dec   <=  d2.val->dec);
push(d3);
}

eq( ) {
Datum d1,  d2,d3;
d2  = pop();
d1  = pop();
d3.val = creaRacional(0, 1, 0.0, 0);
d3.val->dec  =   (double) (d1.val->dec  ==  d2.val->dec);
push(d3);
}

ne(){
Datum d1, d2,d3;
d2 = pop();
d1 = pop();
d3.val = creaRacional(0, 1, 0.0, 0);
d3.val->dec = (double)(d1.val->dec != d2.val->dec);
push(d3);
}

and()
{
Datum d1,   d2,d3;
d2   = pop();
d1   = pop();
d3.val = creaRacional(0, 1, 0.0, 0);
d3.val->dec = (double)(d1.val->dec   !=   0.0 && d2.val->dec   !=  0.0);
push(d3);
}

or()
{
Datum d1, d2,d3;
d2 = pop();
d1 = pop();
d3.val = creaRacional(0, 1, 0.0, 0);
d3.val->dec = (double)(d1.val->dec != 0.0 || d2.val->dec!=0.0);
push(d3);
}

not( )
{
Datum d,d3;
d = pop();
d3.val = creaRacional(0, 1, 0.0, 0);
d3.val->dec = (double)(d.val->dec == 0.0);
push(d3);
}

assign( )        /* asignar el valor superior al siguientevalor */ 
{
Datum d1, d2;
d1 = pop();
d2 = pop();
if (d1.sim->tipo != var && d1.sim->tipo != undef) 
execerror("assignment to non-variable", d1.sim->nombre);
d1.sim->u.val = d2.val;
d1.sim->tipo = var;
push(d2);
} 

print( )  /* sacar el valor superior de la pila e imprimirlo */ 
{
Datum d;
d = pop();
imprimirR(d.val);
}
prexpr( ) /*   imprimir el valor numérico   */
{
Datum d;
d = pop();
printf("\t\t");imprimirR(d.val);
}


BLTIN( )/*  evaluar un predefinido en el tope de la pila  */
{
	Datum d;
	d  =  pop();
	d.val -> dec  =   (*(double   (*)())(*pc++))(d.val -> dec);
	d.val -> type = 0;
	push(d);
}
 


