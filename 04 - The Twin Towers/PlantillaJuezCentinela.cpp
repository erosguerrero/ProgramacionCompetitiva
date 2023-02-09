
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;
int caso = 0;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
int resolver(const int N, const int M, const vector<int>v1, const vector<int>v2, vector<vector<int>>& matriz) {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++)
        {
            int x = v1[i - 1], y = v2[j - 1];
            if (x == y)
                matriz[i][j] = matriz[i - 1][j - 1] + 1;
            else
                matriz[i][j] = max(matriz[i - 1][j], matriz[i][j - 1]);
        }
    }
    return matriz[N][M];
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, M;
     cin >> N >> M;
    if (N == 0 && M == 0)
        return false;
    caso++;
    vector<int> v1, v2;
    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        v1.push_back(num);
    } 
    for (int i = 0; i < M; i++) {
        int num;
        cin >> num;
        v2.push_back(num);
    }
    vector<vector<int>> matriz;
    vector<int> rellena;
    for (int i = 0; i <= M; i++){
        rellena.push_back(0);
    }
    for (int i = 0; i <= N; i++){
        matriz.push_back(rellena);
    }
    cout << "Twin Towers #" << caso << "\nNumber of Tiles : " << resolver(N, M, v1, v2, matriz) << "\n\n";
    
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