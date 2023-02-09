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

const double EPS = 1e-9;
const double PI = acos(-1);

using T = int;
bool lt(int a, int b) { return a < b; }
bool eq(int a, int b) { return a == b; }

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

ostream& operator<<(ostream& os, pt p) {
    return os << "(" << p.x << "," << p.y << ")";
}

double dist(pt a, pt b) { // Euclidean distance
    return hypot(a.x - b.x, a.y - b.y);
}
T dist2(pt a, pt b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

// PRODUCTOS

T dot(pt v, pt w) { return v.x * w.x + v.y * w.y; }

bool isPerp(pt v, pt w) { return dot(v, w) == 0; }

double angle(pt v, pt w) {
    double cosTheta = dot(v, w) / abs(v) / abs(w);
    return acos(max(-1.0, min(1.0, cosTheta)));
}

T cross(pt v, pt w) { return v.x * w.y - v.y * w.x; }

// positivo/cero/negativo: c a la izquieda/sobre/derecha de a-b
T orient(pt a, pt b, pt c) { return cross(b - a, c - a); }

bool inAngle(pt a, pt b, pt c, pt p) {
    assert(orient(a, b, c) != 0);
    if (orient(a, b, c) < 0) swap(b, c);
    return orient(a, b, p) >= 0 && orient(a, c, p) <= 0;
}

double orientedAngle(pt a, pt b, pt c) {
    if (orient(a, b, c) >= 0)
        return angle(b - a, c - a);
    else
        return 2 * PI - angle(b - a, c - a);
}


// ORDENACIÓN POLAR

bool half(pt p) { // true if in blue half
    assert(p.x != 0 || p.y != 0); // the argument of (0,0) is undefined
    return p.y > 0 || (p.y == 0 && p.x < 0);
}

void polarSort(vector<pt>& v) {
    sort(v.begin(), v.end(), [](pt v, pt w) {
        return make_tuple(half(v), 0, sq(v)) < make_tuple(half(w), cross(v, w), sq(w));
        });
}


// TRANSFORMACIONES

pt translate(pt v, pt p) { return p + v; }

// scale p by a certain factor around a center c
pt scale(pt c, double factor, pt p) {
    return c + (p - c) * factor;
}


// rotate 90º counterclockwise
pt perp(pt p) { return { -p.y, p.x }; }

// LINEAS
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


// POLIGONOS, el primer y último puntos coinciden

double areaTriangle(pt a, pt b, pt c) {
    return abs(cross(b - a, c - a)) / 2.0;
}

double areaPolygon(vector<pt> const& p) {
    double area = 0.0;
    for (int i = 0, n = int(p.size()) - 1; i < n; ++i) {
        area += cross(p[i], p[i + 1]);
    }
    return abs(area) / 2.0;
}

bool isConvex(vector<pt> const& p) {
    bool hasPos = false, hasNeg = false;
    for (int i = 0, n = (int)p.size(); i < n; ++i) {
        int o = orient(p[i], p[(i + 1) % n], p[(i + 2) % n]);
        if (o > 0) hasPos = true;
        if (o < 0) hasNeg = true;
    }
    return !(hasPos && hasNeg);
}


// ENVOLVENTE CONVEXA

// para aceptar puntos colineales cambia a >=
// returns true if point r is on the left side of line pq
bool ccw(pt p, pt q, pt r) {
    return orient(p, q, r) > 0;
}

// devuelve un polígono con la envolvente convexa de una nube de puntos P.
vector<pt> convexHull(vector<pt>& P) {
    int n = int(P.size()), k = 0;
    vector<pt> H(2 * n);
    sort(P.begin(), P.end());
    // build lower hull
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && !ccw(H[k - 2], H[k - 1], P[i])) --k;
        H[k++] = P[i];
    }
    // build upper hull
    for (int i = n - 2, t = k + 1; i >= 0; --i) {
        while (k >= t && !ccw(H[k - 2], H[k - 1], P[i])) --k;
        H[k++] = P[i];
    }
    H.resize(k);
    return H;
}


// DIVISIÓN DE UN POLÍGONO

vector<pt> cutPolygon(pt a, pt b, vector<pt> const& P) {
    vector<pt> R; pt c;
    for (int i = 0; i < int(P.size()) - 1; i++) {
        double left1 = cross(b - a, P[i] - a),
            left2 = cross(b - a, P[i + 1] - a);
        if (left1 >= 0) R.push_back(P[i]);  // P[i] is on the left of ab
        if (left1 * left2 < 0) {  // edge (P[i], P[i+1]) crosses line ab
            inter({ P[i], P[i + 1] }, { a,b }, c);
            R.push_back(c);
        }
    }
    if (!R.empty())
        R.push_back(R[0]); // make R's first point = R's last point
    return R;
}



//BIPARTITE
int M, N; // M parte izquierda, N parte derecha
vector<vector <int>> grafo; // dirigido, tamaño M
vector<int> match, vis;

int aug(int l) {
    if (vis[l]) return 0;
    vis[l] = 1;
    for(auto r: grafo[l]){
        if (match[r] == -1 || aug(match[r])){
            match[r] = l;
            return 1;
        }
    }
    return 0;
}

int berge_mcbm() {
    int mcbm = 0;
    match.assign(N + M, -1);
    for (int l = 0; l < M; l++){
        vis.assign(M, 0);
        mcbm += aug(l);
    }
    return mcbm;
}
struct tTower {
    pt position;
    int power;
};

int war(const vector<tTower>& left, const vector<tTower>& right, int R) {
    M = left.size();
    N = right.size();
    grafo = vector<vector<int>>(M,vector<int>());
    for (int i = 0; i < left.size(); i++){
        for (int j = 0; j < right.size(); j++){
            if (dist(left[i].position, right[j].position) <= R) {
                //J ESTÁ AL ALCANCE DE I
                if (left[i].power > right[j].power) {
                    //LA TORRE GANA 
                    //EN EMPATE PIERDE
                    grafo[i].push_back(M + j);
                }
            }
        }
    }
    return berge_mcbm();
}
int Case = 0;
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int Tow; cin >> Tow; // 5 / 300 Watch Towers
    if (Tow == 0)
        return false;

    vector<tTower> towers(Tow);
    for (int i = 0; i < Tow; i++){
        int x, y, P; // > 0
        cin >> x >> y >> P;
        //x,y tower Position and P power, P == 0 its a free tower
         towers[i] = { x,y,P };

    }

    int a, b, R; //a,b IDS of free towers to draw the separation
    cin >> a >> b >> R;
    line divide = line(towers[a - 1].position, towers[b - 1].position);

    vector<tTower> left, right;

    for (int i = 0; i < Tow; i++){
        if (i != a - 1 && i != b - 1) {
            if (towers[i].power != 0) {
                if (divide.side(towers[i].position) > 0) {
                    left.push_back(towers[i]);
                }else{
                    right.push_back(towers[i]);
                }
            }
        }
    }

    int sol = 0;
    if (left.size() > right.size()) {
        sol = war(right, left, R);
    }else {
        sol = war(left,right, R);
    }
    // escribir sol
    cout << "Case " << ++Case << ": "<<sol<< "\n";
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
