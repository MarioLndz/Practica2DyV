//
// Created by mario on 29/03/23.
//

#include "punto.h"
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

Punto::Punto(int la_x, int la_y) {
    this->x = la_x;
    this->y = la_y;

}

int Punto::getCuadrante() const {
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

bool Punto::estaEnEje () const{
    return (this->x == 0 || this->y == 0);
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
        // TODO SI UN PUNTO ESTA EN ALGUN EJE LA TANGENTE ES 0 Y PUEDE DAR ERRORES
        if (cuadrante == 1 || cuadrante == 3){
            if (atan((this->y/(this->x*1.0))) <= atan(otro.y/(otro.x*1.0))){
                es_menor = true;
            }
        } else {
            if ((this->x/(this->y*1.0)) >= (otro.x/((otro.y)*1.0))){
                es_menor = true;
            }
        }



    }
    return (es_menor);
}
/*
bool Punto::esMenor (const Punto & otro) const{
    bool es_menor = false;

    int cuadrante = getCuadrante();

    if (cuadrante != otro.getCuadrante()){  // Distinto Cuadrante
        if (cuadrante < otro.getCuadrante()){
            es_menor = true;
        }
    } else {    // Mismo cuadrante
        if (cuadrante == 1 || cuadrante == )

    }
    return (es_menor);
}
*/
Punto& Punto::operator=(const Punto &p){

    this->x=p.getX();
    this->y=p.getY();

    return *this;
}

ostream & operator<< (ostream & os, const Punto & pt){
    os << "(" << pt.x << "," << pt.y << ")";

    return (os);
}
