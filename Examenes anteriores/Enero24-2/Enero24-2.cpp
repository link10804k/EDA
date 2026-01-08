// Javier Zazo Morillo
// EDA-GDV72

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

// Complejidad: O(log p) siendo p el número de puntos de la recta porque cada iteración se reduce el espacio de búsqueda a la mitad y las operaciones tienen complejidad constante
std::pair<int, int> resolver(const std::vector<int>& c, const std::vector<int>& d, int ini, int fin) {
    int n = fin - ini;
    int mit = (ini + fin) / 2;

    if (c[mit] == d[mit]) return { mit, mit };
    if (n == 1) {
        if (c[ini] > d[ini]) return { -1, 0 };
        else return { ini, fin };
    }

    if (c[mit] < d[mit]) return resolver(c, d, mit, fin);
    else return resolver(c, d, ini, mit);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int nElems;
    std::cin >> nElems;

    if (nElems == 0)
        return false;

    std::vector<int> c, d;
    int aux;
    for (int i = 0; i < nElems; ++i) {
        std::cin >> aux;
        c.push_back(aux);
    }
    for (int i = 0; i < nElems; ++i) {
        std::cin >> aux;
        d.push_back(aux);
    }

    std::pair<int, int> sol = resolver(c, d, 0, nElems);

    // escribir sol
    if (sol.first == sol.second) {
        std::cout << "SI " << sol.first << "\n";
    }
    else {
        std::cout << "NO " << sol.first << " " << sol.second << "\n";
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
