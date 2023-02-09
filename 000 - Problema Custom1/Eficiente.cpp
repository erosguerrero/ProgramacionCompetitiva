

/* La solución eficiente al problema parte de la idea de que realmente no es necesario calcular
 * el camino mínimo desde cada una de las casas de mis amigos hasta la mia, sino que se puede
 * calcular el camino mínimo desde mi casa hasta la de mis amigos invirtiendo el grafo. La inversión
 * puede hacerse durante la entrada y no se contradice realmente con la trampa puesta en el enunciado
 * que estipula que el tiempo que se tarda en llegar de un cruce a otro puede variar dependiendo de
 * la dirección en la que se recorra la calle, ya que realmente se va a recorrer desde casa de mis
 * amigos hasta la mia en cualquier caso aunque las aristas se hayan invertido.
 * De esta forma, la complejidad del algorítmo pasaría a ser O((V + A)*Log(A)), siendo V el número 
 * de cruces y A el número de calles.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

const int INF = 1000000000;
int N, M, X, Z;

using ii = std::pair<int, int>;
using vii = std::vector<ii>;

std::vector<vii> adjList;
std::vector<int> dist;

void dijkstra(int s) {
    dist.assign(adjList.size(), INF);
    dist[s] = 0;
    std::priority_queue<ii, vii, std::greater<ii>> pq;
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

bool resuelveCaso() {
    std::cin >> N >> M >> X >> Z;
    if (!std::cin)
        return false;

    adjList.assign(N, {});
    dist.assign(N, INF);

    for (int i = 0; i < M; i++) {
        int o, d, c;
        std::cin >> o >> d >> c;
        adjList[d].push_back({ c, o });
    }

    dijkstra(Z);

    int contador = 0;
    int tarde = 0;
    int pronto = INF;
    for (int i = 0; i < X; i++) {
        int v;
        std::cin >> v;
        if (dist[v] < INF) {
            contador++;
            tarde = std::max(tarde, dist[v]);
            pronto = std::min(pronto, dist[v]);
        }
    }

    if (contador == 0)
        std::cout << "Se cancela la cena!\n";
    else
        std::cout << contador << " " << pronto << " " << tarde << "\n";
    // escribir sol


    return true;

}

#include <chrono>

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("casoTLE.in");
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