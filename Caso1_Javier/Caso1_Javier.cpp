#ifndef __Metodos__
#define __Metodos__

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <string>

using namespace std;

class Laberinto {
private:
    vector<vector<char>> laberinto;
    vector<vector<bool>> visitado;
    int filas;
    int columnas;

public:
    Laberinto(int filas, int columnas) : filas(filas), columnas(columnas) {
        laberinto.resize(filas, vector<char>(columnas));
        visitado.resize(filas, vector<bool>(columnas, false));
    }

    void generarLaberinto() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(0, 9);

        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                int val = distrib(gen);
                if (val < 2) {
                    laberinto[i][j] = 'X'; // Obstáculo
                }
                else if (val < 4) {
                    laberinto[i][j] = 't'; // Tesoro
                }
                else {
                    laberinto[i][j] = '.'; // Camino
                }
            }
        }
    }

    bool buscarTesoro(int x, int y) {
        if (x < 0 || x >= filas || y < 0 || y >= columnas || laberinto[x][y] == 'X' || visitado[x][y]) {
            return false;
        }

        visitado[x][y] = true;

        if (laberinto[x][y] == 't') {
            return true;
        }

        // Desplazamientos arriba, abajo, derecha, izquierda
        return buscarTesoro(x - 1, y) || buscarTesoro(x + 1, y) || buscarTesoro(x, y - 1) || buscarTesoro(x, y + 1);
    }

    void mostrarLaberinto() {
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                cout << laberinto[i][j];
            }
            cout << endl;
        }
    }

    void guardarResultados(bool puedeLlegar, int x, int y) {
        ofstream writer("resultados.txt", ios::app);
        writer << "Posición inicial: (" << x << ", " << y << ") -> ";
        writer << (puedeLlegar ? "Sí llega a un tesoro" : "No llega a un tesoro") << endl;
    }
};

int main() {
    int filas, columnas;
    cout << "Ingrese el numero de filas:" << endl;
    cin >> filas;
    cout << "Ingrese el numero de columnas:" << endl;
    cin >> columnas;

    Laberinto laberinto(filas, columnas);
    laberinto.generarLaberinto();

    cout << "Laberinto generado:" << endl;
    laberinto.mostrarLaberinto();

    cout << "Ingrese la posicion inicial del agente (x, y):" << endl;
    int x, y;
    cin >> x >> y;

    bool puedeLlegar = laberinto.buscarTesoro(x, y);
    laberinto.guardarResultados(puedeLlegar, x, y);

    cout << (puedeLlegar ? "Si" : "No") << endl;

    return 0;
}

#endif  // __Metodos__
