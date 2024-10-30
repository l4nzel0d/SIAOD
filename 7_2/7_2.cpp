//
//  main.cpp
//  Kruskal's Algorithm
//
//  Created by Himanshu on 28/05/23.
//
 
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
// Data structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Data structure to represent a graph
struct Graph {
    int numV; // Number of vertices
    int numE; // Number of edges
    vector<Edge> edges; // List of edges
     
    // Constructor
    Graph(int V, int E) : numV(V), numE(E) {}
};

// Comparator function to sort edges based on their weights
bool compareEdges(const Edge& e1, const Edge& e2) {
    return e1.weight < e2.weight;
}

// Utility function for finding id of DSU (Disjoint Set Union) member
int getRoot (int i, int id[]) {
    while (i != id[i]) {
        i = id[i];
    }
    return i;
}
 
// Connected operation of DSU (Disjoint Set Union) data structure
bool connected (int p, int q, int id[]) {
    return (getRoot(p, id) == getRoot(q, id));
}
  
// Union operation of DSU
void unionSet (int p, int q, int *id) {
    int i = getRoot(p, id);
    int j = getRoot(q, id);
    id[i] = j;
}

// Kruskal's algorithm for finding MST
vector<Edge> kruskalMST(Graph& graph) {
    vector<Edge> MST; // to store the MST
     
    int *id = new int[graph.numV];
      
    for (int i = 0; i < graph.numV; i++) {
        id[i] = i;
    }

    // Sort the edges based on their weights
    sort(graph.edges.begin(), graph.edges.end(), compareEdges);

    int count = 0;
    int i = 0;
    while (count < graph.numV - 1 && i < graph.edges.size()) {
        int src = graph.edges[i].src;
        int dest = graph.edges[i].dest;

        // Check if adding the current edge forms a cycle
        if (!connected(src, dest, id)) {
            MST.push_back(graph.edges[i]);
            unionSet(src, dest, id);
            count++;
        }
         
        i++;
    }

    delete[] id;
    return MST;
}

// Function to display the edges of the MST
void displayMST(const vector<Edge>& MST) {
    cout << "Minimum Spanning Tree Edges:" << endl << endl;
    cout << "Edge : Weight" << endl;
    for (const auto& edge : MST) {
        cout << edge.src << " -- " << edge.dest << " : " << edge.weight << endl;
    }
}

int main() {
    int V = 5; // Number of vertices in the graph
    int E = 8; // Number of edges in the graph

    // Create a graph with V vertices and E edges
    Graph graph(V, E);
    graph.edges = {
        {0, 1, 1},
        {0, 2, 2},
        {0, 4, 10},
        {1, 4, 6},
        {1, 3, 3},
        {2, 4, 7},
        {2, 3, 4},
        {3, 4, 11}
    };

    // Find MST using Kruskal's algorithm
    vector<Edge> MST = kruskalMST(graph);

    // Display the MST
    displayMST(MST);

    return 0;
}
