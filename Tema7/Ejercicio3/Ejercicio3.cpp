// Javier Zazo Morillo
// EDA-GDV72

#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

#include <map>
#include <set>

struct valueLess {
    bool operator()(const ) {

    }
};

// Complejidad: O()
void resolver(string const& primerDeporte, std::map<string, int>& demandaDeportes) { // Quedaría mejor juntar los dos maps y hacer un map<string, map<string, int>>??
    std::map<string, string> alumnos; // Alumno - Deporte

    string deporte, alumno;
    deporte = primerDeporte;
    while (deporte != "_FIN_") {
        demandaDeportes[deporte] = 0;
        cin >> alumno;
        while (!isupper(alumno[0]) && alumno != "_FIN_") {
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
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    string primerDeporte;
    cin >> primerDeporte;
    if (!cin) return false;

    std::map<string, int> sol; // Deporte - nAlumnos
    resolver(primerDeporte, sol);
    
    
    // Salida
    for (auto [deporte, nAlumnos] : sol) {
        std::cout << deporte << " " << nAlumnos << "\n";
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