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