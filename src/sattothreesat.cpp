#include "reductions.h"

int main(int argc, char const *argv[]) {

    SAT sat = parseCNF();

    printSAT(sat);
    sattothreesat(sat);

    return 0;
}

void sattothreesat(SAT sat) {

    // int startClauses = clauseArray.size();
    std::vector<std::vector<int>> clauseArray = sat.getClauses();
    int lastVariable = sat.getVariables();

    std::cout << clauseArray.size() << " " << clauseArray[5].size() << std::endl;  
    for (int i = 0; i < clauseArray.size(); i++) {

        if (clauseArray[i].size() > 3) {

            lastVariable++;
            std::vector<int> newClause(clauseArray[i].size() - 1);
            //FIll newClause with old clause minus first 2

            newClause[0] = lastVariable;

            for (int j = 1; j < clauseArray[i].size() - 1; j++) {

                newClause[j] = clauseArray[i][j + 1];
            }

            clauseArray.push_back(newClause);
            //Edit old clause
            clauseArray[i][2] = lastVariable;
            clauseArray[i].erase(clauseArray[i].begin() + 3, clauseArray[i].end());
        }
    }

    sat.setClauses(clauseArray);
    sat.setVariables(lastVariable);

    printSAT(sat);
}

void returnProgram(int returnVal) {

    std::cout << "Exit with value: " << returnVal << std::endl;
    exit(returnVal);
}
