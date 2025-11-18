// Javier Zazo Morillo
// EDA-GDV72


#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>


// función que resuelve el problema
int resolver(int nCapitulos) {
	std::map<int, int> diccionario;

    int capitulo;
    for (int i = 0; i < nCapitulos; ++i) {
		std::cin >> capitulo;
        if (diccionario.at(capitulo) != 0) {
            LimpiarSeccion(diccionario, capitulo);
        }
        else {
            diccionario.insert(capitulo, i + 1);
        }
    }
}
void LimpiarSeccion(std::map<int, int>& diccionario, int capitulo) {

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int nCapitulos;
    std::cin >> nCapitulos;

    int sol = resolver(nCapitulos);

    // escribir sol
	std::cout << sol << '\n';
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