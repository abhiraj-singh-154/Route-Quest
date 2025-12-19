# Fuel-Constrained Delivery Optimization

## Overview

This project addresses the problem of planning a **single delivery route** for a vehicle operating in a city while satisfying **delivery precedence** and **fuel constraints**. The objective is to compute a valid route that completes all deliveries and minimizes total travel distance.

The city is modeled as an **undirected weighted graph**, where:

* **Nodes** represent locations such as delivery hubs, destination houses, fuel stations, or intersections
* **Edges** represent roads with an associated fuel cost
* The vehicle has a fuel tank of limited capacity **F** and starts with a **full tank**
* **Fuel stations** are special nodes where the vehicle can refuel back to full capacity

Each delivery consists of a pair `(hub_i, house_i)`, where a package must be picked up from `hub_i` and delivered to `house_i`. A route is considered valid if it satisfies all of the following conditions:

* **House Coverage**: Every destination house is visited at least once
* **Delivery Precedence**: For each pair `(hub_i, house_i)`, the **last visit** to `house_i` occurs **after at least one visit** to `hub_i`
* **Fuel Constraints**:

  * Fuel level never drops below zero
  * Refueling is allowed only at designated fuel station nodes
  * Refueling always restores the tank to full capacity
* **Route Rules**:

  * Only edges provided in the input graph may be traversed
  * Nodes may be visited multiple times
  * The route may start and end at any node

The solution implemented in this project constructs such a route while ensuring feasibility under all constraints.

---

## Input Format

```text
N T M K F
H1 H2 ... HN
D1 D2 ... DN
S1 S2 ... SK
u1 v1 c1
u2 v2 c2
...
uM vM cM
```

### Parameters

* `N` : Number of deliveries

* `T` : Total number of nodes in the graph

* `M` : Number of roads (edges)

* `K` : Number of fuel stations

* `F` : Fuel tank capacity

* `H1..HN` : Node indices of delivery hubs

* `D1..DN` : Node indices of destination houses

* `S1..SK` : Node indices of fuel stations

* Each of the next `M` lines contains:
  `u v c` — an undirected edge between nodes `u` and `v` with fuel cost `c`

All node indices lie in the range `0` to `T-1`.

---

## Output Format

```text
L
n1 n2 n3 ... nL
```

* `L` : Length of the route (number of nodes visited)
* Second line: `L` space-separated node indices representing the full route of the vehicle

---
## Example

### Example Input

```text
2 6 5 1 10
0 3
4 5
2
0 1 4
1 2 3
2 3 2
1 4 5
3 5 3
```

### Example Output

```text
9
0 1 2 3 5 3 2 1 4
```
---

## Project Structure

```text
├── include/
│   ├── Common.h          // Common includes, macros, and type definitions
│   ├── FloydWarshall.h   // Headers for shortest path algorithms
│   ├── Fuel.h            // Headers for fuel management logic
│   ├── Input.h           // Headers for input reading and global variables
│   └── Solver.h          // Headers for the main solving logic
├── src/
│   ├── FloydWarshall.cpp // Implementation of Floyd-Warshall algorithm
│   ├── Fuel.cpp          // Implementation of fuel feasibility checks
│   ├── Input.cpp         // Implementation of input parsing
│   └── Solver.cpp        // Implementation of the greedy heuristic solver
├── input/
│   ├── input_0.txt
│   ├── input_1.txt
│   └── input_2.txt
├── output/
│   ├── output0.txt
│   ├── output1.txt
│   └── output2.txt
└── main.cpp              // Entry point of the application
```

---

## Compilation and Execution

### Step 1: Configure Input/Output Paths

Update the file paths in `main.cpp` if necessary:

```cpp
freopen("input/input_1.txt", "r", stdin);
freopen("output/output1.txt", "w", stdout);
```

### Step 2: Compile

Use a C++ compiler with C++17 support:

```bash
g++ -std=c++17 -Iinclude main.cpp src/*.cpp -o solver
```

### Step 3: Run

```bash
./solver
```

---

## Key Components

### Algorithms Used

* **Floyd–Warshall Algorithm**
  Computes **All-Pairs Shortest Paths (APSP)** to allow constant-time distance queries between any two nodes, along with path reconstruction.

* **Greedy Heuristic with Lookahead**
  Iteratively selects the nearest feasible next node (Hub or House), while ensuring future fuel feasibility.

* **Safety Simulation**
  Before committing to a move, the solver checks whether the vehicle can:

  * Reach the target node, and
  * Subsequently reach a fuel station if needed

---

## Core Functions

* `readInput()`
  Parses the graph, hub locations, house locations, and fuel stations.

* `computeAllPairsShortestPath()`
  Runs Floyd–Warshall and populates distance and parent matrices.

* `computeNearestFuelStations()`
  Precomputes the closest fuel station for every node to speed up feasibility checks.

* `solveFromHub(int hubIndex)`
  Simulates a complete delivery route starting from a chosen hub.

* `canTravel(start, end, fuel)`
  Checks if a leg of travel is possible with the current fuel.

* `buildPath()`
  Reconstructs the node-by-node path between two locations using the parent matrix.

---

## Solution Strategy

The solver attempts to build a valid route by:

1. Trying **each Hub as a starting point**
2. From the current node, greedily selecting the **nearest valid target**

A node is considered a valid target if:

* It is an **unvisited Hub**, or
* It is a **House whose corresponding Hub has already been visited**
* The node is reachable with the **current fuel**

If no Hub or House is reachable, the vehicle travels to the **nearest Fuel Station** to refuel.

---





