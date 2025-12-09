// Javier Zazo Morillo
// EDA-GDV72


#include <iostream>
#include <iomanip>
#include <fstream>

#include <vector>
#include <string>

// función que resuelve el problema
void resolver(std::vector<std::string>& soluc, int k, int n, int m) {
    std::string s = "";
        s.append(std::to_string('a' + m));

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, m;
    std::cin >> n >> m;

    if (!std::cin)
        return false;

    std::vector<std::string> soluc;
    resolver(soluc, 0, n, m);

    // escribir sol
    for (std::string sol : soluc) {
        std::cout << sol << "\n";
    }
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