#include "Graph.h"
#include <iostream>

using namespace std;

const string FILE_PATH = ".//data.in";

int main() {

    Graph g(FILE_PATH);
    g.printGraph();
    g.generateAdjazenzliste();
    g.printAdjazenzliste();
    g.printPfad(1, 2);
    return 0;
}