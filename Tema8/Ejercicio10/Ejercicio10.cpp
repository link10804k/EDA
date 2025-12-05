/*
Nombre completo:
DNI:
Usuario del juez:
Puesto de laboratorio:
Qué has conseguido hacer y qué no:
*/

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <cassert>
#include <utility>

#include <unordered_map>
#include <list>
#include <set>

using namespace std;


using Paciente = string;
using Gravedad = int;
using PosEnLista = std::list<Paciente>::iterator;

struct InfoPaciente {
    Gravedad gravedad;
    PosEnLista posEnLista;
};

class urgencias {
protected:
    std::unordered_map<Paciente, InfoPaciente> pacientes;
    std::list<Paciente> listasGravedad[4]; // 0 recuperado, 1 leve, 2 medio, 3 grave
public:

    // coste: O(1)
    void nuevo_paciente(Paciente p, Gravedad g) {
        if (g < 1 || g > 3)
            throw domain_error("Gravedad incorrecta");

        InfoPaciente info = { g, listasGravedad[0].end()};
        auto infoInsert = pacientes.insert({ p, info }); // O(1)

        if (!infoInsert.second) 
            throw domain_error("Paciente repetido");

        listasGravedad[g].push_back(p); // O(1)
        (*infoInsert.first).second.posEnLista = --listasGravedad[g].end();
    }

    // coste: O(1)
    int gravedad_actual(Paciente p) const {
        auto it = pacientes.find(p); // O(1)

        if (it == pacientes.end())
            throw domain_error("Paciente inexistente");
        
        return (*it).second.gravedad;
    }

    // coste: O(1)
    Paciente siguiente() { // Hay que quitarlo del map???
        int i = 3;
        while (i > 0 && listasGravedad[i].empty()) --i; // O(1) porque siempre son 3 iteraciones

        if (i == 0) throw domain_error("No hay pacientes");
        else {
            Paciente p = listasGravedad[i].front(); // O(1)
            listasGravedad[i].pop_front(); // O(1)

            return p;
        }
    }

    // coste: O(1)
    void mejora(Paciente p) {
        auto it = pacientes.find(p); // O(1)

        if (it == pacientes.end()) {
            throw domain_error("Paciente inexistente");
        }
        else {
            Gravedad* g = &(*it).second.gravedad;
            PosEnLista* p = &(*it).second.posEnLista;

            listasGravedad[*g].erase(*p); // O(1)

            --(*g);
            listasGravedad[*g].push_front((*it).first); // O(1)
            *p = listasGravedad[*g].begin(); // O(1)
        }
    }

    // coste:
    list<Paciente> recuperados() const {
        return listasGravedad[0];
    }


};

bool resuelveCaso() { // No tocar esta función
    string orden, pac;
    int grav;
    cin >> orden;
    if (!cin) return false;

    urgencias sala;

    while (orden != "FIN") {
        try {
            if (orden == "nuevo_paciente") {
                cin >> pac >> grav;
                sala.nuevo_paciente(pac, grav);
            }
            else if (orden == "gravedad_actual") {
                cin >> pac;
                int g = sala.gravedad_actual(pac);
                cout << "La gravedad de " << pac << " es " << g << '\n';
            }
            else if (orden == "siguiente") {
                string p = sala.siguiente();
                cout << "Siguiente paciente: " << p << '\n';
            }
            else if (orden == "recuperados") {
                auto lista = sala.recuperados();
                cout << "Lista de recuperados:";
                for (auto& p : lista)
                    cout << ' ' << p;
                cout << '\n';
            }
            else if (orden == "mejora") {
                cin >> pac;
                sala.mejora(pac);
            }
        }
        catch (std::domain_error e) {
            std::cout << "ERROR: " << e.what() << '\n';
        }
        std::cin >> orden;
    }
    std::cout << "---\n";
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
