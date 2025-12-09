// Javier Zazo Morillo
// EDA-GDV72


#include <iostream>
#include <iomanip>
#include <fstream>

#include <vector>

using Tablero = std::vector<std::vector<bool>>;

struct Pos {
    int x, y;
};

bool esValida(const std::vector<int>& soluc, const Pos& pos, const int& k) {
    int i = 0;
    bool valido = true;
    while (i < k && valido) {
        if (pos.y == soluc[i] ||
            pos.y == soluc[i] - pos.y + i ||
            pos.y == soluc[i] + pos.y - i)
            valido = false;
        ++i;
    }
    return valido;
}
bool esSolucion(const int& k, const int& n) {
    return k == n - 1;
}

// función que resuelve el problema
void resolver(std::vector<int>& soluc, int k, int& n, int& m, int& nSol) {
    for (Pos pos = { k, 0 }; pos.y < m; ++pos.y) {
        if (esValida(soluc, pos, k))
            if (esSolucion(k, n))
                ++nSol;
            else {
                soluc[k] = pos.y;
                resolver(soluc, k + 1, n, m, nSol);
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
    int nSol = 0;
    resolver(soluc, 0, n, n, nSol);
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