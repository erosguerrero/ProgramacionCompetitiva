// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

const vector<pair<int, int>> incrementK = { {-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1} };
const vector<pair<int, int>> incrementB = { {-2,2},{2,2},{2,-2},{-2,-2} };
const int INF = 1000000000;

bool ok(pair<int, int> pos, int N, const vector<vector<bool>>& board) {
    return pos.first >= 0 && pos.second >= 0 && pos.first < (2 * N) && pos.second < (2 * N) && !board[pos.first][pos.second];
}

pair<int, int> nextk(const pair<int,int> pos, int orient) {
    pair<int, int> dest; dest.first = pos.first; dest.second = pos.second;
    dest.first += incrementK[orient].first;
    dest.second += incrementK[orient].second;
    return dest;
}

pair<int, int> nextb(const pair<int, int> pos, int orient) {
    pair<int, int> dest; dest.first = pos.first; dest.second = pos.second;
    dest.first += incrementB[orient].first;
    dest.second += incrementB[orient].second;
    return dest;
}

pair<int, int> nextt(const pair<int, int> pos, int orient, int N) {
    pair<int, int> dest; dest.first = pos.first; dest.second = pos.second;
    if (orient) {
        dest.second = (2 * N) - pos.second - 1;
    }
    else {
        dest.first = (2 * N) - pos.first - 1;
    }
    return dest;
}

bool procesar(pair<pair<int, int>, int> v, vector<vector<vector<bool>>>& visit, pair<int, int> ady, vector<vector<vector<int>>> dist, int type, int N, const vector<vector<bool>>& board) {
    int to_queue = false;
    if (ok(ady, N, board) && visit[ady.first][ady.second][type] != false) {
        visit[ady.first][ady.second][type] = true;
        to_queue = true;
        if (dist[ady.first][ady.second][type] > dist[v.first.first][v.first.second][type] + 1) {
            dist[ady.first][ady.second][type] = dist[v.first.first][v.first.second][type] + 1;
        }
    }
    return to_queue;
}

// función que resuelve el problema
int bfs(const pair<int, int> orig, const pair<int, int> dest, const vector<vector<bool>>& board, int N, vector<vector<vector<bool>>> &visit) {
    vector<vector<vector<int>>> dist(2 * N, vector<vector<int>>(2 * N, vector<int>(3,INF)));
    queue<pair<pair<int, int>, int>> q;
    
    for (int i = 0; i < 3; i++) {
        visit[orig.first][orig.second][i] = true;
        dist[orig.first][orig.second][i] = 0;
        q.push({ { orig.first,orig.second }, i });
    }

    while (!q.empty()) {
        pair<pair<int, int>, int> v = q.front(); q.pop();
        if (v.second != 0){
            //TYPE K

            for (int j = 0; j < 8; j++) {
                pair<int, int> ady = nextk(v.first, j);
                if (procesar(v, visit, ady, dist, 0, N, board)) {
                    q.push({ ady, 0 });
                }
            }
        }
        if (v.second != 1) {
            //TYPE B
            for (int j = 0; j < 4; j++) {
                pair<int, int> ady = nextb(v.first, j);
                if (procesar(v, visit, ady, dist, 0, N, board)) {
                    q.push({ ady, 1 });
                }
            }
        }

        if (v.second != 2) {
            //TYPE T
            for (int j = 0; j < 2; j++) {
                pair<int, int> ady = nextt(v.first, j, N);
                if (procesar(v, visit, ady, dist, 0, N, board)) {
                    q.push({ ady, 2 });
                }
            }
        }
        

    }

    int better = dist[dest.first][dest.second][0];
    if (better > dist[dest.first][dest.second][1]) better = dist[dest.first][dest.second][1];
    if (better > dist[dest.first][dest.second][2]) better = dist[dest.first][dest.second][2];
    return better;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int N; cin >> N;
    if (N==0)
        return false;
    vector<vector<bool>> board(2 * N, vector<bool>(2 * N, true));
    pair<int, int> orig, dest, obs;
    cin >> orig.first >> orig.second;
    cin >> dest.first >> dest.second;


    cin >> obs.first >> obs.second;
    while (obs.first != 0 && obs.second != 0){
        board[obs.first - 1][obs.second - 1] = false;
        cin >> obs.first >> obs.second;
    }

    vector<vector<vector<bool>>> visit(2 * N, vector<vector<bool>>(2 * N, vector<bool>(3, false)));
    int sol = bfs(orig,dest,board, N, visit);

    if (sol == -1) {
        cout << "Solution doesn't exist\n";
    }
    else {
        cout << "Result : " << sol << endl;
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
