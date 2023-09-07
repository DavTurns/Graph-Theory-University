#include "Graph.h"
#include <iostream>
#include <fstream>
#include <list>
#include <vector>

using namespace std;

const string FILE_PATH = "./liste1.txt";

int main() {

    //IMPORTANT THE NODENAMES HAVE TO BE 0, 1, 2, ...
    Graph g(FILE_PATH);

    cout << "is binary: " << g.isBinaryTree();

    g.print_preorder();
    return 0;
}