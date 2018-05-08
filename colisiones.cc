#include <iostream>
using namespace std;


class bola{
private: 
	float masa;
	float velocidad;
	float momento;
public:
	bola(float masa = 0, float velocidad = 0): masa(masa), velocidad(velocidad){
		momento = masa * velocidad;
	}
	 float getMasa(){return masa;}
	 float getVelocidad(){return velocidad;}
	 float getMomento(){return momento;}

	 void setMasa(float masaa){masa = masaa;}
	 void setVelocidad(float velocidadd){velocidad = velocidadd;}
	 void setMomento(){momento = masa *velocidad;}

	 void Choque(bola & b){
	 	float d = this->masa - b.getMasa();
	 	float s = this->masa + b.getMasa();
	 	float nuevav1, nuevav2;

	 	nuevav1 = this->velocidad *(d/s)  +  (2* b.getMasa()* b.getVelocidad())/s;
	 	nuevav2 = (2*this->masa * this->velocidad) / s  +  (-d/s)*b.getVelocidad();

	 	this->velocidad = nuevav1;
	 	b.setVelocidad(nuevav2);

	 	setMomento();
	 	b.setMomento();

	 }
	 void mostrar(){
	 	cout << "masa: " << this->masa  << "     velocidad : " << this->velocidad << " momento : " << getMomento() <<   endl;
	 }

	};



int main(){

	bola bola1(2,1), bola2(2,-2);

	cout << "\bINICIO:\n " << endl;
	cout << "Bola 1" << endl ;bola1.mostrar();
	cout << "\nBola2" << endl;bola2.mostrar();

	bola1.Choque(bola2);
	cout << "\b\n\nFINAL:\n " << endl;
	cout << "Bola 1"  << endl; bola1.mostrar();
	cout << "\nBola 2" << endl; bola2.mostrar();



	return 0;
}