//
// Created by Latitude on 13.05.2023.
//

#ifndef UNTITLED_GRAPH_H
#define UNTITLED_GRAPH_H
#define INFINITY 9999

#include <string>
#include <map>
#include <vector>

using namespace std;

struct Edge {
    string n1;
    string n2;
    int gewicht;
};

class Graph {

public:
    Graph(string datei);

    int nodecount;
    int edgecount;
    vector<string> nodelist;
    vector<Edge> edgelist;

    void minimalerSpannbaum();

    bool compareEdges(const Edge &edge1, const Edge &edge2);
};


#endif //UNTITLED_GRAPH_H
