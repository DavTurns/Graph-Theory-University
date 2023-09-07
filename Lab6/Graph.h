#ifndef LAB6_GRAPH_H
#define LAB6_GRAPH_H

#include <string>
#include <vector>


using namespace std;

struct Edge {
    string node1, node2;
};

class Graph {
private:
    vector<string> nodes;
    vector<Edge> edges;
    int node_count;
    int edge_count;

    bool every_node_has_even_degree();

    bool has_multiple_conex_components();

public:

    Graph(string);

    void printEulerianCycle(string);
};


#endif //LAB6_GRAPH_H
