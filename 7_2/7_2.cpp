//
//  main.cpp
//  Kruskal's Algorithm with Graph Visualization
//
//  Created by Himanshu on 28/05/23.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdlib> // For system() function
#include <limits>
using namespace std;

// Data structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
    
    // Constructor to adjust user input (1-based index) to internal representation (0-based index)
    Edge(int s, int d, int w) : src(s - 1), dest(d - 1), weight(w) {}
};

// Comparator function to sort edges based on their weights
bool compareEdges(const Edge& e1, const Edge& e2) {
    return e1.weight < e2.weight;
}

// Utility function for finding id of DSU (Disjoint Set Union) member
int getRoot(int i, int id[]) {
    while (i != id[i]) {
        i = id[i];
    }
    return i;
}

// Connected operation of DSU (Disjoint Set Union) data structure
bool connected(int p, int q, int id[]) {
    return (getRoot(p, id) == getRoot(q, id));
}

// Union operation of DSU
void unionSet(int p, int q, int *id) {
    int i = getRoot(p, id);
    int j = getRoot(q, id);
    id[i] = j;
}

// Kruskal's algorithm for finding MST
vector<Edge> kruskalMST(vector<Edge>& edges, int V) {
    vector<Edge> MST; // to store the MST
    int *id = new int[V];
    for (int i = 0; i < V; i++) {
        id[i] = i;
    }

    // Sort the edges based on their weights
    sort(edges.begin(), edges.end(), compareEdges);

    int count = 0;
    int i = 0;
    while (count < V - 1 && i < edges.size()) {
        int src = edges[i].src;
        int dest = edges[i].dest;

        // Check if adding the current edge forms a cycle
        if (!connected(src, dest, id)) {
            MST.push_back(edges[i]);
            unionSet(src, dest, id);
            count++;
        }
        i++;
    }

    delete[] id;
    return MST;
}


// Function to generate a DOT file for the graph and create an image
void generateGraphPNG(const vector<Edge>& edges, const string& filename) {
    string dotFileName = filename + ".dot";
    string outputImageFileName = filename + ".png";
    ofstream file(dotFileName);
    
    // Write the header for the DOT file
    file << "graph G {" << endl;

    // Set default node attributes (e.g., make all nodes circles)
    file << "    node [shape=circle];" << endl;

    for (const auto& edge : edges) {
        // Adding 1 back to src and dest for DOT output
        file << "    " << edge.src + 1 << " -- " << edge.dest + 1 
             << " [label=" << edge.weight << "];" << endl;
    }
    
    file << "}" << endl;
    file.close();

    // Automatically generate an image from the DOT file
    string command = "dot -Tpng " + dotFileName + " -o " + outputImageFileName;
    system(command.c_str());
    cout << "Graph image generated: " << outputImageFileName << endl;

    string removeCommand = "del " + dotFileName;
    system(removeCommand.c_str());

}

// Utility function for correctly clearing input stream
void clearCin()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getNumberOfVertices() 
{
    int numV;
    while(true)
    {
        cout << "Enter the number of vertices: ";

        if (cin >> numV && numV > 0) {
            clearCin();
            return numV;
        }
        clearCin();
        cout << "Invalid Input. Number of vertices should be a positive integer\n";
    }
}

int getNumberOfEdges(int numV)
{
    int numE;
    while(true)
    {
        cout << "Enter the number of edges: ";

        if (cin >> numE && numE >= numV - 1)
        {
            clearCin();
            return numE;
        }
        clearCin();
        cout << "Invalid Input. Number of edges should be greater or equal to the number of vertices - 1\n";
    }

}

bool askIfUseExampleGraph()
{
    char choice;
    while (true)
    {
        cout << "Do you want to perform operations on an example graph [Y] or create your own [N]? ";
        cin >> choice;

        // Convert choice to lower case for easier comparison
        choice = tolower(choice);

        if (choice == 'y')
        {
            return true; 
        }
        else if (choice == 'n')
        {
            return false; 
        }
        else
        {
            clearCin(); // Clear the input buffer
            cout << "Invalid input. Please enter 'Y' or 'N'.\n";
        }
    }
}

int main() {
    bool isOnExampleGraph = askIfUseExampleGraph();
    int numV;
    int numE;
    vector<Edge> edges;
    if (isOnExampleGraph) 
    {
        // Example Graph
        numV = 5;
        numE = 8;
        edges.emplace_back(1, 2, 1);
        edges.emplace_back(1, 5, 10);
        edges.emplace_back(1, 3, 2);
        edges.emplace_back(2, 5, 6);
        edges.emplace_back(2, 4, 3);
        edges.emplace_back(5, 4, 11);
        edges.emplace_back(5, 3, 7);
        edges.emplace_back(4, 3, 4);
    }
    else 
    {
        numV = getNumberOfVertices();
        numE = getNumberOfEdges(numV);

        for (int i = 0; i < numE; i++) 
        {
            int src, dest, weight;
            cout << "Enter source, destination, and weight for edge " << i + 1 << ": ";
            cin >> src >> dest >> weight;
            edges.push_back({src, dest, weight});
        }
    }



    // Generate DOT file and image
    generateGraphPNG(edges, "graph");

    // Find MST using Kruskal's algorithm
    vector<Edge> MST = kruskalMST(edges, numV);

    generateGraphPNG(MST, "MST");

    return 0;
}
