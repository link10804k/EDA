// Javier Zazo Morillo
// EDA-GDV72

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

// función que resuelve el problema
int resolver(std::vector<int> const& v, int ini, int fin) {
    int n = fin - ini;
    if (n == 0) {
        return ini;
    }
    else {
        int mit = (fin + ini) / 2;

        if (v[mit - 1] != v[mit] && mit - ini % 2 !0) {
            return resolver(v, ini, mit - 1);
        }
        else {
            return resolver(v, mit, fin);
        }
    }
    


}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    std::cin >> n;
    std::vector<int> v(n);
    for (int& e : v) std::cin >> e;

    // Llamada a la función resolver
    int sol = resolver(v, 0, v.size());

    // Mostrar el resultado
    std::cout << sol << std::endl;
}


//#define DOMJUDGE
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
    //system("PAUSE");
#endif

    return 0;
}