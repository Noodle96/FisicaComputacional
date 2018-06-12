/*
    Ecuaciones de lorentz con el metodo de euler y runge-kutta de cuarto orden
*/

#include<iostream>
#include<fstream>
using namespace std;

// //funcion aplicable para el paracaidista
// double f(double t , double v){
//     double a;
//     a = G - (C)/M * v;
//     return a;
//
// }
//
// //funcione de runge-kutta4
// double rk4(double x, double y, double hp){
//     double k1,k2,k3,k4,m;
//     k1=f(x,y);
//     k2=f(x+hp/2,y+(k1/2)*hp);
//     k3=f(x+hp/2,y+(k2/2)*hp);
//     k4=f(x+hp,y+k3*hp);
//     m = (k1+2*k2+2*k3+k4)/6;
//     y = y + m*hp;
//     return y;
// }

#define SIGMA 10
#define R 28
#define B 2.666667
#define ITERACIONES 20000
#define HP 0.001*0.90


double f1(double X, double x, double y){
    return ((-SIGMA * x) + (SIGMA * y));
}
double f2(double X, double x, double y , double z){
    return ((R*x) -y - (x*z));
}
double f3(double X, double x, double y , double z){
    return ((-B*z) + (x*y) );
}


double rk41(double X, double x, double y, double hp){
    double k1,k2,k3,k4,m;
    k1 = f1(X,x,y);
    k2 = f1(X+hp/2,x+(k1/2)*hp,y);
    k3 = f1(X+hp/2,x+(k2/2)*hp ,y);
    k4 = f1(X+hp,x+k3*hp,y);
    m = (k1 + 2*k2 + 2*k3 + k4)/6;
    x = x + m *hp;
    // cout << "i+++nside: " << x << endl;
    return x;
}
double rk42(double X, double x, double y, double z, double hp){
    double k1,k2,k3,k4,m;
    k1 = f2(X,x,y,z);
    k2 = f2(X+hp/2,x,y+(k1/2)*hp,z);
    k3 = f2(X+hp/2,x,y+(k2/2)*hp ,z);
    k4 = f2(X+hp,x,y+k3*hp,z);
    m = (k1 + 2*k2 + 2*k3 + k4)/6;
    y = y + m *hp;
    return y;
}
double rk43(double X, double x, double y, double z, double hp){
    double k1,k2,k3,k4,m;
    k1 = f3(X,x,y,z);
    k2 = f3(X+hp/2,x,y,z+(k1/2)*hp);
    k3 = f3(X+hp/2,x,y,z+(k2/2)*hp);
    k4 = f3(X+hp,x,y,z+k3*hp);
    m = (k1 + 2*k2 + 2*k3 + k4)/6;
    z = z + m *hp;
    return z;
}

double euler1(double X, double x, double y, double hp){
    double kn;
    kn = f1(X,x,y);
    x = x + kn * hp;
    return x;
}
double euler2(double X, double x, double y, double z,double hp){
    double kn;
    kn = f2(X,x,y,z);
    y = y + kn * hp;
    return y;
}
double euler3(double X, double x, double y, double z,double hp){
    double kn;
    kn = f3(X,x,y,z);
    z = z + kn * hp;
    return z;
}





int limite = 20;
int main(){

    double r1 = 5.000 ,r2 = 5.000,r3 = 5.000;
    double r1p, r2p, r3p;

    double re1 = 5, re2 = 5, re3 = 5;
    double re1p, re2p, re3p;

    double X = 0;
    ofstream datarugen,dataeuler;
    datarugen.open("datos_runge_kutta.txt");
    dataeuler.open("datos_euler.txt");

    // cout << 0 << " " << r1 << " " << r2 << " " << r3 << endl;
    datarugen << 0 << "   " << r1 << "   " << r2 << "   " << r3 << endl;
    dataeuler << 0 << "   " << re1 << "   " << re2 << "   " << re3 << endl;




    X+=HP;
    while(X <= limite){
        r1p = r1;
        r2p = r2;
        r3p = r3;
        r1 = rk41(X,r1p,r2p,HP);
        r2 = rk42(X,r1p,r2p,r3p,HP);
        r3 = rk43(X,r1p,r2p,r3p,HP);
        // cout << X << " "<< r1 << " " << r2 << " " << r3 << endl;
        datarugen << X << "   "<< r1 << "   " << r2 << "   " << r3 << endl;

        re1p = re1;
        re2p = re2;
        re3p = re3;
        re1 = euler1(X,re1p,re2,HP);
        re2 = euler2(X,re1p,re2p,re3p,HP);
        re3 = euler3(X,re1p,re2p,re3p, HP);
        dataeuler << X << "   "<< re1 << "   " << re2 << "   " << re3 << endl;

        X += HP;
    }
    datarugen.close();
    dataeuler.close();


    return 0;
}
