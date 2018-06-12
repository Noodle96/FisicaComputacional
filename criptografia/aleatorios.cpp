 #include"aleatorios.h"


/*
	Implementancion de  generacion de aleatorios mediante
	el metodo de congruencias lineales
	seed = semilla
	a = factor multiplicando
	c = factor sumando
	m = modulo con el que se trabajara
	para garantizar un periodo maximo (m) de la generacion de numeros
	aleatorios se tendra  en cuenta el algoritmo de HULL-DOBEL  que consiste en
		* el GCD(m,c) = 1
		* sea q un primo que pertenesca a m, se cumple que:
			* q | m
			* q | (a -1)
		* si 4 | m => 4 | (a-1)
	El cuerpo de la funcion : aleatorio_of(m) , siendo m la cantidad de bits que desea el numero.
*/




/*
	este constructor dara unn numero aleatorio de bits bits,
*/
Alea::Alea(int bitss){
	bits = bitss;
	//int rango ; cout << "Rango del A: "; cin >> rango; rango por defecto sera 1
    m = potenciar(bits);
    seed = m/2;
	//seed = potenciar(bits-1); // la seed por donde empezara sera un bits menos
	c = formar_c(); // el primer coprimo de un 2 ^ n  sera 3, podemos ponerle un inicio grande, pero de vale lo mismo
	a = formar_a(1);// que de preferencia es el 5 ==> rango numero 1 9 ==> rango numero 2 ....
	primo = 2; // momentaneamente le damos un valor.
	//seed = 5;
	//m = 32;
	//c = 7;
	//a = 5;
}


/*
	este es el segundo constructor  lo que dara numeros aleatorios teniendo como un pseudomaximo a maximo
	pseudomaximo debido a que maximo se reajustara al inferior mas proximo 2^n
*/
Alea::Alea(ZZ maximo_){
	maximo = maximo_; // maximo suoperior a 8 debido a que el mas inferior 2^n es 4 y el 5 es el primer a , seed,a,c < m
	seed = 1;
	m = formar_m(); // =====>
	c = formar_c();
	a = formar_a(1);
}

/*
	los sets and gets
*/
void Alea::setSeed(ZZ s){seed = s;}
ZZ Alea::getSeed(){return seed;}
ZZ Alea::getM(){return m;}
ZZ Alea::getC(){return c;}
ZZ Alea::getA(){return a;}

/*
	=====> ACOMODAR(reajustara a un inferior proximo potencia de 2) MAXIMO DEBIDO A QUE SE PUEDE HALLAS EL MAXIMO PERIODO
	MAXIMO = 2^n
	long NumBits(const ZZ& a)
*/
ZZ Alea::formar_m(){ // debido al algoritmo de HULL-DOBEL
	long num_bits;
	num_bits = NumBits(maximo); // numero de bits de dicho numero
	return potenciar(num_bits-1);
}

/*
	criterio 1 de HULL-dobel
*/


/*
	de preferencia sera 3 debido a que 3 y  un cualquier 2^n seran coprimos,
	pero podemos pasarles valores de parametro para un rango limitado
*/
ZZ Alea::formar_c(){ // de preferencia va ser 3 para un m = 2^n
	ZZ Ctrue;// Ctrue  sera coprimo con  m , proposcion de  HULL-DOBEL
	Ctrue = 2; // inicializaremos el Ctrue un numero regularmente grande.
	while(Ctrue != m){
		if( dijkstra_euclides(Ctrue,m) == 1)
			return Ctrue;
		Ctrue++;
	}
}

ZZ Alea::formar_a(int n){
	//p = 2; // primo el cual dividora a m(logico), y a   a-1  ==>  p | m  &   p | a-1   &    4 | a-1
	//debremos de especificar el rango   de a , podra ser: 5,9,13,17.......
	// y la exepcion debido a quen en dicho rango no exeda el m
	ZZ e;
	try{
		if( n <= ( (m-5)/4 ) + 1){ //despejamos n abajo
			for(e = 5 ; e <  5 + 4*(n - 1) ; e += 4 );
                a= e;
			return a;
		}
		else
			throw "EXCEPCION: nro de bits tienes que ser mayor o igual  4 exede el limite de bits  ó aleatorios menor Ó  igual a dos bits error Ó maximo inferior a 8 .";
	}
	catch(const char *msg){
		cout << msg << endl;
	}
	return a;
}


/*
	estara devolviendo el numeros aleatorio de n bits en el rango de 2^n-1 y 2^n
	ejemplo n = 3
		 2^2 < numeros < 2^3
*/
ZZ Alea::aleatorio_of_bits(){
   	seed =  modulo((a * seed + c), m); // include
   	if( seed >= potenciar(bits-1) )
   		return seed;
   	else
       	return aleatorio_of_bits();
}

/*
	retornara cualquier numero inferior a n
*/
ZZ Alea::aleatorio_of_maximo(){
	seed = modulo( (a * seed + c), m );
    if(seed >= 2 )
    	return seed;
    else
    	return aleatorio_of_maximo();
}

ZZ Alea::primo_aleatorio(){
	while(true){
		primo = aleatorio_of_bits();
		if(Miller_Rabin(primo) == 1)
			return primo;
	}
}
