// Javier Zazo Morillo
// EDA-GDV72

#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

// Complejidad: O(n) siendo n el número de nodos del árbol binario porque el algoritmo visita todos los nodos sin repetir ninguno y todas las operaciones son de complejidad constante
void resolver(bintree<int> bt, int dragones, int& mejorHoja, int& dragonesMejorHoja) {
    if (bt.root() >= 3) {
        if (dragones < dragonesMejorHoja) {
            mejorHoja = bt.root();
            dragonesMejorHoja = dragones;
        }
    }
    else {
        dragones += bt.root() == 1;

        if (!bt.left().empty()) {
            resolver(bt.left(), dragones, mejorHoja, dragonesMejorHoja);
        }
        if (!bt.right().empty()) {
            resolver(bt.right(), dragones, mejorHoja, dragonesMejorHoja);
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<int> bt = leerArbol(-1);

    int mejorHoja = 0;
    int dragonesMejorHoja = INT32_MAX;
    resolver(bt, 0, mejorHoja, dragonesMejorHoja);

    // escribir sol
    std::cout << mejorHoja << "\n";
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