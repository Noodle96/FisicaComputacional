
#include"functions.h"
using namespace std;


int main(){
    // cout << std::time(0) << endl;
    // std::time_t result = std::time(nullptr);
    // std::cout << std::asctime(std::localtime(&result))
    //           << result << " seconds since the Epoch\n";


    // limit num;
    srand(time(NULL));
    // for(int e = 0 ; e < 100 ; e++){
    //     num = aleatorioToMonteCarlo();
    //     cout << num << endl;
    // }

    // cout << valorPi << endl;


    // cout << aleatorioToMonteCarlo() << endl;

    // int iteraciones = 50;
    // cout << piPromedio(iteraciones) << endl;

    // ofstream comparacion;
    // comparacion.open("comparaciones.txt");
    //
    // for(int e = 0 ; e < 100; e++){
    //     cout <<"iteraciones: " << iteraciones << "pi: " << piPromedio(iteraciones) << endl;
    //     comparacion << iteraciones << " "<< piPromedio(iteraciones) << endl;
    //     iteraciones +=500;
    // }
    // comparacion.close();

    //cout << piPromedio(ITERACIONES) << endl;



/*
    poblema 1:
*/
    // problemaEspecifico();
    // test();



/*
    Problema 2
*/
// for(int j = 0 ; j < 10; j++){
//     cout << aleatorioMejorado(0,1) << endl;
// }

    // problemaEspecifico2();



/*
    Problema 4
*/
    problemaEspecifico4();




    return 0;
}
