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





    //     // Pick start and target: for example first two sights
    //     const auto& allSights = sights.getAllSights();
    //     if (allSights.size() < 2) {
    //         cerr << "Need at least 2 sights to test\n";
    //         return 1;
    //     }

    //     int startNode = graph.nodeIndex.at(allSights[0].nearestNode);
    //     int targetNode = graph.nodeIndex.at(allSights[1].nearestNode);


    //     cout << "Running Dijkstra from sight '"
    //          << allSights[0].name << "' to '"
    //          << allSights[1].name << "'...\n";

    //     // Run Dijkstra
    //     DijkstraResult result = dijkstra(adj, startNode);

    //     // Reconstruct path
    //     vector<int> path = reconstructPath(startNode, targetNode, result.prev);

    //     if (path.empty()) {
    //         cout << "No path found!\n";
    //     } else {
    //         ofstream outFile("data/route.csv");
    //         outFile << "osm_node_id,lat,lon\n";
    //         for (int idx : path) {
    //             const auto& sight = allSights[0]; // temp placeholder

    //             long long osmId = graph.indexToNode[idx];

    //             // find lat/lon from TouristSights
    //             auto it = find_if(allSights.begin(), allSights.end(),
    //                             [osmId](const TouristSights::Sight& s){ return s.nearestNode == osmId; });

    //             double lat = (it != allSights.end()) ? it->lat : 0;
    //             double lon = (it != allSights.end()) ? it->lon : 0;

    //             outFile << osmId << "," << lat << "," << lon << "\n";
    //         }
    //         outFile.close();
    //         cout << "Route exported to route.csv\n";
    //     }

    // } catch (const exception& e) {
    //     cerr << "Error: " << e.what() << "\n";
    // }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
