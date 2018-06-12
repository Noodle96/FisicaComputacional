#ifndef ALEATORIOS_H
#define ALEATORIOS_H

//#include<NTL/ZZ.h>

#include"support.h" // para modulo amoung others
#include"primalidad.h"

using namespace std;
using namespace NTL;

class Alea{
protected:
	ZZ seed,a, c,m;
	ZZ maximo; // atributo para el segundo constructorZZ potenciar(int exp, int number = 2);
	int bits;
	ZZ primo;
public:
   	Alea(int bits);
	Alea(ZZ maximo);

	void setSeed(ZZ);
	ZZ getSeed();
	ZZ getM();
	ZZ getC();
	ZZ getA();

    ZZ formar_m();

	/*
		criterio 1 de HULL-dobel
	*/
	ZZ formar_c();
	ZZ formar_a(int n);

	ZZ aleatorio_of_bits(); // para el primer constructor
   	ZZ aleatorio_of_maximo();// para el segundo constructor
   	ZZ primo_aleatorio(); // devuelve un primo en el rango dado
};



#endif // ALEATORIOS_H
