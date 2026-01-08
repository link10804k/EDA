// Javier Zazo Morillo
// EDA-GDV72


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
#include <vector>

// Complejidad: O(n) siendo n el número de nodos del árbol
bool esSimetrico(const bintree<char>& btIzq, const bintree<char>& btDer) {
    if (btIzq.empty() != btDer.empty()) return false;
    if (btIzq.empty() && btDer.empty()) return true;
    else return esSimetrico(btIzq.left(), btDer.right()) && esSimetrico(btIzq.right(), btDer.left());
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<char> bt = leerArbol('.');
    
    bool sol = esSimetrico(bt.left(), bt.right());

    // escribir sol
    std::cout << (sol ? "SI" : "NO") << "\n";
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