// Nombre: Javier Zazo Morillo
// Usuario juez: EDA-GDV72

// Tupla solución: [A1, A2,... A2n-2] donde Ai siendo i par y Aj siendo j = i+1 son los alumnos encargados de i/2 tarea

/* Ejemplo de poda:
n = 2, m = 3; l = 2

Alumnos:    10 10
            10 10
            1  1

Mejores satisfacciones: [10, 10, 10, 10]
Mejores satisfacciones desde: [40, 30, 20, 10]

Primera solución: [0, 1, 0, 1] = 40
Al elegir el alumno 2 para k = 0, la satisfacción total es de 1 + 30 de estimación optimista = 31 -> Se poda porque ya se ha encontrado un valor más alto antes (40)
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    for (auto e : v) out << e;
    return out;
}

bool esValido(std::vector<int>& soluc, int k, int a, int t, vector<int>& tareasPorAlumno) {
    return tareasPorAlumno[a] < t && (k%2 == 0 || soluc[k-1] != a);
}
bool esSolucion(int k, int n) {
    return k == n - 1;
}

// función que resuelve el problema
void resolver(std::vector<int>& soluc, int k, int n, int m, int t, const vector<vector<int>>& preferencias, vector<int>& tareasPorAlumno, int satisfaccion, int& satisfaccionMaxima, const vector<int>& mejoresSatisfaccionesDesde) {
    for (int a = 0; a < m; ++a) {
        soluc[k] = a;

        if (esValido(soluc, k, a, t, tareasPorAlumno)) {
            ++tareasPorAlumno[a];
            satisfaccion += preferencias[a][k/2];
            if (esSolucion(k, n)) {
                if (satisfaccion > satisfaccionMaxima) satisfaccionMaxima = satisfaccion;
            }
            else {
                // Poda por estimación
                int estimacionOptimista = satisfaccion + mejoresSatisfaccionesDesde[k + 1];
                if (estimacionOptimista > satisfaccionMaxima)
                    resolver(soluc, k + 1, n, m, t, preferencias, tareasPorAlumno, satisfaccion, satisfaccionMaxima, mejoresSatisfaccionesDesde);
            }
            --tareasPorAlumno[a];
            satisfaccion -= preferencias[a][k / 2];
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, a, t;
    cin >> n >> a >> t;
    if (n == 0 && a == 0 && t == 0) return false;
    vector<vector<int>> preferencias(a, vector<int>(n));
    for (int i = 0; i < a; ++i)
        for (int j = 0; j < n; ++j) {
            cin >> preferencias[i][j];
        }

    std::vector<int> mejoresSatisfaccionesDesde(n*2);
    for (int i = n-1; i >= 0; --i) {
        int maxSatisfaccion = 0;
        for (int j = 0; j < a; ++j) {
            if (preferencias[j][i] > maxSatisfaccion) maxSatisfaccion = preferencias[j][i];
        }
        mejoresSatisfaccionesDesde[i * 2] = maxSatisfaccion;
        mejoresSatisfaccionesDesde[i * 2 + 1] = maxSatisfaccion;

        if (i < n - 1) {
            mejoresSatisfaccionesDesde[i * 2 + 1] += mejoresSatisfaccionesDesde[(i+1) * 2];        
        }
        mejoresSatisfaccionesDesde[i * 2] += mejoresSatisfaccionesDesde[i * 2 + 1];
    }

    std::vector<int> soluc(n*2);
    vector<int> tareasPorAlumno(a);
    int satisfaccionMaxima = 0;

    resolver(soluc, 0, n*2, a, t, preferencias, tareasPorAlumno, 0, satisfaccionMaxima, mejoresSatisfaccionesDesde);

    // Imprimir solucion
    std::cout << satisfaccionMaxima << "\n";

    return true;
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input1.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso())
        ;

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}