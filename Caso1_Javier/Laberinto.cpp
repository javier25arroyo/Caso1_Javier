#ifndef __Metodos__
#define __Metodos__

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include "Laberinto.h"
#include <queue>

using namespace std;


Laberinto::Laberinto(int rows, int cols, vector<string> map, pair<int, int> start)
    : rows(rows), cols(cols), map(map), start(start) {}

bool Laberinto::isValidMove(int x, int y) {
    return (x >= 0 && x < rows && y >= 0 && y < cols && map[x][y] != 'X');
}

bool Laberinto::canReachTreasure() {
    queue<pair<int, int>> q;
    q.push(start);
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    visited[start.first][start.second] = true;

    int directions[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (map[x][y] == 't') {
            return true;
        }

        for (auto dir : directions) {
            int newX = x + dir[0];
            int newY = y + dir[1];

            if (isValidMove(newX, newY) && !visited[newX][newY]) {
                visited[newX][newY] = true;
                q.push({ newX, newY });
            }
        }
    }

    return false;
}

#endif  __Metodos__
