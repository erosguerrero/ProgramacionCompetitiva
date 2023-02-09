// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <unordered_map>
using namespace std;

struct UFDS {
    vector<int> p;
    int numSets;
    
    UFDS(int n) : p(n, 0), numSets(n) {
        for (int i = 0; i < n; ++i) p[i] = i;
    }
    int find(int x) {
        return (p[x] == x) ? x : p[x] = find(p[x]);
    }
    void merge(int x, int y) {
        int i = find(x), j = find(y);
        if (i == j) return;
        p[i] = j;
        --numSets;
    }
};



// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int a, b, max;
    vector<pair<int, pair<int, int>>> aristas; //coste, extremos
    cin >> a;
    if (!std::cin)
        return false;
    max = a;
    while (a != -1){
        cin >> b;
        if (b > max) max = b;
        aristas.push_back({ 1,{a,b} });
        cin >> a;
        if (a > max) max = a;
    }

    UFDS uf(max+1);
    int coste = 0, sol = 0;
    for (auto ar: aristas){
        if (uf.find(ar.second.first) != uf.find(ar.second.second)){
            uf.merge(ar.second.first, ar.second.second);
            coste += ar.first;
            if (uf.numSets == 1) break;
        }
        else {
            sol++;
        }
    }
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