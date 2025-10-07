// Javier Zazo Morillo
// GDV-EDA72


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

bool disperso(int i1, int i2, int dispersion) {
    return i1 - i2 >= dispersion || i2 - i1 >= dispersion;
}

// Complejidad: O(fin - ini) porque se llama 2 veces a la función de manera recursiva reduciendo el espacio de trabajo a la mitad 
// y el resto de operaciones son de complejidad constante
bool sufDisperso(std::vector<int> const& v, int dispersion, int ini, int fin) {
    int n = fin - ini;
    if (n == 1) {
        return true;
    }
    else {
        int mit = (ini + fin) / 2;
        if (disperso(v[ini], v[fin - 1], dispersion)) {
            if (sufDisperso(v, dispersion, ini, mit) && sufDisperso(v, dispersion, mit, fin)) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int nDatos, dispersion;

    std::cin >> nDatos >> dispersion;
    if (!std::cin)
        return false;

    std::vector<int> v;

    int aux;
    for (int i = 0; i < nDatos; ++i) {
        std::cin >> aux;
        v.push_back(aux);
    }

    

    bool sol = sufDisperso(v, dispersion, 0, nDatos);

    // escribir sol
    std::cout << (sol ? "SI" : "NO") << std::endl;

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