//
// Created by mario on 29/03/23.
//

#include "punto.h"
#include <iostream>

using namespace std;

Punto::Punto(int la_x, int la_y) {
    this->x = la_x;
    this->y = la_y;

}

int Punto::getCuadrante() {
    int cuadrante = 0;

    if (x > 0 && y >= 0){
        cuadrante = 1;
    } else if (x <= 0 && y > 0){
        cuadrante = 2;
    } else if (x < 0 && y <= 0) {
        cuadrante = 3;
    } else if (x >= 0 && y < 0){
        cuadrante = 4;
    }

    return (cuadrante);

}

bool Punto::esMenor(Punto otro) {
    bool es_menor = false;

    int cuadrante = getCuadrante();

    if (cuadrante != otro.getCuadrante()){  // Distinto Cuadrante
        if (this->getCuadrante() < otro.getCuadrante()){
            es_menor = true;
        }
    } else {    // Mismo cuadrante
        switch (cuadrante) {
            case (1):

                break;
            case (2):
                break;
            case (3):
                break;
            case (4):
                break;
            default:
                es_menor = true;
        }

    }


}
