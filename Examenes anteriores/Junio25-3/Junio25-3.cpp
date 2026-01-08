/*
Nombre completo: Javier Zazo Morllo
Usuario del juez: EDA-GDV72

Cuestión extra: ¿Cuál sería la menor complejidad en tiempo que podría tener una función que elimine los k pares clave-valor con menor valor para cada caso (map y unordered_map)? Justifica tu respuesta.

*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

// Complejidad:
template <class K, class V>
void eliminaKMenores(map<K, V>& map, int k) {
    int i = 0;
    while (i < k && !map.empty()) {
        map.erase(map.begin());
        ++i;
    }
}

// Complejidad:
template <class C, class V>
void eliminaKMenores(unordered_map<C, V>& map, int k) {
    vector<string> volcado;
    for (auto [clave, valor] : map) {
        volcado.push_back(clave);
    }

    sort(volcado.begin(), volcado.end());

    int i = 0;
    while (i < k && !map.empty()) {
        map.erase(volcado[i]);
        ++i;
    }
}



void resuelveCaso() {
    map<string, int> map1;
    unordered_map<string, int> map2;
    int n, k;

    // Lectura de datos
    cin >> n >> k;
    string clave;
    int valor;
    for (int i = 0; i < n; ++i) {
        cin >> clave >> valor;
        map1.insert({ clave, valor });
        map2.insert({ clave, valor });
    }

    // Llamada a funciones
    eliminaKMenores(map1, k);
    eliminaKMenores(map2, k);

    // Escritura de la salida

    // Imprimir map1 ordenado por claves
    for (auto [clave, valor] : map1) {
        cout << clave << " " << valor << "\n";
    }
    cout << "-\n";

    // Imprimir map2 ordenado por claves (para ello debes volcarlo a un vector, ordenarlo e imprimirlo)
    vector<pair<string, int>> volcado;
    for (auto entrada : map2) {
        volcado.push_back(entrada);
    }

    sort(volcado.begin(), volcado.end());

    for (auto [clave, valor] : volcado) {
        cout << clave << " " << valor << "\n";
    }
    cout << "---\n";
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input3.txt");
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