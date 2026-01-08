// Javier Zazo Morillo
// EDA-GDV72

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

// Complejidad: O(log p) siendo p el número de puntos de la recta porque cada iteración se reduce el espacio de búsqueda a la mitad y las operaciones tienen complejidad constante
std::pair<int, int> resolver(const std::vector<int>& v1, const std::vector<int>& v2, int ini, int fin) {
    // Casos base
    int n = fin - ini;

    if (n == 0) return { ini, fin }; // Vectores de solo 1 punto
    if (n == 1) {
        int difIni = v1[ini] - v2[ini];
        int difFin = v1[fin] - v2[fin];

        // Cruces dentro del intervalo
        if (difIni == 0) return { ini, ini };
        if (difFin == 0) return { fin, fin };
        if (difIni > 0 != difFin > 0) return { ini, fin };

        // Cruces fuera del intervalo
        if (abs(difIni) < abs(difFin)) return { -1, 0 };
        else return { v1.size() - 1, v1.size() };
    }

    int mit = (ini + fin) / 2;
    int difIzq = v1[mit] - v2[mit];
    int difDer = v1[mit+1] - v2[mit+1];

    // Si está entre estos dos puntos
    if (difIzq > 0 != difDer > 0) {
        return resolver(v1, v2, mit, mit + 1);
    }
    else if (abs(difIzq) < abs(difDer)) {
       return resolver(v1, v2, ini, mit);
    }
    else {
       return resolver(v1, v2, mit, fin);
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int nElems;
    std::cin >> nElems;

    if (nElems == 0)
        return false;

    std::vector<int> v1, v2;
    int aux;
    for (int i = 0; i < nElems; ++i) {
        std::cin >> aux;
        v1.push_back(aux);
    }
    for (int i = 0; i < nElems; ++i) {
        std::cin >> aux;
        v2.push_back(aux);
    }

    std::pair<int, int> sol = resolver(v1, v2, 0, nElems);

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
