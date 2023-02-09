// PC08


#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

// función que resuelve el problema
int resolver(string pistol) {
    double unos=0, ceros=0, muerte=0;

    for (int i = 0; i < pistol.size(); i++){
        if (pistol[i]-'0') {
            unos++;
        }
        else {
            ceros++;
            if (i < pistol.size() - 1) {
                if (pistol[i + 1]-'0') {
                    //ahora es 0 y la proxima es 1
                    muerte++;
                }
            }
            else {
                if (pistol[0] - '0') {
                    //ahora es 0 y la proxima es 1
                    muerte++;
                }
            }
        }
    }
    double a, b;
    a = unos / (unos+ceros); // matarte girando
    b = muerte / ceros;
    if (a > b) {
        //mejor disparar
        return 0;
    }
    else if (a < b) {
        //mejor girar
        return 1;
    }
    else {
        return 2;
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    string pistol; cin >> pistol;
    if (!std::cin)
        return false;

    int sol = resolver(pistol);

    switch (sol)
    {
    case 0: {
        cout << "SHOOT\n";
        break;
    }
    case 1: {
        cout << "ROTATE\n";
        break;
    }
    case 2: {
        cout << "EQUAL\n";
        break;
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