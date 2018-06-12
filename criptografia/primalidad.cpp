#include"primalidad.h"

/*
	generarremos un primo aleatorio dondole de parametro la cantidad de bits
	y para ello utilizaremos el test de Miller-Rabin
*/

/*
	ALGORITMO DE DE MILLER RABIN
	Entrada # 1 : n > 3, un entero impar para ser probado para primality;
	Entrada # 2 : k , un parámetro que determina la precisión de la prueba
 	Salida : compuesto si n es compuesto, de lo contrario probablemente primo


	Escribe n - 1 como 2 ^ r · d con d odd por factoring de 2 de n - 1

 	WitnessLoop: repetir k veces:
    	Escoge un entero aleatorio a en el rango [2, n - 2]
    	X ← a^d mod n
    	Si x = 1 o x = n - 1 entonces
			Continúa WitnessLoop
    	Repita r - 1 veces:
			X ← x 2 mod
        	Si x = 1 entonces
            	Compuesto de retorno
       		Si x = n - 1 entonces
          		Continúa WitnessLoop
    	Compuesto de retorno
 	Regreso probablemente prime

*/
bool Miller_Rabin(ZZ n){
	if( (n < 2) || ( n!=2 && modulo(n,to_ZZ(2)) == 0) )
		return false;

	//escribiremos un n - 1 como un 2 ^ r * d y sacaremos el r y d
	ZZ d, r;
	r = 0;
	d  = n - 1;
	while( modulo(d,to_ZZ(2)) == 0){
		r++;
		d /= 2;
	}
	//ahora daremos las k-vueltas nesesarias para la precision -> define
	Alea aleatorio(n); //aleatorio de tipo ALea que recibe un maximo n
	ZZ a; //aleatorio
	ZZ X;
	bool continue_first_bloque;
	for(auto e = 0 ; e < PRECICION; e++){
		a = aleatorio. aleatorio_of_maximo();
		continue_first_bloque = false;
		X = elevar_modulo(a,d,n);
		if( X == 1 || X == n-1)
			continue;

		for(int j = 1 ; j < r ; j++){ //se repite r-1 veces
			X = elevar_modulo(X,to_ZZ(2),n);
			if ( X == 1 )
				return false;
			if( X == n-1 ){
				continue_first_bloque = true;
				break;
			}
		}
		if(!continue_first_bloque)
			return false;
	}
	return true;
}
