// Cristina y Eros
// PC08


#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
using namespace std;

void calcularSol(double maxLadder, double minLadder, double altura, double w, double ante) {
    double raiz1 = pow(maxLadder, 2) - pow(w, 2);
    double raiz2 = pow(minLadder, 2) - pow(w, 2);
    double pared1 = sqrt(raiz1);
    double pared2 = sqrt(raiz2);

    double corte = pared1 * pared2 / (pared1 + pared2);

    double w2 = ante / 2;
    if (abs(corte-altura)<= 0.000001) {
        cout.setf(ios::fixed, ios::floatfield);
        cout.precision(3);
        cout << w <<endl;
    }
    else if (corte > altura) { 

        calcularSol(maxLadder,minLadder,altura,w+w2,w2);
    }
    else {
        calcularSol(maxLadder, minLadder, altura, w - w2,w2);
    }
}

// función que resuelve el problema
void resolver(double long1, double long2, double altura) {
    //debemos encontrar el punto donde se cortan ambas rectas/escaleras.
    //sabemos que w no puede ser mayor que la escalera mas corta porque si no, no apoyarían en las paredes.
    //usamos divide y venceras para comprobar intentar buscar el punto de corte igualando las rectas
    double maxLadder;
    double minLadder;
    if (long1 > long2) {
        maxLadder = long1;
        minLadder = long2;
    }
    else {
        maxLadder = long2;
        minLadder = long1;
    }

    double w = minLadder / 2;
    calcularSol(maxLadder, minLadder, altura, w, w);
    

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    double long1, long2, altura;
    // leer los datos de la entrada
    cin >> long1 >> long2 >> altura;
    if (! std::cin)
        return false;
    
    resolver(long1,long2,altura);
    
    
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