/*
8.   Represent a given graph using adjacency matrix /adjacency list and find the shortest path using
Dijkstra's algorithm (single source all destination).*/
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Structure to represent an edge
struct Edge {
    int destination, weight;
};

// Graph representation using adjacency list
class GraphAdjList {
private:
    int vertices;
    vector<vector<Edge>> adjList;

public:
    GraphAdjList(int V) : vertices(V), adjList(V) {}

    void addEdge(int u, int v, int w) {
        adjList[u].push_back({v, w});
    }

    // Dijkstra's Algorithm
    vector<int> dijkstra(int source) {
        vector<int> dist(vertices, numeric_limits<int>::max());
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[source] = 0;
        pq.push({0, source});

        while (!pq.empty()) {
            int u = pq.top().second;
            int distanceU = pq.top().first;
            pq.pop();

            if (distanceU > dist[u]) {
                continue; // Skip if already processed a shorter path to u
            }

            for (const Edge& neighbor : adjList[u]) {
                int v = neighbor.destination;
                int weightUV = neighbor.weight;

                if (dist[u] + weightUV < dist[v]) {
                    dist[v] = dist[u] + weightUV;
                    pq.push({dist[v], v});
                }
            }
        }

        return dist;
    }
};

int main() {
    int numVertices, numEdges;

    // Taking user input for the number of vertices and edges
    cout << "Enter the number of vertices: ";
    cin >> numVertices;
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    // Creating a graph representation
    GraphAdjList graph(numVertices);

    // Taking user input for edges
    for (int i = 0; i < numEdges; ++i) {
        int u, v, w;
        cout << "Enter edge " << i + 1 << " (source destination weight): ";
        cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }

    // Taking user input for the source node
    int sourceNode;
    cout << "Enter the source node: ";
    cin >> sourceNode;

    // Dijkstra's Algorithm
    vector<int> shortestDistances = graph.dijkstra(sourceNode);

    // Displaying shortest distances
    cout << "Shortest distances from node " << sourceNode << ":\n";
    for (int i = 0; i < numVertices; ++i) {
        cout << "To node " << i << ": " << shortestDistances[i] << endl;
    }

    return 0;
}
