/*
Nombre completo: Javier Zazo Morillo
Usuario del juez: EDA-GDV72
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

// Complejidad: O(n) siendo n el número de nodos del árbol porque el algoritmo recorre todos los nodos y solo hace operaciones de complejidad constante
template <class T>
int acumuladores(bintree<T> const& tree, int& nAcumuladores) {
    int acumulador = 0;

    if (!tree.empty()) {
        acumulador += acumuladores(tree.left(), nAcumuladores);
        acumulador += acumuladores(tree.right(), nAcumuladores);

        int raiz = tree.root();
        if (acumulador == raiz) ++nAcumuladores;
        acumulador += raiz;
    }   

    return acumulador;
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<int> tree;
    tree = leerArbol(-1);

    int nAcumuladores = 0;
    acumuladores(tree, nAcumuladores);

    cout << nAcumuladores << endl;
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    ifstream in("input2.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}
