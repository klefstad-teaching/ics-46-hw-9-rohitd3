#include "dijkstras.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>

using namespace std;

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    vector<int> path;
    int current = destination;
    while (current != -1) {
        path.push_back(current);
        current = previous[current];
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& path, int total_cost) {
    if (path.empty()) {
        cout << "No path found." << endl;
        return;
    }

    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i < path.size() - 1) {
            cout << " ";
        }
    }
    cout << " " << endl;
    cout << "Total cost is " << total_cost << endl;
}

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.size();
    vector<int> distance(n, INF);
    distance[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const Edge& e : G[u]) {
            int v = e.dst;
            int weight = e.weight;

            if (distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push({distance[v], v});
            }
        }
    }

    return distance;
}
