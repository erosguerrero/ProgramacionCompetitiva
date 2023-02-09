// Eros y Cristina
// PC08


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


using namespace std;



int dfs(int v, vector<bool> &visited,const vector<vector<int>> &adjList) {
    int tam = 1; visited[v] = true;
    for (int w : adjList[v])
        if (!visited[w]) tam += dfs(w, visited, adjList);
    return tam;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, m, l; //n vertices, y m aristas
    cin >> n >> m >> l;
    vector<vector<int>> ady(n);
    vector<bool> visited(n, false); // Inicializar en la funcion que llam// Obtiene el numero de nodos que se recorren

    for (int i = 0; i < m; i++)
    {
        int a,b;
        cin >> a >> b;
        ady[a-1].push_back(b-1);
    }
    int sol = 0;
    for (int i = 0; i < l; i++)
    {
        int x;
        cin >> x;
        if (!visited[x-1]) {
            sol += dfs(x-1, visited, ady);
        }
    }
    // escribir sol
    cout << sol << endl;

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