# Route Planner – Graph-Based Tourist Route Optimization

## Overview

This project implements a route optimization system for tourist sightseeing using real-world OpenStreetMap (OSM) data.  
It models the road network as a weighted graph, computes shortest paths between selected sights using Dijkstra’s algorithm, and applies a greedy Traveling Salesman heuristic to determine an optimized visiting order. The final route is reconstructed and visualized on an interactive map.

Core optimization logic is implemented in C++, while data preprocessing and visualization are handled in Python.

---

## Architecture

The system consists of two main components:

### Python layer
- Extracts OSM road network data (OSMnx)  
- Filters tourist sights  
- Fetches edge distances  
- Provides GUI for sight selection  
- Visualizes final route (Folium)  

### C++ layer
- Loads processed graph data  
- Implements adjacency list graph structure  
- Runs Dijkstra’s shortest path algorithm  
- Applies greedy TSP heuristic  
- Reconstructs full route  
- Exports optimized route to `route.csv`  

Communication between components is file-based (CSV).

---

## Algorithms Implemented

**Dijkstra’s Algorithm**  
Used to compute shortest paths between selected sights.  
Complexity: O((V + E) log V)

**Greedy TSP (Nearest Neighbor Heuristic)**  
Approximates optimal visiting order by iteratively selecting the closest unvisited sight.

**Path Reconstruction**  
Uses predecessor tracking from Dijkstra runs to reconstruct the final route.

---

## How to Run

**Setup Python environment for OSMnx library (recommended via Conda)**

### Extract OSM data:
```bash
python ./python/extract-osm.py
```
Generates:
- `tourist_sights.csv` - tourist locations
- `graph_edges.csv` - pairwise node distances

### Select sights:
```bash
python ./python/gui.py
```
Generates:
- `selected_sights.csv`

### Compile and run C++ optimizer:
- Deactivate venv if needed
```bash
g++ -std=c++17 cpp/sights/Sights.cpp cpp/graph/Graph.cpp cpp/dijkstra/dijkstra.cpp cpp/main.cpp -o main
./main.exe
```
Generates:
- `route.csv` - optimal walking route for selected sights

### Visualize route:
- Reactivate venv if needed
 ```bash
python ./python/visualize.py
```
Generates:
- `route_with_sights.html`

## Key Concepts Demonstrated
- Graph modeling of real-world road networks
- Shortest path computation (Dijkstra)
- Heuristic optimization (TSP approximation)
- Multi-language system integration (Python + C++)
- Real-world data preprocessing and visualization
