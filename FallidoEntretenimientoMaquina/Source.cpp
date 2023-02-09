#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 2;
class Trie {
    int prefixes;
    int words;
    std::vector<Trie*> child;
public:
    Trie() :prefixes(0), words(0), child(MAXN, nullptr) {}

    ~Trie() {
        for (int i = 0; i < MAXN; ++i)
            delete child[i];
    }

    void add(const char* s) {
        if (*s == '\0') ++words;
        else {
            Trie* t;
            if (child[*s - '0'] == nullptr) { //numero de hijo
                t = child[*s - '0'] = new Trie();
                t->prefixes = 1;
            }
            else {
                t = child[*s - '0'];
                t->prefixes++;
            }
            t->add(s + 1);
        }
    }

    int find(const char* s) const {
        //Le entra un string y devuelve el número de apariciones
        if (*s == '\0') return this->words;
        else {
            return this->child[*s - '0']->find(s + 1);
        }
    }

};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int C, F; cin >> C >> F;
    if (!std::cin)
        return false;

    vector<vector<char>> matriz(F, vector<char>(C));

    for (int i = 0; i < F; i++)
    {
        for (int j = 0; j < C; j++)
        {
            cin >> matriz[i][j];
        }
    }
    Trie words;
    for (int i = 0; i < F; i++)
    {
        for (int j = 0; j < C; j++)
        {
            //POR CADA ELEMENTO DE LA MATRIZ

            //METER EL PROPIO ELEMENTO
            string der;
            for (int x = j + 1; x < C; x++)
            {
                //DIRECCION A LA DERECHA
                der.push_back(matriz[i][x]);
                words.add(der.c_str());
            }

            string izq;
            for (int nox = j - 1; nox >= 0; nox--)
            {
                //DIRECCION A LA IZQUIERDA
                izq.push_back(matriz[i][nox]);
                words.add(izq.c_str());
            }

            string abj;
            for (int y = i; y < F; y++)
            {
                //DIRECCION HACIA ABAJO
                abj.push_back(matriz[y][j]);
                words.add(abj.c_str());
            }

            string arr;
            for (int noy = i; noy >= 0; noy--)
            {
                //DIRECCION HACIA ARRIBA
                arr.push_back(matriz[noy][j]);
                words.add(arr.c_str());
            }

            string dbaj;
            for (int d = 0; d < min(F - i, C - j); d++)
            {
                //Ver limites
                //diagonal baja izq der
                dbaj.push_back(matriz[i + d][j + d]);
                words.add(dbaj.c_str());
            }

            string dalt;
            for (int d = 0; d <= min(i, j); d++)
            {
                //Ver limites
                //diagonal alta izq der
                dalt.push_back(matriz[i - d][j - d]);
                words.add(dalt.c_str());
            }
            string dbaj2;
            for (int d = 0; d < min(F - i, j); d++)
            {
                //Ver limites
                //diagonal baja der izq
                dbaj2.push_back(matriz[i + d][j - d]);
                words.add(dbaj2.c_str());
            }

            string dalt2;
            for (int d = 0; d <= min(i, C-j-1); d++)
            {
                //Ver limites
                //diagonal alta der izq
                dalt2.push_back(matriz[i - d][j + d]);
                words.add(dalt2.c_str());
            }
        }
    }

    int cases; cin >> cases;
    vector<string> consultas(cases);
    for (int i = 0; i < cases; i++)
    {
        cin >> consultas[i];
    }
    sort(consultas.begin(), consultas.end());
    for (int i = 0; i < consultas.size(); i++)
    {
        int apar = words.find(consultas[i].c_str());
        if (apar > 0) {
            cout << consultas[i] << " " << apar << endl;
        }
    }
    cout << "---\n";
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