// Javier Zazo Morillo
// EDA-GDV72


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

struct Sol {
    bool esDeBusqueda;
    int min;
    int max;
};

//Complejidad: O(n) siendo n el número de nodos del árbol porque se hacen dos llamadas recursivas de tamaño mitad cada iteración 
// (y el resto de operaciones son de complejidad constante).
Sol esDeBusqueda(const bintree<int>& bt) {
    if (bt.empty()) {
		return Sol{ true, -1, -1 };
    }
    Sol izq = esDeBusqueda(bt.left());
    Sol der = esDeBusqueda(bt.right());

    return Sol{ izq.esDeBusqueda && der.esDeBusqueda && (izq.max < bt.root() || izq.max == -1) && (der.min > bt.root() || der.min == -1),
        (izq.min != -1 ? izq.min : bt.root()), (der.max != -1 ? der.max : bt.root()) };
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
	bintree<int> datos = leerArbol(-1);

    Sol sol = esDeBusqueda(datos);

    // escribir sol
    std::cout << (sol.esDeBusqueda ? "SI" : "NO") << std::endl;
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