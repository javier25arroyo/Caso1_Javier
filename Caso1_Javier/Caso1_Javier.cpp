#ifndef __METODOS__
#define __METODOS__

#include <vector>
#include <random>
#include <iostream>
#include <fstream> 

using namespace std;

class Laberinto {
private:
    vector<vector<char>> laberinto; // Representa la cuadrícula del laberinto
    vector<vector<bool>> visitado; // Guarda el estado de las celdas visitadas
    int filas; // Número de filas en el laberinto
    int columnas; // Número de columnas en el laberinto
    vector<int> dx; // Arreglo de desplazamientos en el eje x para moverse arriba, abajo, derecha e izquierda
    vector<int> dy; // Arreglo de desplazamientos en el eje y para moverse arriba, abajo, derecha e izquierda

public:
    Laberinto(int filas, int columnas) : filas(filas), columnas(columnas) {
        laberinto.resize(filas, vector<char>(columnas)); // Cambia el tamaño de la cuadrícula del laberinto
        visitado.resize(filas, vector<bool>(columnas, false)); // Cambia el tamaño de la cuadrícula de celdas visitadas
        dx = { -1, 1, 0, 0 }; // Inicializa los desplazamientos en el eje x
        dy = { 0, 0, -1, 1 }; // Inicializa los desplazamientos en el eje y
    }

    void generarLaberinto() {
        random_device rd; // Dispositivo aleatorio para generar números aleatorios
        mt19937 gen(rd()); // Generador de números aleatorios Mersenne Twister
        uniform_int_distribution<> distrib(0, 9); // Distribución uniforme de 0 a 9

        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                int val = distrib(gen); // Genera un número aleatorio para la celda
                laberinto[i][j] = (val < 2) ? 'X' : (val < 4) ? 't' : '.'; // Asigna 'X', 't' o '.' a cada celda según el número aleatorio
            }
        }
    }

    bool buscarTesoro(int x, int y, ofstream& writer) {
        if (x < 0 || x >= filas || y < 0 || y >= columnas || laberinto[x][y] == 'X' || visitado[x][y]) {
            return false; // Si la celda actual está fuera de los límites, es una pared o ya ha sido visitada, devuelve falso
        }

        visitado[x][y] = true; // Marca la celda actual como visitada

        if (laberinto[x][y] == 't') {
            writer << "Posicion de tesoro: (" << x << ", " << y << ")\n"; // Si la celda actual contiene el tesoro, escribe su posición en el archivo de salida y devuelve verdadero
            return true;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i]; // Calcula la nueva coordenada x
            int ny = y + dy[i]; // Calcula la nueva coordenada y

            if (nx >= 0 && nx < filas && ny >= 0 && ny < columnas && laberinto[nx][ny] != 'X' && !visitado[nx][ny]) {
                if (buscarTesoro(nx, ny, writer)) { // Llama recursivamente a la función para la nueva celda
                    return true; // Si se encuentra el tesoro en alguna de las llamadas recursivas, devuelve verdadero
                }
            }
        }

        writer << "Posicion sin tesoro: (" << x << ", " << y << ")\n"; // Si la celda actual no contiene el tesoro, escribe su posición en el archivo de salida
        return false; // Devuelve falso para indicar que el tesoro no se encontró en la celda actual
    }

    void mostrarLaberinto() {
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                cout << laberinto[i][j] << " "; // Imprime la cuadrícula del laberinto
            }
            cout << endl;
        }
    }

    void guardarResultados(bool puedeLlegar, int x, int y) {
        ofstream writer("resultados.txt", ios::app); // Abre el archivo de salida en modo de apendizaje
        if (puedeLlegar) {
            writer << "El agente puede llegar al tesoro desde la posicion (" << x << ", " << y << ")\n"; // Escribe el resultado en el archivo de salida
        }
        else {
            writer << "El agente no puede llegar al tesoro desde la posicion (" << x << ", " << y << ")\n"; // Escribe el resultado en el archivo de salida
        }
    }
};

int main() {
    int filas, columnas;
    cout << "Ingrese el numero de filas y columnas separados por un espacio:" << endl;
    cin >> filas >> columnas;

    Laberinto laberinto(filas, columnas); // Crea un objeto de laberinto con el número de filas y columnas especificado
    laberinto.generarLaberinto(); // Genera el laberinto

    cout << "Laberinto generado:" << endl;
    laberinto.mostrarLaberinto(); // Muestra el laberinto generado

    cout << "Ingrese la posicion inicial del agente (x, y):" << endl;
    int x, y;
    cin >> x >> y;

    ofstream writer("resultados.txt", ios::app); // Abre el archivo de salida en modo de apendizaje
    bool puedeLlegar = laberinto.buscarTesoro(x, y, writer); // Busca el tesoro comenzando desde la posición especificada
    writer.close(); // Cierra el archivo de salida
    laberinto.guardarResultados(puedeLlegar, x, y); // Guarda el resultado de la búsqueda en el archivo de salida

    cout << (puedeLlegar ? "Si" : "No") << endl; // Imprime si se puede llegar al tesoro o no

    return 0;
}

#endif
