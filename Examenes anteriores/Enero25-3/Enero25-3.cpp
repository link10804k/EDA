/*
Nombre completo: Javier Zazo Morillo
Usuario del juez: EDA-GDV72
*/

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <list>
#include <utility>
#include <unordered_map>
#include <unordered_set>

using namespace std;

using Jugador = string;
using Equipo = string;

using Anchor = std::list<Jugador>::iterator;

struct InfoJugador {
    Equipo equipo;
    unordered_set<Equipo> equipos;
};
struct InfoEquipo {
    std::list<Jugador> fichajes;
    std::unordered_map<Jugador, Anchor> posFichajes;
};

class GestorFutbolistas {
private:
    std::unordered_map<Jugador, InfoJugador> jugadores;
    std::unordered_map<Equipo, InfoEquipo> equipos;
public:
    // Coste: O(1) porque todas las operaciones son constantes en promedio
    void fichar(const Jugador& jugador, const Equipo& equipo) {

        InfoEquipo* infoEquipo = &equipos[equipo]; // O(1)
        InfoJugador* info = &jugadores[jugador]; // O(1)

        if (info->equipo != equipo) {
            if (info->equipos.size() > 0) {
                InfoEquipo* infoEquipoAntiguo = &equipos[info->equipo];

                auto it = infoEquipoAntiguo->posFichajes.find(jugador);

                Anchor a = (*it).second;
                infoEquipoAntiguo->fichajes.erase(a); // O(1)

                infoEquipoAntiguo->posFichajes.erase(it); // O(1)
            }

            infoEquipo->fichajes.push_front(jugador); // O(1)
            infoEquipo->posFichajes[jugador] = infoEquipo->fichajes.begin(); // O(1)

            info->equipo = equipo;
            info->equipos.insert(equipo); // O(1)
        }       
    }

    // Coste: O(1) porque todas las operaciones son constantes en promedio
    Equipo equipoActual(const Jugador& jugador) const {
        auto it = jugadores.find(jugador); // O(1)

        if (it == jugadores.end()) throw domain_error("Jugador inexistente");
        
        return (*it).second.equipo;
    }

    // Coste: O(1) porque todas las operaciones son constantes en promedio
    int fichados(const Equipo& equipo) const {
        auto it = equipos.find(equipo); // O(1)

        if (it == equipos.end()) throw domain_error("Equipo inexistente");
        
        return (*it).second.fichajes.size();
    }

    // Coste: O(min(n, f)) siendo n el número de fichajes que se piden y f el número de fichajes del equipo
    // porque se copia ese número de elementos de una lista a otra (y el resto de operaciones son constantes en promedio)
    list<Jugador> ultimosFichajes(const Equipo& equipo, int n) const {
        auto it = equipos.find(equipo); // O(1)

        if (it == equipos.end()) throw domain_error("Equipo inexistente");

        std::list<Jugador> listaDevolucion;
        
        const std::list<Jugador>* listaEquipo = &(*it).second.fichajes;
        auto itEquipo = listaEquipo->begin();
        int i = 0;
        
        while (itEquipo != listaEquipo->end() && i < n) { // O(min(n, f))
            listaDevolucion.push_back(*itEquipo); // O(1)

            ++itEquipo;
            ++i;
        }

        return listaDevolucion;
    }

    // Coste: O(1) porque todas las operaciones son constantes en promedio
    int cuantosEquipos(const Jugador& jugador) const {
        auto it = jugadores.find(jugador); // O(1)

        if (it == jugadores.end()) return 0;
        else return (*it).second.equipos.size();
    }
};


bool resuelveCaso() {
    string operacion;
    cin >> operacion;
    if (!cin) return false;

    GestorFutbolistas gestor;
    while (operacion != "FIN") {
        try {
            if (operacion == "fichar") {
                string jugador, equipo;
                cin >> jugador >> equipo;
                gestor.fichar(jugador, equipo);
            }
            else if (operacion == "equipo_actual") {
                string jugador;
                cin >> jugador;
                string equipo = gestor.equipoActual(jugador);
                cout << "El equipo de " << jugador << " es " << equipo << endl;
            }
            else if (operacion == "fichados") {
                string equipo;
                cin >> equipo;
                int n = gestor.fichados(equipo);
                cout << "Jugadores fichados por " << equipo << ": " << n << endl;
            }
            else if (operacion == "ultimos_fichajes") {
                string equipo;
                int n;
                cin >> equipo >> n;
                list<string> ultimos = gestor.ultimosFichajes(equipo, n);
                cout << "Ultimos fichajes de " << equipo << ": ";
                for (const auto& jugador : ultimos) {
                    cout << jugador << " ";
                }
                cout << endl;
            }
            else if (operacion == "cuantos_equipos") {
                string jugador;
                cin >> jugador;
                int n = gestor.cuantosEquipos(jugador);
                cout << "Equipos que han fichado a " << jugador << ": " << n << endl;
            }
        }
        catch (std::exception& e) {
            cout << "ERROR: " << e.what() << "\n";
        }
        cin >> operacion;
    }

    cout << "---\n";
    return true;
}

//#define DOMJUDGE
int main() {
#ifndef DOMJUDGE
    ifstream in("input3.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso()) {}

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
