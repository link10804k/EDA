// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include<vector>

// función que resuelve el problema
bool resolver(int datos[], int pos, int nDatos) {
    int max = datos[0];
    for (int i = 1; i < pos + 1; ++i) {
        if (datos[i] > max) {
            max = datos[i];
        }
    }

    bool menores = true;
    int i = pos + 1;

    while (i < nDatos && menores) {
        if (datos[i] <= max) {
            menores = false;
        }
        ++i;
    }
    return menores;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int nDatos;
    int pos;

    std::cin >> nDatos;
    std::cin >> pos;

    int* datos = new int[nDatos];
    for (int i = 0; i < nDatos; ++i) {
        std::cin >> datos[i];
    }

    bool sol = resolver(datos, pos, nDatos);
    delete[] datos;

    // escribir sol
    if (sol) {
        std::cout << "SI" << std::endl;
    }
    else {
        std::cout << "NO" << std::endl;
    }

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