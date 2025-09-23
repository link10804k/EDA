// Javier Zazo Morillo
// EDA-GDV72
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

// Complejidad: O(n*log(n)) porque se podrían ordenar los vectores primero (O(n*log(n))) y luego utilizar 
// el mismo algoritmo que para vectores ordenados (O(n)). Entonces quedaría como n + n*log(n) (O(n*log(n))).

// función que resuelve el problema
void comparaListados(vector<string> &eda, vector<string> &tpv,
    vector<string>& comunes, vector<string>& soloEda, vector<string>& soloTpv) {

    std::sort(eda.begin(), eda.end());
    std::sort(tpv.begin(), tpv.end());

    int edaPos = 0;
    int tpvPos = 0;

    while (edaPos < eda.size() && tpvPos < tpv.size()) {
        if (eda[edaPos] == tpv[tpvPos]) {
            comunes.push_back(eda[edaPos]);
            edaPos++;
            tpvPos++;
        }
        else if (eda[edaPos] < tpv[tpvPos]) {
            soloEda.push_back(eda[edaPos]);
            edaPos++;
        }
        else {
            soloTpv.push_back(tpv[tpvPos]);
            tpvPos++;
        }
    }

    if (edaPos < eda.size()) {
        for (int j = edaPos; j < eda.size(); ++j) {
            soloEda.push_back(eda[j]);
        }
    }
    else if (tpvPos < tpv.size()) {
        for (int j = tpvPos; j < tpv.size(); ++j) {
            soloTpv.push_back(tpv[j]);
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    vector<string> eda(n);
    vector<string> comunes;
    vector<string> soloEda;
    vector<string> soloTpv;
    for (string& e : eda) cin >> e;
    cin >> n;
    vector<string> tpv(n);
    for (string& e : tpv) cin >> e;
    comparaListados(eda, tpv, comunes, soloEda, soloTpv);
    for (string& e : comunes) cout << e << " ";
    cout << endl;
    for (string& e : soloEda) cout << e << " ";
    cout << endl;
    for (string& e : soloTpv) cout << e << " ";
    cout << endl;
}


//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
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