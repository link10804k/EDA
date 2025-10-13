// Javier Zazo Morillo
// GDV-EDA72

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// Complejidad: O(log(fin-ini)) porque solo se llama una vez a la función recursiva cada iteración, se le divide a la mitad el espacio de trabajo 
// y el resto de operaciones son de complejidad constante (O(1))
bool elemento_situado(const vector<int>& v, int ini, int fin) {
    if (v.size() == 0) {
        return false;
    }
    else if (fin - ini == 1) {
        return v[ini] == ini;
    }
    else {
        int mit = (ini + fin) / 2;
        if (v[mit] == mit) {
            return true;
        }
        else if (v[mit] > mit) {
            return elemento_situado(v, ini, mit);
        }
        else {
            return elemento_situado(v, mit, fin);
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    vector<int> sec(n);
    for (int& e : sec) cin >> e;
    cout << (elemento_situado(sec, 0, n) ? "SI" : "NO") << endl;
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
    //system("PAUSE");
#endif

    return 0;
}
