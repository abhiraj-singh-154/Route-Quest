# Fuel-Constrained Delivery Optimization

## Overview

This project solves a **fuel-constrained delivery routing problem** on a city map represented as a **weighted undirected graph**. A single delivery vehicle must pick up packages from designated **Hubs** and deliver them to corresponding **Houses**, while respecting fuel limitations and refueling constraints.

The objective is to compute a **valid route with minimum total travel distance** that completes all deliveries.

---

## Problem Description

Each delivery consists of:

* A **Hub** node where a package must be picked up
* A **House** node where that package must be delivered

### Constraints

* **Precedence Constraint**
  A package must be picked up from its Hub *before* it can be delivered to its House.

* **Fuel Constraint**
  The vehicle has a fixed **maximum fuel capacity**. Traveling along an edge consumes fuel equal to the edge weight.

* **Refueling Constraint**
  The vehicle can refuel to full capacity **only** at designated **Fuel Stations**.

* **Optimization Goal**
  Minimize the **total distance traveled** while completing all deliveries.

---

## Input Format

The input is read from a file (e.g., `input/input_1.txt`) with the following structure:

```text
n t m k fuelCapacity
h[0] h[1] ... h[n-1]        // n hub node indices
d[0] d[1] ... d[n-1]        // n destination (house) node indices
fs[0] fs[1] ... fs[k-1]     // k fuel station node indices
m lines of: u v w           // bidirectional edge between u and v with weight w
```

### Parameters

* `n` : Number of deliveries (hub–house pairs)
* `t` : Total number of nodes in the graph (indexed `0` to `t-1`)
* `m` : Number of edges
* `k` : Number of fuel stations
* `fuelCapacity` : Maximum fuel the vehicle can hold

---

## Output Format

The output is written to a file (e.g., `output/output1.txt`) in the following format:

```text
<length of the path>
<space-separated sequence of node indices representing the full route>
```

---

## Project Structure

```text
├── include/
│   ├── common.h          // Common includes, macros, and type definitions
│   ├── FloydWarshall.h   // Headers for shortest path algorithms
│   ├── Fuel.h            // Headers for fuel management logic
│   ├── input.h           // Headers for input reading and global variables
│   └── Solver.h          // Headers for the main solving logic
├── src/
│   ├── FloydWarshall.cpp // Implementation of Floyd-Warshall algorithm
│   ├── Fuel.cpp          // Implementation of fuel feasibility checks
│   ├── input.cpp         // Implementation of input parsing
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
g++ -std=c++17 -Iinclude main.cpp src/*.cpp -o solution
```

### Step 3: Run

```bash
./solution
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

A node is considered a valid candidate if:

* It is an **unvisited Hub**, or
* It is a **House whose corresponding Hub has already been visited**

And additionally:

* The node is reachable with the **current fuel**
* From that node, it is still possible to reach a **Fuel Station** (to avoid dead ends)

If no Hub or House is reachable, the vehicle travels to the **nearest Fuel Station** to refuel.

---

## Constraints Handled

* **Dependency Management**
  Ensures a House is only visited after its corresponding Hub has been visited.

* **Fuel Management**
  Fuel is decremented on every move and reset to `fuelCapacity` upon visiting a Fuel Station.

* **Path Continuity**
  Uses precomputed shortest paths to generate the exact step-by-step route.

---

## Output Description

The program outputs:

* The **total number of nodes** in the final route
* The **ordered list of node IDs** representing the complete delivery path

This route satisfies all constraints while aiming to minimize the total travel cost.
