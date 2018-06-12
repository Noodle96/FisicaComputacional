#include<iostream>
#include<fstream>
#include<climits>
using namespace std;

//constantes
#define A 0.4
#define B 0.01 //0.37
#define C 0.3
#define D 0.005 //0.05
#define TF 100
#define TO 0
#define N 5000
#define DELTA (TF-TO)/N
#define TOTAL 10000
#define R 250
#define Z 1000

/*
    R(1) = 300;
    F(1) = 100;

    for e = 1 : 50000
      R(e+1) = R(e) + R(e)*(a-b*F(e)) * delta;
      F(e+1) = F(e) + F(e) *(-c + d *R(e))* delta;

      printf("%d %d\n", R(e),F(e));
    endfor
*/

void datosZorroConejo(){
    ofstream data;
    data.open("datos.txt" );
    long double zv, rv, temprv;
    rv = R;
    zv = Z;
    data << 1 << " " << zv << " " << rv << endl;
    for(int e = 2 ; e < TOTAL ; e++){
        temprv = rv;
        rv = rv + rv *(A-(B*zv)) * DELTA;

        zv = zv + zv *(-C + (D*temprv)) * DELTA;
        data << e << " " << zv << " " << rv << endl;
    }
    data.close();
}



int main(){

    datosZorroConejo();


    return 0;
}
