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

Punto::Punto (){
    this->x = 0;
    this->y = 0;

    this->origen = offset{0,0};
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

            if (esta_cotan <= otra_cotan){
                es_menor = true;
            }
        }

    }
    return (es_menor);
}

bool Punto::operator> (const Punto & otro) const{   // this > otro <=> otro < this
    return (otro < (*this));
}
bool Punto::operator== (const Punto & otro) const{
    bool son_iguales = true;

    if (this->x != otro.x){
        son_iguales = false;
    } else if (this->y != otro.y){
        son_iguales = false;
    }

    return (son_iguales);

}

bool Punto::operator!= (const Punto & otro) const{
    return (!(*this == otro));
}

bool Punto::operator<= (const Punto & otro) const{
    return ((*this) == otro || (*this) < otro);


}
bool Punto::operator>= (const Punto & otro) const{
    return ((*this) > otro || (*this) == otro);
}

Punto& Punto::operator=(const Punto &p){
    this->x = p.getX();
    this->y = p.getY();
    this->origen = p.origen;

    return *this;
}

ostream & operator<< (ostream & os, const Punto & pt){
    os << "(" << pt.getX() << "," << pt.getY() << ")";

    return (os);
}

void Punto::setOrigen(Punto el_origen) {
    this->origen.x = el_origen.getX();
    this->origen.y = el_origen.getY();
}
