#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <limits>
#include <algorithm>

using namespace std;

// Define the graph using an adjacency list
unordered_map<char, vector<pair<char, int>>> graph = {
    {'A', {{'B', 10}, {'E', 3}}},
    {'B', {{'C', 2}, {'E', 4}}},
    {'C', {{'D', 9}}},
    {'D', {{'C', 7}}},
    {'E', {{'B', 1}, {'C', 8}}}
};

// Recursive function to find the shortest path using Dijkstra's algorithm
void dijkstra_recursive(char current, char destination, unordered_map<char, int>& distances, unordered_map<char, char>& predecessors, set<char>& visited) {
    visited.insert(current);

    cout << "Processing node: " << current << endl;

    // Check each neighbor of the current node
    for (auto& neighbor : graph[current]) {
        char neighbor_node = neighbor.first;
        int weight = neighbor.second;

        // If the neighbor hasn't been visited and we found a shorter path
        if (visited.find(neighbor_node) == visited.end() && distances[current] + weight < distances[neighbor_node]) {
            distances[neighbor_node] = distances[current] + weight;
            predecessors[neighbor_node] = current;
            cout << "Updated distance for node " << neighbor_node << " to " << distances[neighbor_node] << " via " << current << endl;
        }
    }

    // Find the unvisited node with the smallest distance
    char next_node = 0;
    int min_distance = numeric_limits<int>::max();
    for (auto& node : distances) {
        if (visited.find(node.first) == visited.end() && node.second < min_distance) {
            min_distance = node.second;
            next_node = node.first;
        }
    }

    // If we have a valid next node and it isn't the destination, recurse
    if (next_node != 0 && next_node != destination) {
        dijkstra_recursive(next_node, destination, distances, predecessors, visited);
    }
}

// Function to find the shortest path using Dijkstra's algorithm
void dijkstra(char start, char end) {
    // Initialize distances and predecessors
    unordered_map<char, int> distances;
    unordered_map<char, char> predecessors;
    set<char> visited;

    for (auto& node : graph) {
        distances[node.first] = numeric_limits<int>::max();
    }

    distances[start] = 0;
    predecessors[start] = 0;

    cout << "Starting Dijkstra's algorithm from node " << start << " to " << end << ":\n";

    // Run the recursive Dijkstra's algorithm
    dijkstra_recursive(start, end, distances, predecessors, visited);

    // Output the shortest path and its cost
    if (distances[end] == numeric_limits<int>::max()) {
        cout << "No path found from " << start << " to " << end << endl;
    } else {
        cout << "\nShortest path cost from " << start << " to " << end << ": " << distances[end] << endl;

        // Reconstruct the path
        vector<char> path;
        for (char at = end; at != 0; at = predecessors[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());

        cout << "Path: ";
        for (char node : path) {
            cout << node << " ";
        }
        cout << endl;
    }
}

int main() {
    char start, end;
    cout << "Enter the starting node: ";
    cin >> start;
    cout << "Enter the ending node: ";
    cin >> end;

    // Convert input to uppercase to match the graph definition
    start = toupper(start);
    end = toupper(end);

    // Run Dijkstra's algorithm
    if (graph.find(start) == graph.end() || graph.find(end) == graph.end()) {
        cout << "Invalid starting or ending node. Please enter nodes from A to E." << endl;
    } else {
        dijkstra(start, end);
    }

    return 0;
}
