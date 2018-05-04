/*
    problema del pendulo y del resorte
*/

// to compile:  g++ -o example-tmpfile example-tmpfile.cc -lboost_iostreams -lboost_system -lboost_filesystem


#include<iostream>
#include<vector>
#include"gnuplot-iostream.h"
using namespace std;


#define G 9.8
#define L 1
#define DELTA 0.1
using pairPoint = pair<float,float>;
#define MAX 90


void pendulo(){
    vector< pairPoint > tvector,wvector;
    float W[MAX], tetha[MAX];
    W[0] = 0;
    tetha[0] = 0.5;
    tvector.push_back(make_pair(0,W[0]));
    wvector.push_back(make_pair(0,tetha[0]));
    for(int e = 0 ; e < MAX ; e++){
        tetha[e+1] = tetha[e] + W[e]*DELTA;
        W[e+1] = W[e] - (G/L)*tetha[e]*DELTA;

        tvector.push_back(make_pair(e+1,tetha[e+1]));
        wvector.push_back(make_pair(e+1,W[e+1]));
    }

    auto et = wvector.begin();
    auto it = tvector.begin();
    cout << "\t\t\t t,s \t\t\t theta \t\t\t W" << endl << endl;
    for( ; it != tvector.end(); it++,et++){

        cout << "\t\t\t" << (*it).first << "\t\t\t" << (*it).second << "\t\t\t"<<(*et).second<< endl;
    }

    Gnuplot gp;
    gp << "set xrange [0:100]\nset yrange [-100:100]\n";
	// Data will be sent via a temporary file.  These are erased when you call
	// gp.clearTmpfiles() or when gp goes out of scope.  If you pass a filename
	// (e.g. "gp.file1d(pts, 'mydata.dat')"), then the named file will be created
	// and won't be deleted (this is useful when creating a script).
	gp << "plot" << gp.file1d(tvector) << "with lines title 'theta',"
    << gp.file1d(wvector) << "with lines title 'W'" << std::endl;
   // << gp.file1d(vvm) << "with lines title 'Velocidad Terminal o Limite'"<< std::endl;
}

#define M 1
#define K 1
#define DELTA2 0.5

#define V 0.6
#define B 1.6
#define FUERZAEXTRA V*B

void resorte(){
    vector< pairPoint > Xvector,Vvector;
    float w[MAX], x[MAX];
    w[0] = 0;
    x[0] = 1;
    Xvector.push_back(make_pair(0,x[0]));
    Vvector.push_back(make_pair(0,w[0]));
    for(int e  = 0 ; e < MAX ; e++){
        x[e+1] = x[e] + w[e]*DELTA2;
        w[e+1] = w[e] (-(K/M)*x[e]-FUERZAEXTRA)*DELTA2 ;

        Xvector.push_back(make_pair(e+1,x[e+1]));
        Vvector.push_back(make_pair(e+1,w[e+1]));
    }
    auto it = Xvector.begin();
    auto et = Vvector.begin();
    cout << "\t\t\t t,s \t\t\t X[e] \t\t\t v(e)" << endl << endl;
    for( ; it != Xvector.end(); it++,et++){

        cout << "\t\t\t" << (*it).first << "\t\t\t" << (*it).second << "\t\t\t"<<(*et).second<< endl;
    }

    Gnuplot gp;
    gp << "set xrange [0:100]\nset yrange [-100:100]\n";
	// Data will be sent via a temporary file.  These are erased when you call
	// gp.clearTmpfiles() or when gp goes out of scope.  If you pass a filename
	// (e.g. "gp.file1d(pts, 'mydata.dat')"), then the named file will be created
	// and won't be deleted (this is useful when creating a script).
	gp << "plot" << gp.file1d(Xvector) << "with lines title 'X()',"
    << gp.file1d(Vvector) << "with lines title 'V()'" << std::endl;
   // << gp.file1d(vvm) << "with lines title 'Velocidad Terminal o Limite'"<< std::endl;
}




int main(){

    system("clear");
    //pendulo();
    //resorte();

    return 0;
}
