// Javier Zazo Morillo
// EDA-GDV72

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include <unordered_map>
#include <vector>
#include <algorithm>

using Equipo = string;
using Problema = string;

using InfoProblema = std::unordered_map<Problema, std::pair<bool, int>>; // Completado, Tiempo

struct InfoEquipo {
	int nResueltos;
    int tiempo;
	InfoProblema problemas;
};

// Complejidad: O(S + E + E*log(E))), siendo S el número de envíos (submissions) y E el número de equipos 
// porque se hacen S iteraciones para procesar los envíos, E iteraciones para copiar los equipos al vector 
// y el sort() que ordena los equipos tiene complejidad E*log(E).
void procesaEnvios(std::unordered_map<Equipo, InfoEquipo>& equipos, std::vector<Equipo>& equiposOrdenados) {
    string equipo, problema, veredicto;
    int minuto;

    cin >> equipo;
    // O(S) siendo S el número de envíos (submissions), porque las operaciones del unordered map son constantes en promedio
    while (equipo != "FIN") {
        cin >> problema >> minuto >> veredicto;
		auto& infoEquipo = equipos[equipo];
        if (infoEquipo.problemas[problema].first == false) { // Si el problema está resuelto no se hace nada
			if (veredicto == "AC") { // Si se resuelve correctamente se suma el tiempo al posible tiempo añadido por fallos y se marca como resuelto
				infoEquipo.problemas[problema].first = true;
                infoEquipo.nResueltos += 1;
				infoEquipo.tiempo += minuto + infoEquipo.problemas[problema].second * 20;
            }
			else { // Si no se resuelve correctamente se penaliza con un fallo
                infoEquipo.problemas[problema].second += 1;
            }
        }
        cin >> equipo;
    }
    
	// O(E) siendo E el número de equipos
    for (const auto& [equipo, info] : equipos) {
		equiposOrdenados.push_back(equipo);
    }

    // O(E*log(E)) siendo E el número de equipos
    std::sort(equiposOrdenados.begin(), equiposOrdenados.end(), [&](const Equipo& a, const Equipo& b) {
        InfoEquipo infoA = equipos[a];
        InfoEquipo infoB = equipos[b];
        
		if (infoA.nResueltos != infoB.nResueltos) return infoA.nResueltos > infoB.nResueltos; // Mayor número de problemas resueltos
        if (infoA.tiempo != infoB.tiempo) return infoA.tiempo < infoB.tiempo; // Menor tiempo
        return a < b; // Orden alfabético por el nombre del equipo
    });
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    std::unordered_map<Equipo, InfoEquipo> equipos;
    std::vector<Equipo> equiposOrdenados;
    procesaEnvios(equipos, equiposOrdenados);

    // Se imprime la salida
    for (Equipo nombreEquipo : equiposOrdenados) {
        const auto& info = equipos[nombreEquipo];
        std::cout << nombreEquipo << " " << info.nResueltos << " " << info.tiempo << "\n";
    }
    cout << "---\n";
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}