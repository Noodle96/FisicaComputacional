#include"form.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////

// formulario
float solAnalitica(float tiempo, float coef_resist, float masa){
    float cSm = coef_resist/masa;
    float mSc =pow(cSm,-1);
    float exp = cSm*tiempo*(-1);
    float velocidad = (gravedad*mSc)*(1-pow(e,exp));
    return velocidad;
}

//la ecuacion ha sido simplificada
//ecuacion general
//  v(ti) = v(ti-1) + [g -c/m*v(ti-1)]*ti-ti-1
float solNumerica(float tiempo, float cr, float m){
    if(tiempo == 0 )return 0;
    else{
        return 2*gravedad + solNumerica(tiempo-2)*(1-(2*cr/m));
    }
}

float solNumericaVector(float tiempo,std::vector<parOrdenado>&v, float cr, float m){
    if(tiempo == 0 ){
        v.push_back(std::make_pair(0,0));
        return 0;
}
    else{
        v.push_back(std::make_pair(tiempo,2*gravedad + solNumericaVector(tiempo-2,v)*(1-(2*cr/m))));
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////


//make vector
std::vector<parOrdenado> doVectorsolAnalitica(){
    // float coef_r, m;
    // cout << "coef_resis: "; cin >> coef_r;
    // cout << "masa: "; cin >> m;
    std::vector< parOrdenado > va;
    int cont = 0;
    int velocidad = -1;
    for(float t = 0 ; t <= LIMITE; t+=2){
        if(solAnalitica(t) != velocidad){cont++;}
        va.push_back( std::make_pair(t,solAnalitica(t)) ); // aqui se agrega el coef y la masa
    }
    return va;
}

std::vector<parOrdenado> doVectorsolNumerico(){
    // float coef_r, m;
    // cout << "coef_resis: "; cin >> coef_r;
    // cout << "masa: "; cin >> m;
    std::vector< parOrdenado > va;
    solNumericaVector(LIMITE,va);//,coef_r,m)

    return va;
}
//se calculara la velocidad limite con el analisis analítico
std::vector<parOrdenado> doVelocidadTerminal(){
    float velocidad_maxima = FLT_MAX;
    std::vector< parOrdenado > v;
    float X = LIMITE;
    v.push_back(std::make_pair(0,solAnalitica(velocidad_maxima)));
    v.push_back(std::make_pair(X,solAnalitica(velocidad_maxima)));
    // std::cout << "velocidad maxima: " << velocidad_maxima << std::endl;
    // std::cout << "funcion: " << solAnalitica(velocidad_maxima) << std::endl;
    return v;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

//ploted
void ploted(std::vector<parOrdenado> &v,std::vector<parOrdenado>&vnu, std::vector<parOrdenado>&vvm){
    Gnuplot gp;
    gp << "set xrange [0:60]\nset yrange [0:70]\n";
	// Data will be sent via a temporary file.  These are erased when you call
	// gp.clearTmpfiles() or when gp goes out of scope.  If you pass a filename
	// (e.g. "gp.file1d(pts, 'mydata.dat')"), then the named file will be created
	// and won't be deleted (this is useful when creating a script).
	gp << "plot" << gp.file1d(v) << "with lines title 'Sol Analitica, exacta',"
    << gp.file1d(vnu) << "with lines title 'Sol Númerica, aproximada'" << std::endl;
   // << gp.file1d(vvm) << "with lines title 'Velocidad Terminal o Limite'"<< std::endl;

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////

void diferencia(std::vector< parOrdenado >&va, std::vector< parOrdenado >&vn){
    auto ita = va.begin();
    auto itn = vn.begin();
    ita++;itn++;
    std::cout << std::endl << std::endl << "\t\tDIFERENCIA" << std::endl;
    std::cout <<std::endl <<  "\t\tt,s\t\t %" << std::endl << std::endl;
    for(; ita != va.end() ; ita++,itn++){
        // std::cout << "\t\t" << (*ita).first << "\t\t+  "<< ((*itn).second/(*ita).second)*100 -100 << "%" << std::endl;
        std::cout << "\t\t" << (*ita).first << "\t\t"<< ((*ita).second - (*itn).second)*100*(1/(*ita).second) << "%" << std::endl;

    }
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
