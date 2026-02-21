#include "dijkstra.hpp"

DijkstraResult dijkstra(
    const vector<vector<Graph::Edge>>& adjList,
    int startNode) {

    int n = adjList.size();
    vector<float> dist(n, numeric_limits<float>::infinity());

    priority_queue<
        pair<float, int>,
        vector<pair<float, int>>,
        greater<pair<float, int>>
    > pq;

    vector<int> prev(n, -1);

    dist[startNode] = 0;
    pq.push({0, startNode});

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        float currentDist = top.first;
        int currentNode = top.second; 

        if (currentDist > dist[currentNode]) continue;

        for (const auto& edge : adjList[currentNode]) {
            int v = edge.destination; //neighboring edge
            float weight = edge.weight;

            if (dist[v] > dist[currentNode] + weight) {
                dist[v] = dist[currentNode] + weight;
                prev[v] = currentNode;
                pq.push({dist[v], v});
            }
        }
    }

    DijkstraResult result = {dist, prev};

    return result;
}

vector<int> reconstructPath(int startNode, int targetNode, const vector<int>& prev) {
    vector<int> path;

    for (int v = targetNode; v != -1; v = prev[v]) {
        path.push_back(v);
    }

    reverse(path.begin(), path.end());

    if (path.front() != startNode) {
        return {}; // no path exists
    }

    return path;
}

