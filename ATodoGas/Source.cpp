// Eros Guerrero
// PC08


#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
using namespace std;

// función que resuelve el problema
struct tStation {
    int ini;
    int fin;

    tStation(int x, int r, int L) {
        ini = x - r; fin = x + r;
        if (ini < 0) ini = 0;
        if (fin > L) fin = L;
    }

    bool operator<(tStation const& otro) const{
        if (otro.ini == ini)
            return otro.fin < fin;
        return otro.ini < ini;
    }
};



/*
if (roads.top().fin < cover) {
            roads.pop();
            eliminated++;
        }
        else {
            cover = roads.top().fin;
            roads.pop();
        }
        
        */

int resolver(priority_queue<tStation> &roads, int L) {
    int usadas = 0;
    int C = 0;
    int alcanza = 0;
    bool imposible = false;
            while (!imposible && C < L && !roads.empty()) {
                if (roads.top().ini > C) imposible = true;
                while (!roads.empty() && roads.top().ini <= C)
                {
                    if (roads.top().fin > alcanza) {
                        alcanza = roads.top().fin;
                        roads.pop();
                    }else {
                        roads.pop();
                    }
                }
                    usadas++;
                    C = alcanza;
                }


            if (imposible || C < L) {
                usadas = -1;
            }   

    return usadas;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int L, G; //Carretera largo L
    cin >> L >> G;
    if (L == 0 && G == 0)
        return false;
    priority_queue<tStation> roads;
    for (int i = 0; i < G; i++){
        int x, r;
        cin >> x >> r;
        roads.push(tStation(x, r, L));
    }

    int sol = resolver(roads, L);

    // escribir sol
    if (sol != -1) sol = G - sol;
    cout << sol << endl;
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
