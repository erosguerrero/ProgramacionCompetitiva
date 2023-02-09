// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <string>
using namespace std;

/*
struct combination {
    int n1;
    int n2;
    int n3;
    int n4;
};
*/
const int INF = 1000000000;

string vectorToString(vector<int> v) {
    stringstream ss;
    for (size_t i = 0; i < v.size(); i++) {
        ss << v[i];
    }
    return ss.str();
}

int next(string u, int i, int j) {
    vector<int> num(u.begin(), u.end());
    for (int i = 0; i < 4; i++){
        num[i] -= 48;
    }
    switch (j) {
    case 0: {
        num[i]++;
        break;
    }
    case 1: {
        num[i]--;
        break;
    }
    }
    num[i] %= 10;
    return num[0]*1000+num[1]*100+num[2]*10+num[3];
}

int bfs(string og, string dest, vector<int>& dist, vector<bool>& visited) {
    queue<string> q;
    q.push(og);
    while (!q.empty()){
        string u = q.front(); q.pop();
        int iu = stoi(u);
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 2; j++){
                int v = next(u, i, j);
                if (to_string(v) == dest)
                    return dist[iu] + 1;
                if (!visited[v]) {
                    dist[v] = dist[iu] + 1;
                    visited[v] = true;
                    q.push(to_string(v));
                }
            }
            
        }
    }
    return -1;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    vector<int> og(4), dest(4);
    vector<int> dist(10000, 0);
    vector<bool> visited(10000, false);
    cin >> og[0] >> og[1] >> og[2] >> og[3];
    cin >> dest[0] >> dest[1] >> dest[2] >> dest[3];

    string strOG = vectorToString(og);
    string strDest = vectorToString(dest);
    dist[stoi(vectorToString(og))] = 0;
    visited[stoi(vectorToString(og))] = true;

    int N;
    cin >> N;
    for (int i = 0; i < N; i++){
        vector<int> c(4);
        cin >> c[0] >> c[1] >> c[2] >> c[3];
        string str3 = vectorToString(c);
        visited[stoi(vectorToString(c))] = true;
        dist[stoi(vectorToString(og))] = -1;
    }
    cout << bfs(strOG, strDest, dist, visited) << "\n";
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