#include <iostream>
#include "punto.h"
#include<stdlib.h>
#include<time.h>
#include <vector>
#include <set>

using namespace std;

int main() {
    srand(time(NULL));

    const int TOPE = 3;
    const int LIMITE_SUP = 5;

    vector<Punto> puntos;
    set<Punto> p;

    // Generamos tantos puntos como indice TOPE
    // Las coordenadas estarán entre ] -LIMITE_SUP, LIMITE_SUP [
    for (int i = 0; i < TOPE; ++i){
        int x = (-1*LIMITE_SUP) + rand()%(2*LIMITE_SUP);
        int y = (-1*LIMITE_SUP) + rand()%(2*LIMITE_SUP);

        p.insert(Punto(x,y));
        puntos.push_back(Punto(x,y));

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
