#include "racional.h"
#include  <math.h>
#include  <errno.h>

extern    int	errno;
double   errcheck();


double  Log(double x)
{
	return errcheck(log(x), "log");
}

// double  Log10(Racional *x)
// {
// 	int num = numerador( x );
// 	int den = denominador( x );
// 	int entero = num / den;
// 	return  errcheck(log10(entero), "log10"); 
// }

// double  Exp(Racional *x)
// {
// 	int num = numerador( x );
// 	int den = denominador( x );
// 	int entero = num / den;
// 	return  errcheck(exp(entero) , "exp"); 
// } 

// double  Sqrt(Racional *x)
// {
// 	int num = numerador( x );
// 	int den = denominador( x );
// 	int entero = num / den;
// 	return  errcheck(sqrt(entero), "sqrt");
// }

double Pow(Racional *x, double y)
{
	int num = numerador( x );
	int den = denominador( x );
	int entero = num / den;
	return errcheck(pow(entero,y), "exponentiation");
}

double integer(Racional *x) 
{
	int num = numerador( x );
	int den = denominador( x );
	int entero = num / den;
	return ((long)entero);
}

double errcheck(double d, char *s)   /* revisar el resultado de la llamada                            a la biblioteca */
{
	if (errno == EDOM) {
		errno = 0;
		execerror(s, "argument out of donain"); 
	} else if (errno == ERANGE) {
		errno = 0;
		execerror(s,"result out of range"); 
        } 
        return d;
}
