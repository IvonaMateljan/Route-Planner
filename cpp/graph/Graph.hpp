#pragma once
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;


class Graph {
    public:
        struct Edge {
            int destination;
            float weight;
        };
        

    
    private:
        vector<vector<Edge>> adjList;
        vector<long long> indexToNode; // graph index -> OSM node id
        unordered_map<long long, int> nodeIndex; //OSM node id -> graph index

        void addEdge(int u, int v, float distance);

    public:
        Graph(const string& csvFilePath);
        int getIndexByOSMId(long long osmNode) const;
        long long getOSMFromIndex(int index) const;
        const vector<vector<Edge>>& getAdjList() const;
};