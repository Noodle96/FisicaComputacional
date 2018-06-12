#include"support.h"

///////////////////////////////////////////////////////////////////////////////////////////////

/*
	Este es el algoritmo de euclides extendido.
	retornara  la x		en  	ax + by = mcd(a,b)
*/

ZZ inversa_in_modulo( ZZ &n1, ZZ &mod){
	ZZ mode = mod;
	ZZ cociente , resto;
    ZZ s,s1,s2;
    //s = 0;
    s1 = 1;
    s2 = 0;
    while(mode > 0){
		cociente = n1/mode;
        resto = n1 - cociente * mode;
        n1 = mode;
        mode = resto;  // updating resto

        s = s1 - cociente * s2;
        s1 = s2;
        s2 = s;     // updating s;
   }
   return modulo(s1,mod);
}

//////////////////////////////////////////////////////////////////////////////////////////////

/*
	este sera la funcion modulo que retorna el resto "r"    en    D = d* q + r
*/
ZZ modulo(ZZ Div, ZZ div){
		ZZ q = Div / div;
	   // if(Div > 0)
	 	   return  Div - q * div;
       // else
       //    return Div - (q-1)*div;
       /* las variables de tipo ZZ en la division a / b = floor(a,b) is for this reason that
        one step*/
}

//////////////////////////////////////////////////////////////////////////////////////////////

/*
	El algoritmo de exponenciacion modular  en  base ^exp mod(n)
*/


ZZ elevar_modulo(ZZ number, ZZ exp, ZZ mod){
	//pequeño teorema de fermat
	if( exp == mod - 1)
		return to_ZZ(1);
	if( exp == mod )
		return number;

	ZZ acu, pa;
	acu = 1;
	pa = 2; // entre dos para saber si es oar o impar
    while(exp != 0){
    	if( modulo(exp,pa) == 1 )
       		 acu = modulo(acu*number,mod);
        number = modulo(number*number,mod);
        exp = exp/2;
    }
   	return acu;
}

///////////////////////////////////////////////////////////////////////////////////////////////

ZZ MCD(ZZ a, ZZ b){
	ZZ cociente, resto;
	while(b > 0){
		cociente = a/b;
        resto = a - cociente * b;
        a = b;
        b = resto;
   }
   return a;
}

//////////////////////////////////////////////////////////////////////////////////////////////

ZZ potenciar( int bits, int base){
	ZZ acu,convert;
	acu = 1;
	convert = to_ZZ(base);
	while(bits != 0){
		if( modulo(to_ZZ(bits),to_ZZ(2)) == 1 )
			acu *= convert;
		convert *= convert;
		bits /= 2;
	}
	return acu;

}

//////////////////////////////////////////////////////////////////////////////////////////////

						// IMPLEMENTACION DE LEHMER

ZZ lehmer_gcd(ZZ x, ZZ y){
    ZZ x_, y_, a, b, c, d;
    ZZ q, q_, t, tt, u;
    ZZ grupos_x;
    ZZ grupos_y;
    ZZ base;
    base = 1000; // determina un arreglo de potencias de la base.
    Vec<ZZ> arr_potencias = genera_array_base(base); // se crea un array con las potencias de la base.
                                       			   // si es base 2 se trata de una forma especial (moviendo bits)
    while(y > base){
        x_ = digitos_base(x, arr_potencias, grupos_x ); // x_ tendrá los dígitos más significativos que unidos serán <= a la base
        		             							           // la función usa búsqueda binaria en el array de potencias  de la base
        y_ = digitos_base(y, arr_potencias, grupos_y);

        a = 1; b = 0; c = 0; d = 1;
        if(grupos_x == grupos_y){ //necesario pues en la siguiente vuelta hay que asegurar que x e y tengan la misma cantidad d cifras
            while( ((y_+c) != 0) && ((y_+d) != 0) ){
                q = (x_+a) / (y_+c);
                q_ = (x_+b)/ (y_+d);
                if (q != q_){
                    break;
                }
                t=a-q*c;
                a = c;
                c = t;
                t = b - q*d;
                b = d;
                d = t;
                t = x_ - q*y_;
                x_ = y_;
                y_ = t;
            }
        }
        if (b == 0){
            tt = x%y;
            x = y;
            y = tt;
        }
        else{
            tt = a*x + b*y;
            u = c*x + d*y;
            x = tt;
            y = u;
        }
    }
    ZZ v = dijkstra_euclides(x,y);
    return v;
}

Vec<ZZ> genera_array_base(ZZ base){
    //repetir el primer y último elemento para
    //  retornar lo deseado en la busq. binaria
    //  así se agregan dos elementos más

    Vec<ZZ> vec;
    vec.SetLength(MAX_POTENCIAS+2);

    vec.put(0,base);
    ZZ potencia;
    potencia = 1;
    long i;
    for(i = 1; i != MAX_POTENCIAS+1; i++){
        potencia *= base;
        vec.put(i,potencia);
    }
    vec.put(MAX_POTENCIAS+1,potencia);

    return vec;
}


ZZ digitos_base(ZZ num, Vec<ZZ>arr, ZZ &grupos){
    grupos = b_binaria(num, arr, to_ZZ(0), to_ZZ(MAX_POTENCIAS+2 -1) );

    if (grupos == 0)
        grupos = 1;
    else
        if (grupos == MAX_POTENCIAS+1 )
            grupos = MAX_POTENCIAS;
    ZZ r;
    r = num / arr.get( to_long(grupos) );
    return r;
}

ZZ b_binaria(ZZ x, Vec<ZZ>arr, ZZ low, ZZ high){
    ZZ medio;
    if (high > low)
        medio= (high-low)/2 + low;
    else
        medio = (low-high)/2 + low;
    if(arr.get(to_long(medio)) == x || (low > high))
        return (low-1); //medio == low, asi retorna la potencia menor de la base
    else{
        if (arr.get(to_long(medio)) < x)
            return b_binaria(x,arr,medio+1, high);
        else
            return b_binaria(x,arr,low,medio-1);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
	Con la reduccionn que hara lehmer se le aplicara el algoritmo de dijkstra
*/
ZZ dijkstra_euclides( ZZ a,  ZZ b){
    if(a==0 || b==0)
        return a+b;
    else if(a>b){
        a%=b;
        return dijkstra_euclides(a,b);
    }
    else if(b>a){
        b%=a;
        return dijkstra_euclides(a,b);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

/*
	retorna la cantidad de digitos de cierto numero 1003 = 4
*/
int cantidad_digitos(ZZ n){
	int cont;
	while(n != 0){
		cont++;
		n /= 10;
	}
	return cont;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
	convierte string a entero
*/
ZZ convert_ZZ(string str){
	stringstream os;
	ZZ converted;
	os << str;
	os >> converted;
	return converted;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	converte ZZ a string
*/

string convert_string(ZZ zz){
	stringstream r;
	string converted;
	r << zz;
	r >> converted;
	return converted;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
	convierte un string en entero, este sera utilizado para convertir una cadena de string en un entero
	en ese caso el string tendra solo dos caracteres.
*/
int convert_entero(string str){
	int acum = 0;
	unsigned int len = str.length();
	for(unsigned int e = 0 ; e < len ; e++){
		acum += (str[e]-'0')*potenciar_int(len-e-1,10);
	}
	return acum;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

int potenciar_int( int bits, int base){
	int acu = 1;
	while(bits != 0){
		if( modulo(to_ZZ(bits),to_ZZ(2)) == 1 )
			acu *= base;
		base *= base;
		bits /= 2;
	}
	return acu;

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
