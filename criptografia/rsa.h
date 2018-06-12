#ifndef RSA_H
#define RSA_H
//#include<iostream>
//#include<NTL/ZZ.h>
#include"aleatorios.h" // general
#include"support.h"
//using namespace NTL;
//susing namespace std;

#define ext ".txt"
using Clave = std::pair<ZZ, ZZ>;

class RSA{

protected:
	ZZ p;
	ZZ q;
	ZZ n;
	ZZ fi_n;
	ZZ e;
	ZZ d;
	ZZ generate_N();
	ZZ generate_Fi_N();
	ZZ form_get_d();
	string alfabeto;

public:
	RSA(int); // int  nro de bits
	ZZ getN()const;
	ZZ getE()const;
	string getAlfabeto();
	ZZ form_get_e(int);//bits-1 menor que fi(n)
	Clave generate_key_public();
	Clave generate_key_private();
	ZZ Cifrar(ZZ, ZZ, ZZ); //< mensaje/clave_e/n >

	void Cifrar_Bloque(string,ZZ,ZZ); //<mensaje/clave/_e/n>
	void Descifrar_Bloque();// <mensaje_cifrado>

	ZZ Descifrar(ZZ); // < mensajecifrado >
	void save_keys(Clave &);
	Clave sacar_keys();
	string convertir_to_string_numbers(string); // name del file
	void convertir_to_string_characters();
};




#endif // RSA_H
