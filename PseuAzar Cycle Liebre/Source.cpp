// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

int Case;

int f(long long int Z, long long int I, long long int M, long long int L) {
    return (Z * L + I) % M;
}


typedef pair<unsigned int, unsigned int> uu;
// <µ,λ> : <inicio ciclo, longitud ciclo>
uu floydCycleFinding(long long int Z, long long int I, long long int M, long long int L) {
    int tortoise = f(Z,I,M,L), hare = f(Z,I,M,f(Z,I,M,L));
    while (tortoise != hare) {
        tortoise = f(Z,I,M,tortoise); hare = f(Z,I,M,f(Z,I,M,hare));
    }
    int mu = 0; hare = L;
    while (tortoise != hare) {
        tortoise = f(Z, I, M,tortoise); hare = f(Z, I, M, hare); mu++;
    }
    int lambda = 1; hare = f(Z, I, M, tortoise);
    while (tortoise != hare) {
        hare = f(Z, I, M, hare); lambda++;
    }
    return uu(mu, lambda);
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int Z, I, M, L;
    cin >> Z >> I >> M >> L;
    if (Z==0 && I==0 && M==0 && L==0)
        return false;

    unsigned int longi = floydCycleFinding(Z, I, M, L).second;

    // escribir sol
    cout << "Case " << ++Case << ": ";
    cout << longi << endl;
    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 

    Case = 0;
    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
