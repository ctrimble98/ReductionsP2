#include "reductions.h"

SAT sattothreesat(SAT sat) {

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

    return sat;
}

SAT coltosat(COL col) {

    SAT sat;

    std::set<std::pair<int, int>> edges = col.getEdges();
    int colours = col.getColours();
    int nodes = col.getNodes();

    int variables = colours * nodes;
    unsigned long colourPairNo = binCoeff(colours, 2);
    unsigned long ALONo = nodes;
    unsigned long AMONo = nodes * colourPairNo;
    unsigned long edgeNo = edges.size() * colours;
    unsigned long clauseNo =  ALONo + AMONo + edgeNo;
    std::vector<std::vector<int>> clauseArray;
    clauseArray.reserve(clauseNo);

    unsigned long currentClause = 0;

    std::vector<int> newClause(colours);
    for (int i = 0; i < ALONo; i++) {

        for (int j = 0; j < colours; j++) {

            newClause[j] = i * colours + j + 1;
        }
        //clauseArray[i] = newClause;
        clauseArray.push_back(newClause);
        currentClause++;
        // newClause.clear();
    }

    // std::cout << currentClause << '\n';

    newClause.resize(2);
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < colours; j++) {
            for (int k = j + 1; k < colours; k++) {

                newClause[0] = -1*(i * colours + j + 1);
                newClause[1] = -1*(i * colours + k + 1);
                //clauseArray[ALONo + i * colourPairNo + j] = newClause;
                clauseArray.push_back(newClause);
                currentClause++;
                // newClause.clear();
            }
        }
    }

    // std::cout << currentClause << '\n';

    int i = 0;
    for (std::pair<int, int> edge: edges) {

        for (int j = 0; j < colours; j++) {

            //Subtract one from each edge to make it an index
            newClause[0] = -1*((edge.first - 1) * colours + j + 1);
            newClause[1] = -1*((edge.second - 1) * colours + j + 1);
            //clauseArray[ALONo + AMONo + ] = newClause;
            clauseArray.push_back(newClause);
            currentClause++;
            // newClause.clear();
        }
        i++;
    }

    // std::cout << currentClause << '\n';

    sat.setVariables(variables);
    sat.setClauses(clauseArray);

    return sat;
}

COL threesattocol(SAT sat) {

    COL col;

    std::vector<std::vector<int>> clauseArray = sat.getClauses();
    int variables = sat.getVariables();

    variables = variables <= 3 ? 4: variables;

    int nodes = 3 * variables + clauseArray.size();

    std::set<std::pair<int, int>> edgesSet;

    //Reserve all but edges invloving Ci
    //edgesSet.reserve(variables + (variables * variables - variables) + 2 * (variables * variables - variables));

    int currentEdge = 0;

    for (int i = 0; i < variables; i++) {

        edgesSet.insert(std::pair<int, int>(i + 1, i + variables + 1));
        currentEdge++;
    }

    for (int i = 0; i < variables; i++) {
        for (int j = 0; j < variables; j++) {

            if (i != j) {
                edgesSet.insert(std::pair<int, int>(i + 2*variables + 1, j + 2*variables + 1));
                currentEdge++;
            }
        }
    }

    for (int i = 0; i < variables; i++) {
        for (int j = 0; j < variables; j++) {

            if (i != j) {
                edgesSet.insert(std::pair<int, int>(i + 2*variables + 1, j + 1));
                edgesSet.insert(std::pair<int, int>(i + 2*variables + 1, j + variables + 1));
                currentEdge += 2;
            }
        }
    }

    for (int i = 0; i < clauseArray.size(); i++) {
        for (int j = 0; j < variables; j++) {
            if (std::find(clauseArray[i].begin(), clauseArray[i].end(), j) == clauseArray[i].end()) {
                edgesSet.insert(std::pair<int, int>(i + 3*variables + 1, j + 1));
                currentEdge++;
            }
            if (std::find(clauseArray[i].begin(), clauseArray[i].end(), (-1)*j) == clauseArray[i].end()) {
                edgesSet.insert(std::pair<int, int>(i + 3*variables + 1, j + variables + 1));
                currentEdge++;
            }
        }
    }

    std::cout << currentEdge << '\n';

    col.setEdges(edgesSet);
    col.setNodes(nodes);
    col.setColours(variables + 1);

    return col;
}

unsigned long binCoeff(int n, int r) {

    unsigned long num = 1;
    for (int i = r + 1; i <= n; i++) {
        num *= i;
    }

    unsigned long denom = 1;
    for (int i = 1; i <= n - r; i++) {
        denom *= i;
    }

    return num/denom;
}

void returnProgram(int returnVal) {

    std::cout << "Exit with value: " << returnVal << std::endl;
    exit(returnVal);
}
