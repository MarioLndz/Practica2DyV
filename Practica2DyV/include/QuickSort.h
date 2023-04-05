//
// Created by mario on 4/04/23.
//

#include "punto.h"
#include <vector>

using namespace std;

#ifndef PRACTICA2DYV_QUICKSORT_H
#define PRACTICA2DYV_QUICKSORT_H

/* ************************************************************ */
/*  Método de ordenación rápida  */

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
static void insercion_lims(vector<Punto> & T, int inicial, int final){
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
    }
}

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
void insercion(vector<Punto> & T, int num_elem) {
    insercion_lims(T, 0, num_elem);
};

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
static void dividir_qs(vector<Punto> & T, int inicial, int final, int & pp){
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
}

const int UMBRAL_QS = 50;

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
static void quicksort_lims(vector<Punto> & T, int inicial, int final){
    int k;
    if (final - inicial < UMBRAL_QS) {
        insercion_lims(T, inicial, final);
    } else {
        dividir_qs(T, inicial, final, k);
        quicksort_lims(T, inicial, k);
        quicksort_lims(T, k + 1, final);
    };
}

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
void quicksort(vector<Punto> & T, int num_elem){
    quicksort_lims(T, 0, num_elem);
}

#endif //PRACTICA2DYV_QUICKSORT_H
