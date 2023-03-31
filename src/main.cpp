#include <iostream>
#include "punto.h"
#include<stdlib.h>
#include<time.h>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

Punto MenorOrdenado(const vector<Punto> & p){
    const int MAX = 100000;
    Punto salida(MAX,MAX);
    int maximo = MAX;

    for(int i=0;i<p.size();i++){

        if(p.at(i).getY()<=maximo){

            maximo=p.at(i).getY();

            if(salida.getY()==p.at(i).getY()){

                if(salida.getX()>p.at(i).getX()){

                    salida=p.at(i);
                }
            }
            else {

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

// nos quedamos con los puntos que pertencen a la envolvente conexa
// recibe el vector ya ordenado

vector<Punto> EnvolventeConexa(vector<Punto> p){

    Punto p1 = p.at(0);
    Punto p2 = p.at(1);

    vector<Punto> salida;

    salida.push_back(p1);
    salida.push_back(p2);

    // cogemos los dos primeros puntos y partir de ahí vamos comprobando si el segmento que
    // forman p1 y p2 y el que forman p2 y p3 representan un dextrogiro

    for(int i=2;i<p.size();i++){

        Punto p3 = p.at(i);

        if(!GiroALaDerecha(p1,p2,p3)){             // en caso de que el giro sea a la izq
                                                   // entonces metemos el punto en salida y
            salida.push_back(p3);                  // cambiamos los puntos
            p1=p2;
            p2=p3;
        }
    }

    return salida;
}

/* ************************************************************ */
/*  Método de ordenación rápida  */

/**
   @brief Ordena un vector por el método quicksort.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: número de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo quicksort.
*/
inline static
void quicksort(vector<Punto> & T, int num_elem);

/**
   @brief Ordena parte de un vector por el método quicksort.

   @param T: vector de elementos. Tiene un número de elementos
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posición que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posición detrás de la última de la parte del
                   vector a ordenar.
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1 de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo quicksort.
*/
static void quicksort_lims(vector<Punto> & T, int inicial, int final);


/**
   @brief Ordena un vector por el método de inserción.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: número de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de inserción.
*/
inline static
void insercion(vector<Punto> & T, int num_elem);


/**
   @brief Ordena parte de un vector por el método de inserción.

   @param T: vector de elementos. Tiene un número de elementos
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posición que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posición detrás de la última de la parte del
                   vector a ordenar.
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1 de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de inserción.
*/
static void insercion_lims(vector<Punto> & T, int inicial, int final);


/**
   @brief Redistribuye los elementos de un vector según un pivote.

   @param T: vector de elementos. Tiene un número de elementos
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posición que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posición detrás de la última de la parte del
                   vector a ordenar.
		   inicial < final.
   @param pp: Posición del pivote. Es MODIFICADO.

   Selecciona un pivote los elementos de T situados en las posiciones
   entre inicial y final - 1. Redistribuye los elementos, situando los
   menores que el pivote a su izquierda, después los iguales y a la
   derecha los mayores. La posición del pivote se devuelve en pp.
*/
static void dividir_qs(vector<Punto> & T, int inicial, int final, int & pp);



// https://es.wikipedia.org/wiki/Envolvente_convexa
// https://es.wikipedia.org/wiki/M%C3%A9todo_de_Graham
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

        puntos.push_back(Punto(x,y, offset{3,3}));

    }

    cout << "SIN ORDENAR" << endl;
    for (int i = 0; i < TOPE; ++i){
        cout << puntos.at(i) << endl;
    }

    quicksort(puntos, TOPE);

    cout << "ORDENADO" << endl;
    for (int i = 0; i < TOPE; ++i){
        cout << puntos.at(i) << endl;
    }

    return 0;
}



/**
   Implementación de las funciones
**/


inline static void insercion(vector<Punto> & T, int num_elem)
{
    insercion_lims(T, 0, num_elem);
}


static void insercion_lims(vector<Punto> & T, int inicial, int final)
{
    int i, j;
    Punto aux;
    for (i = inicial + 1; i < final; i++) {
        j = i;
        while ((T[j] < T[j-1]) && (j > 0)) {
            aux = T[j];
            T[j] = T[j-1];
            T[j-1] = aux;
            j--;
        };
    };
}


const int UMBRAL_QS = 50;


inline void quicksort(vector<Punto> & T, int num_elem)
{
    quicksort_lims(T, 0, num_elem);
}

static void quicksort_lims(vector<Punto> & T, int inicial, int final)
{
    int k;
    if (final - inicial < UMBRAL_QS) {
        insercion_lims(T, inicial, final);
    } else {
        dividir_qs(T, inicial, final, k);
        quicksort_lims(T, inicial, k);
        quicksort_lims(T, k + 1, final);
    };
}


static void dividir_qs(vector<Punto> & T, int inicial, int final, int & pp)
{
    Punto pivote, aux;
    int k, l;

    pivote = T[inicial];
    k = inicial;
    l = final;
    do {
        k++;
    } while ((T[k] <= pivote) && (k < final-1));
    do {
        l--;
    } while (T[l] > pivote);
    while (k < l) {
        aux = T[k];
        T[k] = T[l];
        T[l] = aux;
        do k++; while (T[k] <= pivote);
        do l--; while (T[l] > pivote);
    };
    aux = T[inicial];
    T[inicial] = T[l];
    T[l] = aux;
    pp = l;
};
