// Javier Zazo Morillo
// EDA-GDV72

#include <iostream>
#include <iomanip>
#include <fstream>
#include <set>
#include <vector>

int sumaDigitosCuadrados(int n) { // O(1)
    int res = 0;
    while (n != 0) {
        res += std::pow(n % 10, 2);
        n /= 10;
    }
    return res;
}
bool estaEnSet(const std::set<int>& s, int n) { // O(log(s.size()))
    std::set<int>::iterator it;
    it = s.find(n); // O(log(s.size()))

    return it != s.end();
}
// Complejidad: O()
std::vector<int> esFeliz(int n) {
    std::set<int> s;
    std::vector<int> v;

    while (n != 1 && !estaEnSet(s, n)) {
        s.insert(n);
        v.push_back(n);
        n = sumaDigitosCuadrados(n);
    }
    v.push_back(n);
    v.push_back(n == 1);

    return v;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    std::cin >> n;

    if (!std::cin)
        return false;

    std::vector<int> sol = esFeliz(n);

    // escribir sol
    for (int n : sol) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

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