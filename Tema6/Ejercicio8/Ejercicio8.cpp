// Javier Zazo Morillo
// EDA-GDV72


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

// función que resuelve el problema
int diametro(bintree<char> bt, int& max) {
    if (bt.empty()) return 0;
	else {
		int diametroIzq = diametro(bt.left(), max);
		int diametroDer = diametro(bt.right(), max);
	}
    if (diametro(bt.left()) >= diametro(bt.right())) {
		return diametro(bt.left()) + 1;
    }
    else {
		return diametro(bt.right(), max) + 1;
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<char> datos = leerArbol('.');

	int max = 0
    diametro(datos, max);

    // escribir sol
    std::cout << max << '\n';
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
