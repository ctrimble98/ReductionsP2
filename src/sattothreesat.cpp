#include "Reductions.h"

int main(int argc, char const *argv[]) {

    SAT sat;
    parseCNF(sat);
    sattothreesat(sat);

    return 0;
}

void sattothreesat(SAT sat) {

    // int startClauses = clauseArray.size();
    std::vector<std::vector<int>> clauseArray = sat.getClauses();
    int lastVariable = sat.getVariables();
    for (int i = 0; i < clauseArray.size(); i++) {

        if (clauseArray[i].size() > 3) {

            lastVariable++;
            std::vector<int> newClause(clauseArray[i].size() - 1);
            //FIll newClause with old clause minus first 2


            clauseArray.push_back(newClause);
            //Edit old clause
            clauseArray[i][2] = lastVariable;
            clauseArray[i].erase(clauseArray[i].begin() + 3, clauseArray[i].end());
        }
    }
}

void returnProgram(int returnVal) {

    std::cout << "Exit with value: " << returnVal << std::endl;
    exit(returnVal);
}
