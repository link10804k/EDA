/*
Nombre completo: Javier Zazo Morillo
Usuario del juez: EDA-GDV72

Indica y explica el formato de la tupla solución: [S0, S1,... Sn-1] donde Si es un booleano que dice si se va a poner una suma o una resta en el número

¿Cuándo se da el caso peor?

    Cuando no es posible llegar a M.

Indica cuántas llamadas (en función de n) genera el algoritmo en dicho caso.

    Se hacen 2^n llamadas porque cada ciclo se hacen el doble de llamadas que en el anterior

*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

bool esSolucion(int k, int n) {
    return k == n - 1;
}

// función que resuelve el problema y justificación del coste
void resolver(vector<bool>& sol, int k, int n, int M, const vector<int>& v, bool& resuelto, int cuenta, const vector<int>& mayorCombinacionDesde) {
    if (!resuelto) {
        sol[k] = true;
        cuenta += v[k];

        if (esSolucion(k, n)) {
            if (cuenta == M) resuelto = true;
        }
        else {
            // Poda por estimación optimista
            if (abs(cuenta) + mayorCombinacionDesde[k + 1] >= abs(M))
                resolver(sol, k + 1, n, M, v, resuelto, cuenta, mayorCombinacionDesde);
        }

        cuenta -= v[k];      
    }
    if (!resuelto && k >= 1) {
        sol[k] = false;
        cuenta -= v[k];

        if (esSolucion(k, n)) {
            if (cuenta == M) resuelto = true;
        }
        else {
            // Poda por estimación optimista
            if (abs(cuenta) + mayorCombinacionDesde[k + 1] >= abs(M))
                resolver(sol, k + 1, n, M, v, resuelto, cuenta, mayorCombinacionDesde);
        }

        cuenta += v[k];
    }
}

void resuelveCaso() {
    int n = 0, M;
    cin >> M >> n;
    vector<int> v(n);
    for (int& e : v)
        cin >> e;

    vector<bool> sol(n);
    bool resuelto = false;

    vector<int> mayorCombinacionDesde(n);

    for (int i = n - 1; i >= 0; --i) {
        mayorCombinacionDesde[i] = v[i];
        if (i < n-1) mayorCombinacionDesde[i] += mayorCombinacionDesde[i + 1];
    }

    // llamada a función que resuelve el problema
    if (n > 0)
        resolver(sol, 0, n, M, v, resuelto, 0, mayorCombinacionDesde);
    else if (M == 0) resuelto = true;
    // salida de datos
    std::cout << (resuelto ? "SI" : "NO") << "\n";
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input2.txt");
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