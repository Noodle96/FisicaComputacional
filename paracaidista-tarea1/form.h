#ifndef FORM_H
#define FORM_H

#include<cmath>
#include<vector>
#include<cfloat>
#include"gnuplot-iostream.h"

using parOrdenado = std::pair<float,float>;

#define gravedad 9.8
#define LIMITE 250
#define e 2.718281828
#define MASA 68.1
#define COEF 12.5

//las formulas a continuacion mostradas son referenciadas en description.txt
float solAnalitica(float tiempo, float coef_resist =COEF*2, float masa=MASA);//tiempo, coef_resis, masa
float solNumerica(float tiempo, float coef_resis=COEF*2, float masa = MASA); //tiempo, coef_resis, masa



//hace el calculo y defrente llena al vector
float solNumericaVector(float,std::vector<parOrdenado>&, float coef_resis = 12.5, float = 68.1);



// haciendo los vectores para ploted
//incluso con valore de la masa y coeficiente de resistecia
std::vector<parOrdenado> doVectorsolAnalitica();
std::vector<parOrdenado> doVectorsolNumerico();

std::vector<parOrdenado> doVelocidadTerminal();

//ploted
void ploted(std::vector<parOrdenado>&,std::vector<parOrdenado>&,std::vector<parOrdenado>&vvm);

//diferencia
void diferencia(std::vector< parOrdenado >&,std::vector< parOrdenado >&);

#endif //FORM_H
