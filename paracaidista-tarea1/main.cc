#include<iostream>
#include"form.h"

using namespace std;
// to compile:  g++ -o example-tmpfile example-tmpfile.cc -lboost_iostreams -lboost_system -lboost_filesystem


int main(){
    // print table solucion solAnalitica
    vector<parOrdenado> vana = doVectorsolAnalitica();
    vector<parOrdenado> vnu = doVectorsolNumerico();
    std::vector< parOrdenado > vvm = doVelocidadTerminal();
    system("clear");

    cout << "\n\t\tSOLUCION ANALITICA     Y      SOLUCION NUMERICA" << endl << endl << endl;
    cout << "\t\tt,s\t\tv,m/s" << "\t\tv,m/s" << "\t\t %" <<endl << endl;

    float pare_ana = -1,cont_ana = 0;

    auto itn = vnu.begin();
    for(auto ita= vana.begin() ; ita!= vana.end() ; ita++,itn++){
        // vector analitico                                         //vector numerico                   //diferencia
        cout <<"\t\t"<< (*ita).first << "\t\t" << (*ita).second << "\t\t" << (*itn).second <<  "\t\t"<< ((*ita).second - (*itn).second)*100*(1/(*ita).second) << "  %" << endl;
        if((*ita).second != pare_ana){
            cont_ana++;
            pare_ana = (*ita).second;
        }
    }
    cout << endl;
    cout << "\t\t\tMaximas iteraciones: " << cont_ana << endl;

    // for(float j = 0 ; j < 30; j+=2){
    //     cout << j << "\t\t"<< solNumerica(j) << endl;
    // }


    // float final = solNumericaVector(20,v);
    // for(auto it = v.begin(); it != v.end(); it++){
    //     cout << (*it).first << "\t\t" << (*it).second << endl;
    // }


    //diferencia(vana,vnu);
    ploted(vana,vnu,vvm);
    return 0;
}
