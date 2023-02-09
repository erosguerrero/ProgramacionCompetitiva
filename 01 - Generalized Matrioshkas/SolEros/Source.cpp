// Eros Guerrero y Cristina Díez
// PC08


#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <cmath>
using namespace std;
// función que resuelve el problema
bool resolver(stringstream &ss) {
    stack<pair<int,int>> mneg;
    int n;
    ss >> n;
    while (ss) {
        int cont=0;
        if (n < 0) mneg.push({ n,0 });
        else {
            if (mneg.empty() || n != abs(mneg.top().first)) {
                return false;
            }else {

                int k = mneg.top().first;
                mneg.pop();
                if (!mneg.empty()) {
                    pair<int,int> q = mneg.top();
                    q.second -= k;
                    mneg.pop();
                    if (q.second >= q.first * -1) { return false; }
                    mneg.push(q);
                    
                }
            }

        }
        ss >> n;
    }
    if (mneg.empty()) return true;
    return false;

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    string str; getline(cin, str);
    stringstream ss(str);

    if (!std::cin)
        return false;

    //Leemos una línea




    bool sol = resolver(ss);

    // escribir sol
    if (sol) {
        cout << ":-) Matrioshka!";
    }
    else {
        cout << ":-( Try again.";
    }
    cout << endl;
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