#include "reductions.h"

//Function to reuce a COL problem to a COL problem through SAT and 3-SAT
int main(int argc, char const *argv[]) {

    COL col = parseCOL();

    //store the staring nodes, edges and colours
    int startNodes = col.getNodes();
    int startEdges = col.getEdges().size();
    int startColours = col.getColours();

    col = threesattocol(sattothreesat(coltosat(col)));

    //If test is specified, only print the key values
    if (argc > 1 && std::string(argv[1]) == "Test") {

        std::cout << "Start Nodes, Start Edges, Start Colours, Nodes, Edges, Colours" << std::endl;
        std::cout << startNodes << ", " << startEdges << ", " << startColours << ", " << col.getNodes() << ", " << col.getEdges().size() << ", " << col.getColours() << std::endl;
    } else {

        printCOL(col);
    }

    return 0;
}
