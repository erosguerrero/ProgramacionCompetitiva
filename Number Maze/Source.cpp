// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

using vi = vector<int>;
int INF = 1000000000;
bool ok(int i, int j, int F, int C) {
    return i >= 0 && j >= 0 && i < F&& j < C;
}
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int F, C;
    cin >> F >> C;
    vector<vector<int>> Maze(F,vector<int>(C));
    int df[] = { 1,0,-1,0 }, dc[] = { 0,1,0,-1 };
    for (int i = 0; i < F; i++)
    {
        for (int j = 0; j < C; j++)
        {
            cin >> Maze[i][j];
        }
    }
    vector<int> dist(F*C, INF);
    dist[0] = Maze[0][0]; //Al origen del origen 0
    int pi = 0, pj = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({ Maze[0][0],0 }); // Coste, vertice (0, s, origen)


    while (!pq.empty()){
        pair<int, int> front = pq.top(); pq.pop();
        int d = front.first, u = front.second; // d es coste, y "u" la arista
        if (d > dist[u]) continue;
        
        //COMPROBAR LOS 4 ADYACENTES
        for (int k = 0; k < 4; ++k) {
            pi = u / C; pj = u % C;

            int ni = pi + df[k], nj = pj + dc[k];

            if (ok(ni, nj, F, C)) {
                if (dist[u] + (Maze[ni][nj]) < dist[C * ni + nj]) {
                    dist[C * ni + nj] = dist[u] + (Maze[ni][nj]);
                    pq.push({ dist[C * ni + nj] , C * ni + nj });
                }
            }
                
        }
    }

    cout << dist[(C*(F-1))+(C-1)] << endl;


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