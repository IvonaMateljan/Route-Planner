#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

class TouristSights {
    public: 
        struct Sight {
            long long osmid;
            long long nearestNode;
            string type;
            string name;
            double lon;
            double lat;
        };

        private: 
            vector<Sight> sights;
            unordered_map<long long, int> nodeIndex;
        
        public:
            TouristSights(const string& csvFilePath);
            const vector<Sight>& getAllSights() const;
            int getIndexByOSMId(long long osmid) const;
};
