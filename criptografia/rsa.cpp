#include"rsa.h"

/*
	generando primos aleatorios  p y q de manera privada.
	a = 00			A = 27 			1 = 53
	b = 01			B = 28			2 = 54
	c = 02			C = 29			3 = 55
	d = 03			D = 30			4 = 56
	e = 04			E = 31			5 = 57
	f = 05			F = 32			6 = 58
	g = 06			G = 33			7 = 59
	h = 07			H = 34			8 = 60
	i = 08			I = 35			9 = 61
	j = 09			J = 36			0 = 62
	k = 10			K = 37
	l = 11			L = 38
	m = 12			M = 39
	n = 13			N = 40
	o = 14			O = 41
	p = 15			P = 42
	q = 16			Q = 43
	r = !7			R = 44
	s = 18			S  = 45
	t = 19			T = 46
	u = 20			U = 47
	v = 21			V = 48
	w = 22			W  = 49
	x = 23			X = 50
	y = 24			Y = 51
	z = 25			Z = 52
   " "= 26
*/
RSA::RSA(int bits){
	alfabeto = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890+-*/.,";
	Alea aleatorio(bits);
	//p = GenPrime_ZZ(1024);
	//q = GenPrime_ZZ(1024);
	p = aleatorio.primo_aleatorio();
	q = aleatorio.primo_aleatorio();
	n = generate_N();
	fi_n = generate_Fi_N();
	e = form_get_e(bits-1);
	d = form_get_d();
}

//////////////////////////////////////////////////////////////////////////////////////

/*
	return n
*/
ZZ RSA::getN()const{
	return n;
}
/*
	get e
*/
ZZ RSA::getE()const{
	return e;
}

string RSA::getAlfabeto(){
	return alfabeto;
}

///////////////////////////////////////////////////////////////////////////////////////

/*
	n sera el modulo el que se trabajara   y se calculara con p * q
*/
ZZ RSA::generate_N(){
	return  p*q;
}


/*
	fi(n) = (p-1)*(q-1), ya que p y q son primos entonces tiene p-1 elementos que
	 son coprimos con  este.
*/
 ZZ RSA::generate_Fi_N(){
 	return (p-1) * (q-1);
 }

/////////////////////////////////////////////////////////////////////////////////////////

/*
	generando e, este formara parte de la clave publica. que tiene que cumplir con lo sgte
		*  1 <= e <= fi(n).
		*  coprimo con fi(n)-> GCD( e,fi(n) ) = 1.
*/
ZZ RSA::form_get_e(int b){ // remember that b = bits-1
	Alea aleatorio(b);
	ZZ pseudo_e;
	while(true){
		//e = GenPrime_ZZ(1023);
		pseudo_e = aleatorio.aleatorio_of_bits();// aleatorio [2 to 2^1024 -1]
		if (dijkstra_euclides(pseudo_e,fi_n) == 1 && pseudo_e < fi_n){
			break;
		}
	}
	return pseudo_e;
}

//////////////////////////////////////////////////////////////////////////////////////////

/*
	generando d, que este formara parte de la clave privada y sera formada mediante el
	algoritmo  extendido de euclides y cumplira que:
	d = (1/e)mod fi(n).
*/
ZZ RSA::form_get_d(){
	ZZ pseudo_d;
	ZZ es;
	es = getE();
	pseudo_d = inversa_in_modulo(es,fi_n);
	return pseudo_d;
};

//////////////////////////////////////////////////////////////////////////////////////////

/*
	crearemos un tipo clave donde se guardara <e,n>, con la intencion de que solo esta
	 funcion este publica.
*/
Clave RSA::generate_key_public(){
	return Clave(e,n);
}

/*
	De igualmanera crearemos  una clave privada <d,n>.
*/
Clave RSA::generate_key_private(){
    return Clave(d,n);
}

///////////////////////////////////////////////////////////////////////////////////////////

/*
	EL CIFRADO SE HARA CON (MENSAJE,E,N)
*/
ZZ RSA::Cifrar(ZZ sms, ZZ ete,  ZZ nte){
	return elevar_modulo(sms,ete,nte);
}

/////////////////////////////////////////////////////////////////////////////////////////////

/*
	EN  EL DESIFRADO  SOLO SE PASARA EL MENSAJE CIFRADO YA QUE EL CIFRAMIENTO SE HIZO CON LA
	LLAVE PUBLICA <e,n> DEL POSEEDOR Y ESTE TENIENDO AMBAS LLAVES , DESCIFRARA CON SU LLAVE
	PRIVADA <d,n>
*/
ZZ RSA::Descifrar(ZZ cifrado){
	return elevar_modulo(cifrado,d,n);
}
/////////////////////////////////////////////////////////////////////////////////////////////

/*
	guardaremos en el archivo directorio_publico.txt la clave publica Clave<e,n>
	para que luego otro cliente vengay en caso quiera mandar un mensaje a otro ,
	pues saque la Clave
*/
void RSA::save_keys(Clave &clave){
	fstream entrada;
	entrada.open("directorio_publico.txt", ios::out);
	entrada << clave.first << " " << clave.second << endl;
	entrada.close();
}
/*
	LAS CLAVES PUBLICAS <E,N> SE GUARDARAN EN UNNARCHIVO POR DEFECTO LLAMADO
	DIRECTORIO_PUBLICO.TXT
*/
Clave RSA::sacar_keys(){
	fstream salida;
	Clave clave;
	salida.open("directorio_publico.txt", ios::in );
		salida >> clave.first >> clave.second;
	salida.close();
	return clave;
}

