#pragma once
#include "Common.h"

extern int n, t, m, k, fuelCapacity;

extern vector<vector<int>> graph;
extern vector<int> hubs, houses, fuelStations;

extern vector<int> isHub, isHouse, isFuel;
extern map<int, int> houseToHub;

void resetGlobals();
void readInput();
