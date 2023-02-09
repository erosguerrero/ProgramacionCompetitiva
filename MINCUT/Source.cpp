// Eros Guerrero
// PC08


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;



const int MAX_N = 50;
const int INF = 1000000000;

typedef vector<int> vi;
vector<vi> adj, cap;
vi parent;
vector<bool> visited;

int n, m;
// En parent dejamos el anterior en el recorrido BFS

void bfs(int s, int t) {
    queue<int> q;
    visited.assign(n,false);
    q.push(s);
    parent[s] = -1; visited[s] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == t) break;
        for (int i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i];
            if (!visited[v] && (cap[u][v] > 0)) {
                parent[v] = u;
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

int sendFlow(int s, int t) {
    // Intentamos llegar de s a t
    bfs(s, t);
    if (!visited[t])
        return 0; // No pudimos
        // Buscamos capacidad m´as peque˜na en el camino
    int flow = INF, v = t;
    while (v != s) {
        flow = min(cap[parent[v]][v], flow);
        v = parent[v];
    }
    // Mandamos flujo
    v = t;
    while (v != s) {
        cap[parent[v]][v] -= flow;
        cap[v][parent[v]] += flow; // INVERSA
        v = parent[v];
    }
    return flow;
}

int edmondsKarp(int s, int t) {
    int ret = 0;
    int flow = 0;
    do {
        flow = sendFlow(s, t);
        ret += flow;
    } while (flow > 0);
    return ret;
}
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    // n <= 50, m<=500
    cin >> n >> m;
    if (n==0 && m==0)
        return false;


    int city1, city2, cost;
    parent.assign(n, -1);

    cap = vector<vi>(n, vi(n, INF));
    adj = vector<vi>(n, vi());

    for (int i = 0; i < m; i++)
    {
        cin >> city1 >> city2 >> cost;
        city1--;
        city2--;
        cap[city1][city2] = cost;
        cap[city2][city1] = cost;
        adj[city1].push_back(city2);
        adj[city2].push_back(city1);
    }

    edmondsKarp(0, 1); //Una vez estudiado, ahora otro bfs para ver los que cruzan del lado s al t
    bfs(0, 1);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (cap[i][j] == 0) {
                if (visited[i]!=visited[j]){
                    cout << i + 1 << " " << j + 1 << endl;
                }
            }
        }
    }
    printf("\n");
    

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
