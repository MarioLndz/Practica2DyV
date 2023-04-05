#include <iostream>
#include<stdlib.h>
#include<time.h>
#include <vector>
#include <set>
#include <cmath>
#include <cstdlib>

#include "punto.h"
#include "QuickSort.h"

using namespace std;

Punto MenorOrdenado(const vector<Punto> & p){
    const int MAX = 100000;
    Punto salida = p.at(0);
    int minimo = salida.getY();

    for(int i = 1; i < p.size(); ++i){
        if(p.at(i).getY() <= minimo){
            if (p.at(i).getY() == minimo) {
                if(salida.getX() > p.at(i).getX()){
                    minimo = p.at(i).getY();
                    salida=p.at(i);
                }
            } else {
                minimo = p.at(i).getY();
                salida = p.at(i);
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

vector<Punto> EnvolventeConexa_lims(vector<Punto> p, int inicial, int final){
    int num_elementos = final - inicial;

    // Buscamos el punto con la menor ordenada y la seleccionamos como nuestro origen
    Punto origen = MenorOrdenado(p);

    // O(n)
    for (int i = 0; i < num_elementos; ++i){
        p.at(i).setOrigen(origen);
    }

    // O(nlog(n))
    quicksort(p, num_elementos);


    Punto p1 = p.at(0);
    Punto p2 = p.at(1);
    Punto p3 = p.at(2);

    vector<Punto> salida;

    salida.push_back(p1);
    salida.push_back(p2);
    salida.push_back(p3);

    // cogemos los dos primeros puntos y partir de ahí vamos comprobando si el segmento que
    // forman p1 y p2 y el que forman p2 y p3 representan un dextrogiro (giro a la derecha)

    for(int i = inicial + 3; i < final; ++i){
        p1 = salida.at(salida.size() - 2);
        p2 = salida.back();
        p3 = p.at(i);
        while (salida.size() > 1 && GiroALaDerecha(p1,p2,p3)) {
            salida.pop_back();

            p1 = salida.at(salida.size() - 2);
            p2 = salida.back();
            p3 = p.at(i);
        }

        salida.push_back(p.at(i));

    }

    return (salida);
}

// nos quedamos con los puntos que pertencen a la envolvente conexa
// recibe el vector ya ordenado

vector<Punto> EnvolventeConexa(vector<Punto> p){

    return (EnvolventeConexa_lims(p, 0, p.size()));
}

// https://es.wikipedia.org/wiki/Envolvente_convexa
// https://es.wikipedia.org/wiki/M%C3%A9todo_de_Graham

// https://code-with-me.global.jetbrains.com/T6bi-mBf_SafpdhAPbjiow#p=CL&fp=E88DBB3E890228CE13CC0F3D432EC1D0B00233AFCF49A50A1949AA94740196C8

int main() {
    srand(time(NULL));

    const int TOPE = 10;
    const int LIMITE_SUP = 10;


    vector<Punto> puntos;

    // Generamos tantos puntos como indice TOPE
    // Las coordenadas estarán entre ] -LIMITE_SUP, LIMITE_SUP [
    for (int i = 0; i < TOPE; ++i){
        int x = (-1*LIMITE_SUP) + rand()%(2*LIMITE_SUP);
        int y = (-1*LIMITE_SUP) + rand()%(2*LIMITE_SUP);

        puntos.push_back(Punto(x,y));

    }

    cout << "SIN ORDENAR" << endl;
    for (int i = 0; i < TOPE; ++i){
        cout << puntos.at(i) << endl;
    }

    vector<Punto> envolvente = EnvolventeConexa(puntos);

    cout << endl;
    cout << "ENVOLVENTE CONVEXA" << endl;
    for (vector<Punto>::iterator it = envolvente.begin(); it != envolvente.end(); ++it){
        cout << *it << endl;
    }

    return 0;
}