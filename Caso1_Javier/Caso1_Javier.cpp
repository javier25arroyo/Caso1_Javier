#include <iostream>
#include <vector>
#include <string>
#include "Laberinto.h"

using namespace std;

int main() {
    int rows, cols;
    cout << "Ingrese el numero de filas y columnas: ";
    cin >> rows >> cols;

     vector< string> map(rows);
     cout << "Ingrese el mapa:\n";
    for (int i = 0; i < rows; ++i) {
         cin >> map[i];
    }

    int startX, startY;
     cout << "Ingrese la posicion inicial del agente (x, y): ";
     cin >> startX >> startY;

     Laberinto laberinto(rows, cols, map, { startX, startY });

    if (laberinto.canReachTreasure()) {
         cout << "Output: yes\n";
    }
    else {
         cout << "Output: no\n";
    }

    return 0;
}

