// Javier Zazo Morillo
// EDA-GDV72

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

#include <unordered_map>

using DNI = string;
using Puntos = int;

class carnet_puntos {
private:
    std::unordered_map<DNI, Puntos> conductores;
    std::unordered_map<Puntos, int> conductoresPorPuntos;

public:
    carnet_puntos() {}

    // Complejidad: O(1) porque insert() es constante en promedio
    void nuevo(DNI const& conductor) {
         if (!conductores.insert({conductor, 15}).second) 
             throw std::domain_error("Conductor duplicado");
         else {
             ++conductoresPorPuntos[15];
         }
    }

    // Complejidad: O(1) porque find() es constante en promedio
    void quitar(DNI const& conductor, int puntos) {
        std::unordered_map<DNI, Puntos>::iterator it = conductores.find(conductor);

        if (it == conductores.end()) {
            throw std::domain_error("Conductor inexistente");
        }
        else {
            --conductoresPorPuntos[(*it).second];

            (*it).second -= puntos;
            if ((*it).second < 0) (*it).second = 0;

            ++conductoresPorPuntos[(*it).second];
        }
    }

    // Complejidad: O(1) porque find() es constante en promedio
    int consultar(DNI const& conductor) const {
        std::unordered_map<DNI, Puntos>::const_iterator it = conductores.find(conductor);

        if (it == conductores.end()) {
            throw std::domain_error("Conductor inexistente");
        }
        else {
            return (*it).second;
        }
    }

    // Complejidad: O(1) porque at() es constante en promedio
    int cuantos_con_puntos(int puntos) const {
        if (puntos < 0 || puntos > 15) {
            throw std::domain_error("Puntos no validos");
        }
        else {
            std::unordered_map<Puntos, int>::const_iterator it = conductoresPorPuntos.find(puntos);

            if (it == conductoresPorPuntos.end()) {
                return 0;
            }
            else {
                return (*it).second;
            }
        }
    }
};

bool resuelveCaso() {
    std::string orden, dni;
    int punt;
    std::cin >> orden;
    if (!std::cin)
        return false;

    carnet_puntos dgt;

    while (orden != "FIN") {
        try {
            if (orden == "nuevo") {
                cin >> dni;
                dgt.nuevo(dni);
            }
            else if (orden == "quitar") {
                cin >> dni >> punt;
                dgt.quitar(dni, punt);
            }
            else if (orden == "consultar") {
                cin >> dni;
                punt = dgt.consultar(dni);
                cout << "Puntos de " << dni << ": " << punt << '\n';
            }
            else if (orden == "cuantos_con_puntos") {
                cin >> punt;
                int cuantos = dgt.cuantos_con_puntos(punt);
                cout << "Con " << punt << " puntos hay " << cuantos << '\n';
            }
            else
                cout << "OPERACION DESCONOCIDA\n";
        }
        catch (std::domain_error e) {
            std::cout << "ERROR: " << e.what() << '\n';
        }
        std::cin >> orden;
    }
    std::cout << "---\n";
    return true;
}


int main() {
    // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // restablecimiento de cin
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    //system("pause");
#endif
    return 0;
}
