#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <random>
#include <chrono>
#include <vector>

using namespace std;

struct Punto {int x; int y;};
struct Recta {Punto p1; Punto p2;};


// Recibimos un vector con los puntos en un orden aleatorio y tendremos que 
// ordenarlo de manera que formemos un poligono convexo

vector<Punto> Ordenacion(vector<Punto> v){
	
	vector<Punto> salida;
	
	return salida;
	
}

int angulo(Recta r1, Recta r2){
	
	int pendiente_r1 = (r1.p2.y-r1.p1.x)/(r1.p2.x-r1.p1.x);
}

/*
int main(){
	
	vector<Punto> v;
	
	const int MIN = -10;
	const int MAX =  10;
	
	std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<Punto> distr(MIN, MAX);
  
    for(int i = 0; i < n; i++){
    
	 	v.pushback(distr(eng));
    };
	
}
*/
