#include <vector>
#include <string>

using namespace std;

class Graph {
private:
    int node_count;
    int edge_count;
    int matrix[100][100];
    vector<int> adjazenzliste[10];

public:

    Graph(string);

    Graph();

    Graph(Graph &g);

    void addEdge(int x, int y);

    bool isEdge(int x, int y);

    void printGraph();

    void generateAdjazenzliste();

    void printAdjazenzliste();

    void printPfad(int, int);

};
