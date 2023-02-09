// CDS y EJS
// PC08


#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

const int MAX_V = 100;
int hora;
int hijosRaiz;
using vi = vector<int>;
using vvi = vector<vi>;
vi horaVertice(MAX_V);
vi alcanzable(MAX_V);

void dfs(int u, int uParent, const vvi& adjList, vector<bool> &impt) {
    horaVertice[u] = alcanzable[u] = hora; hora++;
    for (int i = 0; i < adjList[u].size(); ++i) {
        int v = adjList[u][i];
        if (v == uParent) continue;
        if (horaVertice[v] == 0) {
            if (uParent == -1) hijosRaiz++;
            dfs(v, u, adjList, impt);
            if (alcanzable[v] >= horaVertice[u])
                if (uParent != -1) {
                    // u es punto de articulaci´on.
                    impt[u] = true;
                }
            alcanzable[u] = min(alcanzable[u], alcanzable[v]);
        }
        else
            alcanzable[u] = min(alcanzable[u], horaVertice[v]);
    }

}
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int N;
    cin >> N; // 1 to N
    if (N == 0)
        return false;

    vvi adjList(N);
    vector<bool> impt(N, false);
    int source, dest;
    cin >> source;
    while (source != 0)
    {
        string conex;
        getline(cin, conex);
        stringstream ss(conex);
       
        while (ss) {
            ss >> dest;
            if (!ss.fail()) {
                adjList[source - 1].push_back(dest - 1);
                adjList[dest - 1].push_back(source - 1);
            }
           
        }
        cin >> source;
    }

    hora = 1;
    alcanzable.assign(MAX_V, -1);
    horaVertice.assign(MAX_V, 0);
    int sol = 0;

    for (int i = 0; i < N; i++){
        if (!horaVertice[i]) {
            hijosRaiz = 0;

            dfs(i,-1,adjList, impt);
            if (hijosRaiz > 1)
            {
                impt[i] = true;
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        if (impt[i]) sol++;
    }
    cout << sol << endl;
 

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
