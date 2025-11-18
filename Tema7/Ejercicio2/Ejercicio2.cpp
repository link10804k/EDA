// Javier Zazo Morillo
// EDA-GDV72

#include <iostream>
#include <fstream>
#include <string>

#include <map>
#include <vector>

using namespace std;

using Diccionario = map<string, int>;

// Complejidad: O(diccionarioAntiguo.size() + diccionarioNuevo.size()) porque se tienen que recorrer todos los campos de los dos diccionarios y, en el peor caso, cada iteración solo se recorre el campo de un diccionario.
void comparaDiccionarios(const Diccionario& diccionarioAntiguo, const Diccionario& diccionarioNuevo, vector<string>& clavesAnadidas, vector<string>& clavesEliminadas, vector<string>& clavesModificadas) {
    string valAntiguo, valNuevo;

	Diccionario::const_iterator itAntiguo = diccionarioAntiguo.begin();
	Diccionario::const_iterator itNuevo = diccionarioNuevo.begin();

    while (itAntiguo != diccionarioAntiguo.end() && itNuevo != diccionarioNuevo.end()) {
        if (itAntiguo->first == itNuevo->first) {
            if (itAntiguo->second != itNuevo->second) {
				clavesModificadas.push_back(itAntiguo->first);
            }
			++itAntiguo;
            ++itNuevo;
        }
        else if (itAntiguo->first < itNuevo->first) {
            clavesEliminadas.push_back(itAntiguo->first);
            ++itAntiguo;
        }
        else {
            clavesAnadidas.push_back(itNuevo->first);
            ++itNuevo;
        }
    }

    if (itAntiguo != diccionarioAntiguo.end()) {
        for (; itAntiguo != diccionarioAntiguo.end(); ++itAntiguo) {
            clavesEliminadas.push_back(itAntiguo->first);
        }
    }
    else if (itNuevo != diccionarioNuevo.end()) {
        for (; itNuevo != diccionarioNuevo.end(); ++itNuevo) {
            clavesAnadidas.push_back(itNuevo->first);
        }
    }
}

void leerDiccionario(Diccionario& diccionario) {
    char c;
    string clave;
    int valor;
    cin.get(c);
    while (c != '\n') {
        cin.unget();
        cin >> clave >> valor;
		diccionario[clave] = valor;
        cin.get(c);
    }
}

void resuelveCaso() {
    Diccionario antiguo;
    Diccionario nuevo;
    leerDiccionario(antiguo);
    leerDiccionario(nuevo);
    
    vector<string> clavesAnadidas;
	vector<string> clavesEliminadas;
	vector<string> clavesModificadas;

    comparaDiccionarios(antiguo, nuevo, clavesAnadidas, clavesEliminadas, clavesModificadas);

    if (clavesAnadidas.empty() && clavesEliminadas.empty() && clavesModificadas.empty()) {
        std::cout << "Sin cambios";
        std::cout << "\n";
    }
    else {
        if (!clavesAnadidas.empty()) {
            std::cout << "+";
            for (string c : clavesAnadidas) {
                std::cout << " " << c;
            }
            std::cout << "\n";
        }
        if (!clavesEliminadas.empty()) {
            std::cout << "-";
            for (string c : clavesEliminadas) {
                std::cout << " " << c;
            }
            std::cout << "\n";
        }
        if (!clavesModificadas.empty()) {
            std::cout << "*";
            for (string c : clavesModificadas) {
                std::cout << " " << c;
            }
            std::cout << "\n";
        }
    }
	std::cout << "---\n";
}


int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    int numCasos; char c;
    std::cin >> numCasos;
    cin.get(c);
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}