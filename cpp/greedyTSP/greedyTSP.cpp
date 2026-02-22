#include <vector>
#include <limits>
#include <fstream>
#include <limits>
#include "../dijkstra/dijkstra.hpp"
#include "../sights/Sights.hpp"
#include "../graph/Graph.hpp"
using namespace std;

void greedyTSP(
    const vector<vector<float>>& distanceMatrix, 
    const vector<TouristSights::Sight>& sights, //selected sights
    const vector<DijkstraResult>& resultDijkstra,
    const Graph& graph) {
    vector<int> visited;
    int n = sights.size();
    visited.push_back(0);

    while (visited.size() < n) {
        int last = visited.back();
        float minDist = std::numeric_limits<float>::infinity();
        int next = -1;
        for (int i = 0; i < n; i++) {
            if (find(visited.begin(), visited.end(), i) == visited.end() &&
                distanceMatrix[last][i] < minDist) {
                minDist = distanceMatrix[last][i];
                next = i;
            }
        }
        visited.push_back(next);
    }
    visited.push_back(0);

    ofstream file("data/route.csv");
    file << "osmId\n";
    for (int idx = 0; idx < visited.size() - 1; idx++) {
        cout << sights[visited[idx]].name << "\n";
        file << sights[visited[idx]].nearestNode << "\n";
        auto startNode = graph.getIndexByOSMId(sights[visited[idx]].nearestNode);
        auto endNode = graph.getIndexByOSMId(sights[visited[idx + 1]].nearestNode);
        vector<int> path = reconstructPath(startNode, endNode, resultDijkstra[visited[idx]].prev);
        for(int i = 1; i < path.size() - 1; i++){
            long long osmId = graph.getOSMFromIndex(path[i]);
            file << osmId << "\n";
        }
        
    }
    cout << sights[visited[0]].name << "\n";
    file << sights[visited[0]].nearestNode << "\n";
    file.close();
}

vector<vector<float>> buildDistanceMatrix(
    vector<DijkstraResult>& result, 
    TouristSights& selectedSights, 
    Graph& graph){
    auto selected = selectedSights.getAllSights();
    int n = selected.size();
    vector<vector<float>> distanceMatrix(n, vector<float>(n, 0));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == j) continue;
            int endNode = graph.getIndexByOSMId(selected[j].nearestNode);
            distanceMatrix[i][j] = result[i].dist[endNode];
        }
    }

    return distanceMatrix;
}
