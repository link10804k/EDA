// Javier Zazo Morillo
// EDA-GDV72


#include <iostream>
#include <iomanip>
#include <fstream>


// Complejidad: O(n) siendo n el número de letras de la palabra (si tienen el mismo número de letras) ya que se itera 2n veces para conseguir las letras
// y el resto operaciones son de coste constante. Además, en el mejor de los casos (que las palabras tengan un número diferente de letras), 
// la complejidad es constante (O(1)) porque se devuelve falso antes de iterar sobre las palabras.
bool resolver(std::string palabra1, std::string palabra2) {
    if (palabra1.length() != palabra2.length()) {
        return false;
    }

    int letras1['z' - 'a' + 1]{};
    int letras2['z' - 'a' + 1]{};

    for (int i = 0; i < palabra1.length(); ++i) {
        ++letras1[palabra1[i] - 'a'];
    }
    for (int i = 0; i < palabra2.length(); ++i) {
        ++letras2[palabra2[i] - 'a'];
    }

    bool anagrama = true;
    int i = 0;
    while (i < ('z' - 'a' + 1) && anagrama) {
        if (letras1[i] != letras2[i]) {
            anagrama = false;
        }
        ++i;
    }
    return anagrama;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    std::string palabra1, palabra2;
    std::cin >> palabra1 >> palabra2;

    bool sol = resolver(palabra1, palabra2);

    // escribir sol
    if (sol) {
        std::cout << "SI" << std::endl;
    }
    else {
        std::cout << "NO" << std::endl;
    }
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