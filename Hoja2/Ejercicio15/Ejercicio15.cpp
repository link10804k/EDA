/*
Nombre completo: Javier Zazo Morillo
DNI:
Usuario del juez: EDA-GDV72
Puesto de laboratorio:
Qué has conseguido hacer y qué no:
*/


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// Complejidad: O(log(fin-ini)) porque cada llamada recursiva reduce la zona de búsqueda a la mitad.
// En el mejor caso, cuando el incremento deseado está en la mitad, la complejidad es constante (O(1)).
int BuscarIncremento(vector<int> const& v, int incrementoDeseado, int ini, int fin) {
    if (incrementoDeseado == 0) {
        return 0;
    }
    int n = fin - ini;
    if (n == 1) {
        return -1;
    }
    else {
        int mit = (ini + fin) / 2;
        int incremento = v[mit] - v[mit - 1];
        if (incremento == incrementoDeseado) {
            return mit;
        }
        else if (incremento < incrementoDeseado){
            return BuscarIncremento(v, incrementoDeseado, mit, fin);
        }
        else {
            return BuscarIncremento(v, incrementoDeseado, ini, mit);
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, inc;
    cin >> inc >> n;
    vector<int> sec(n);
    for (int& e : sec) cin >> e;

    // Llamada a función y escritura de la salida
    int sol = BuscarIncremento(sec, inc, 0, n);

    cout << sol << endl;
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input2.txt");
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
