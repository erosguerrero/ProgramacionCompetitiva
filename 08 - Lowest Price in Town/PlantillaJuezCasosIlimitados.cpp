// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;


int caso = 1;
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    double UP;
    int M;
    cin >> UP >> M;

    if (!std::cin)
        return false;

    vector<pair<int, double>> ofertas(M);
    for (int i = 0; i < M; i++){
        cin >> ofertas[i].first >> ofertas[i].second;
    }

    vector<double> sol(101);
    for (int k = 0; k <= 100; k++) {
        sol[k] = UP * k;
    }

    for (int i = 0; i < ofertas.size(); i++) {
        for (int j = 0; j <= 100 - ofertas[i].first; j++) {
            for (int l = 1; l <= ofertas[i].first; l++) {
                sol[j + l] = min(sol[j + l], sol[j] + ofertas[i].second);
            }
        }
    }
    cin.ignore();
    string str; getline(cin, str);
    stringstream ss(str);
    int n;
    ss >> n;
    cout << "Case " << caso << ": \n";
    while (ss) {
        cout << "Buy " << n << " for $" << fixed << setprecision(2) << sol[n] << "\n";
        ss >> n;
    }
    caso++;
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