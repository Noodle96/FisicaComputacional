#include"functions.h"

/*
    Genera nnmeros aleatorios dado unn¿ minimo y maximo con ka funcion rand de c++
*/
limit aleatorioToMonteCarlo(){
    // el 10000 para que al dividir le de mas precision debido a que debe de ver muchos
    // numero aleatorios
    limit a ;
    a = 0 + rand() %(R*10000-0);
    // a = -R * 10000 + rand() % (R*10000 - (-R*10000));
    return a/10000;
}
limit aleatorioMejorado(int min, int max){
    limit a ;
    a = min*10000 + rand() % (max*10000 - min*10000);
    return limit(a /10000);
}

/*
    formaremos un ciclo con el numero maximo de ITERACIONES
    y formaremos el circulo y el cuadrado
    n = puntos dentro de el circulo
    N = puntos fuera del circulo
    n + N = puntos totales
*/
limit Pi(int iteraciones){
    limit n=0,N=0;
    limit aleatoriox, aleatorioy, r;
    std::ofstream dataCirculo,dataCuadrado;
    dataCirculo.open("circulo.txt");
    dataCuadrado.open("cuadrado.txt");

    for(int e = 0 ; e < iteraciones ; e++){
        aleatoriox = aleatorioToMonteCarlo();
        aleatorioy = aleatorioToMonteCarlo();
        r = sqrt( pow(aleatoriox,2) + pow(aleatorioy,2) );
        //verify if is to n or N
        if(r <=R){
            n++;
            dataCirculo << aleatoriox << " " << aleatorioy << std::endl;
        }
        else{
            dataCuadrado << aleatoriox << " " << aleatorioy << std::endl;
        }
    }
    N = iteraciones- n;

    dataCirculo.close();
    dataCuadrado.close();
    std::cout << "n: " << n << "N: " << N << std::endl;
    return 4* n/iteraciones;
}

limit piPromedio(int itera){
    limit valorPi;
    limit sum = 0;
    for(int e = 0 ;e < VECES ; e++){
        valorPi = Pi(itera);
        sum += valorPi;
    }
    return sum / VECES;
}


limit funcion1(limit x){
    limit res;
    res = pow(E,-pow(x,2));
    return res;
}
void test(){
    std::ofstream data;
    data.open("test.txt");
    limit y;
    for(float i = 0 ;i<=1 ; i+=0.01){
        y = funcion1(i);
        data << i << " " << y << std::endl;
    }
    data.close();
}
void problemaEspecifico(){
    std::ofstream dataInside,dataOutside;
    dataInside.open("insidefuncion1.txt");
    dataOutside.open("outsidefuncion1.txt");
    srand(time(NULL));
    limit x, y,imagen;
    limit n, N;

    //integral [0,1] e  ^ -x²
    for(int e = 0 ;e < ITERACIONES ; e++){
        x = aleatorioToMonteCarlo();
        y = aleatorioToMonteCarlo();
        imagen = funcion1(x);
        if( y <= imagen){
            n++;
            dataInside << x << " " << y << std::endl;
            // std::cout << x << " " << y << std::endl;

        }
        else{
            dataOutside << x << " " << y << std::endl;
        }
    }
    N = ITERACIONES;
    std::cout << "n: " << n << " N: " << N << std::endl;
    dataInside.close();
    dataOutside.close();
    std:: cout << "Area de la figura es : " << n/N << std::endl;

}

void problemaEspecifico2(){
    srand(time(NULL));
    std::ofstream dataInside, dataOutside;
    dataInside.open("insidefuncion2.txt");
    dataOutside.open("outsidefuncion2.txt");
    limit n = 0,N,imagen,x,y;
    for(int e = 0 ; e < ITERACIONES; e++){
        x = aleatorioMejorado(-1,1); // to problema 2 x = aleatorioMejorado(0,1);
        y= aleatorioMejorado(-1,1);
        if(y >= 0){ // f(x) = x
            imagen = x*x; // no es nesesario funcion to problema 2 imagen = x
            if(y < imagen){
                n++;
                dataInside << x << " " << y << std::endl;
            }else{
                dataOutside << x << " " << y << std::endl;
            }
        }else{ // f(x) = -x
            imagen = -(x*x); //to problema 2 imagen = -x
            if(y > imagen){
                n++;
                dataInside << x << " " << y << std::endl;
            }else{
                dataOutside << x << " " << y << std::endl;
            }
        }
    }//endfor
    dataInside.close();
    dataOutside.close();
    N = ITERACIONES;
    std::cout << "n: " << n << " N: " << N << std::endl;
    std::cout << "Area de la figura: " << 2*n/N << std::endl;
}

void problemaEspecifico4(){
    std::ofstream dataInside, dataOutside;
    dataInside.open("insidefuncion4.txt");
    dataOutside.open("outsidefuncion4.txt");
    limit n = 0,N, imagen,x,y,z;
    for(int e =  0 ; e < ITERACIONES; e++){
        x = aleatorioMejorado(0,1);
        y = aleatorioMejorado(0,1);
        z = aleatorioMejorado(0,1);
        imagen = pow(x,2) + pow(y,2);
        if(z > imagen){
            n++;
            dataInside << x  << " " << y << " " << z << std::endl;
        }
        else{
            dataOutside << x  << " " << y << " " << z << std::endl;
        }

    }
    N = ITERACIONES;
    std::cout << "n: " << n << " N: " << N << std::endl;
    std::cout << "El volumen del cuerpo es: " << n/N << std::endl;
    dataInside.close();
    dataOutside.close();
}













//
