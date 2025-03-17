#include "dijkstras.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include <algorithm>

using namespace std;

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if(distances[destination] == INF) return path;
    for (int i = destination; i != 0; i = previous[i]) {
        path.push_back(i);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& path, int total_cost) {
    if (total_cost == INF) {
        cout << "No path found." << endl;
        return;
    }

    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i] << " ";
    }

    cout << endl;
    cout << "Total cost is " << total_cost << endl;
}

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
//     int numVertices = G.size();
//     vector<int> distances(numVertices, INF);
//     vector<bool> visited(numVertices, false);
//     distances[source] = 0;
    
//     priority_queue<pair<int, int>> minHeap;  // pair<vertex, weight>
//     minHeap.push({source, 0});

//     while (!minHeap.empty()) {
//         int u = minHeap.top().second;
//         if (visited[u]) continue;
//         visited[u] = true;

//         for (Edge edge : graph[u]) {
//             int v = edge.dest;
//             int weight = edge.second;

//             if (!visited[v] && distances[u] + weight < distances[v]) {
//                 distances[v] = distances[u] + weight;
//                 previous[v] = u;
//                 minHeap.push({v, distances[v]});
//             }
//         }
//     }

//     return distances;

// }


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