/////////////////////////////////////////////////////////////////////////////////////////////
/*
	Se leera el mensaje el cual se wuiere enviar a la otra persona y lo convertira
	en una cadena de numeros respecto al ALFABETO mencionado.
*/

string RSA::convertir_to_string_numbers(string NameFile){
	char c;
	unsigned short digs;
	unsigned short  cont = 0;
	string cadena_numbers,lline;
	fstream salida;
	salida.open(NameFile+ext, ios::in);
	getline(salida,lline);

	while( cont != lline.length() ){
		c = lline[cont];
		digs = alfabeto.find(c);
		if(digs < 10)
			cadena_numbers += "0";
		cadena_numbers += to_string(digs);
		cont++;
	}
	salida.close();
	return cadena_numbers;
}


///////////////////////////////////////////////////////////////////////////////////////////////////

/*
	ciframiento por bloques
	el cifrado se guardara en el file llamado cifrado.txt
*/

void RSA::Cifrar_Bloque(string msg, ZZ e, ZZ n){
	string cadena_numbers_cifrada;
	string bloque_str;
	ZZ bloque_ZZ;
	int len_bloque_entero_n = cantidad_digitos(n);
	int len_variacion;

	for(unsigned int h = 0 ; h < msg.length() ; h += (len_bloque_entero_n - 1) ){ // se creara bloques de tamaño N-1
		bloque_str = msg.substr(h,(len_bloque_entero_n - 1));
		bloque_ZZ = convert_ZZ(bloque_str);
		bloque_ZZ = elevar_modulo(bloque_ZZ,e,n); // reutilizando variable
		len_variacion = cantidad_digitos(bloque_ZZ);

		bloque_str  = convert_string(bloque_ZZ);// reutilizando variable.

		if( len_variacion == (len_bloque_entero_n)) // debe de tener la misma cantidad de digitos que la n
			cadena_numbers_cifrada += bloque_str;
		else{
			for(auto j = 0 ; j < ( len_bloque_entero_n - len_variacion ); j++)
				cadena_numbers_cifrada += to_string(0);
			cadena_numbers_cifrada += bloque_str;
		}
	}
	fstream entrada;
	entrada.open("cifrado.txt", ios::out);
	entrada << cadena_numbers_cifrada;
	entrada.close();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

/*
	desciframiento por bloques, paso inverso del ciframiento
	de parametro solo sera el mensaje cifrado ya que en su poder tendra la Clave<d,n>
	que es la clave privada
	ojo:last_range es para no completar 00 en la ultima rueda debido a que hay la probabilidad de que el mensaje
	sea un nunero no multiplo de la cantidad de bloques
	y en caso lo sea no afectaria :
		al bloque anterior:  ya que es si o si el ultimo bloque

	descifrado.txt sera el name por defecto en donde se guardara el descifrado
*/

void RSA::Descifrar_Bloque(){
	//sacando el mensaje cifrado de cifrado.txt
	fstream salida;
	string cifrado;
	salida.open("cifrado.txt", ios::in);
	getline(salida,cifrado);
	salida.close();


	string cadena_numbers_descifrada;
	string bloque_str;
	ZZ bloque_ZZ;
	unsigned int len_bloque_entero_n = cantidad_digitos(n);
	unsigned int len_variacion;
	unsigned int last_range = cifrado.length() / len_bloque_entero_n;

	for(unsigned int k = 0 ; k < cifrado.length() ; k += len_bloque_entero_n){
		last_range--;
		bloque_str = cifrado.substr(k,len_bloque_entero_n);
		bloque_ZZ = convert_ZZ(bloque_str);
		bloque_ZZ = elevar_modulo(bloque_ZZ,d,n);
		len_variacion = cantidad_digitos(bloque_ZZ);
		bloque_str = convert_string(bloque_ZZ);

		if(len_variacion == len_bloque_entero_n - 1)
			cadena_numbers_descifrada += bloque_str;
		else{
			for(unsigned int j = 0 ; j < ((len_bloque_entero_n-1)-(len_variacion)) && last_range != 0 ; j++)
				cadena_numbers_descifrada += to_string(0);
			cadena_numbers_descifrada += bloque_str;
		}
	}
	fstream entrada;
	entrada.open("descifrado.txt",ios::out);
		entrada << cadena_numbers_descifrada << endl;
	entrada.close();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

/*
		convertira el mensaje numerico  descifrado en un mensaje con caracteres
		el file por defecto a abrirse sera descifrado.txt
		y el file por defecto en donde se guaradara el mensaje_final sera mensaje_final.txt
*/
void RSA::convertir_to_string_characters(){
	fstream salida;
	string lline;
	salida.open("descifrado.txt",ios::in);
		getline(salida,lline);
	salida.close();

	string cadena_characters;
	string bloque_str;
	int bloque_int;

	for(unsigned int k = 0 ; k < lline.length(); k += 2){
		bloque_str = lline.substr(k,2); // se reconocera en bloques de dos
		bloque_int = convert_entero(bloque_str);
		cadena_characters += alfabeto[bloque_int]; // buscaremos el character de la poscion boque_int
	}

	fstream entrada;
	string FileName; cout << "Name del file en donde guardara el mensaje_final: "; cin >> FileName;
	cout << "Hecho !!!" << endl;
	entrada.open(FileName+ext, ios::out | ios::app);
	entrada << cadena_characters << endl;
	entrada.close();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
