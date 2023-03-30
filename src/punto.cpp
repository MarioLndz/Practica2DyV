//
// Created by mario on 29/03/23.
//

#include "punto.h"
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

Punto::Punto(int la_x, int la_y, offset el_origen) {
    this->x = la_x;
    this->y = la_y;

    this->origen = el_origen;

}

int Punto::getCuadrante() const {
    int cuadrante = 0;

    if (x > origen.x && y >= origen.y){
        cuadrante = 1;
    } else if (x <= origen.x && y > origen.y){
        cuadrante = 2;
    } else if (x < origen.x && y <= origen.y) {
        cuadrante = 3;
    } else if (x >= origen.x && y < origen.y){
        cuadrante = 4;
    }

    return (cuadrante);

}

int Punto::getX() const{

    return (this->x);
}

int Punto::getY() const{

    return (this->y);
}

bool Punto::operator< (const Punto & otro) const{
    bool es_menor = false;

    int cuadrante = getCuadrante();

    if (cuadrante != otro.getCuadrante()){  // Distinto Cuadrante
        if (cuadrante < otro.getCuadrante()){
            es_menor = true;
        }
    } else {    // Mismo cuadrante
        if (cuadrante == 1 || cuadrante == 3){
            float esta_tan = abs((origen.y - this->y)/(abs(origen.x - this->x)*1.0));
            float otra_tan = abs((origen.y - otro.y)/(abs(origen.x - otro.x)*1.0));

            if (esta_tan <= otra_tan){
                es_menor = true;
            }
        } else {
            float esta_cotan = abs(origen.x - this->x)/(abs(origen.y - this->y)*1.0);
            float otra_cotan = abs(origen.x - otro.x)/(abs(origen.y - otro.y)*1.0);
            cout << this << esta_cotan << "\t" << otro << otra_cotan << endl;

            if (esta_cotan <= otra_cotan){
                es_menor = true;
            }
        }



    }
    return (es_menor);
}

Punto& Punto::operator=(const Punto &p){

    this->x=p.getX();
    this->y=p.getY();

    return *this;
}

ostream & operator<< (ostream & os, const Punto & pt){
    os << "(" << pt.getX() << "," << pt.getY() << ")";

    return (os);
}
