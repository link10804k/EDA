
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// Complejidad: O(fin - ini) porque se llama 2 veces a la función recursiva dándole a cada llamada la mitad del espacio de trabajo
// y las operaciones que se hacen en cada llamada son de complejidad constante (O(1)).
bool caucasico(const std::vector<int>& v, int ini, int fin, int& par) {
    if (fin - ini == 1) {
        par = (v[ini] % 2 == 0);
        return true;
    }
    else {
        int mit = (ini + fin) / 2;

        if (!caucasico(v, ini, mit, par)) {
            return false;
        }
        int parIzq = par;

        if (!caucasico(v, mit, fin, par)) {
            return false;
        }
        int parDer = par;

        if (abs(parIzq - parDer) > 2) {
            return false;
        }
        else {
            par = parIzq + parDer;
            return true;
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, par;
    cin >> n;
    if (n == 0) return false;
    vector<int> sec(n);
    for (int& e : sec) cin >> e;
    cout << (caucasico(sec, 0, n, par) ? "SI" : "NO") << endl;
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
    //system("PAUSE");
#endif

    return 0;
}