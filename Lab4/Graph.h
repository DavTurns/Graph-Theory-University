#include <vector>
#include <string>

using namespace std;

struct Node {
    int info;
    vector<Node *> adjacent_node_list;
};

class Graph {

private:
    int node_count;
    int edge_count;

    vector<Node *> nodelist;

    void preorder_help_function(Node *current_node, vector<int> &parent);

public:

    Graph(string);

    bool isBinaryTree();

    int special_BFS();

    void addEdge(int x, int y);

    int max_degree();

    void print_preorder();
};

/*

011
101
110

{{0,1,1},{1,0,1},{1,1,0}}

{{1,2},{0,2,{0,1}}



*/