#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include<iostream>
#include<cstdio> //
#include<ctime> //rand
#include<cstdlib>
#include<fstream> // ofstream, ifstream
#include<cmath> // sqrt
using limit = float;

#define ITERACIONES 20000
#define DELTA 1000
#define R 1
#define VECES 50
#define E 2.718281828


limit aleatorioToMonteCarlo();
limit aleatorioMejorado(int,int);
limit Pi(int);
limit piPromedio(int itera);
//problema 1 de la practica 9
void test();
limit funcion1(limit);
void problemaEspecifico(); // problema 1 de la tarea 9
void problemaEspecifico2();
void problemaEspecifico4();

#endif // FUNCTIONS_H
