#include "Graph.h"
#include <string>

const std::string FILE_PATH = "./Land2.txt";

int main() {
    Graph g(FILE_PATH);
    g.printEulerianCycle("Sibiu");
    system("pause");
    return 0;
}
