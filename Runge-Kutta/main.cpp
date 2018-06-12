

/*
    PROBLEMA DEL PARACAIDISTA CON EULER , RUNGE-KUTTA Y LA SOLUCION EXACTA
*/

#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;
#define C 12.5
#define M 68.5
#define G 9.8

#define ITERACIONES 50
#define h 2 // runge-kutta

#define DELTA 0.75 // numerica
#define e 2.718281828




//funcion aplicable para el paracaidista
double f(double t , double v){
    double a;
    a = G - (C)/M * v;
    return a;

}

//funcione de runge-kutta4
double rk4(double x, double y, double hp){
    double k1,k2,k3,k4,m;
    k1=f(x,y);
    k2=f(x+hp/2,y+(k1/2)*hp);
    k3=f(x+hp/2,y+(k2/2)*hp);
    k4=f(x+hp,y+k3*hp);
    m = (k1+2*k2+2*k3+k4)/6;
    y = y + m*hp;
    return y;
}

//solucion de paracaidista exacta
double solucionAnaliticaExacta(int tiempo){
    double cSm = C/M;
    double exp = cSm * -1 *tiempo;
    return (G*(1/cSm)*(1 - pow(e,exp)));
}

void  solucionNumerica(){
    int tiempo = 0;
    double velocidad = 0 ;
    ofstream dataN;
    double v = 0;
    dataN.open("numerico.txt");
    dataN << 0 << " " << v << endl;
    while(tiempo < ITERACIONES){
        tiempo += DELTA;
        v = v + (G - (C/M)*v)*DELTA;
        dataN << tiempo << " " << v << endl;
    }
    dataN.close();
}


int main(){
    // double rs, next,next2;
    // rs = rk4(2,0,2);
    // next = rk4(4,rs,2);
    // next2 = rk4(6,next,2);
    // cout << rs << endl;
    // cout << next << endl;
    // cout << next2 << endl;



////////////////////////////////////RUNGE-KUTTA H = 2////////////////////////////////

    ofstream data;
    int ite = 0;
    double RK4 = 0;
    double t = 0,v = RK4;
    data.open("rungekutta.txt");
    data << t << " " << RK4 << endl;
    // cout << "t: " << t << "      rk4: " << RK4 << endl;
    while(ite < ITERACIONES){
        t += h;
        RK4 = rk4(t,v,h);
        data << t << " " << RK4 << endl;
        // cout << "t: " << t << "      rk4: " << RK4 << endl;
        v = RK4;
        ite += h;
    }
    data.close();


////////////////////////////////////////////////////////////////////////////////





////////////////////////////////////SOLUCION-ANALITICA ////////////////////////////////

    ofstream dataA;
    double velocidad;
    int iter = 0;
    double sol_anali;
    dataA.open("analitica.txt");
    while(iter < ITERACIONES){
        sol_anali = solucionAnaliticaExacta(iter);
        // cout << "t: " << iter << "   " << sol_anali << endl;
        dataA << iter << " " << sol_anali << endl;
        iter +=h;
    }
    dataA.close();



////////////////////////////////////////////////////////////////////////////////






////////////////////////////////////SOLUCION-NUMERICA H = 0.75////////////////////////////

    solucionNumerica();

////////////////////////////////////////////////////////////////////////////////






    return  0;
}
