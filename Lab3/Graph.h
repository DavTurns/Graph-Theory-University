#include <vector>
#include <string>

using namespace std;

class Graph {
private:
    int m;
    int matrix[100][100];
    vector<int> adjazenzliste[10];

public:
    int node_count;

    void BFS(int, bool * = nullptr);

    void printConexComponent();

    Graph(string);

    Graph();

    Graph(Graph &g);

    void addEdge(int x, int y);

    bool isEdge(int x, int y);

    void printGraph();

    void generateAdjazenzliste();

    void printAdjazenzliste();
};

/*

011
101
110

{{0,1,1},{1,0,1},{1,1,0}}

{{1,2},{0,2,{0,1}}



*/