// Javier Zazo Morillo
// EDA-GDV72

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

bool esValida(const std::vector<int>& soluc, const int& k, const int& a, const std::vector<std::vector<bool>>& consentimientos, const std::vector<bool>& usados) {
    if (k == 0) return true; 
    else return !usados[a] && consentimientos[a][soluc[k - 1]];
}
bool esSolucion(const int& k, const int& n) {
    return k == n - 1;
}
// Tupla solución: [A0, A1,... An-1] siendo n el número de artistas, Ai+1 dando consentimiento para ir detrás de Ai
// Complejidad: O(n^n) siendo n el número de artistas
void resolver(std::vector<int>& soluc, int k, int& n, int& m, const std::vector<std::vector<int>>& beneficios, const std::vector<std::vector<bool>>& consentimientos, std::vector<bool>& usados, 
    int& mejorSolucion, int& beneficioActual, const std::vector<int>& mejoresSolucionesAPartirDe) {
    for (int a = 0; a < m; ++a) {
        soluc[k] = a;
        if (esValida(soluc, k, a, consentimientos, usados)) {
            beneficioActual += beneficios[a][k];
            if (esSolucion(k, n)) {
                if (beneficioActual > mejorSolucion) mejorSolucion = beneficioActual;
            }
            else {
                // Poda por estimación optimista
                int estimacionOptimista = mejoresSolucionesAPartirDe[k] + beneficioActual;
                if (estimacionOptimista > mejorSolucion) {
                    usados[a] = true;
                    resolver(soluc, k + 1, n, m, beneficios, consentimientos, usados, mejorSolucion, beneficioActual, mejoresSolucionesAPartirDe);
                    usados[a] = false;
                }                 
            }
            beneficioActual -= beneficios[a][k];
        }
    }
}

/* Ejemplo de poda: ponemos el último artista al principio
2
3
160 10 20
10 20 30
140 20 10
0 0 0
0 1 1
0 0 1

La primera solución encontrada sería [0, 2, 1] -> 210

mejoresDonaciones = [160, 20, 30]
mejoresDonacionesAPartirDe = [50, 30]

Al elegir el artista 1 en k=0, tendríamos de beneficio 10 + 50 de estimación = 60 -> Entonces se puede podar
*/

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    vector<vector<int>> beneficios(n, vector<int>(n));
    vector<vector<bool>> consentimientos(n, vector<bool>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> beneficios[i][j];

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            int b;
            cin >> b;
            consentimientos[i][j] = b;
        }

    // Datos backtracking
    std::vector<int> soluc(n);
    std::vector<bool> usados(n);
    int mejorSolucion = 0;
    int beneficioActual = 0;

    std::vector<int> mejoresDonaciones(n); // Para la poda
    for (int i = 0; i < n; ++i) {
        int max = 0;
        for (int j = 0; j < n; ++j) {
            if (beneficios[j][i] > max) {
                max = beneficios[j][i];
            }
        }
        mejoresDonaciones[i] = max;
    }

    std::vector<int> mejoresDonacionesAPartirDe(n-1); // Para la poda
    for (int i = 0; i < n-1; ++i) {
        for (int j = i+1; j < n; ++j) {
            mejoresDonacionesAPartirDe[i] += mejoresDonaciones[j];
        }
    }

    resolver(soluc, 0, n, n, beneficios, consentimientos, usados, mejorSolucion, beneficioActual, mejoresDonacionesAPartirDe);

    // salida
    std::cout << (mejorSolucion == 0 ? "NEGOCIA CON LOS ARTISTAS" : std::to_string(mejorSolucion)) << "\n";
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input3.txt");
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