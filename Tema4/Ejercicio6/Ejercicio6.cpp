// Javier Zazo Morillo
// GDV-EDA72


#include <iostream>
#include <iomanip>
#include <fstream>
#include "Set.h"
#include <vector>

// COmplejidad: O(v.size() * k) porque se hacen como mucho v.size() iteraciones dentro de las cuales se utiliza un res.add() siendo su tamaño k
Set<int> resolver(const vector<int>& v, int k) {
    Set<int> res;
    
    int i = 0;
    while (res.size() < k) { // O(v.size() * k)
        res.add(v[i]);
        ++i;
    }
    
    for (int j = i; j < v.size(); ++j) { // O(v.size() * k)
        if (v[j] < res.getMax()) {
            res.add(v[j]);
            if (res.size() > k) res.removeMax();          
        }
    }
    return res;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int k; // n elementos menores distintos
    std::cin >> k;

    if (k == 0)
        return false;

    vector<int> v;
    
    int aux;
    std::cin >> aux;

    while (aux != -1) {
        v.push_back(aux);
        std::cin >> aux;
    }

    Set<int> sol = resolver(v, k);

    // escribir sol
    std::cout << sol << std::endl;

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
