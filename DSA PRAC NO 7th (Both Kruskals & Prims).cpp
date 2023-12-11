/*#PROVIDED BY mr.SHLOK
7. Represent a graph of your college campus using adjacency list /adjacency matrix. Nodes should represent
the various departments/institutes and links should represent the distance between them. Find minimum
spanning tree
a) Using Kruskal’s algorithm.
b) Using Prim’s algorithm.*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Edge {
    int src, dest, weight;
};

bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

class Graph {
public:
    Graph(int numVertices);
    void addEdge(int src, int dest, int weight);
    void kruskalMST();
    void primMST();

private:
    int numVertices;
    vector<Edge> edges;
    vector<int> parent;

    int find(int i);
    void unionSets(int x, int y);
    int minKey(const vector<int>& key, const vector<bool>& mstSet);
};

Graph::Graph(int numVertices) : numVertices(numVertices) {
    parent.resize(numVertices);
    edges.clear();
}

void Graph::addEdge(int src, int dest, int weight) {
    Edge edge = {src, dest, weight};
    edges.push_back(edge);
}

int Graph::find(int i) {
    if (parent[i] == -1)
        return i;
    return find(parent[i]);
}

void Graph::unionSets(int x, int y) {
    parent[x] = y;
}

void Graph::kruskalMST() {
    sort(edges.begin(), edges.end(), compareEdges);
    fill(parent.begin(), parent.end(), -1);

    cout << "Minimum Spanning Tree using Kruskal's Algorithm:\n";

    for (const Edge& edge : edges) {
        int x = find(edge.src);
        int y = find(edge.dest);

        if (x != y) {
            cout << "Edge: " << edge.src << " - " << edge.dest << " | Weight: " << edge.weight << endl;
            unionSets(x, y);
        }
    }
}

int Graph::minKey(const vector<int>& key, const vector<bool>& mstSet) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < numVertices; ++v) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}

void Graph::primMST() {
    vector<int> key(numVertices, INT_MAX);
    vector<bool> mstSet(numVertices, false);

    key[0] = 0;

    cout << "Minimum Spanning Tree using Prim's Algorithm:\n";

    for (int count = 0; count < numVertices - 1; ++count) {
        int u = minKey(key, mstSet);

        mstSet[u] = true;

        for (const Edge& edge : edges) {
            if (edge.src == u && !mstSet[edge.dest] && edge.weight < key[edge.dest]) {
                cout << "Edge: " << edge.src << " - " << edge.dest << " | Weight: " << edge.weight << endl;
                key[edge.dest] = edge.weight;
            }
        }
    }
}

int main() {
    while (true) {
        int numVertices;
        cout << "\nEnter the number of departments/institutes (0 to exit): ";
        cin >> numVertices;

        if (numVertices == 0) {
            cout << "Exiting...\n";
            break;
        }

        Graph graph(numVertices);

        cout << "Enter the distances between departments (0 for no direct connection):\n";
        for (int i = 0; i < numVertices; ++i) {
            for (int j = i + 1; j < numVertices; ++j) {
                int distance;
                cout << "Distance from department " << i << " to " << j << ": ";
                cin >> distance;
                if (distance > 0) {
                    graph.addEdge(i, j, distance);
                    graph.addEdge(j, i, distance);
                }
            }
        }

        int choice;
        cout << "Choose the algorithm:\n";
        cout << "1. Kruskal's Algorithm\n";
        cout << "2. Prim's Algorithm\n";
        cout << "Enter your choice (0 to exit): ";
        cin >> choice;

        switch (choice) {
            case 1:
                graph.kruskalMST();
                break;
            case 2:
                graph.primMST();
                break;
            case 0:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
