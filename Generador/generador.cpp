#include<iostream>
#include<fstream>
#include<set>
#include<time.h>

using namespace std;

int main (int argc, char * argv[]){

    if (argc != 2) {
        cout << "Invalid number of arguments" << endl;
        exit(1);

    }

    const int TOPE = atoi(argv[1]);

    ofstream file;

    file.open("data.txt");

    if (!file){
        exit(-1);
    }

    set<pair<int,int>> p;

    const int LIMITE_SUP = TOPE/2;

    srand(time(NULL));

    // Generamos tantos puntos como indique TOPE
    // Las coordenadas estarán entre ]-LIMITE_SUP, LIMITE_SUP[
    for (int i = 0; i < TOPE; ++i){
        int x = (-1*LIMITE_SUP) + rand()%(2*LIMITE_SUP);
        int y = (-1*LIMITE_SUP) + rand()%(2*LIMITE_SUP);

        if (!(p.insert(pair<int,int>(x,y)).second)){
            --i;
        }

    }

    for (auto it = p.begin(); it != p.end(); ++it){
        file << (*it).first << "\t" << (*it).second << endl;
    }

    file.close();



    return 0;
}
