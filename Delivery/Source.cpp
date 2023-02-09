// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

/*
*           { 1 si i && j == 1
Caja(i,j) = { 5 si i && j == 2
    Caja de {
         {
*/

// función que resuelve el problema
long long int f(vector<long long int> &sol,int n) {
    if (n <= 0) return 1;
    else if (n == 1) return 1;
    else if (n == 2) return 5;
    else {
        if (sol[n] != -1) return sol[n];
        else {
            sol[n] = f(sol, n - 1) + 4 * f(sol, n - 2) + 2*f(sol, n-3);
            return sol[n];
        }
    }

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    vector<long long int> sol(n+1, -1);

    long long int num = f(sol, n);
    // escribir sol
    cout << num << endl;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}