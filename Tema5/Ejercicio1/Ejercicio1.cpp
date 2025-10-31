// Javier Zazo Morillo
// EDA-GDV72


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stack>

// función que resuelve el problema
bool resolver(std::string s) {
    std::stack<char> stack;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            stack.push(s[i]);
        }
        else if (s[i] == ')') {
            if (!stack.empty() && stack.top() == '(') {
                stack.pop();
            }
            else return false;
        }
        else if (s[i] == ']') {
            if (!stack.empty() && stack.top() == '[') {
                stack.pop();
            }
            else return false;
        }
        else if (s[i] == '}') {
            if (!stack.empty() && stack.top() == '{') {
                stack.pop();
            }
            else return false;
        }
    }
    if (stack.empty()) return true;
    else return false;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    std::string s;
    std::getline(std::cin, s);

    if (!std::cin)
        return false;

    bool sol = resolver(s);

    // escribir sol
    std::cout << (sol ? "SI" : "NO") << '\n';

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