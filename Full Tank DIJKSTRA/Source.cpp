/*
Cada vertice, en la cola de prioridad y en el vector de dist, tenemos como vertice {p,l} guarda p el lugar y luego los litros

*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using ii = pair<int, int>;
const int INF = 1000000000;
using vii = vector<pair<int,int>>;

struct tEstado {
    int v;
    int l; 
    int p; 

    bool operator<(const tEstado& other)const {
        return  p > other.p;
    }
};

int dijkstra(int s, int n, int c, int e,const vector<vector<pair<int, int>>> &grafo,const vector<int> &p) {

    vector<vector<int>> dist (n, vector<int>(c+1, INF));

    dist[s][0] = 0;
    priority_queue<tEstado> pq; //q
    pq.push({s,0,0 });

    while (!pq.empty()) {
        tEstado front = pq.top(); pq.pop();

        if (front.v == e) return front.p;

        if ( dist[front.v][front.l] < front.p) continue; //revisar

        if (front.l < c && dist[front.v][front.l+1] >= (front.p + p[front.v])) {
            dist[front.v][front.l + 1] = front.p + p[front.v];
            pq.push({front.v,front.l+1, front.p + p[front.v]});
        }



        for (auto a : grafo[front.v]) {
            if (front.l >= a.first && dist[a.second][front.l - a.first] >= front.p )
            {
                dist[a.second][front.l - a.first] = front.p;
                pq.push({ a.second,front.l - a.first, front.p});
            }
        }
    }

    return INF;

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, m;
    cin >> n >> m;
    if (!std::cin)
        return false;
    vector<int> p(n);
    vector<vector<pair<int,int>>> grafo(n, vector<pair<int,int>>());

    for (int i = 0; i < n; i++){
        cin >> p[i]; //price in i city
    }
    int u, v, d;
    for (int i = 0; i < m; i++){
        cin >> u>>v>>d;
        grafo[u].push_back({ d,v });
        grafo[v].push_back({ d,u });
    }
    int q; cin >> q;


    for (int i = 0; i < q; i++){
        int c, s, e; //capacity, starting end end goal
        cin >> c >> s >> e;
        int sol = dijkstra(s,n,c,e, grafo, p);
        if (sol == INF) {
            cout << "impossible\n";
        }else {
            cout << sol << endl;
        }
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