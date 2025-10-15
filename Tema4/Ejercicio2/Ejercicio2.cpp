// Javier Zazo Morillo
// GDV-EDA72

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

#include "horas.h"

Hora LeerHora() {
    std::string hora;
    std::cin >> hora;

    return Hora(int(hora[0] + hora[1]), int(hora[3] + hora[4]), int(hora[6] + hora[6]));
}

int BusquedaBinaria(const std::vector<Hora>& trenes, Hora hora, int ini, int fin) {
    if (fin - ini == 1) {
        return ini;
    }
    else {
        int mit = (ini + fin) / 2;

        if (trenes[mit] < hora) {
             return BusquedaBinaria(trenes, hora, mit, fin);
        }
        else {
            return BusquedaBinaria(trenes, hora, ini, mit + 1);
        }
    }
}
// función que resuelve el problema
void resolver(const std::vector<Hora>& trenes, const std::vector<Hora>& horas) {
    for (Hora h : horas) {
        BusquedaBinaria(trenes, h, 0, trenes.size());
    }

}
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int nTrenes, nHoras;
    std::cin >> nTrenes >> nHoras;

    if (nTrenes == 0 && nHoras == 0)
        return false;

    std::vector<Hora> trenes;
    for (int i = 0; i < nTrenes; ++i) {
        try {
            trenes.push_back(LeerHora());
        }
        catch (std::string error) {
            std::cout << error << std::endl;
        }
    }

    std::vector<Hora> horas;
    for (int i = 0; i < nHoras; ++i) {
        try {
            horas.push_back(LeerHora());
        }
        catch (std::string error) {
            std::cout << error << std::endl;
        }
    }

    TipoSolucion sol = resolver(trenes, horas);

    // escribir sol

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
