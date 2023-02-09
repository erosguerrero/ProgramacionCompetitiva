// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
//GLOBALES
int V,S; // vértices del grafo completo
vector<vector<int>> dista; // matriz de adyacencia del grafo
vector<vector<int>> memo; // tabla de DP
using ii = pair<int, int>;

vector<int> tiendas;


const int INF = 1000000000;
using vii = vector<pair<int, int>>;
vector<vii> adjList;

// devuelve el coste de ir desde pos al origen (el vértice 0)
// pasando por todos los vértices no visitados (con un bit a 0)
int tsp(int pos, int visitados) {
    

    if (visitados == (1 << S) - 1) // hemos visitado ya todos los vértices
        return dista[pos][0]; // volvemos al origen

    if (memo[pos][visitados] != -1)
        return memo[pos][visitados];

    int res = 1000000000; // INF
    for (int i = 1; i < S; ++i) {
        if (!(visitados & (1 << i))) // no hemos visitado vértice i
            res = min(res, dista[pos][i] + tsp(i, visitados | (1 << i)));
    }

    return memo[pos][visitados] = res;
}

void dijkstra(int s, vector<int>& dist) {
    dist.assign(adjList.size(), INF);
    dist[s] = 0;
    priority_queue<ii, vii, greater<ii>> pq;
    pq.push({ 0, s });
    while (!pq.empty()) {
        ii front = pq.top(); pq.pop();
        int d = front.first, u = front.second;
        if (d > dist[u]) continue;
        for (auto a : adjList[u]) {
            if (dist[u] + a.first < dist[a.second]) {
                dist[a.second] = dist[u] + a.first;
                pq.push({ dist[a.second], a.second });
            }
        }
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    cin >> V;
    int roads; cin >> roads;


    adjList.assign(V,{});

    for (int i = 0; i < roads; i++){
        int a, b, c;
        cin >> a >> b >> c;
        adjList[a].push_back({ c,b });
        adjList[b].push_back({ c,a });
    }
    // escribir sol
    cin >> S; S++;
    tiendas.assign(S, 0);
    vector<int> dist;
    for (int i = 1; i < S; i++){
        cin >> tiendas[i];
    }

    dista.assign(S, vector<int>(S, 0)); // rellenamos la matriz de distancias entre vértices 
    memo.assign(S, vector<int>(1 << S, -1));


    for (int i = 0; i < S; i++)
    {
        dist.assign(V, INF);
        dijkstra(tiendas[i], dist);
        for (int j = 0; j < S; j++)
        {
            dista[i][j] = dist[tiendas[j]];
            dista[j][i] = dist[tiendas[j]];
        }
    }

    cout << tsp(0, 1) << '\n';
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