#ifndef SUPPORT_H
#define SUPPORT_H
#include<sstream>
#include<fstream>
#include<iostream>
#include<NTL/ZZ.h>
#include<NTL/vector.h> // para lehmer
using namespace NTL;
using namespace std;

#define MAX_POTENCIAS 3 // para generar un arreglo de potencias de la base PARA LEHMER

/*
	FUNCIONES:
		*inversa_in_modulo: este es el algoritmo eextendido de euclides para hallar en nuestro caso la x
		*modulo: devulve el resto de un division .
		*elevar_modulo: exponenciacion modulas
		*MCD: el mcd de a,b , quiza para numero pequeños
		*potenciar : similar a la expinenciacion modulas ,pero sin modulo
*/

ZZ inversa_in_modulo( ZZ&, ZZ&);
ZZ modulo(ZZ,ZZ);
ZZ elevar_modulo(ZZ, ZZ, ZZ); // num/exp/mod
ZZ MCD(ZZ,ZZ);
ZZ potenciar(int bits ,int number = 2);


///////////////////////////////////////////////////////////////////
//	IMPLEMENTACION DE LEHMER
//	INPUT
//		Dos números x, y (x>=y) enteros positivos en cierta base b.
//	OUTPUT
//		mcd(x,y).
////////////////////////////////////////////////////////////////////

ZZ lehmer_gcd(ZZ x, ZZ y);

ZZ dijkstra_euclides(ZZ a, ZZ b);

ZZ b_binaria(ZZ num, Vec<ZZ> arr, ZZ low, ZZ high); // devuelve el valor de la potencia <= num dentro de arr

Vec<ZZ> genera_array_base(ZZ base);

ZZ digitos_base(ZZ num, Vec<ZZ>arr, ZZ &grupos);



int cantidad_digitos(ZZ);

ZZ convert_ZZ(string);


/*
    convierte string a entero
*/
int convert_entero(string);

string convert_string(ZZ);

int potenciar_int( int, int);


#endif // SUPPORT_H
