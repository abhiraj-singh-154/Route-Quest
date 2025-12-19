#include "Input.h"
#include "FloydWarshall.h"
#include "Fuel.h"
#include "Solver.h"

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("input/input_1.txt", "r", stdin);
    freopen("output/output1.txt", "w", stdout);

    readInput();
    computeAllPairsShortestPath();
    computeNearestFuelStations();

    bestCost = INF;

    for (int i = 0; i < n; i++) {
        solveFromHub(i);
    }

    cout << bestPath.size() << "\n";
    for (int x : bestPath) cout << x << " ";
    cout << "\n";
}
