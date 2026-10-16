#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
    int to;
    int distance;
};

static string canonical(string s) {
    for (char &c : s) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    return s;
}

class RoutePlanner {
private:
    vector<string> names;
    map<string, int> idByName;
    vector<vector<Edge>> graph;

public:
    bool loadLocations(const string &path) {
        ifstream in(path);
        if (!in) return false;

        int n;
        in >> n;
        names.assign(n + 1, "");
        graph.assign(n + 1, {});

        for (int i = 0; i < n; ++i) {
            int id;
            string name;
            in >> id >> name;
            if (id < 1 || id > n) return false;
            names[id] = name;
            idByName[canonical(name)] = id;
        }
        return true;
    }

    bool loadRoads(const string &path) {
        ifstream in(path);
        if (!in) return false;

        int n, m;
        in >> n >> m;
        if (n + 1 != static_cast<int>(names.size())) return false;

        for (int i = 0; i < m; ++i) {
            int u, v, w;
            in >> u >> v >> w;
            if (u <= 0 || v <= 0 || u >= static_cast<int>(graph.size()) ||
                v >= static_cast<int>(graph.size()) || w < 0) return false;
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }
        return true;
    }

    void showLocations() const {
        map<char, vector<string>> grouped;
        for (size_t i = 1; i < names.size(); ++i) {
            if (!names[i].empty()) grouped[toupper(names[i][0])].push_back(names[i]);
        }
        for (auto &[initial, group] : grouped) {
            sort(group.begin(), group.end());
            cout << initial << " ---> ";
            for (const auto &name : group) cout << name << ' ';
            cout << '\n';
        }
    }

    int findLocation(const string &name) const {
        auto it = idByName.find(canonical(name));
        return (it == idByName.end()) ? -1 : it->second;
    }

    pair<int, vector<int>> shortestPath(int source, int destination) const {
        const int INF = numeric_limits<int>::max() / 4;
        vector<int> dist(graph.size(), INF), parent(graph.size(), -1);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

        dist[source] = 0;
        pq.push({0, source});

        while (!pq.empty()) {
            auto [currentDist, u] = pq.top();
            pq.pop();
            if (currentDist != dist[u]) continue;
            if (u == destination) break;

            for (const auto &edge : graph[u]) {
                int nextDist = currentDist + edge.distance;
                if (nextDist < dist[edge.to]) {
                    dist[edge.to] = nextDist;
                    parent[edge.to] = u;
                    pq.push({nextDist, edge.to});
                }
            }
        }

        if (dist[destination] == INF) return {-1, {}};

        vector<int> path;
        for (int at = destination; at != -1; at = parent[at]) path.push_back(at);
        reverse(path.begin(), path.end());
        return {dist[destination], path};
    }

    void printRoute(const vector<int> &path) const {
        for (size_t i = 0; i < path.size(); ++i) {
            if (i) cout << " --> ";
            cout << names[path[i]];
        }
        cout << '\n';
    }
};

int main() {
    RoutePlanner planner;
    if (!planner.loadLocations("data/map_set.txt") || !planner.loadRoads("data/data.txt")) {
        cerr << "Could not load data files. Run the program from the repository root.\n";
        return 1;
    }

    cout << "Best Shortest Route - Dhaka Demo\n";
    cout << "================================\n";
    cout << "Listed locations:\n";
    planner.showLocations();

    while (true) {
        cout << "\nType q at From to exit.\n";
        string from, to;
        cout << "From: ";
        cin >> from;
        if (canonical(from) == "q") break;
        cout << "To: ";
        cin >> to;

        int source = planner.findLocation(from);
        int destination = planner.findLocation(to);
        if (source == -1 || destination == -1) {
            cout << "Location not found. Use the exact listed spelling (underscores included).\n";
            continue;
        }

        auto [distance, path] = planner.shortestPath(source, destination);
        if (distance < 0) {
            cout << "No route is available between these locations.\n";
            continue;
        }

        cout << "Shortest distance from " << from << " to " << to << ": "
             << distance << " km\n";
        cout << "Route: ";
        planner.printRoute(path);
    }

    cout << "Goodbye.\n";
    return 0;
}
