#include "Sights.hpp"

TouristSights::TouristSights(const string& csvFilePath){
        ifstream file(csvFilePath);
        if (!file.is_open()) throw runtime_error("Cannot open file " + csvFilePath);

        string line;
        getline(file, line); // skip header

        while (getline(file, line)) {
            stringstream ss(line);
            string field;

            Sight s;

            getline(ss, field, ','); 
            s.osmid = stoll(field);

            getline(ss, field, ',');
            s.name = field;

            getline(ss, field, ',');
            s.type = field;

            getline(ss, field, ',');
            s.lat = stod(field);

            getline(ss, field, ',');
            s.lon = stod(field);

            getline(ss, field, ',');
            s.nearestNode = stoll(field);

            nodeIndex[s.osmid] = sights.size();
            sights.push_back(s);
        }
        file.close();
    }

    const vector<TouristSights::Sight>& TouristSights::getAllSights() const {
        return sights;
    }

    int TouristSights::getIndexByOSMId(long long osmid) const {
        auto it = nodeIndex.find(osmid);
        return it != nodeIndex.end() ? it->second : -1;
    }

