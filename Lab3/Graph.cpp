#include "Graph.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <list>
#include <queue>

using namespace std;

void Graph::BFS(int x, bool *liste_schonbesuchte_knoten_zhgskomponente) {
    //bool *liste_schonbesuchte_knoten_zhgskomponente is an array of bools,
    // which mark the node on index i with true or false as visited, is only to not print the same conexcomponents
    // multiple times
    bool no_visited_nodes_parameter = false;
    if(liste_schonbesuchte_knoten_zhgskomponente == nullptr) {
        liste_schonbesuchte_knoten_zhgskomponente = new bool[node_count];
        no_visited_nodes_parameter = true;
    }
    vector<int> besuchteknoten;
    queue<int> queue;

    besuchteknoten.push_back(x);
    liste_schonbesuchte_knoten_zhgskomponente[x] = true;
    queue.push(x);

    cout << "\nBFS: ";

    while (!queue.empty()) {
        int aktuellerknoten = queue.front();
        cout << aktuellerknoten << " ";
        queue.pop();

        int adjazenzliste_size = adjazenzliste[aktuellerknoten].size();

        for (int i = 0; i < adjazenzliste_size; ++i) {

            int aktuellerknoten_in_adjazenzliste_von_knoten = adjazenzliste[aktuellerknoten][i];
            bool schonbesucht = false;

            for (int j = 0; j < besuchteknoten.size(); j++) {
                if (besuchteknoten[j] == aktuellerknoten_in_adjazenzliste_von_knoten) {
                    schonbesucht = true;
                    break;
                }
            }
            if (!schonbesucht) {
                queue.push(aktuellerknoten_in_adjazenzliste_von_knoten);
                besuchteknoten.push_back(aktuellerknoten_in_adjazenzliste_von_knoten);
                liste_schonbesuchte_knoten_zhgskomponente[aktuellerknoten_in_adjazenzliste_von_knoten] = true;
            }
        }
    }
    if(no_visited_nodes_parameter) delete[] liste_schonbesuchte_knoten_zhgskomponente;
}

void Graph::printConexComponent() {

    cout << "\nHere are all ConexComponents:\n";

    //bool *liste_mit_schon_besuchten_knoten is an array of bools,
    // which mark the node on index i with true or false as visited, is only to not print the same conexcomponents
    // multiple times
    bool *liste_mit_schon_besuchten_knoten = new bool[node_count];

    for (int i = 0; i < node_count; i++) {

        if (!liste_mit_schon_besuchten_knoten[i]) {
            BFS(i, liste_mit_schon_besuchten_knoten);
            cout << endl;
        }
    }
}

Graph::Graph(string datei) {
    ifstream in(datei);
    in >> node_count;
    for (int i = 0; i < node_count; i++) {
        for (int j = 0; j < node_count; j++) {
            in >> matrix[i][j];
        }
    }
    in.close();
    generateAdjazenzliste();
}

void Graph::addEdge(int x, int y) {
    matrix[x][y] = 1;
    matrix[y][x] = 1;
}

bool Graph::isEdge(int x, int y) {
    return matrix[x][y] == 1;
}

void Graph::printGraph() {
    cout << "\nMatrix is: \n";
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
    cout << "\n";
}
