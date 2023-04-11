#include <iostream>
#include<fstream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <random>


#include "punto.h"
#include "QuickSort.h"

using namespace std;
using namespace std::chrono;

/**
 * @brief Esta función se encargará de buscar el punto con la menor ordenada en parte de una colección de puntos
 * @param p Vector de puntos
 * @param inicio Posición de inicio
 * @param final Posición final de búsqueda
 * @return Punto del vector situado más abajo y a la izquierda (la menor ordenada)
 */
Punto MenorOrdenado_lims(const vector<Punto> & p, int inicio, int final){
    Punto salida = p.at(inicio);
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

/**
 * @brief Encuentra el punto con la menor ordenada de un vector de puntos dado
 * @param p Vector de puntos
 * @return Punto del vector situado más abajo y a la izquierda (la menor ordenada)
 */
Punto MenorOrdenado(const vector<Punto> & p){
    return (MenorOrdenado_lims(p, 0, p.size()));
}

/**
 * Esta función comprobará si el segmento que forman tres puntos dados forman un giro a la derecha
 * @param p1 Primer punto del segmento
 * @param p2 Segundo punto del segmento
 * @param p3 Tercer punto del segmento
 * @return Devuelve true en caso de formarse un giro a la derecha entre los tres puntos y false en caso contrario
 */
bool GiroALaDerecha(Punto p1, Punto p2, Punto p3){

    bool salida = false;             // uso la fórmula

    if((((p2.getX()-p1.getX())*(p3.getY()-p1.getY()))-((p2.getY()-p1.getY())*(p3.getX()-p1.getX())))<0){

        salida = true;
    }

    return salida;
}

/**
 * @brief Ordena según el ángulo a partir de la menor ordenada de parte de una colección de puntos dada
 * @param p Vector de puntos
 * @param inicial Posición inicial
 * @param final Posición final
 */
void OrdenaPorAngulo_lims (vector<Punto> & p, int inicial, int final){
    // Primero ordenamos el vector según el ángulo formado, tomando como origen al punto con la menor ordenada
    // Buscamos el punto con la menor ordenada y la seleccionamos como nuestro origen
    Punto origen = MenorOrdenado_lims(p, inicial, final);

    // O(n)
    for (int i = inicial; i < final; ++i){
        p.at(i).setOrigen(origen);
    }

    // O(nlog(n))
    quicksort_lims(p, inicial, final);
}

/**
 * @brief Ordena segun el angulo a partir de la menor ordenada de una colección de puntos dada
 * @param p
 */
void OrdenaPorAngulo (vector<Punto> & p){
    OrdenaPorAngulo_lims(p, 0, p.size());
}

/**
 * @brief Calcula la envolvente conexa de parte de una colección de puntos dado usando el algoritmo de escaneo de Graham
 * @param p Vector de puntos
 * @param inicial Posicion inicial sobre la que se realizaran los calculos
 * @param final Posicion final
 * @return Vector de puntos ordenado segun el ángulo que forman la envolvente convexa
 */
vector<Punto> EnvolventeConexa_lims(vector<Punto> p, int inicial, int final){
    // Primero ordenamos según el angulo
    OrdenaPorAngulo_lims(p, inicial, final);

    //Calculamos la envolvente convexa
    Punto p1 = p.at(inicial);
    Punto p2 = p.at(inicial+1);
    Punto p3 = p.at(inicial+2);

    vector<Punto> salida;

    salida.push_back(p1);
    salida.push_back(p2);
    salida.push_back(p3);

    // cogemos los tres primeros puntos y partir de ahí vamos comprobando si el segmento que
    // forman p1 y p2 y el que forman p2 y p3 representan un dextrogiro (giro a la derecha)

    for(int i = inicial + 3; i < final; ++i){
        p1 = salida.at(salida.size() - 2);
        p2 = salida.back();
        p3 = p.at(i);
        while (salida.size() > 2 && GiroALaDerecha(p1,p2,p3)) {
            salida.pop_back();

            p1 = salida.at(salida.size() - 2);
            p2 = salida.back();
            p3 = p.at(i);
        }

        salida.push_back(p.at(i));

    }

    return (salida);
}

/**
 * @brief Funcion que calcula la envolvente convexa de una coleccion de puntos dado usando el algoritmo de escaneo de Graham
 * @param p Vector de puntos
 * @return Vector de puntos que contiene los puntos que forman la envolvente convexa
 */
vector<Punto> EnvolventeConexa(vector<Punto> p){
    return (EnvolventeConexa_lims(p, 0, p.size()));
}

/**
 * @brief Funcion que nos permite comparar dos Puntos según su coordenada X
 * @param a Primer Punto
 * @param b Segundo Punto
 * @return Devuelve -1 si a<b, 0 si a==b y 1 si a>b
 */
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

/**
 * @brief Funcion que ordena un vector de puntos según su coordenada X
 * @param p Vector de puntos a ordenar
 */
void OrdenaPorOrdenada (vector<Punto> & p){
    qsort(p.data(), p.size(), sizeof(Punto), comparePuntos);
}

/**
 * @brief Función que calculará los indices de los puntos que forman la tangente exterior superior e inferior de dos
 *        polígonos convexos.
 * @pre Los Poligono no deben atravesarse, sino que uno se debe situar a la izquierda del otro.
 * @param izquierda Poligono situado a la izquierda
 * @param derecha Poligono situado a la derecha
 * @return Vector de enteros cuyas dos primeras posiciones son los índices de los puntos del polinomio de la izquierda
 *         y el de la derecha respectivamente que forman la tangente exterior superior. Las otras dos posiciones son
 *         análogas para la tangente exterior inferior
 */
vector<int> CalculaTangentes(const vector<Punto> & izquierda, const vector<Punto> & derecha){
    // Vemos cuántos puntos hay en cada polinomio
    int n1 = izquierda.size();
    int n2 = derecha.size();

    // Buscamos el punto más a la derecha del polinomio izquierdo y el punto más a
    // la izquierda del polinomio derecho

    int a = 0;

    while (a < (n1-1) && izquierda.at(a).getX() <= izquierda.at(a+1).getX()){
        ++a;
    }

    int b = n2-1;
    while (b > 0 && derecha.at(b).getX() >= derecha.at(b-1).getX()){
        --b;
    }

    // Calculamos la tangente superior
    int tsup_a = a, tsup_b = b;
    bool done = false;

    while (!done){
        done = true;

        // A partir del punto b, calcularemos el primer giro que no sea a la derecha con puntos del polinomio de la
        // izquierda
        while (GiroALaDerecha(derecha.at(tsup_b), izquierda.at(tsup_a), izquierda.at((tsup_a+1)%n1))){
            tsup_a = (tsup_a + 1) % n1;
        }

        // Si tras encontrarlo el giro que se produce desde a, es a la izquierda, realizamos el mismo proceso pero ahora
        // para el polinomio de la derecha
        while (!GiroALaDerecha(izquierda.at(tsup_a), derecha.at(tsup_b), derecha.at((n2+tsup_b-1)%n2))){
            tsup_b = (n2+tsup_b-1)%n2;
            done = false;
        }
    }

    // Calculamos la tangente inferior, cuyo proceso es análogo solo que a la inversa
    int tinf_a = a, tinf_b = b;
    done = false;

    while (!done){
        done = true;
        while (GiroALaDerecha(izquierda.at(tinf_a), derecha.at(tinf_b), derecha.at((tinf_b+1)%n2))){
            tinf_b = (tinf_b + 1)%n2;
        }

        while (!GiroALaDerecha(derecha.at(tinf_b), izquierda.at(tinf_a), izquierda.at((n1+tinf_a-1)%n1))){
            tinf_a = (n1+tinf_a-1)%n1;
            done = false;
        }

    }

    vector<int> salida = {tsup_a, tsup_b, tinf_a, tinf_b};

    return (salida);

}

/**
 * @brief Funcion que une dos poligonos convexos a partir de sus tangentes exteriores
 * @param U Primer polígono
 * @param V Segundo polígono
 * @return Polígono ya fusionado
 */
 /*
vector<Punto> Fusion (const vector<Punto>& U, const vector<Punto> & V){
    vector<int> tangentes = CalculaTangentes(U, V);

    int n1 = U.size();
    int n2 = V.size();

    vector<Punto> salida;

    int tsup_i = tangentes.at(0);   // Tangente superior izquierda
    int tsup_d = tangentes.at(1);   // Tangente superior derecha

    int tinf_i = tangentes.at(2);   // Tangente inferior izquierda
    int tinf_d = tangentes.at(3);   // Tangente inferior derecha

    // Aniadimos a salida desde el punto de la tangente inferior derecha hasta la superior derecha
    for (int i = tinf_d; i != tsup_d; i=(i+1)%n2){
        salida.push_back(V.at(i));
    }

    salida.push_back(V.at(tsup_d));

    // Insertamos en salida desde la tangente superior izquierda hasta la inferior izquierda
    for (int j = tsup_i; j != tinf_i; j=(j+1)%n1){
        salida.push_back(U.at(j));
    }

    salida.push_back(U.at(tinf_i));

    //Ordenamos previamente por el angulo
    OrdenaPorAngulo(salida);

    return (salida);
}*/

 vector<Punto> Fusion (const vector<Punto>& U, const vector<Punto> & V){
     vector<int> tangentes = CalculaTangentes(U, V);

     int n1 = U.size();
     int n2 = V.size();

     vector<Punto> aux;

     int tsup_i = tangentes.at(0);   // Tangente superior izquierda
     int tsup_d = tangentes.at(1);   // Tangente superior derecha

     int tinf_i = tangentes.at(2);   // Tangente inferior izquierda
     int tinf_d = tangentes.at(3);   // Tangente inferior derecha

     // Aniadimos a salida desde el punto de la tangente inferior derecha hasta la superior derecha
     for (int i = tinf_d; i != tsup_d; i=(i+1)%n2){
         aux.push_back(V.at(i));
     }

     aux.push_back(V.at(tsup_d));

     // Insertamos en salida desde la tangente superior izquierda hasta la inferior izquierda
     for (int j = tsup_i; j != tinf_i; j=(j+1)%n1){
         aux.push_back(U.at(j));
     }

     aux.push_back(U.at(tinf_i));

     Punto menor_ordenada = MenorOrdenado(aux);

     int i = 0;
     bool encontrado_indice = false;

     for (auto it = aux.begin(); it != aux.end(); ++it){
         it->setOrigen(menor_ordenada);
         if (!encontrado_indice && (*it) != menor_ordenada){
             ++i;
         } else {
             encontrado_indice = true;
         }
     }

     vector<Punto> salida;
     salida.push_back(aux.at(i));
     int tamanio = aux.size();

     for (int j = (i+1)%tamanio; j != i; j=(j+1)%tamanio){
         salida.push_back(aux.at(j));
     }

     return (salida);
 }

const int UMBRAL = 100;

/**
 * @brief Funcion que calcula la envolvente conexa de parte de una colección de puntos dado siguiendo la filosofía
 *        Divide y Vencerás
 * @pre El vector debe estar ordenado según la coordenada X
 * @param p Vector de puntos
 * @param inicial Posicion inicial
 * @param final Posicion final
 * @return Devuelve la envolvente convexa de los puntos dados
 */
vector <Punto> DivideyVenceras_lims (vector<Punto> p, int inicial, int final){
    vector<Punto> solucion;
    if (final - inicial <= UMBRAL){
        solucion = EnvolventeConexa_lims(p, inicial, final);
    } else {
        int k = (final - inicial)/2;

        vector<Punto> U (p.begin(), p.begin()+k);

        vector<Punto> V (p.begin()+k, p.end());

        solucion = Fusion(DivideyVenceras_lims(U, 0, k), DivideyVenceras_lims(V, 0, final-k));

    }

    return (solucion);
}

/**
 * @brief Funcion que calcula la envolvente conexa de parte de una coleccion de puntos dado siguiendo la filosofía
 *        Divide y Venceras
 * @param p Vector de puntos
 * @return Envolvente conexa de los puntos dados
 */
vector<Punto> DivideyVenceras (vector<Punto> p){
    return (DivideyVenceras_lims(p, 0, p.size()));
}

// https://barcelonageeks.com/casco-convexo-conjunto-1-algoritmo-o-envoltura-de-jarvis/

// https://es.wikipedia.org/wiki/Envolvente_convexa
// https://es.wikipedia.org/wiki/M%C3%A9todo_de_Graham

// https://code-with-me.global.jetbrains.com/x-c2PuonJXq21SXSubSG5g#p=CL&fp=A80558952338E1A89A6484B5332C1D2672C285B3C3F87D61D83AE9E7C0E6CD94

int main (int argc, char * argv[]) {
    if (argc != 2){
        cout << "Invalid number of arguments" << endl;
        exit(1);
    }

    // Leemos los datos de entrada
    ifstream file;

    file.open(argv[1]);

    if (!file){
        cout << "Error opening file" << endl;
        exit(1);
    }

    vector<Punto> puntos;
    bool done = false;
    while (!done){
        int x, y;

        file >> x >> y;

        if (file.eof()){
            done = true;
        } else {
            puntos.push_back(Punto(x,y));
        }

    }


    OrdenaPorOrdenada(puntos);

    high_resolution_clock::time_point t_antes, t_despues;
    duration<double> transcurrido;

    t_antes = high_resolution_clock::now();

    //sentencia o programa a medir

    vector<Punto> salida = DivideyVenceras(puntos);

    t_despues = high_resolution_clock::now();
    transcurrido = duration_cast<duration<double>>(t_despues - t_antes);
    cout << puntos.size() << "  " << transcurrido.count() << endl;

    return 0;
}
