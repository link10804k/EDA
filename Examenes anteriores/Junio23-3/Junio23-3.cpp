/*
Nombre completo:
DNI:
Usuario del juez:
Puesto de laboratorio:
Qué has conseguido hacer y qué no:
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <unordered_map>
#include <map>
#include <list>

using namespace std;


class Fecha {
    int _dia, _mes, _anio;

public:
    Fecha(int d = 0, int m = 0, int a = 0) : _dia(d), _mes(m), _anio(a) {}
    int dia() const { return _dia; }
    int mes() const { return _mes; }
    int anio() const { return _anio; }
    bool operator<(Fecha const& other) const {
        return _anio < other._anio ||
            (_anio == other._anio && _mes < other._mes) ||
            (_anio == other._anio && _mes == other._mes && _dia < other._dia);
    }
};

inline std::istream& operator>>(std::istream& entrada, Fecha& h) {
    int d, m, a; char c;
    std::cin >> d >> c >> m >> c >> a;
    h = Fecha(d, m, a);
    return entrada;
}

inline std::ostream& operator<<(std::ostream& salida, Fecha const& f) {
    salida << std::setfill('0') << std::setw(2) << f.dia() << '/';
    salida << std::setfill('0') << std::setw(2) << f.mes() << '/';
    salida << std::setfill('0') << std::setw(2) << f.anio();
    return salida;
}

using Codigo = string;
using Cliente = string;

struct InfoCodigo {
    int cantidadTotal = 0;
    map<Fecha, int> fechasAdquisicion;
    list<Cliente> listaEspera;
};

class Tienda {
private:
    unordered_map<Codigo, InfoCodigo> productos;
public:
    // Complejidad: O(min(s, c)) siendo s el tamaño de la lista de espera y c la cantidad de productos recibida
    vector<Cliente> adquirir(Codigo const& cod, Fecha const& f, int cant) {
        vector<Cliente> clientesServidos;

        InfoCodigo* infoCodigo = &productos[cod];

        if (infoCodigo->listaEspera.size() > 0) {
            while (infoCodigo->listaEspera.size() > 0 && cant > 0) {
                clientesServidos.push_back(infoCodigo->listaEspera.front());
                infoCodigo->listaEspera.pop_front();

                --cant;
            }
        }

        if (cant > 0) {
            infoCodigo->cantidadTotal += cant;
            infoCodigo->fechasAdquisicion[f] += cant;
        }
        
        return clientesServidos;
    }

    // Complejidad: O(1) porque todas las operaciones son de complejidad constante en promedio
    pair<bool, Fecha> vender(Codigo const& cod, Cliente const& cli) {
        bool vendido = false;
        Fecha fechaProducto;

        InfoCodigo* infoCodigo = &productos[cod];

        if (infoCodigo->cantidadTotal > 0) {
            --infoCodigo->cantidadTotal;

            auto it = infoCodigo->fechasAdquisicion.begin();

            vendido = true;
            fechaProducto = (*it).first;

            --(*it).second;
            if ((*it).second == 0) infoCodigo->fechasAdquisicion.erase(it);
        }
        else {
            infoCodigo->listaEspera.push_back(cli);
        }

        return { vendido, fechaProducto };
    }

    // Complejidad: O(1) porque todas las operaciones son de complejidad constante en promedio
    int cuantos(Codigo const& cod) const {
        auto it = productos.find(cod);

        if (it == productos.end()) return 0;
        else return (*it).second.cantidadTotal;
    }

    // Complejidad: O(1) porque todas las operaciones son de complejidad constante en promedio
    bool hay_esperando(Codigo const& cod) const {
        auto it = productos.find(cod);

        if (it == productos.end()) return false;
        else return (*it).second.listaEspera.size() > 0;
    }
};

bool resuelveCaso() {
    std::string operacion, cod, cli;
    Fecha f;
    int cant;
    std::cin >> operacion;
    if (!std::cin)
        return false;

    Tienda tienda;

    while (operacion != "FIN") {
        if (operacion == "adquirir") {
            cin >> cod >> f >> cant;
            vector<Cliente> clientes = tienda.adquirir(cod, f, cant);
            cout << "PRODUCTO ADQUIRIDO";
            for (auto c : clientes)
                cout << ' ' << c;
            cout << '\n';
        }
        else if (operacion == "vender") {
            cin >> cod >> cli;
            pair<bool, Fecha> venta = tienda.vender(cod, cli);
            if (venta.first) {
                cout << "VENDIDO " << venta.second << '\n';
            }
            else
                cout << "EN ESPERA\n";
        }
        else if (operacion == "cuantos") {
            cin >> cod;
            cout << tienda.cuantos(cod) << '\n';
        }
        else if (operacion == "hay_esperando") {
            cin >> cod;
            if (tienda.hay_esperando(cod))
                cout << "SI\n";
            else
                cout << "NO\n";
        }

        std::cin >> operacion;
    }
    std::cout << "---\n";
    return true;
}


//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input3.txt");
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