#ifndef __METODOS__
#define __METODOS__

#include <vector>
#include <random>
#include <iostream>
#include <fstream> 

using namespace std;

class Laberinto {
private:
    vector<vector<char>> laberinto; 
    vector<vector<bool>> visitado;
    int filas; 
    int columnas; 
    vector<int> dx; 
    vector<int> dy; 

public:
    Laberinto(int filas, int columnas) : filas(filas), columnas(columnas) {
        laberinto.resize(filas, vector<char>(columnas)); 
        visitado.resize(filas, vector<bool>(columnas, false)); 
        dx = { -1, 1, 0, 0 }; 
        dy = { 0, 0, -1, 1 }; 
    }

    void generarLaberinto() {
        random_device rd; 
        mt19937 gen(rd()); 
        uniform_int_distribution<> distrib(0, 9); 

        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                int val = distrib(gen); 
                laberinto[i][j] = (val < 2) ? 'X' : (val < 4) ? 't' : '.'; 
            }
        }
    }

    bool buscarTesoro(int x, int y, ofstream& writer) {
        if (x < 0 || x >= filas || y < 0 || y >= columnas || laberinto[x][y] == 'X' || visitado[x][y]) {
            return false; 
        }

        visitado[x][y] = true; 

        if (laberinto[x][y] == 't') {
            writer << "Posicion de tesoro: (" << x << ", " << y << ")\n"; 
            return true;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i]; 

            if (nx >= 0 && nx < filas && ny >= 0 && ny < columnas && laberinto[nx][ny] != 'X' && !visitado[nx][ny]) {
                if (buscarTesoro(nx, ny, writer)) { 
                    return true;
                }
            }
        }

        writer << "Posicion sin tesoro: (" << x << ", " << y << ")\n"; 
        return false; 
    }

    void mostrarLaberinto() {
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                cout << laberinto[i][j] << " "; 
            }
            cout << endl;
        }
    }

    void guardarResultados(bool puedeLlegar, int x, int y) {
        ofstream writer("resultados.txt", ios::app); 
        if (puedeLlegar) {
            writer << "El agente puede llegar al tesoro desde la posicion (" << x << ", " << y << ")\n"; 
        }
        else {
            writer << "El agente no puede llegar al tesoro desde la posicion (" << x << ", " << y << ")\n";
        }
    }
};

int main() {
    /*Daniel Echeverri Ortega
      Sebastian Chinchilla
      Javier Pérez Arroyo */

    int filas, columnas;
    cout << "Ingrese el numero de filas y columnas separados por un espacio:" << endl;
    cin >> filas >> columnas;

    Laberinto laberinto(filas, columnas); 
    laberinto.generarLaberinto(); 

    cout << "Laberinto generado:" << endl;
    laberinto.mostrarLaberinto(); 

    cout << "Ingrese la posicion inicial del agente (x, y):" << endl;
    int x, y;
    cin >> x >> y;

    ofstream writer("resultados.txt", ios::app); 
    bool puedeLlegar = laberinto.buscarTesoro(x, y, writer); 
    writer.close(); 
    laberinto.guardarResultados(puedeLlegar, x, y); 

    cout << (puedeLlegar ? "Si" : "No") << endl; 

    return 0;
}

#endif




//Conclusiones del código:
//1. El código nos genera un laberinto usando una cuadrícula de caracteres, con paredes, tesoros y celdas vacías, que son generadas generadas aleatoriamente.Utilizando un algoritmo de búsqueda en profundidad (DFS) para localizar un tesoro dentro del laberinto desde una posición inicial dada.
//2. La complejidad temporal de la búsqueda del tesoro (buscarTesoro) en el peor de los casos es 0 (filas×columnas), ya que potencialmente todas las celdas del laberinto pueden ser visitadas una vez. La complejidad espacial es 0 (filas×columnas), debido al almacenamiento de las estructuras laberinto y visitado, que guardan el estado del laberinto y las celdas visitadas.
//3.  Se puede mejorar la eficiencia del código implementando algoritmos más avanzados de búsqueda de caminos como A* o BFS si se conoce más sobre la estructura del laberinto y también podemos permitir las probabilidades de generar paredes y tesoros sean configurables para una mayor flexibilidad.
