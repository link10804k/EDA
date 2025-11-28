// Javier Zazo Morillo
// EDA-GDV72


#include <iostream>
#include <iomanip>
#include <fstream>

#include <unordered_map>
#include <list>

using LibroKey = char;

struct LibroValue {
    int nPags;
    int pagActual;
    std::list<LibroKey>::iterator posHistorial;
};

using Libros = std::unordered_map<LibroKey, LibroValue>;

using HistorialAbiertos = std::list<LibroKey>;

class eReader {
private:
    Libros libros;
    HistorialAbiertos historialAbiertos;
public:
    eReader() {

    }
    ~eReader() {

    }
    void poner_libro(LibroKey x, int n) {
        LibroValue infoLibro = { n, 1, historialAbiertos.end() };
        libros.insert({ x, infoLibro });
    }
    void abrir(LibroKey x) {
        auto it = libros.find(x);

        if (it == libros.end()) {
            throw "Libro no encontrado";
        }
        else {
            //historialAbiertos.push_front(x);
            //libros[x].posHistorial = historialAbiertos.begin();

            libros[x].posHistorial = historialAbiertos.insert(historialAbiertos.begin(), x); // Funciona igual que las otras dos líneas (Pero así se puede hacer en una línea)
        }
    }
    void avanazar_pag() {
        if (historialAbiertos.empty()) {
            throw "Ningun libro abierto";
        }
        else {
            LibroValue& libro = libros[historialAbiertos.front()];

            libro.pagActual = (libro.pagActual % libro.nPags) + 1;
        }
    }
    LibroKey abierto() {
        if (historialAbiertos.empty()) {
            throw "Ningun libro abierto";
        }
        else {
            return historialAbiertos.front();
        }
    }
    int pag_libro(LibroKey x) {
        auto it = libros.find(x);

        if (it == libros.end()) {
            throw "Libro no encontrado";
        }
        else {
            return (*it).second.pagActual;
        }
    }
    void elim_libro(LibroKey x) {
        auto it = libros.find(x);

        if (it != libros.end()) {
            auto itHistorial = (*it).second.posHistorial;
            if (itHistorial != historialAbiertos.end()) {
                historialAbiertos.erase(itHistorial);
            }
            libros.erase(it);
        }
    }
    std::list<LibroKey> recientes(int n) {
        std::list<LibroKey> l;
        int i = 0;
        for (auto it = historialAbiertos.begin(); it != historialAbiertos.end() && i < n; ++it, ++i) {
            l.push_front((*it));
        }
        return l;
    }
};

// Instrucciones eReader
bool resuelveCaso() { 
    LibroKey libro;
    int pagActual, nPags, n;
    eReader reader;

    // leer los datos de la entrada
    std::string s;
    std::cin >> s;

    if (!std::cin) return false;
    
    while (s != "FIN") {
        try {
            if (s == "poner_libro") {
                std::cin >> libro >> nPags;

                reader.poner_libro(libro, nPags);
            }
            else if (s == "abierto") {
                std::cout << reader.abierto() << "\n";
            }
            else if (s == "abrir") {
                std::cin >> libro;

                reader.abrir(libro);
            }
            else if (s == "pag_libro") {
                std::cin >> libro;

                int pagActual = reader.pag_libro(libro);
                std::cout << "Libro " << libro << " por pagina " << pagActual << "\n";
            }
            else if (s == "recientes") {
                std::cin >> n;

                std::list<LibroKey> l = reader.recientes(n);
                std::cout << "Ultimos libros abiertos:";
                for (LibroKey libro : l) {
                    std::cout << " " << libro;
                }
                std::cout << "\n";
            }
            else if (s == "elim_libro") {
                std::cin >> libro;

                reader.elim_libro(libro);
            }
            else if (s == "avanzar_pag") {
                reader.avanazar_pag();
            }
            else {
                std::cout << "OPERACION DESCONOCIDA\n";
            }
        }
        catch (const char* error) {
            std::cout << "ERROR: " << error << "\n";
        }
        std::cin >> s;
    }
    std::cout << "---\n";
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
    system("PAUSE");
#endif

    return 0;
}
