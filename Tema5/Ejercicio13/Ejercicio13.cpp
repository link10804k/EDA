// Javier Zazo Morillo
// EDA-GDV72

#include <iostream>
#include <iomanip>
#include <fstream>
#include "list_eda.h"
using namespace std;


template <class T>
class list_plus : public list<T> {
    using Nodo = typename list<T>::Nodo;

public:
	// Complejidad: O(n) siendo n el tamaño de la lista porque, como mucho, se recorre linealmente toda la lista.
    void adelantar(int pos, int length, int newPos) {
        if (length == 0 || newPos < 0 || pos <= 0 || pos <= newPos || pos >= this->size()) {
            return;
        }

        int nodoIzqIndex = newPos - 1; // El nodo que se va a quedar a la izquierda del segmento
        int nodoDerIndex = newPos; // El nodo que se va a quedar a la derecha del segmento   
        int anteriorNodoIzqIndex = pos - 1; // El nodo que estaba a la izquierda del segmento
        int anteriorNodoDerIndex = pos + length; // El nodo que estaba a la derecha del segmento
        int priNodoSegIndex = pos; // El primer nodo del segmento
        int ultNodoSegIndex = pos + length - 1; // El último nodo del segmento

        Nodo* nodoIzq = nullptr;
        Nodo* nodoDer = nullptr;
        Nodo* anteriorNodoIzq = nullptr;
        Nodo* anteriorNodoDer = nullptr;
        Nodo* priNodoSeg = nullptr;
        Nodo* ultNodoSeg = nullptr;

        Nodo* act = this->fantasma->sig;
        int i = 0;

        while (act != this->fantasma && (nodoIzq == nullptr || nodoDer == nullptr || anteriorNodoIzq == nullptr || anteriorNodoDer == nullptr || priNodoSeg == nullptr || ultNodoSeg == nullptr)) {
            if (i == nodoIzqIndex) {
                nodoIzq = act;
            }
            if (i == nodoDerIndex) {
                nodoDer = act;
            }
            if (i == anteriorNodoIzqIndex) {
                anteriorNodoIzq = act;
            }
            if (i == anteriorNodoDerIndex) {
                anteriorNodoDer = act;
            }
            if (i == priNodoSegIndex) {
                priNodoSeg = act;
            }
            if (i == ultNodoSegIndex) {
                ultNodoSeg = act;
            }
            act = act->sig;
            ++i;
        }
        if (ultNodoSeg == nullptr || ultNodoSeg == this->fantasma) {
			ultNodoSeg = this->fantasma->ant;
        }
        if (anteriorNodoDer == nullptr) {
            anteriorNodoDer = this->fantasma;
        }
        if (nodoIzq == nullptr) {
            nodoIzq = this->fantasma;
        }

        nodoIzq->sig = priNodoSeg;
        priNodoSeg->ant = nodoIzq;
        ultNodoSeg->sig = nodoDer;
        nodoDer->ant = ultNodoSeg;
        anteriorNodoIzq->sig = anteriorNodoDer;
        anteriorNodoDer->ant = anteriorNodoIzq;
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    char e;
    int n, pos, length, dif;
    list_plus<char> l;

    // leer los datos de la entrada
    cin >> n >> pos >> length >> dif;
    for (int i = 1; i <= n; ++i) {
        cin >> e;
        l.push_back(e);
    }

    l.adelantar(pos, length, pos-dif);

    // Le damos una vuelta para comprobar que la lista está bien formada
    for (int i = 0; i < l.size(); ++i) {
        e = l.back();
        l.pop_back();
        l.push_front(e);
    }

    // Ahora imprimimos la lista y de paso la dejamos vacía (tb para probar su consistencia)
    while (!l.empty()) {
        cout << l.front() << " ";
        l.pop_front();
    }
    cout << endl;
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
