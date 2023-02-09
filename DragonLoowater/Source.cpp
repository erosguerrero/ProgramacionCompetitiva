// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <algorithm>
using namespace std;

// función que resuelve el problema
int resolver(priority_queue<int, vector<int>, greater<int>>&h,priority_queue<int, vector<int>, greater<int>>&k) {
    int cont = 0;
    while (!h.empty() && !k.empty())
    {
        if (h.top() <= k.top()) {
            cont += k.top();
            h.pop();
            k.pop();

        }
        else {
            k.pop();
        }
    }
    if (k.empty() && !h.empty())
    {
        cont = -1;
    }
    return cont;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, m; //n heads m knights
    cin >> n >> m;
    if (n == 0 && m == 0)
        return false;
    priority_queue<int, vector<int>, greater<int>> heads, knights;
    int aux;
    for (int i = 0; i < n; i++)
    {
        cin >> aux;
        heads.push(aux);
    }
    for (int i = 0; i < m; i++)
    {
        cin >> aux;
        knights.push(aux);
    }


    int sol = resolver(heads,knights); //gold coins

    // escribir sol
    if (sol == -1) {
        cout << "Loowater is doomed!" << endl;
    }
    else {
        cout << sol << endl;
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


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
