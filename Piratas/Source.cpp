// PC08


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

const int MAX_N = 1024000;
const int MAX_M = 100;
int idx = 0;
int first[MAX_M];
int prof[2 * MAX_N + 1];

class SegmentTree {
    vector<int> st;
    int tam; // N´umero de hojas que manejamos
    vector<int> lazy;
public:
    // Tama˜no m´aximo que podremos guardar
    // (n´umero de hojas).
    // Antes de las consultas, se necesita rellenar
    // con los datos iniciales usando build().
    SegmentTree(int maxN) {
        st.assign(4 * maxN + 10,0);
        lazy.assign(4 * maxN + 10, 0);
    }
    int bucaneers() {

    }

    int query(int a, int b) {
        return query(1, 0, tam - 1, a, b);
    }


    int query(int vertex, int L, int R, int i, int j) {
        pushLazyUpdate(vertex,L,R);
        if (i > R || j < L) {
            return 0;
        }
        if (L >= i && R <= j)
            // Segmento completamente dentro de la consulta
            return st[vertex];
        int mitad = (L + R) / 2;
        return query(2 * vertex, L, mitad, i, j) +
            query(2 * vertex + 1, mitad + 1, R, i, j);
    }
    void update(int pos, int newVal) {
        update(1, 0, tam - 1, pos, newVal);
    }
    void setLazyUpdate(int vertex, int value) {
        // Mezclamos
        // Importante +=: el nodo podr´ıa tener
        // otras operaciones pendientes anteriores
        /*
        NOP = 0
        SET 0 = 1
        SET 1 = 2
        INV = 3
        */
        lazy[vertex] = value;
    }

    void pushLazyUpdate(int vertex, int L, int R) {
        st[vertex] += (R - L + 1) * lazy[vertex];

        //HAY QUE TENER EN CUENTA QUE HABÍA ANTES EN LAZY :)
        switch (lazy[vertex]){
        case 1: {
             //SET 0
            
            st[vertex] = 0;
        }
        case 2: {
            //SET 1
            st[vertex] = 1;
        }
        case 3: {
            //INV
            if (lazy[vertex] == 0) {
                if (st[vertex] == 0) st[vertex] = 1;
                else st[vertex] = 0;
            }
            else if (lazy[vertex] == 1) {
                st[vertex] = 1;
            }
            else if (lazy[vertex] == 2) {
                st[vertex] = 0;
            }
            else {
                    //invertir la invertisión es no hacer nada
            }
        }
        default:
            break;
        }
        if (L != R) {
            // Tenemos hijos
            int m = (L + R) / 2;
            setLazyUpdate(2 * vertex, lazy[vertex]);
            setLazyUpdate(2 * vertex + 1, lazy[vertex]);
        }
        lazy[vertex] = 0;
    }

    void updateRange(int vertex, int L, int R,int a, int b, int op) {
        // Resolvemos posibles operaciones pendientes
        pushLazyUpdate(vertex, L, R);
        if ((b < L) || (R < a)) return;
        // ¿Intervalo afectado por completo?
        if ((a <= L) && (R <= b)) {
            // Nos aplicamos la operaci´on y propagamos la
            // pereza a los hijos. Para evitar copiar/pegar,
            // lo hacemos aplic´andonos la pereza, y luego
            // resolvi´endola
            setLazyUpdate(vertex, op);
            pushLazyUpdate(vertex, L, R);
            return;
        }

        // Intervalo no afectado por completo. No podemos
        // ser perezosos. Aplicamos la operaci´on en
        // los hijos
        int m = (L + R) / 2;
        updateRange(2 * vertex, L, m, a, b, op);
        updateRange(2 * vertex + 1, m + 1, R, a, b, op);
        // Combinamos
        st[vertex] = st[2 * vertex] + st[2 * vertex + 1];
    }

    void update(int vertex, int l, int r,int pos, int newVal) {
        if ((pos < l) || (r < pos)) return;
        if (l == r) {
            st[vertex] = newVal;
            return;
        }
        int m = (l + r) / 2;
        if ((l <= pos) && (pos <= m))
            update(2 * vertex, l, m, pos, newVal);
        else
            update(2 * vertex + 1, m + 1, r, pos, newVal);
        st[vertex] = st[2 * vertex] + st[2 * vertex + 1];
    }
    void updateRange(int a, int b, int v) {
        updateRange(1, 0, tam - 1, a, b, v);
    }
    void build(const vector<int> &values, int n) {
        tam = n;
        build(values, 1, 0, n - 1);
    }
    void build(const vector<int> &values, int p, int l, int r) {
        if (l == r) {
            st[p] = values[l];
            return;
        }
        int m = (l + r) / 2;
        build(values, 2 * p, l, m);
        build(values, 2 * p + 1, m + 1, r);
        st[p] = st[2 * p] + st[2 * p + 1];
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    string land = "";
    int M; cin >> M;
    for (int i = 0; i < M; i++){
        int mul; cin >> mul;
        string cad; cin >> cad;
        for (int j = 0; j < mul; j++)
        {
            land += cad;
        }
    }
    vector<int> pirates;
    for (int i = 0; i < land.size(); i++){
        pirates.push_back(land[i]-'0');
    }

    //land is INDEX OF PIRATES  01010101010
    SegmentTree tree(land.size());
    tree.build(pirates, land.size());

    int q; cin >> q;
    while (q--){
        char order;
         int a, b; cin >> order >> a >> b;
         cout << "Q" << q << ": ";
        switch (order)
        {
        case 'F': {
            //MUTA LOS PIRATAS DE A a B en BUCANIERS

            tree.updateRange(a,b, 1);
        }
        case 'E': {
            //MUTA LOS PIRATAS DE A a B en BARBARIERS
            tree.updateRange(a,b, 2);
        }
        case 'I': {
            //DE A a B los invierte
            tree.updateRange(a,b,3);
        }
        case 'S': {
            //Cuantos Bucaneers entre a y b (included)
            tree.bucaneers();
        }
        default:
            cout << "ERROR";
            break;
        }
        cout << endl;
    }

 //   TipoSolucion sol = resolver(datos);
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
    for (int i = 0; i < numCasos; ++i) {
        cout << "Case " << i+1 << endl;
        resuelveCaso();
    }


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}