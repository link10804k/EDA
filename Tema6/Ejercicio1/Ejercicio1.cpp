// Javier Zazo Morillo
// EDA-GDV72

#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

template <typename T>
int nodos(bintree<T> const& tree) {
	
}
template <typename T>
int hojas(bintree<T> const& tree) {

}
template <typename T>
int altura(bintree<T> const& tree) {

}

template <class T>
class bintree : public bintree<T> {
    using Link = std::shared_ptr<TreeNode>;

public:
    int nodes(bintree<T> const& tree) {
        return tree.nodos(tree.root());
    }
    int leaves(bintree<T> const& tree) {
        return tree.hojas(tree.root());
    }
    int height(bintree<T> const& tree) {
        return tree.altura(tree.root());
    }
private:
    int nodos(const Link& raiz) {

    }
    int hojas(const Link& raiz) {

    }
    int altura(const Link& raiz) {

    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<char> tree;
    tree = leerArbol('.');


    //std::cout << nodos(tree) << " " << hojas(tree) << " " << altura(tree) << endl;
}


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
