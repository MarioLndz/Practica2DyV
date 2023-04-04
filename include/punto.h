//
// Created by mario on 29/03/23.
//

#ifndef PUNTO_H
#define PUNTO_H

#include <iostream>

using namespace std;

struct offset {
    int x;
    int y;
};

class Punto {
private:
    int x;
    int y;

    offset origen;

public:
    Punto(int la_x, int la_y, offset el_origen=offset{0,0});
    Punto ();

    int getCuadrante () const;

    bool operator< (const Punto & otro) const;
    bool operator> (const Punto & otro) const;
    bool operator== (const Punto & otro) const;
    bool operator<= (const Punto & otro) const;
    bool operator>= (const Punto & otro) const;

    int getX() const;

    int getY() const;

    void setOrigen (Punto el_origen);

    friend ostream & operator<< (ostream & os, const Punto & pt);

    Punto& operator=(const Punto &p);


};

#endif //PUNTO_H
