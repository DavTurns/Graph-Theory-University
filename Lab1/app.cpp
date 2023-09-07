#include "Graph.h"
#include <iostream>

using namespace std;

const string FILE_PATH = ".//data.in";

int main() {

    Graph g(FILE_PATH);
    g.printGraph();
    g.generateAdjazenzliste();
    g.printAdjazenzliste();
    cout << "\nmax_degree is: " << g.maximalerGrad() << "\n";
    cout << "min_degree is: " << g.minimalerGrad() << "\n";
    system("pause");
}