#include "Graph.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

Graph::Graph() {
    node_count = 0;
    edge_count = 0;
}

Graph::Graph(Graph &g) {
    node_count = g.node_count;
    edge_count = g.edge_count;
    for (int i = 0; i < node_count; i++) {
        for (int j = 0; j < node_count; j++) {
            if (g.matrix[i][j] == 1) {
                matrix[i][j] = 1;
            }
        }
    }
}

Graph::Graph(string datei) {

    ifstream f;
    f.open(datei);
    //cout << filesystem::current_path() << endl;
    if (!f) { // file couldn't be opened
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }

    f >> node_count;
    f >> edge_count;
    int x, y;
    for (int i = 0; i < edge_count; i++) {
        f >> x >> y;
        addEdge(x, y);
    }
}

void Graph::addEdge(int x, int y) {
    matrix[x][y] = 1;
    matrix[y][x] = 1;
}

bool Graph::isEdge(int x, int y) {
    return matrix[x][y] == 1;
}

void Graph::printGraph() {
    cout << "\nMatrix is:";
    for (int i = 0; i < node_count; i++) {
        for (int j = 0; j < node_count; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph::generateAdjazenzliste() {
    cout << "adjlist:\n";
    for (int i = 0; i < node_count; i++) {
        vector<int> aktueller_knoten;

        for (int j = 0; j < node_count; j++) {
            if (matrix[i][j] == 1) {
                aktueller_knoten.push_back(j);
            }
        }
        adjazenzliste[i] = aktueller_knoten;
    }
}

void Graph::printAdjazenzliste() {
    cout << "\nAdjacency list is: ";
    for (int i = 0; i < node_count; i++) {

        cout << "\n" << i << " :[ ";

        for (int j = 0; j < adjazenzliste[i].size(); j++) {
            cout << adjazenzliste[i][j] << " ";
        }
        cout << "]";
    }
    cout <<"\n";
}

void Graph::printPfad(int anfang, int ende) {
    bool pfadgefunden = false;
    int größe_liste_anfangknoten = adjazenzliste[anfang].size();

    for (int i = 0; i < größe_liste_anfangknoten; i++) {
        int nächsterknoten = adjazenzliste[anfang][i];
        for (int j = 0; j < adjazenzliste[nächsterknoten].size(); j++) {
            if (adjazenzliste[nächsterknoten][j] == ende) {
                cout << "\nPfad: " << anfang << "->" << nächsterknoten << "->" << ende;
                pfadgefunden = true;
            }
        }
    }
    if (!pfadgefunden) {
        cout << "Kein Pfad gefunden";
    }
}