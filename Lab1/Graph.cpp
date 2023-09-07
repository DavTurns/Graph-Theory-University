#include "Graph.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <list>

using namespace std;

Graph::Graph(string file_path) {

    ifstream f;
    int x, y;

    f.open(file_path);
    cout << filesystem::current_path() << endl;
    if (!f) { // file couldn't be opened
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
    f >> node_count;
    f >> edge_count;


    //generate Matrix
    for (int i = 0; i < edge_count; i++) {
        f >> x >> y;
        addEdge(x, y);
    }

    //generate Nodelist
    for (int i = 0; i < edge_count; i++) {
        f >> x >> y;
        pair<int, int> temp;
        temp.first = x;
        temp.second = y;
        kantenliste.push_back(temp);
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
    cout << "\nMatrix is:\n";
    for (int i = 0; i < node_count; i++) {
        for (int j = 0; j < node_count; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph::generateAdjazenzliste() {

    for (int i = 0; i < node_count; i++) {
        vector<int> aktueller_knoten;

        for (int j = 0; j < node_count; j++) {
            if (matrix[i][j] == 1) {
                aktueller_knoten.push_back(j);
            }
        }
        adjazenzliste.push_back(aktueller_knoten);
    }
}

void Graph::printAdjazenzliste() {
    cout << "\nAdjacency list is: ";
    for (int i = 0; i < edge_count; i++) {
        cout << "\n" << i << " :[ ";

        for (int j = 0; j < adjazenzliste[i].size(); j++) {
            cout << adjazenzliste[i][j] << " ";
        }
        cout << "]";
    }
    cout << "\n";
}

int Graph::maximalerGrad() {
    int maxGrad = 0;
    int aktuellerKnotenGrad;

    for (int i = 0; i < edge_count; i++) {
        aktuellerKnotenGrad = adjazenzliste[i].size();
        if (aktuellerKnotenGrad > maxGrad)
            maxGrad = aktuellerKnotenGrad;
    }
    return maxGrad;
}

int Graph::minimalerGrad() {
    int minGrad = edge_count - 1;
    int aktuellerKnotenGrad;

    for (int i = 0; i < edge_count; i++) {
        aktuellerKnotenGrad = adjazenzliste[i].size();
        if (aktuellerKnotenGrad < minGrad)
            minGrad = aktuellerKnotenGrad;
    }
    return minGrad;
}
