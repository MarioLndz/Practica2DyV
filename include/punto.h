//
// Created by mario on 29/03/23.
//

#ifndef PUNTO_H
#define PUNTO_H

#include <iostream>

using namespace std;

class Punto {
private:
    int x;
    int y;

public:
    Punto(int la_x, int la_y);

    int getCuadrante () const;

    bool operator< (const Punto & otro) const;

    bool estaEnEje () const;

    friend ostream & operator<< (ostream & os, const Punto & pt);


};

#endif //PUNTO_H
