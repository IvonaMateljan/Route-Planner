#include "Graph.hpp"

void Graph::addEdge (int location1, int location2, float distance){
            adjList[location1].push_back({location2, distance});
        }

Graph::Graph(const string& csvFilePath){
    ifstream file(csvFilePath);
    if(!file.is_open()) throw runtime_error("Cannot open file " +  csvFilePath);

    string line;
    getline(file, line);
    
    struct RawEdge {
        long long u, v;
        float w;
    };

    vector<RawEdge> edges;
    unordered_set<long long> nodes;

    while (getline(file,line)){
        stringstream ss(line);
        string field;
        RawEdge e;

        getline(ss, field, ',');
        e.u = stoll(field);
        nodes.insert(e.u);

        getline(ss, field, ',');
        e.v = stoll(field);
        nodes.insert(e.v);

        getline(ss, field, ',');
        e.w = stof(field);

        edges.push_back(e);
    }

    int idx = 0;
    for(long long node : nodes){
        nodeIndex[node] = idx++;
        indexToNode.push_back(node);
    }

    adjList.resize(nodes.size());

    for(const auto& e : edges){
        int u = nodeIndex[e.u]; //e.u -> osmid, u -> nodeIndex
        int v = nodeIndex[e.v];
        addEdge(u, v, e.w);
    }
}

int Graph::getIndexByOSMId(long long osmNode) const {
        auto it = nodeIndex.find(osmNode);
        return it == nodeIndex.end() ? -1 : it->second;
    }

const vector<vector<Graph::Edge>>& Graph::getAdjList() const {
    return adjList;
}

long long Graph::getOSMFromIndex(int index) const{
    long long osmid = indexToNode[index];
    return osmid;
}