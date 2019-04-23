#include "reductions.h"

int main(int argc, char const *argv[]) {

    COL col = parseCOL();

    //printCOL(col);

    col = threesattocol(sattothreesat(coltosat(col)));

    //printCOL(col);
    std::cout << "Nodes, Edges, Colours" << std::endl;
    std::cout << col.getNodes() << ", " << col.getEdges().size() << ", " << col.getColours() << std::endl;

    return 0;
}
