#include<iostream>
#include<fstream>
using namespace std;

#define a 0.4
#define b 0.37
#define c 0.3
#define d 0.05
#define h 1/50
#define ITERACIONES 5000

double f1(double x, double R, double F){
	return (a*R - c *R*F);
}
double f2(double x , double F, double R){
	return (-b*F + d *R*F);
}

double rk41(double x, double R, double F){
	double k1,k2,k3,k4,m;
	k1 = f1(x,R,F);
	k2 = f1(x+(h/2),R+(h/2)*k1,F);
	k3 = f1(x+(h/2),R+(h/2)*k2,F);
	k4 = f1(x+h,R+(k3*h),F);
	m = (k1+ 2*k2 + 2*k3 + k4)/6;
	R = R + m*h;
	return R;
}

double rk42(double x, double F, double R){
	double k1,k2,k3,k4,m;
	k1 = f2(x,F,R);
	k2 = f2(x+(h/2),F+(h/2)*k1,R);
	k3 = f2(x+(h/2),F+(h/2)*k2,R);
	k4 = f2(x+h,F+(k3*h),R);
	m = (k1+ 2*k2 + 2*k3 + k4)/6;
	F = F + m*h;
	return F;
}

int main(){
	ofstream data;
	data.open("datos.txt");
	double rk4r,rk4f;
	double RK4R = 0.25 ,RK4F = 1;
	double x = 0;
	// cout << RK4R << " " << RK4F << endl;
	data << 0 << " " << RK4R << " " << RK4F << endl;
	int iter = 1;
	while(iter < ITERACIONES){
		rk4r = RK4R;
		rk4f = RK4F;
		RK4R = rk41(x,rk4r,rk4f);
		RK4F = rk42(x,rk4f,rk4r);
		// cout << RK4R << " " << RK4F << endl;
		data << iter << " " << RK4R << " " << RK4F << endl;
		x+=h;
		iter++;
	}
	data.close();
	cout << "hola" << endl;
	return 0;
}
