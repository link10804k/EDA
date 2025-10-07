// Javier Zazo Morillo
// EDA-GDV72


#include <iostream>
#include <iomanip>
#include <fstream>

// O(n) siendo n el número de dígitos del entero porque cada llamada a función se va reduciendo el número en un dígito 
// hasta llegar al caso base de un único dígito
// función que resuelve el problema
int Complementario(int num) {
    if (num <= 9) {
        return 9 - num;
    }
    else {
        return 10*Complementario(num / 10) + 9 - (num % 10);
    }
}
// O(n) siendo n el número de dígitos del entero porque cada llamada a función se va reduciendo el número en un dígito 
// hasta llegar al caso base de un único dígito
// función que resuelve el segundo problema
int ComplementarioInverso(int num, int total) {
    if (num <= 9) {
        return total*10 + 9 - num;
    }
    else {
        return ComplementarioInverso(num / 10, total*10 + (9 - num % 10));
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int num;
    std::cin >> num;

    int sol = Complementario(num);
    int sol2 = ComplementarioInverso(num, 0);
    // escribir sol

    std::cout << sol << " " << sol2 << std::endl;
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