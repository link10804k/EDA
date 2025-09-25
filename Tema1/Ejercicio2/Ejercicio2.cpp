// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

// función que resuelve el problema
int* resolver(std::vector<int> datos) {
    int* sol = new int[2];
    sol[0] = 0;
    sol[1] = 0;

    for (int i = 1; i < datos.size() - 1; ++i) {
        if (datos[i - 1] < datos[i] && datos[i] > datos[i + 1]) { // Picos
            ++sol[0];
        }
        else if (datos[i - 1] > datos[i] && datos[i] < datos[i + 1]) { // Valles
            ++sol[1];
        }
    }
    return sol;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int nDatos;
	std::cin >> nDatos;

	std::vector<int> datos(nDatos);
    for (int i = 0; i < nDatos; ++i) {
		std::cin >> datos[i];
    }

    int* sol = resolver(datos);   

    // escribir sol
	std::cout << sol[0] << " " << sol[1] << std::endl;
    delete(sol);
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