// Nombre del alumno .....
// Usuario del Juez ......

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
const int INF = 1000000000;
const pair<int, int> star[8] = { {-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {0,1} };
int V; // vértices del grafo completo
vector<vector<int>> dist; // matriz de adyacencia del grafo
vector<vector<int>> memo; // tabla de DP
// devuelve el coste de ir desde pos al origen (el vértice 0)
// pasando por todos los vértices no visitados (con un bit a 0)

// Obtiene el numero de nodos que se recorren
int dfs(int v, vector<vector<int>> adjList, vector<int> visited) {
    int tam = 1; visited[v] = true;
    for (int w : adjList[v])
        if (!visited[w]) tam += dfs(w, adjList, visited);
    return tam;
}





int tsp(int pos, int visitados) {
    if (visitados == (1 << V) - 1) // hemos visitado ya todos los vértices
        return dist[pos][0]; // volvemos al origen
    if (memo[pos][visitados] != -1)
        return memo[pos][visitados];
    int res = INF; // INF
    for (int i = 1; i < V; ++i)
        if (!(visitados & (1 << i))) // no hemos visitado vértice i
            res = min(res, dist[pos][i] + tsp(i, visitados | (1 << i)));
    return memo[pos][visitados] = res;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int X, Y;
    cin >> X >> Y;
    if (! std::cin)
        return false;

    vector<vector<int>> adjList(X*Y);
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            if (i - 1 >= 0)
                adjList[i * X + j].push_back((i - 1) * X + j);
            if (i + 1 < X)
                adjList[i * X + j].push_back((i + 1) * X + j);
            if (j - 1 >= 0)
                adjList[i * X + j].push_back(i * X + (j - 1));
            if (j + 1 < Y)
                adjList[i * X + j].push_back(i * X + (j + 1));
        }
    }

    vector<pair<int, int>> points;
    vector<pair<int, int>> starPoint;
    vector<pair<int, int>> walkeable;
    for (int i = 0; i < X; i++){
        for (int j = 0; j < Y; j++){
            char c;
            cin >> c;
            switch (c){
            case '@': case '!': {
                points.push_back({ i,j });
                break;
            }
            case '~': case '#': {
                adjList[i * X + j].clear();
                break;
            }
            case '*': {
                if (i - 1 >= 0)
                    adjList[(i - 1) * X + j].clear();
                if (i + 1 < X)
                    adjList[(i + 1) * X + j].clear();
                if (j - 1 >= 0)
                    adjList[i * X + j - 1].clear();
                if (j + 1 < Y)
                    adjList[i * X + j + 1].clear();
            }
            }
        }
    }

    // escribir sol
    int d = tsp(0, 1);
    cout << (d == INF ? -1 : d) << "\n";
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