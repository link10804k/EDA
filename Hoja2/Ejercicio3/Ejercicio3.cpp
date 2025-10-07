// Javier Zazo Morillo
// EDA-GDV72

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

// Complejidad: O(fin-ini) porque el método se llama recursivamente 2 veces dividiendo el espacio de trabajo por 2 cada ciclo hasta llegar al caso base 
// sin hacer ninguna operación con los componentes del vector (solo hace operaciones de complejidad constante)
bool parcialmenteOrdenado(const vector<int>& v, int ini, int fin, int& min, int& max) {
    int mit = (ini + fin) / 2;

    if (fin - ini == 1) { // Solo funciona para vectores de tamaño 2^0
        return true;
    }
    else if (fin - ini == 2) {
        if (v[ini] <= v[mit]) {
            min = v[ini];
            max = v[mit];
            return true;
        }
        else {
            return false;
        }
    }
    else {
        int minIzq, maxIzq;
        int minDer, maxDer;

        if (parcialmenteOrdenado(v, ini, mit, minIzq, maxIzq) && parcialmenteOrdenado(v, mit, fin, minDer, maxDer)) {
            if (minIzq <= minDer && maxDer >= maxIzq) {
                min = minIzq;
                max = maxDer;
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
}

bool parcialmenteOrdenado(const vector<int>& v) {
    int min, max;
    return parcialmenteOrdenado(v, 0, v.size(), min, max);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int e;
    cin >> e;
    if (e == 0) return false;
    vector<int> sec;
    while (e != 0) {
        sec.push_back(e);
        cin >> e;
    }
    cout << (parcialmenteOrdenado(sec) ? "SI" : "NO") << endl;
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