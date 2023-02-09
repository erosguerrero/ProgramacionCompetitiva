// PC08

#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

struct point{
    double x, y; //la y ni sirve para nada, pero la dejamos 
    bool ini;
    double opa;
    point(double x1,double y1, bool i, double r ): x(x1), y(y1), ini(i), opa(r) {

    }

    bool operator<(const point &other) const {

        if (this->x == other.x && this->y > other.y)
            return true;
        else {
            return this->x > other.x;
        }
    }
};
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int NL; cin >> NL;
    priority_queue<point> puntos;
    for (int i = 0; i < NL; i++){
        double x1, y1, x2, y2, r;
        cin >> x1 >> y1 >> x2 >> y2 >> r;
        puntos.push({x1,y1,x1<x2,r});
        puntos.push({ x2,y2,x2<x1,r });
    }
    //A partir de aqui tendriamos una cola de prioridad ordenada por x
    double iniInt = -1;
    double val = 1;

    if (puntos.empty()) {
        cout << "1\n";
        cout << "-inf +inf 1.000\n";
    }
    else {
        cout << 2 * NL + 1 << endl;
        for (int i = 0; i < 2 * NL; i++)
        {
            point act = puntos.top(); puntos.pop();
            if (iniInt < 0) {
                cout << setprecision(3) << fixed << "-inf ";
            }
            else {
                cout << iniInt << " ";
            }

            cout << act.x << " " << val << endl;
            iniInt = act.x;

            if (act.ini) {
                val *= act.opa;
            }
            else {
                val /= act.opa;
            }
        }
        cout << iniInt << " +inf " << val << endl;
    }
    cout << endl;
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