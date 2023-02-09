// PC08 : Criaturas de bolsillo
#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <vector>
using namespace std;

const int NMAX = 1000;
const int MMAX = 1000;
const int INF = 1000000000;

struct tMonster {
    string name;
    int redes;

    bool operator< (const tMonster other) const {
        if (redes == other.redes && name < other.name) {
            return true; //En caso de empate gana el orden alfabético
        }
        else {
            return redes < other.redes;
        }
    }
};

bool cmp(tMonster const p1, tMonster const p2) {
    return p1.name < p2.name; //Comparador para ordenar por nombre y no por probabilidad
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, m; //redes, monstruos
    cin >> n >> m;
    if (!std::cin)
        return false;
    vector<tMonster> monsters(m);
    double prob; string name;

    for (int i = 0; i < m; i++) {
        cin >> name >> prob;
        if (prob == 0) {
            monsters[i] = { name, INF };
        }
        else {
            monsters[i] = { name, (int)ceil(1 / prob) }; //Se puede hacer función que redondee si el módulo: 1%prob != 0 => 1/prob +1
        }
    }

    sort(monsters.begin(), monsters.end()); //Ordenación Voraz n(logn) siendo N el número de monstruos

    int i = 0;
    vector<tMonster> capturados;
    while (i < monsters.size() && n > 0) {
        if (n >= monsters[i].redes) {
            n -= monsters[i].redes;
            capturados.push_back(monsters[i]);
            i++;
        }else {
            break;
        }
    }

    sort(capturados.begin(), capturados.end(), cmp); //Volvemos a ordenar nuestros capturados, pero por orden alfabético
    
    cout << capturados.size() << "\n";
    for (int i = 0; i < capturados.size(); i++) {
        cout << capturados[i].name << ":" << capturados[i].redes << "\n";
    }
    cout << "\n";
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
