#include <vector>
#include <string>

using namespace std;

class Graph {

private:
    int node_count;
    int edge_count;
    int matrix[100][100];
    vector<pair<int, int>> kantenliste;
    vector<vector<int>> adjazenzliste;

public:

    Graph(string);

    void addEdge(int x, int y);

    bool isEdge(int x, int y);

    void printGraph();

    void generateAdjazenzliste();

    void printAdjazenzliste();

    int maximalerGrad();

    int minimalerGrad();

};