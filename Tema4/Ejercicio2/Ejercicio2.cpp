// Javier Zazo Morillo
// GDV-EDA72

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

#include "horas.h"

Hora LeerHora() {
    std::string hora;
    std::cin >> hora;

    std::string horas = hora.substr(0, 2);
    std::string minutos = hora.substr(3, 2);
    std::string segundos = hora.substr(6, 2);

    return Hora(std::stoi(horas), std::stoi(minutos), std::stoi(segundos));
}
std::string EscribirHora(Hora hora) {
    return (std::to_string(hora.GetHoras()) + ":" + std::to_string(hora.GetMins()) + ":" + std::to_string(hora.GetSegs()));
}

int BusquedaBinaria(const std::vector<Hora>& trenes, Hora hora, int ini, int fin) {
    if (trenes[trenes.size() - 1] < hora) {
        return -1;
    }
    else if (fin - ini == 1) {
        return fin;
    }
    else {
        int mit = (ini + fin) / 2;

        if (trenes[mit] < hora) {
             return BusquedaBinaria(trenes, hora, mit, fin);
        }
        else {
            return BusquedaBinaria(trenes, hora, ini, mit);
        }
    }
}
// función que resuelve el problema
std::vector<std::string> resolver(const std::vector<Hora>& trenes, int nHoras) {
    std::vector<std::string> respuestas;
    int respuesta;

    std::vector<Hora> horas; // dentro de resolver
    for (int i = 0; i < nHoras; ++i) {
        try {
            horas.push_back(LeerHora());
        }
        catch (const char* error) {
            std::cout << error << std::endl;
        }
    }


    for (Hora h : horas) {
        respuesta = BusquedaBinaria(trenes, h, 0, trenes.size());
        if (respuesta == -1) {
            respuestas.push_back("NO");
        }
        else {
            respuestas.push_back(EscribirHora(trenes[respuesta]));
        }
    }
    return respuestas;
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
        trenes.push_back(LeerHora());
    }

    std::vector<std::string> sol = resolver(trenes, nHoras);

    // escribir sol
    for (std::string s : sol) {
        std::cout << s << std::endl;
    }
    std::cout << "---" << std::endl;

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
