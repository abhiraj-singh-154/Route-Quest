#pragma once
#include "Common.h"

extern vector<vector<int>> dist;
extern vector<vector<int>> parent;

void computeAllPairsShortestPath();
void buildPath(int start, int end, vector<int>& path);
