// Javier Zazo Morillo
// EDA-GDV72


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

// Complejidad: O(n) siendo n el número de nodos del árbol porque se hacen dos llamadas recursivas de tamaño mitad cada iteración (y el resto de operaciones son de complejidad constante).
bool esDeBusqueda(bintree<int> bt, int& min, int& max) {
    if (bt.empty()) {	
		max = INT32_MIN;
		min = INT32_MAX;
        return true;
    }
	int minIzq, maxIzq, minDer, maxDer;
    if (esDeBusqueda(bt.left(), minIzq, maxIzq) && esDeBusqueda(bt.right(), minDer, maxDer) && (bt.root() > maxIzq) && (bt.root() < minDer)) {
        if (bt.left().empty()) {
			min = bt.root();
        }
        else {
            min = minIzq;
        }
        if (bt.right().empty()) {
            max = bt.root();
        }
        else {
			max = maxDer;
        }
		return true;
    }
    else {
		return false;
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
	bintree<int> datos = leerArbol(-1);

    int min = 0; 
    int max = 0;
    bool sol = esDeBusqueda(datos, min, max);

    // escribir sol
    std::cout << (sol ? "SI" : "NO") << std::endl;
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