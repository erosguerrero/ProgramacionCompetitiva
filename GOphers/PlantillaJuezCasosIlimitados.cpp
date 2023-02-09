// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

int M, N;
vector<vector<int>> grafo;
vector<int> match, vis;

int aug(int l) {
    if (vis[l]) return 0;
    vis[l] = 1;
    for (auto r : grafo[l])
        if (match[r] == -1 || aug(match[r])) {
            match[r] = l;
            return 1;
        }


        return 0;
}

int berge_mcbm() {
    int mcbm = 0;
    match.assign(N + M, -1);
    for (int l = 0; l < N; l++) {
        vis.assign(N, 0);
        mcbm += aug(l);
    }
    return mcbm;
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    double  s, v;
    cin >> N >> M >> s >> v;
    if (! std::cin)
        return false;

    double distMax = s * v;
    vector<pair<double, double>> izquierda;
    double x, y;
    grafo.assign(N+M,vector<int>());
    for (int i = 0; i < N; i++)
    {
        cin >> x >> y;
        izquierda.push_back({x,y});
    }

    for (int i = 0; i < M; i++)
    {
        cin >> x >> y;
        for (int j = 0; j < N; j++)
        {
            double a = abs(izquierda[j].first - x);
            double b = abs(izquierda[j].second - y);
            double dist = hypot(a,b);
            //int dist = sqrt(pow(izquierda[j].first - x, 2) + pow(izquierda[j].second - y, 2));
            if (dist <= distMax) {

                grafo[j].push_back(N + i);
            }
        }
        
        
    }

    int sol = berge_mcbm();
    cout << N-sol << endl;
    
    
    // escribir sol
    
    
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