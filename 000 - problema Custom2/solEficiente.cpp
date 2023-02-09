#include <iostream>
#include <iomanip>
#include <fstream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;


// Resuelve un caso de prueba, leyendo de la entrada la
// configuracioon, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    int nAsig;
    double horasTotales;
    cin >> nAsig;

    if (!std::cin)
        return false;

    cin >> horasTotales;


    // relacion nota/esfuerzo  10 horas 5 puntos 10/5 =2 mejor que 20 horas 5 puntos 20/5 = 4
    //dicha relacion es las horas necesarias para sacar un punto (puede tener decimales)
    vector<double> horasPorPunto;

    int minHorasAprobar = 0;

    for (int i = 0; i < nAsig; i++)
    {
        int id, horasAprobAsig;
        cin >> id >> horasAprobAsig;
        horasTotales -= horasAprobAsig;
        double relacion = (double) horasAprobAsig /(double)5;
        horasPorPunto.push_back(relacion);
    }

 
    if (horasTotales < 0)
    {
        cout << "Imposible aprobar todo" << endl;
    }
    else
    {
        sort(horasPorPunto.begin(), horasPorPunto.end());

        //partimos de un 5 en todas las asignaturas. En el bucle iremos sumando puntos a cada asignatura
        double sumaNotas = (double) 5 * nAsig;

        for (int i = 0; i < horasPorPunto.size(); i++)
        {
            double horasParaDiez = 5 * horasPorPunto[i]; //calculamos cuanto costaria sacar un 10 en esa asignatura

            //si se puede sacar un 10 en esa asignatura entonces interesa sacarlo
            if (horasTotales >= horasParaDiez)
            {
                sumaNotas += 5;
                horasTotales -= horasParaDiez;
            }
            else
            {
                /*Regla de 3 ya que las horas y puntos son proporcionales como se indica en el enunciado 
                *  horasPorPunto[i]  -----  1 punto
                *  horas restantes   -----  x puntos 
                */
                double puntosASumar = horasTotales / horasPorPunto[i];

                sumaNotas += puntosASumar;
                break;//ya no podemos usar mas timepo, ya no se ven el resto de asignaturas
            }
        }
        double media = sumaNotas / nAsig;
        cout << fixed << setprecision(3) << media << endl;

    }


    // escribir sol


    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datoslvarios1.txt");
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