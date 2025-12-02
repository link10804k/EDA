#include <iostream>
#include <vector>
#include <array>

using Mapa = std::vector<std::vector<bool>>; // Se representa por filas

struct Vector2D {
    int x = 0, y = 0;
    Vector2D operator+(const Vector2D& other) {
        return { x + other.x, y + other.y };
    }
};
using Point2D = Vector2D;

const int NUM_DIRS = 4;
const std::array<Point2D, NUM_DIRS> DIRS = { { {1, 0}, {0, 1}, {-1, 0}, {0, -1} } }; // Derecha, Abajo, Izquierda, Arriba

void laberinto(std::vector<Point2D>& soluc, int n, int k, const Mapa& muros, Mapa& visitadas) {
    for (int dir = 0; dir < NUM_DIRS; ++dir) {
        Point2D pos = soluc[k-1] + DIRS[dir];
        soluc[k] = pos;
        if (esValida(pos, muros)) {
            if (esSolucion(pos, n)) {

            }
            else {
                visitadas[pos.x][pos.y] = true;
                laberinto(soluc, n, k + 1, muros, visitadas);
                visitadas[pos.x][pos.y] = false;
            }
        }
    }
}

bool esValida(Point2D pos, const Mapa& muros) {
    return !muros[pos.x][pos.y];
}
bool esSolucion(Point2D pos, int n) {
    return n == pos.x && n == pos.y; // La casilla de salida es la de abajo a la derecha
}

int main() // Tupla solución: [C0, C1, C3,...Cl] donde Ci es una casilla libre, Ci es adyacente a Ci-1 y Cl es la casilla destino
{
    const int tam = 5;
    Mapa muros = {  
        { 0, 0, 0, 0, 1 },
        { 0, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 1, 1, 0, 1 },
        { 0, 0, 0, 0, 0 }   
    };
    Mapa visitadas = {
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0 }
    };

    std::vector<Point2D> sol;
    laberinto(sol, tam, 0, muros, visitadas);
}




