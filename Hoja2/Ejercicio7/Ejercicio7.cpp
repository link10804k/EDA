#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// Complejidad: O(log(fin-ini)) porque solo se llama una vez a la función recursiva cada iteración, se le divide a la mitad el espacio de trabajo 
// y el resto de operaciones son de complejidad constante (O(1))
int minimo(const vector<int>& sec, int ini, int fin) {
    if (fin - ini == 1) {
        return sec[ini];
    }
    else {
        int mit = (ini + fin) / 2;

        if (mit > 0 && sec[mit - 1] < sec[mit]) {
            return minimo(sec, ini, mit);
        }
        else if (mit < sec.size() - 1 && sec[mit + 1] < sec[mit]) {
            return minimo(sec, mit, fin);
        }
        else {
            return sec[mit];
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    if (!cin) return false;
    vector<int> sec(n);
    for (int& e : sec) cin >> e;
    cout << minimo(sec, 0, n) << endl;
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
    //system("PAUSE");
#endif

    return 0;
}