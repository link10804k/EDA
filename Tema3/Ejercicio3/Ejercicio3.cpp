// Javier Zazo Morillo
// EDA-GDV72


#include <iostream>
#include <iomanip>
#include <fstream>

#include <vector>

using Tablero = std::vector<std::vector<bool>>;

bool esValida(const std::vector<int>& soluc, const int& k, const std::vector<bool>& columnasOcupadas, const int& columnaActual) {
    bool valido = true;
    if (columnasOcupadas[columnaActual])
        return false;
    int i = 0;
    while (i < k && valido) {
        if (std::abs(soluc[k] - soluc[i]) == k - i)
            valido = false;
        ++i;
    }
    return valido;
}
bool esSolucion(const int& k, const int& n) {
    return k == n - 1;
}

// Complejidad: O(n^n)
void resolver(std::vector<int>& soluc, int k, int& n, int& m, int& nSol, std::vector<bool>& columnasOcupadas, std::vector<bool>& diagonalesOcupadas) {
    for (int i = 0; i < m; ++i) {
        soluc[k] = i;
        if (esValida(soluc, k, columnasOcupadas, i)) {
            if (esSolucion(k, n)) {
                ++nSol;
            }
            else {     
                columnasOcupadas[i] = true;
                //diagonalesOcupadas
                resolver(soluc, k + 1, n, m, nSol, columnasOcupadas);
                columnasOcupadas[i] = false;
            }
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    std::cin >> n;

    std::vector<int> soluc(n); // Columnas
    std::vector<bool> columnasOcupadas(n);
    int nSol = 0;
    resolver(soluc, 0, n, n, nSol, columnasOcupadas);
    // escribir sol

    std::cout << nSol << "\n";
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