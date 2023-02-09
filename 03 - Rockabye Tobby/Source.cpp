// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>

struct tMedicamento {
    std::string nombre;
    int frecuencia;
    int original;
    int llegada;
};

struct Comparator {
    bool operator()(tMedicamento const& uno, tMedicamento const& otro) {
        if (otro.frecuencia == uno.frecuencia)
            return otro.llegada < uno.llegada;
        return otro.frecuencia < uno.frecuencia;
    }
};


// función que resuelve el problema
void resolver(int datos) {


}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, necesarios;
    std::cin >> n>> necesarios;

    std::priority_queue<tMedicamento, std::vector<tMedicamento>, Comparator> medicamentos;

    for (int i = 0; i < n; i++) {
        tMedicamento t;
        std::cin >> t.nombre >> t.frecuencia;
        t.original = t.frecuencia;
        t.llegada = i;
        medicamentos.push(t);
    }

    for (int i = 0; i < necesarios; i++) {
        tMedicamento aux = medicamentos.top();
        medicamentos.pop();
        std::cout << aux.frecuencia << " " << aux.nombre << std::endl;
        aux.frecuencia += aux.original;
        medicamentos.push(aux);
    }



    // escribir sol


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