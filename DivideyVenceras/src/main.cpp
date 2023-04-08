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
Punto MenorOrdenado_lims(const vector<Punto> & p, int inicio, int final){
    Punto salida = p.at(inicio);
    int tamanio = final - inicio;
    int minimo = salida.getY();

    for(int i = inicio+1; i < final; ++i){
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
Punto MenorOrdenado(const vector<Punto> & p){
    return (MenorOrdenado_lims(p, 0, p.size()));
}

Punto MayorOrdenada(const vector<Punto> & p){
    Punto salida = p.at(0);
    int maximo = salida.getY();

    for(int i = 1; i < p.size(); ++i){
        if(p.at(i).getY() >= maximo){
            if (p.at(i).getY() == maximo) {
                if(salida.getX() < p.at(i).getX()){
                    maximo = p.at(i).getY();
                    salida=p.at(i);
                }
            } else {
                maximo = p.at(i).getY();
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

void OrdenaVector (vector<Punto> & p ){
    int num_elementos = p.size();

    // Buscamos el punto con la menor ordenada y la seleccionamos como nuestro origen
    Punto origen = MenorOrdenado(p);

    // O(n)
    for (int i = 0; i < num_elementos; ++i){
        p.at(i).setOrigen(origen);
    }

    // O(nlog(n))
    quicksort(p, num_elementos);
}

vector<Punto> EnvolventeConexa_lims(vector<Punto> p, int inicial, int final){
    // Buscamos el punto con la menor ordenada y la seleccionamos como nuestro origen
    Punto origen = MenorOrdenado_lims(p, inicial, final);
    cout << "MENOR ORDENADA:\t" << origen << endl;

    // O(n)
    for (int i = inicial; i < final; ++i){
        p.at(i).setOrigen(origen);
    }

    // O(nlog(n))
    quicksort_lims(p, inicial, final);

    cout << "ORDENADO:\t";
    for (int i = inicial; i < final; ++i){
        cout << p.at(i) << "\t";
    }
    cout << endl;

    Punto p1 = p.at(inicial);
    Punto p2 = p.at(inicial+1);
    Punto p3 = p.at(inicial+2);

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

    cout << "ENVOLVENTE:\t";
    for (auto p = salida.begin(); p != salida.end(); ++p){
        cout << *p << "\t";
    }
    cout << endl;

    return (salida);
}

// nos quedamos con los puntos que pertencen a la envolvente conexa
// recibe el vector ya ordenado

vector<Punto> EnvolventeConexa(vector<Punto> p){

    return (EnvolventeConexa_lims(p, 0, p.size()));
}

int comparePuntos (const void * a, const void * b) {
    Punto * p = (Punto *) a;
    Punto * q = (Punto *) b;

    int retorno = 0;

    if (p->getX() < q->getX()){
        retorno = -1;
    } else if (p -> getX() > q->getX()) {
        retorno = 1;
    }
    return (retorno);
}

void OrdenaPorOrdenada (vector<Punto> & p){
    qsort(p.data(), p.size(), sizeof(Punto), comparePuntos);
}

// Encuentra la mayor (la que se encuentra más arriba) y la menor tangente
// (la que se encuentra más abajo) que hay entre dos polinomios distintos

vector<int> CalculaTangentes(const vector<Punto> & izquierda, const vector<Punto> & derecha){
    // Vemos cuántos puntos hay en cada polinomio
    int n1 = izquierda.size();
    int n2 = derecha.size();

    // Buscamos el punto más a la derecha del polinomio izquierdo y el punto más a
    // la izquierda del polinomio derecho

    int a = 0;

    while (izquierda.at(a).getX() <= izquierda.at(a+1).getX() && a < n1){
        ++a;
    }

    int b = n2-1;
    while (derecha.at(b).getX() >= derecha.at(b-1).getX() && b > 0){
        --b;
    }

    // Calculamos la tangente superior
    int tsup_a = a, tsup_b = b;
    bool done = false;

    while (!done){
        done = true;
        while (GiroALaDerecha(derecha.at(tsup_b), izquierda.at(tsup_a), izquierda.at((tsup_a+1)%n1))){
            tsup_a = (tsup_a + 1) % n1;
        }

        while (!GiroALaDerecha(izquierda.at(tsup_a), derecha.at(tsup_b), derecha.at((n2+tsup_b-1)%n2))){
            tsup_b = (n2+tsup_b-1)%n2;
            done = false;
        }
    }

    // Calculamos la tangente inferior, cuyo proceso es análogo solo que a la inversa
    int tsub_a = a, tsub_b = b;
    done = false;

    while (!done){
        done = true;
        while (GiroALaDerecha(izquierda.at(tsub_a), derecha.at(tsub_b), derecha.at((tsub_b+1)%n2))){
            tsub_b = (tsub_b + 1)%n2;
        }

        while (!GiroALaDerecha(derecha.at(tsub_b), izquierda.at(tsub_a), izquierda.at((n1+tsub_a-1)%n1))){
            tsub_a = (n1+tsub_a-1)%n1;
            done = false;
        }

    }


    vector<int> salida = {tsup_a, tsup_b, tsub_a, tsub_b};

    return (salida);

}


vector<Punto> Fusion (const vector<Punto>& U, const vector<Punto> & V){
    vector<int> tangentes = CalculaTangentes(U, V);
    cout << "Tangente:\n";
    for (auto it = tangentes.begin(); it != tangentes.end(); ++it){
        cout << *it << "\t";
    }
    cout << endl;

    vector<Punto> salida;

    return (salida);
}

/*
 * pre: Ordenado por la ordenada (X)
 */
vector<Punto> DivideyVenceras (vector<Punto> p){
    OrdenaPorOrdenada(p);

    cout << "DIVIDE Y VENCERAS:\t";
    for (auto i = p.begin(); i != p.end(); ++i){
        cout << *i << "\t";
    }
    cout << endl << endl;

    vector<Punto> U = EnvolventeConexa_lims(p, 0, p.size()/2);
    vector<Punto> V = EnvolventeConexa_lims(p, (p.size()/2)+(p.size()%2), p.size());

    Fusion(U,V);

    return (p);

}

// https://barcelonageeks.com/casco-convexo-conjunto-1-algoritmo-o-envoltura-de-jarvis/


// https://es.wikipedia.org/wiki/Envolvente_convexa
// https://es.wikipedia.org/wiki/M%C3%A9todo_de_Graham

// https://code-with-me.global.jetbrains.com/1C-3HYoknGpbHx4cESkXhQ#p=CL&fp=CC7CB05072EC3227F21C3403743715B37A118A9EE5CB9BAF45C5183A19C1F404

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
        cout << puntos[i] << endl;
    }

    DivideyVenceras(puntos);



    return 0;
}