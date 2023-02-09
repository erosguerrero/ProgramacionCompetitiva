#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>
#include <vector>
using namespace std;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    ofstream file;
    long int N, M;
    cin >> N >> M;
    unordered_map<int, vector<int>> lista; //Numero, Posicion

    if (!std::cin)
        return false;

    for (int i = 0; i < N; i++) {
        int c;
        cin >> c;
        lista[c].push_back(i);
    }
    for (int i = 0; i < M; i++) {
        int num, pos;
        cin >> pos >> num;
        if (lista[num].size() < pos) {
            cout << "0\n";
        }
        else {
            cout << lista[num].at(pos - 1) + 1 << "\n";
        }
    }
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    while (resuelveCaso());

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     //system("PAUSE");
     #endif
    
    return 0;
}