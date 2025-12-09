// Javier Zazo Morillo
// EDA-GDV72


#include <iostream>
#include <iomanip>
#include <fstream>

#include <vector>
#include <string>

// función que resuelve el problema
void resolver(std::vector<char>& soluc, int k, int& n, int& m, std::vector<bool>& usadas) {
    for (char c = 'a'; c < 'a' + m; ++c) {
        soluc[k] = c;

        if (!usadas[c - 'a']) { // ¿Es válida?
            if (k == n - 1) { // ¿Es solución?
                for (char sol : soluc) {
                    std::cout << sol;
                }
                std::cout << "\n";
            }
            else {
                usadas[c - 'a'] = true;
                resolver(soluc, k + 1, n, m, usadas);
                usadas[c - 'a'] = false;
            }
        } 
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, m;
    std::cin >> m >> n;

    if (!std::cin)
        return false;

    std::vector<char> soluc(n);
    std::vector<bool> usadas(m);
    resolver(soluc, 0, n, m, usadas);

    std::cout << "\n";

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