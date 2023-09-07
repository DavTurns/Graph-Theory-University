#include "Graph.h"
#include <iostream>
#include <fstream>
#include <list>
#include <vector>

using namespace std;

const string FILE_PATH = "..//data.in";

int main() {
    Graph g(FILE_PATH);

    g.printGraph();

    g.printAdjazenzliste();

    g.BFS(2);

    g.printConexComponent();

    return 0;
}