/*
Nombre completo : Javier Zazo Morillo
Usuario del juez : EDA-GDV72

Tupla solución : [A0, A1,... An-1] donde Ai es el área atendida por el voluntario i

Marcadores:
- indicesZonasLimpias: vector de bools de tamaño del número de zonas que almacena si una zona está completamente limpia para no mandar voluntarios a zonas sin lodo
- zonasLimpias: entero que almacena el número de zonas completamente limpias (para el requisito de l)
- lodoMax: entero que almacena la mayor cantidad de lodo retirado en una combinación
- lodoRetirado: entero que almacena el lodoRetirado hasta el momento

Ejemplo de aplicación de poda por estimación :
    Cada voluntario tiene diferentes cantidades de lodo que puede retirar según la zona, entonces para hacer una estimación optimista 
    podemos coger la mayor cantidad de lodo a retirar posible sin tener en cuenta el lodo de las zonas y calcular lo que se retiraría a partir de i zona
    para así comprobar si el lodo retirado hasta el momento más lo que se podría llegar a retirar a partir de la siguiente zona (de manera optimista) 
    es mayor a la máxima cantidad de lodo retirado en anteriores combinaciones

    ej: 
        n = 4, m = 3, l = 0
        lodo zonas = 10, 7, 6
        voluntarios =   2, 3, 1
                        4, 3, 1
                        2, 1, 1
                        4, 4, 4

        maximoLodoDesde = [14, 11, 7, 4]

        Primera solución = [0, 0, 0, 0] = 10 (ignoramos posibles valores más altos posteriores)
        Al elegir la zona 2 para k = 0 y para k = 1, se tendría de lodo retirado 2 + 7 de estimación optimista = 9 por lo que se podaría esta rama
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;

template <class T>
ostream& operator<<(ostream& out, vector<T> const& v) {
    for (auto& e : v) out << e << " ";
    return out;
}

bool esValido(int i, const vector<bool>& indicesZonasLimpias) {
    return !indicesZonasLimpias[i];
}
bool esSolucion(int k, int n) {
    return k == n - 1;
}
// función que resuelve el problema
void resolver(vector<int>& soluc, int k, int n, int m, int l, vector<int>& kilosPorArea, vector<vector<int>> const& kilosPorVoluntario, vector<bool>& indicesZonaslimpias, int& zonasLimpias, int& lodoMax, int& lodoRetirado, const vector<int>& maximoLodoDesde) {
    for (int i = 0; i < m; ++i) {
        soluc[k] = i;
        if (esValido(i, indicesZonaslimpias)) {
            int lodoARetirar = min(kilosPorVoluntario[k][i], kilosPorArea[i]);
            lodoRetirado += lodoARetirar;
            kilosPorArea[i] -= lodoARetirar;
            if (kilosPorArea[i] == 0) {
               ++zonasLimpias;
               indicesZonaslimpias[i] = true;
            }
            
            if (esSolucion(k, n)) {
                if (zonasLimpias >= l && lodoRetirado > lodoMax) lodoMax = lodoRetirado;
            }
            else {
                // Poda por estimación
                int estimacionOptimista = maximoLodoDesde[k + 1];
                if (lodoRetirado + estimacionOptimista > lodoMax) {
                    resolver(soluc, k + 1, n, m, l, kilosPorArea, kilosPorVoluntario, indicesZonaslimpias, zonasLimpias, lodoMax, lodoRetirado, maximoLodoDesde);
                }          
            }

            if (kilosPorArea[i] == 0 && lodoARetirar != 0) 
            {
                --zonasLimpias;
                indicesZonaslimpias[i] = false;
            }
            lodoRetirado -= lodoARetirar;
            kilosPorArea[i] += lodoARetirar;
        }
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, m, l;
    cin >> n >> m >> l;
    vector<int> kilosPorArea(m);
    for (int i = 0; i < m; ++i) {
        cin >> kilosPorArea[i];
    }
    vector<vector<int>> kilosPorVoluntario(n, vector<int>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> kilosPorVoluntario[i][j];

    vector<int> maximoLodoDesde(n);
    for (int i = n-1; i >= 0; --i) {
        int maxLodo = 0;
        for (int j = 0; j < m; ++j) {
            if (kilosPorVoluntario[i][j] > maxLodo) maxLodo = kilosPorVoluntario[i][j];
        }
        maximoLodoDesde[i] = maxLodo;
        if (i < n - 1) maximoLodoDesde[i] += maximoLodoDesde[i + 1];
    }

    vector<int> soluc(n);
    vector<bool> indicesZonasLimpias(m);
    int lodoMax = 0;
    int lodoRetirado = 0;
    int zonasLimpias = 0;
    int k = 0;
    resolver(soluc, k, n, m, l, kilosPorArea, kilosPorVoluntario, indicesZonasLimpias, zonasLimpias, lodoMax, lodoRetirado, maximoLodoDesde);
    if (lodoMax == 0) cout << "IMPOSIBLE" << endl;
    else cout << lodoMax << endl;
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input1.txt");
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
