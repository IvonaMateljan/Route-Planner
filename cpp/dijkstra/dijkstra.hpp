#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "../graph/Graph.hpp"
using namespace std;

struct DijkstraResult {
    vector<float> dist;
    vector<int> prev;
};

DijkstraResult dijkstra(
    const vector<vector<Graph::Edge>>& adjList,
    int startNode);

vector<int> reconstructPath(int startNode, int targetNode, const vector<int>& prev);