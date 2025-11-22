// Javier Zazo Morillo
// EDA-GDV72

#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

#include <unordered_map>
#include <vector>
#include <algorithm>

using Deporte = string;
using Alumno = string;

// Complejidad: O(D*I + D + D*log(D)) siendo D el número de deportes e I el número máximo de inscripciones a un deporte
// porque se hacen D*I iteraciones para rellenar el diccionario, D iteraciones para volcarlo sobre un vector y D*log(D) iteraciones para ordenarlo.
void resolver(string const& primerDeporte, std::unordered_map<Deporte, int>& demandaDeportes, std::vector<Deporte>& deportesOrdenados) {
    std::unordered_map<Alumno, Deporte> alumnos;

    string deporte, alumno;
    deporte = primerDeporte;
    while (deporte != "_FIN_") { // O(D*I) siendo D el número de deportes e I el número máximo de inscripciones a un deporte
        demandaDeportes[deporte] = 0;
        cin >> alumno;
        while (!isupper(alumno[0]) && alumno != "_FIN_") { // O(I) siendo I el número máximo de inscripciones a un deporte
            if (!alumnos.count(alumno)) { // Si no ha salido antes el alumno lo inserta y añade 1 al contador del deporte
                alumnos[alumno] = deporte;
                ++demandaDeportes[deporte];
            }
            else if (alumnos[alumno] != deporte && alumnos[alumno] != "ya restado") { // Si el alumno ha salido antes y ha salido en otro deporte, no se inserta en este y no se tiene en cuenta ni para este ni para el otro deporte
                --demandaDeportes[alumnos[alumno]];
                alumnos[alumno] = "ya restado"; // Señal para no volver a restar
            }
            // Si el alumno ya estaba inscrito en este deporte, no se hace nada
            
            cin >> alumno;
        }
        deporte = alumno;
    }

    for (auto [nombreDeporte, nInscripciones] : demandaDeportes) { // O(D) siendo D el número de deportes
        deportesOrdenados.push_back(nombreDeporte);
    }

    std::sort(deportesOrdenados.begin(), deportesOrdenados.end(), [&](const Deporte& deporte1, const Deporte& deporte2) { // O(D*log(D)) siendo D el número de deportes
        int nInscripciones1 = demandaDeportes[deporte1];
        int nInscripciones2 = demandaDeportes[deporte2];

        if (nInscripciones1 != nInscripciones2) return nInscripciones1 > nInscripciones2;
        return deporte1 < deporte2;
    });
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    string primerDeporte;
    cin >> primerDeporte;
    if (!cin) return false;

    std::unordered_map<Deporte, int> demandaDeportes;
    std::vector<Deporte> deportesOrdenados;
    resolver(primerDeporte, demandaDeportes, deportesOrdenados);
    
    
    // Salida
    for (Deporte deporte : deportesOrdenados) {
        std::cout << deporte << " " << demandaDeportes[deporte] << "\n";
    }
    cout << "---\n";
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
#endif

    return 0;
}