#include <string>
#include "Graph.h"

using namespace std;

const string FILE_PATH = "./data.in";

int main() {

    Graph g1(FILE_PATH);
    g1.minimalerSpannbaum();
    system("pause");
    return 0;
}

