#include "dijkstras.h"
#include <iostream>
#include <fstream>

int main() {
    string filename;
    cout << "Enter file: ";
    cin >> filename;

    Graph G;
    file_to_graph(filename, G);

    vector<int> previous(G.size(), -1);
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    cout << "Shortest paths from vertex 0:" << endl;
    for (int i = 0; i < G.size(); ++i) {
        if (i != 0) {
            vector<int> path = extract_shortest_path(distances, previous, i);
            print_path(path, distances[i]);
        }
    }

    return 0;
}