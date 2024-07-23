#pragma once

#ifndef Laberinto_h
#define Laberinto_h

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <utility>

using namespace std;

class Laberinto {
public:
    Laberinto(int rows, int cols, vector<string> map, pair<int, int> start);
    bool canReachTreasure();

private:
    int rows, cols;
    vector<string> map;
    pair<int, int> start;
};

#endif

