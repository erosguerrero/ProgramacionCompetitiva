// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <random>
#include <tuple>
#include <cassert>
using namespace std;

using T = double;
int Case = 0;
//bool lt(double a, double b) { return a - EPS < b; };
//bool eq(double a, double b) { return fabs(a - b) < EPS; }




struct pt {
    T x, y;
    pt operator+(pt p) const { return { x + p.x, y + p.y }; }
    pt operator-(pt p) const { return { x - p.x, y - p.y }; }
    pt operator*(T d) const { return { x * d, y * d }; }
    pt operator/(T d) const { return { x / d, y / d }; } // only for floating-point

    bool operator==(pt o) const { return x == o.x && y == o.y; }
    bool operator!=(pt o) const { return !(*this == o); }

    bool operator<(pt o) const { // sort points lexicographically
        if (x == o.x) return y < o.y;
        return x < o.x;
    }
};

T sq(pt v) { return v.x * v.x + v.y * v.y; }
double abs(pt v) { return sqrt(sq(v)); }

T cross(pt v, pt w) { return v.x * w.y - v.y * w.x; }

// rotate 90º counterclockwise
pt perp(pt p) { return { -p.y, p.x }; }
struct line {
    pt v; T c;
    // from direction vector v and offset c
    line(pt v, T c) : v(v), c(c) {}
    // from equation ax + by = c
    line(T a, T b, T c) : v({ b,-a }), c(c) {}
    // from points p and q
    line(pt p, pt q) : v(q - p), c(cross(v, p)) {}

    T side(pt p) { return cross(v, p) - c; }

    double dist(pt p) { return abs(side(p)) / abs(v); }

    line translate(pt t) { return { v, c + cross(v,t) }; }

    pt proj(pt p) { return p - perp(v) * side(p) / sq(v); }
};



bool inter(line l1, line l2, pt& out) {
    T d = cross(l1.v, l2.v);
    if (d == 0) return false;
    out = (l2.v * l1.c - l1.v * l2.c) / d; // requires floating-point coordinates
    return true;
}



double areaPolygon(vector<pt> const& p) {
    double area = 0.0;
    for (int i = 0, n = int(p.size()) - 1; i < n; ++i) {
        area += cross(p[i], p[i + 1]);
    }
    return abs(area) / 2.0;
}

vector<pt> cutPolygon(pt a, pt b, vector<pt> const& P) {
    vector<pt> R; pt c;
    for (int i = 0; i < int(P.size()) - 1; i++) {
        double left1 = cross(b - a, P[i] - a),
            left2 = cross(b - a, P[i + 1] - a);
        if (left1 >= 0) R.push_back(P[i]); // P[i] is on the left of ab
        if (left1 * left2 < 0) { // edge (P[i], P[i+1]) crosses line ab
            inter({ P[i], P[i + 1] }, { a, b }, c);
            R.push_back(c);
        }
    }
    if (!R.empty())
        R.push_back(R[0]); // make R's first point = R’s last point
    return R;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int N;
    double W, H;
    pt fount;
    cin >> N >> W >> H >> fount.x >> fount.y; 
    /*
    N NUMBER OF LINES
    W WIDTH
    H HEIGHT
    X,Y FOUNTAIN
    NEXT N LINES 2 POINTS OF LINE X1 Y1 X2 Y2*/
    if (!std::cin)
        return false;

    vector<pt> P;
    P.push_back({ 0,0 });
    P.push_back({ W,0 });
    P.push_back({ W,H });
    P.push_back({ 0,H });
    P.push_back({ 0,0 });




    pt a, b;
    for (int i = 0; i < N; i++)
    { //cutPolygon(pt a, pt b, vector<pt> const& P)
        cin >> a.x >> a.y >> b.x >> b.y;
        line L = line(a, b);

        if (L.side(fount) > 0) {
            //está a la izq
            P = cutPolygon(a, b, P);
        }else {
            //derecha
            P = cutPolygon(b, a, P);
        }
    }
    

    double area = areaPolygon(P);
    cout <<setprecision(3)<<fixed<<"Case #"<<++Case<<": " << area << endl;

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