// Javier Zazo Morillo
// EDA-GDV72

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

// función que resuelve el problema
bool resolver(int nDatos) {
    std::vector<int> datos;
    bool dalton = true;
    int aux;

    for (int i = 0; i < nDatos; ++i) {
        std::cin >> aux;
        datos.push_back(aux);
    }

    if (datos[1] > datos[0]) { // Ascendente
        int i = 2;
        while (i < nDatos && dalton) {
            if (datos[i] <= datos[i - 1]) {
                dalton = false;
            }
            ++i;
        }
    }
    else { // Descendente
        int i = 2;
        while (i < nDatos && dalton) {
            if (datos[i] >= datos[i - 1]) {
                dalton = false;
            }
            ++i;
        }
    }
    return dalton;
}
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    int nDatos;
	std::cin >> nDatos;

    if (nDatos == 0)
        return false;

    bool sol = resolver(nDatos);

    // escribir sol

    if (sol) {
        std::cout << "DALTON" << std::endl;
    }
    else {
        std::cout << "DESCONOCIDOS" << std::endl;
    }

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
