#include <iostream>
#include "punto.h"
#include<stdlib.h>
#include<time.h>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

Punto MenorOrdenado(vector<Punto> p){
    const int MAX = 100000;
    Punto salida(MAX,MAX);
    int maximo = MAX;

    for(int i=0;i<p.size();i++){

        if(p.at(i).getY()<=maximo){

            maximo=p.at(i).getY();

            if(salida.getY()==p.at(i).getY()){

                if(salida.getY()==p.at(i).getY()){

                    salida=p.at(i);
                }
            }
            else{

                salida=p.at(i);
            }


        }
    }
}

int main() {
    srand(time(NULL));

    const int TOPE = 5;
    const int LIMITE_SUP = 5;

    vector<Punto> puntos;
    set<Punto> p;

    // Generamos tantos puntos como indice TOPE
    // Las coordenadas estarán entre ] -LIMITE_SUP, LIMITE_SUP [
    for (int i = 0; i < TOPE; ++i){
        int x = (-1*LIMITE_SUP) + rand()%(2*LIMITE_SUP);
        int y = (-1*LIMITE_SUP) + rand()%(2*LIMITE_SUP);

        p.insert(Punto(x,y,offset{1,1}));
        puntos.push_back(Punto(x,y, offset{1,1}));

    }

    cout << "SIN ORDENAR" << endl;
    for (int i = 0; i < TOPE; ++i){
        cout << puntos.at(i) << endl;
    }

    cout << endl << "ORDENADO" << endl;
    for (set<Punto>::iterator it = p.begin(); it != p.end(); ++it ){
        cout << *it << endl;
    }

    return 0;
}
