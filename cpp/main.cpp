#include "sights/Sights.hpp"
#include "graph/Graph.hpp"
#include "dijkstra/dijkstra.hpp"
#include "greedyTSP/greedyTSP.cpp"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main() {
    try {
        TouristSights allSights("data/tourist_sights.csv");
        TouristSights selectedSights("data/selected_sights.csv");

        Graph graph("data/graph_edges.csv");
        const auto& adj = graph.getAdjList();
        vector<DijkstraResult> result;

        for(const auto& sight : selectedSights.getAllSights()){
            int startNodeIndex = graph.getIndexByOSMId(sight.nearestNode); //graph_edges.csv maps sights to nearest node, not by osmid
            result.push_back(dijkstra(adj, startNodeIndex));
        }
        
        vector<vector<float>> distanceMatrix = buildDistanceMatrix(result, selectedSights, graph);
        greedyTSP(distanceMatrix, selectedSights.getAllSights(), result, graph);


    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
