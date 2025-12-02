// Javier Zazo Morillo
// EDA-GDV72

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

#include <unordered_map>
#include <list>

using DNI = string;
using Puntos = int;
using PosEnLista = std::list<DNI>::iterator;

struct InfoDNI {
    Puntos puntos;
    PosEnLista posEnLista;
};

class carnet_puntos {
private:
    std::unordered_map<DNI, InfoDNI> conductores;
    std::list<DNI> conductoresPorPuntos[16];
public:
    carnet_puntos() {}

    // Complejidad: O(1) porque insert() es constante en promedio
    void nuevo(DNI const& conductor) {
        InfoDNI info = { 15, conductoresPorPuntos->end() }; // O(1)
        auto insertInfo = conductores.insert({ conductor, info }); // O(1)
        if (!insertInfo.second) {
            throw std::domain_error("Conductor duplicado");
        }
        else {
            conductoresPorPuntos[15].push_front(conductor); // O(1)
            (*insertInfo.first).second.posEnLista = conductoresPorPuntos[15].begin(); // O(1)
        }
    }

    // Complejidad: O(1) O(1) porque find() y erase() son constantes (find en promedio)
    void quitar(DNI const& conductor, int puntos) { // ERASE MAL
        std::unordered_map<DNI, InfoDNI>::iterator it = conductores.find(conductor); // O(1)

        if (it == conductores.end()) { // O(1)
            throw std::domain_error("Conductor inexistente");
        }
        else {
            conductoresPorPuntos[(*it).second.puntos].erase((*it).second.posEnLista); // O(1) :)

            (*it).second.puntos -= puntos;
            if ((*it).second.puntos < 0) (*it).second.puntos = 0;

            conductoresPorPuntos[(*it).second.puntos].push_front(conductor); // O(1)
            (*it).second.posEnLista = conductoresPorPuntos[(*it).second.puntos].begin(); // O(1)
        }
    }

    // Complejidad: O(1) porque find() y erase() son constantes (find en promedio)
    void recuperar(DNI const& conductor, int puntos) {
        std::unordered_map<DNI, InfoDNI>::iterator it = conductores.find(conductor); // O(1)

        if (it == conductores.end()) { // O(1)
            throw std::domain_error("Conductor inexistente");
        }
        else {
            conductoresPorPuntos[(*it).second.puntos].erase((*it).second.posEnLista); // O(1) :)

            (*it).second.puntos += puntos;
            if ((*it).second.puntos > 15) (*it).second.puntos = 15;

            conductoresPorPuntos[(*it).second.puntos].push_front(conductor); // O(1)
            (*it).second.posEnLista = conductoresPorPuntos[(*it).second.puntos].begin(); // O(1)
        }
    }

    // Complejidad: O(1) porque find() es constante en promedio
    int consultar(DNI const& conductor) const {
        std::unordered_map<DNI, InfoDNI>::const_iterator it = conductores.find(conductor); // O(1)

        if (it == conductores.end()) { // O(1)
            throw std::domain_error("Conductor inexistente");
        }
        else {
            return (*it).second.puntos;
        }
    }

    // Complejidad: O(1) porque el operador [] en una array es constante
    int cuantos_con_puntos(int puntos) const {
        if (puntos < 0 || puntos > 15) {
            throw std::domain_error("Puntos no validos");
        }
        else {
            return conductoresPorPuntos[puntos].size();
        }
    }
    // Complejidad: O(1) porque el operador [] en una array es constante
    std::list<DNI> lista_por_puntos(int puntos) const {
        if (puntos < 0 || puntos > 15) {
            throw std::domain_error("Puntos no validos");
        }
        else {
            return conductoresPorPuntos[puntos];
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
            else if (orden == "recuperar") {
                cin >> dni >> punt;
                dgt.recuperar(dni, punt);
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
            else if (orden == "lista_por_puntos") {
                cin >> punt;
                auto const& lista = dgt.lista_por_puntos(punt);
                cout << "Tienen " << punt << " puntos:";
                for (auto const& dni : lista)
                    cout << ' ' << dni;
                cout << '\n';
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
