#include "reductions.h"

void printSAT(SAT sat) {

    std::vector<std::vector<int>> clauseArray = sat.getClauses();

    std::cout << "p CNF " << sat.getVariables() << " " << clauseArray.size() << std::endl;

    for (int i = 0; i < clauseArray.size(); i++) {
        for (int j = 0; j < clauseArray[i].size(); j++) {

            std::cout << clauseArray[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void printCOL(COL col) {

    std::set<std::pair<int, int>> edges = col.getEdges();

    std::cout << "p edge " << col.getNodes() << " " << edges.size() << std::endl;

    for (std::pair<int, int> p: edges) {

        std::cout << "e " << p.first << " " << p.second << std::endl;
    }
}
