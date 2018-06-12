#include"aleatorios.h"
#include"rsa.h"

int main(){
/*

	// PARA UN LIMITE DE NRO DE BITS
	ZZ cont;
	cont = 0 ;
	int bits; cout << "bits: "; cin >> bits;
    Alea ale(bits);
    cout << endl << "semilla: "<<  ale.getSeed() << endl;
    cout << "m: " << ale.getM() << endl;
   	cout << "c: " << ale.getC() << endl;
    cout << "a: " << ale.getA() << endl;

	ZZ x;
	for ( x = 0; x <   ( potenciar(bits) - potenciar(bits - 1) ) + 2; x++){ // +2 para verificar la huelta
		cout << ale.aleatorio_of_bits() << " ";
		cont++;
    }
   	cout << endl << "Contador: " << cont << endl;
	cout << endl << endl;






   	ZZ max,e;
   	cout << "Maximo: "; cin >> max;
   	Alea alemax(max);
   	cout << "aleatorio de maximos: " << endl;
   	for(e = 0 ; e < 2* (max+1);  e++){
		cout << alemax.aleatorio_of_maximo() << endl;
   	}
   	cout << "info max" << endl;
   	cout << "m_maximo: " << alemax.getM() << endl;
   	cout << "c_max: " << alemax.getC() << endl;
   	cout << "a_max: " << alemax.getA() << endl;





	int n; cout << "n: "; cin >> n;
	cout << potenciar(n) << endl;
   	ZZ a,b;
   	a = 1200; b= 3600;
   	cout << "gcd con lehmer: " << lehmer_gcd(a,b) << endl;





	ZZ e;
	for(e = 8  ; e < 1000 ; e++){
		if(Miller_Rabin(e) == 1)
			cout << e << ", ";
	}
	cout  << endl << " 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997 " << endl;
	*/



/*
	int bits; cout << "Nro de bits "; cin >> bits;
	Alea aleatorios(bits);
	for(int e = 0 ; e < 10; e++)
		cout << aleatorios.primo_aleatorio() << " ";
	cout << endl;
	//ZZ a,b;
	//a = potenciar(1000);
	//b = potenciar(1024);
	//cout << lehmer_gcd(to_ZZ(1299),b) << endl;
*/


/*
	ZZ MENSAJE, CIFRADO,DESCIFRADO;
	MENSAJE = RandomLen_ZZ(5); // mensaje inferior a bits of p and q
	CIFRADO = usuarioA.Cifrar(MENSAJE,Bp.first,Bp.second);
	DESCIFRADO = usuarioB.Descifrar(CIFRADO);

	cout << "MENSAJE: " <<  MENSAJE << endl << endl;
	cout << "CIFRADO: " << CIFRADO << endl << endl;
	cout << "DESCIFRADO: " << DESCIFRADO << endl << endl;
*/



/*
												RSA
							USUARIO_B QUIERE ENVIAR UN MENSAJE A USUARIO_A
							AQUI EMPIEXZA TODO.
*/


//////////////////////////////////////////////////////////////////////////////////////////////////////////////


	Clave Apublica,APRIVADA,Bpublica,BPRIVADA, clavesA;
	int bits; cout << "bitssss: "; cin >> bits;
	RSA usuarioA(bits), usuarioB(bits);

	Apublica = usuarioA.generate_key_public();
	APRIVADA = usuarioA.generate_key_private();

	Bpublica = usuarioB.generate_key_public();
	BPRIVADA = usuarioB.generate_key_private();

	//cout << "datos de e y m " << endl;
	//cout << usuarioA.getE() << endl << endl;
	//cout << usuarioA.getN() << endl;

	//cout << "viendo la info de la clave " << endl;
	//cout << Ap.first << endl << endl;
	//cout << Ap.second << endl << endl;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
		el usuarioA guardara la clave publica en un file por defecto llamado directorio_publico.txt
	*/
	usuarioA.save_keys(Apublica);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
		usuarioB sacara las llaves del usuarioA para poder enviar sms
	*/
	clavesA = usuarioB.sacar_keys();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
		en un file YYYYYYYYYY.tx se guardar el mensaje que se quiere enviar al usuarioA
	*/
	string NameFile; cout << "Nombre del file del  Mensaje "; cin >> NameFile; //name del folder dond esta el msg
 	string cadena_numeros;

	//UsuarioB convertira su mensaje en un string de numeros
	cadena_numeros = usuarioB.convertir_to_string_numbers(NameFile); // name del archivo
	//cout << string_numeros << endl;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
		CIFRAMIENTO DEL MENSAJE
		el mensaje a cifrar sera la cadena de numeros que convirtio

		el mensaje cifrado por defecto se guardara en el file llamada cifrado.txt
	*/
	usuarioB.Cifrar_Bloque(cadena_numeros, clavesA.first, clavesA.second);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
		UNA VES FORMADO EL CIFRADO.txt
		EL USUARIO_A SE DA CUENTA QUE LE QUIEREN ENVIAR UN MENSAJE Y COGE EL ARCHIVO CIFRAR.TXT PARA
		DESCIFRARLO

		el file oir defectco en donde se guardara el descifrado se llamara descifrado.txt
	*/

	usuarioA.Descifrar_Bloque();
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 	/*
		una ves descifrado el mensaje el usuarioA podra convetirlo a una cadena de caraccteres y ver el mensaje
		el nombre del file se pedira por consola .
	*/
	usuarioA.convertir_to_string_characters();


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    return 0;
}
