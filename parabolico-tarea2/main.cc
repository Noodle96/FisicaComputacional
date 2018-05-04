/*
    problema del mov parabolico
    https://www.fisicalab.com/apartado/movimiento-parabolico#contenidos
*/

// to compile:  g++ -o example-tmpfile example-tmpfile.cc -lboost_iostreams -lboost_system -lboost_filesystem

#include<iostream>
#include<vector>
#include<cmath>
#include"gnuplot-iostream.h"
using namespace std;
using pairPoint  = pair<float,float>;

#define PI 3.14159265

#define G 9.8
#define Vo 10
#define O 37


#define Vox Vo*cos(O*PI/180)
#define Voy Vo*sin(O*PI/180)
#define xo 0
#define yo 0


void parabolicoNormal(){
    vector<pairPoint> xy;
    vector<pairPoint> vxvy;
    vector<pairPoint> recta;
    recta.push_back(make_pair(0,0));
    recta.push_back(make_pair(20,0));


    float x = 0,y = 30;
    float vx = 0,vy = 0;
    xy.push_back(make_pair(xo,yo));

    vxvy.push_back(make_pair(Vox,Voy));

    float t = 0;
    cout << endl << endl;
    cout << "\tt,s\t\tx\t\ty\t\tVx\t\tVy";
    cout << endl << endl;
    for(;  t < 2 ;t+=0.01){
        x = Vox * t;
        y = yo + Voy*t - (G*t*t)/2;
        xy.push_back(make_pair(x,y));

        vx = Vox;
        vy = Voy -G*t;
        vxvy.push_back(make_pair(vx,vy));
        cout <<"\t"<< t << "\t\t" << x << setprecision(4) << "\t\t"<< y << setprecision(3) << "\t\t"<< vx<< setprecision(3)<<  "\t\t"<< vy<<  setprecision(3)<<endl;
    }

    Gnuplot gp;
    gp << "set xrange [0:20]\nset yrange [-3:3]\n";
	// Data will be sent via a temporary file.  These are erased when you call
	// gp.clearTmpfiles() or when gp goes out of scope.  If you pass a filename
	// (e.g. "gp.file1d(pts, 'mydata.dat')"), then the named file will be created
	// and won't be deleted (this is useful when creating a script).
	gp << "plot" << gp.file1d(xy) << "with point title 'parabola',"
    <<gp.file1d(recta) << "with lines title 'recta y = 0'" << endl;
   // << gp.file1d(vvm) << "with lines title 'Velocidad Terminal o Limite'"<< std::endl;

}









int main(){

    // float resu = sin(37*PI/180);
    system("clear");
    parabolicoNormal();
    // float total = 12.123456788;
    // cout << fixed << setprecision(2) << total << endl;




    return  0;
}
