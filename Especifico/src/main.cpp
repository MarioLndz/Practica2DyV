#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <random>

#include "punto.h"
#include "QuickSort.h"
//Prueba

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

/**
 * @brief Funcion que calcula la envolvente convexa de una coleccion de puntos dado usando el algoritmo de escaneo de Graham
 * @param p Vector de puntos
 * @return Vector de puntos que contiene los puntos que forman la envolvente convexa
 */
vector<Punto> EnvolventeConexa(vector<Punto> p){
    return (EnvolventeConexa_lims(p, 0, p.size()));
}

// https://es.wikipedia.org/wiki/Envolvente_convexa
// https://es.wikipedia.org/wiki/M%C3%A9todo_de_Graham

// https://code-with-me.global.jetbrains.com/T6bi-mBf_SafpdhAPbjiow#p=CL&fp=E88DBB3E890228CE13CC0F3D432EC1D0B00233AFCF49A50A1949AA94740196C8

int main(int argc, char * argv[]) {
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

    high_resolution_clock::time_point t_antes, t_despues;
    duration<double> transcurrido;

    t_antes = high_resolution_clock::now();

    vector<Punto> envolvente = EnvolventeConexa(puntos);

    t_despues = high_resolution_clock::now();
    transcurrido = duration_cast<duration<double>>(t_despues - t_antes);
    cout << puntos.size() << "\t" << transcurrido.count() << endl;

    return 0;
}
