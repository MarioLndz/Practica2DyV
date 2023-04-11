#include<iostream>
#include<fstream>
#include<set>
#include<time.h>
#include<string>

using namespace std;

int main (int argc, char * argv[]){

    if (argc != 2 && argc != 3) {
        cout << "GENERADOR: Invalid number of arguments" << endl;
        exit(1);

    }


    const int TOPE = atoi(argv[1]);
    const int MAX = TOPE/2;

    int num_max = TOPE <= MAX ? TOPE : MAX;

    string filename = "data.txt";

    if (argc == 3){
        filename = argv[2];
    }

    ofstream file;

    file.open(filename.c_str());

    if (!file){
        exit(-1);
    }

    set<pair<int,int>> p;

    const int LIMITE_SUP = num_max/2;

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
