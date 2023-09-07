#include "Graph.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

Graph::Graph(string datei) {

    ifstream file(datei);
    if (!file) { // file couldn't be opened
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
    string zeile;

    edgecount = 0;
    nodecount = 0;

    while (getline(file, zeile)) {
        stringstream ss(zeile);
        string knoten1, knoten2;
        string gewicht_als_string;
        ss >> knoten1 >> knoten2 >> gewicht_als_string;
        int gewicht = stoi(gewicht_als_string);

        auto it = find_if(edgelist.begin(), edgelist.end(),
                          [knoten1](Edge knoten) { return (knoten1 == knoten.n1 or knoten1 == knoten.n2); });
        if (it == edgelist.end()) {
            nodelist.push_back(knoten1);
            nodecount++;
        }
        it = find_if(edgelist.begin(), edgelist.end(),
                     [knoten2](Edge knoten) { return (knoten2 == knoten.n1 or knoten2 == knoten.n2); });
        if (it == edgelist.end()) {
            nodelist.push_back(knoten2);
            nodecount++;
        }


        //NEUE KANTE MACHEN
        Edge newedge;
        newedge.n1 = knoten1;
        newedge.n2 = knoten2;
        newedge.gewicht = gewicht;
        edgelist.push_back(newedge);
        edgecount++;
    }
}

void Graph::minimalerSpannbaum() {

    //remove all loops
    vector<Edge> edgelist_edited;
    for (auto edge: edgelist) {
        if (edge.n1 != edge.n2)
            edgelist_edited.push_back(edge);
    }

    vector<string> nodelist_added;
    vector<Edge> edgelist_added;
    sort(edgelist_edited.begin(), edgelist_edited.end(),
         [](Edge edge1, Edge edge2) { return edge1.gewicht < edge2.gewicht; });
    nodelist_added.push_back(edgelist_edited[0].n1);
    Edge aktuelle_kante;

    while (nodelist_added.size() != nodecount) {
        //add edge with minimal weight which doesn't create a cycle

        for (int i = 0; i < edgecount; i++) {
            aktuelle_kante = edgelist_edited[i];
            int count_knoten_in_liste = 0;
            bool n1_in = false;
            bool n2_in = false;

            auto it = find(nodelist_added.begin(), nodelist_added.end(), aktuelle_kante.n1);

            if (it != nodelist_added.end()) {
                n1_in = true;
                count_knoten_in_liste++;
            }

            it = find(nodelist_added.begin(), nodelist_added.end(), aktuelle_kante.n2);
            if (it != nodelist_added.end()) {
                n2_in = true;
                count_knoten_in_liste++;
            }

            if (count_knoten_in_liste == 1) {
                edgelist_added.push_back(aktuelle_kante);
                if (!n1_in) nodelist_added.push_back(aktuelle_kante.n1);
                if (!n2_in) nodelist_added.push_back(aktuelle_kante.n2);
            }
        }
    }

    for (int i = 0; i < edgelist_added.size(); i++) {
        cout << "\n" << edgelist_added[i].n1 << " " << edgelist_added[i].n2 << " " << edgelist_added[i].gewicht;
    }
}