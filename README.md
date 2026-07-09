# 🌐 Smart Transportation Network

A collection of **C++ graph theory applications** built to simulate, analyze, and optimize a 500-city transportation grid. This project models physical infrastructure to calculate minimum construction costs, simulate traffic congestion, and identify critical vulnerabilities in the network.

---

# 🏗️ Core Infrastructure: The Graph Generator

Before any routing or optimization occurs, a foundational mathematical graph is established to represent the cities and roads. This logic is encapsulated in a shared header file (`NetworkGraph.h`) used across all tasks. 

*(Note: For self-contained compilation, a copy of `NetworkGraph.h` is stored inside each assignment folder).*

## ✨ Core Graph Features
* 🗺️ **Network Generation:** Instantiates a 500-node undirected, weighted graph with realistic sparseness.
* 💾 **Memory Efficiency:** Utilizes an Adjacency List (`vector<vector>`) to efficiently store the sparse graph.
* ⏱️ **Time Complexity:** $O(V^2)$ for initial generation.

---

# 🛣️ Assignment 1: Basic Network Metrics

A foundational module that analyzes basic connectivity and distance metrics across the 500-city grid.

## 📌 Problem Statement

Before optimizing a transportation grid, the baseline connectivity must be understood. This module identifies isolated clusters of cities and computes the absolute shortest travel distances between points assuming no traffic or infrastructure damage.

## ✨ Features

* 🔗 **Component Analysis:** Identifies the largest connected group of cities (Task A).
* 🧩 **Cluster Mapping:** Calculates the total number of disconnected sub-grids and their respective sizes (Task B).
* 📍 **Shortest Path Routing:** Computes the optimal distance from a source city to all other reachable cities (Task C).

## 🧠 Data Structures & Algorithms Used

| Feature                 | DSA Concept                           | Why                                                                             |
| :---------------------- | :------------------------------------ | :------------------------------------------------------------------------------ |
| Component / Cluster Map | Breadth-First Search (`queue`)        | Systematically explores all connected nodes level-by-level to group components. |
| Shortest Path Routing   | Dijkstra's Algorithm (`priority_queue`) | Greedily selects the lowest-cost path using a Min-Heap for optimal routing.     |

### ⏱️ Time Complexity

| Operation             | Complexity              |
| :-------------------- | :---------------------- |
| Component Counting    | O(V + E)                |
| Shortest Path Routing | O((V + E) log V)        |

---

# 🚦 Assignment 2: Advanced Routing & Infrastructure

An advanced analysis module simulating real-world engineering constraints, including budget optimization, disaster recovery, and real-time traffic dynamics.

## 📌 Problem Statement

Governments need to minimize infrastructure costs while maintaining full connectivity, plan for systemic failures (natural disasters), and adapt to dynamic edge weights (traffic). This module applies advanced graph algorithms to solve these specific urban planning and logistical challenges.

## ✨ Features

* 💰 **MST Optimization:** Calculates the cheapest possible network to connect all 500 cities.
* 🎯 **Strategic City Identification:** Ranks cities by connectivity to recommend logistics and airport hubs.
* ⚠️ **Disaster Recovery:** Reroutes traffic dynamically when specific cities or roads are destroyed.
* 🚗 **Traffic-Aware Routing:** Scales edge weights based on simulated congestion to find the fastest (not just shortest) route.
* 💥 **Vulnerability Analysis:** Brute-forces node removals to find the single point of failure that shatters the network.

## 🧠 Data Structures & Algorithms Used

| Feature                     | DSA Concept                         | Why                                                                              |
| :-------------------------- | :---------------------------------- | :------------------------------------------------------------------------------- |
| MST Construction            | Kruskal's Algorithm + Union-Find    | Sorts edges by weight and safely connects nodes without creating cycles.         |
| Strategic Hubs              | Degree Centrality + Sorting         | Counts adjacent edges per node to measure a city's structural influence.         |
| Disaster / Traffic Routing  | Modified Dijkstra's Algorithm       | Re-calculates optimal paths while explicitly ignoring removed nodes/scaled edges.|
| Vulnerability Analysis      | Iterative BFS Component Counting    | Measures network resilience by simulating the structural impact of losing a node.|

### ⏱️ Time Complexity

| Operation                   | Complexity              |
| :-------------------------- | :---------------------- |
| MST Optimization            | O(E log E)              |
| Centrality Ranking          | O(V log V)              |
| Dynamic Routing (Traffic)   | O((V + E) log V)        |
| Vulnerability Analysis      | O(V × (V + E))          |

---

### 🚀 Run Instructions

Navigate to the specific assignment folder, compile with C++17, and execute the desired task file.

```bash
# Example 1: Running Task A from Assignment 1
cd Assignment_1_Basic_Metrics
g++ -std=c++17 task_A_largest_component.cpp -o task_A
./task_A

# Example 2: Running MST Optimization from Assignment 2
cd Assignment_2_Advanced_Routing
g++ -std=c++17 task1_mst.cpp -o task1_mst
./task1_mst
