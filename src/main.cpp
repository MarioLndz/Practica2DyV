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

                if(salida.getX()>p.at(i).getX()){

                    salida=p.at(i);
                }
            }
            else{

                salida=p.at(i);
            }


        }
    }

    return salida;
}

// devuelve true en caso de ser un giro a la dcha y falso en caso de que sea a la izq

bool GiroALaDerecha(Punto p1, Punto p2, Punto p3){

    bool salida = false;             // uso la fórmula

    if((((p2.getX()-p1.getX())*(p3.getY()-p1.getY()))-((p2.getY()-p1.getY())*(p3.getX()-p1.getX())))<0){

        salida = true;
    }

    return salida;
}

// nos quedamos con los puntos que pertencen a la envolvente conexa
// recibe el vector ya ordenado

vector<Punto> EnvolventeConexa(vector<Punto> p){

    Punto p1 = p.at(0);
    Punto p2 = p.at(1);

    vector<Punto> salida;

    salida.push_back(p1);
    salida.push_back(p2);

    // cogemos los dos primeros puntos y partir de ahí vamos comprobando si el segmento que
    // forman p1 y p2 y el que forman p2 y p3 representan un dextrogiro

    for(int i=2;i<p.size();i++){

        Punto p3 = p.at(i);

        if(!GiroALaDerecha(p1,p2,p3)){             // en caso de que el giro sea a la izq
                                                   // entonces metemos el punto en salida y
            salida.push_back(p3);                  // cambiamos los puntos
            p1=p2;
            p2=p3;
        }
    }

    return salida;
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
