#include "reductions.h"

//Function to reduce SAT to 3-SAT
SAT sattothreesat(SAT sat) {

    //Get the clauses and the total variables from the SAT object
    std::vector<std::vector<int>> clauseArray = sat.getClauses();
    int lastVariable = sat.getVariables();

    //Iterate through the array of clauses and if they are longer than 3, split them into two smaller clauses
    for (int i = 0; i < clauseArray.size(); i++) {

        if (clauseArray[i].size() > 3) {

            //Add to the variable count and make a vector to store the new clause
            lastVariable++;
            std::vector<int> newClause;
            newClause.reserve(clauseArray[i].size() - 1);

            //Add the negative of the new variable to the new clause
            newClause.push_back((-1)*lastVariable);

            //Add all terms from the old clause to the new clause, starting at the third term
            for (int j = 2; j < clauseArray[i].size(); j++) {

                newClause.push_back(clauseArray[i][j]);
            }

            //Add the new clause to te list of clauses and edit the old clause appropriately
            clauseArray.push_back(newClause);
            clauseArray[i][2] = lastVariable;
            clauseArray[i].erase(clauseArray[i].begin() + 3, clauseArray[i].end());
        }
    }

    //Set the updated SAT values and return it
    sat.setClauses(clauseArray);
    sat.setVariables(lastVariable);

    return sat;
}

//Function to reduce COL to SAT
SAT coltosat(COL col) {

    //Init a SAT object to store the result
    SAT sat;

    //Get the edges colours and nodes from the COL object
    std::set<std::pair<int, int>> edges = col.getEdges();
    int colours = col.getColours();
    int nodes = col.getNodes();

    //The number of variables for the SAT and the number of pairs of colours
    int variables = colours * nodes;
    unsigned long colourPairNo = binCoeff(colours, 2);

    //The number of clauses required for each section of the reduction
    unsigned long ALONo = nodes;
    unsigned long AMONo = nodes * colourPairNo;
    unsigned long edgeNo = edges.size() * colours;
    unsigned long clauseNo =  ALONo + AMONo + edgeNo;

    //Init the vector to store the clauses
    std::vector<std::vector<int>> clauseArray;
    clauseArray.reserve(clauseNo);

    //Fill the ALO clauses
    std::vector<int> newClause(colours);
    for (int i = 0; i < ALONo; i++) {

        for (int j = 0; j < colours; j++) {

            newClause[j] = i * colours + j + 1;
        }
        clauseArray.push_back(newClause);
    }

    //Fill the AMO clauses
    newClause.resize(2);
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < colours; j++) {
            for (int k = j + 1; k < colours; k++) {

                newClause[0] = -1*(i * colours + j + 1);
                newClause[1] = -1*(i * colours + k + 1);
                clauseArray.push_back(newClause);
            }
        }
    }

    //Fill the edge clauses
    int i = 0;
    for (std::pair<int, int> edge: edges) {

        for (int j = 0; j < colours; j++) {

            //Subtract one from each edge to make it an index
            newClause[0] = -1*((edge.first - 1) * colours + j + 1);
            newClause[1] = -1*((edge.second - 1) * colours + j + 1);

            clauseArray.push_back(newClause);
        }
        i++;
    }

    //Fill and return the SAT object
    sat.setVariables(variables);
    sat.setClauses(clauseArray);

    return sat;
}

//Function to reduce 3-SAT to COL
COL threesattocol(SAT sat) {

    //Init a COL object for the result
    COL col;

    //Get the clauses from the SAT object and check the SAT is a 3-SAT
    std::vector<std::vector<int>> clauseArray = sat.getClauses();
    for (std::vector<int> clause: clauseArray) {

        if (clause.size() > 3) {
            returnProgram(1);
        }
    }

    //Get the variables and ensure there is 4
    int variables = sat.getVariables();
    variables = variables <= 3 ? 4: variables;

    //Set the total nodes and init a vector to store the edges
    //The nodes are ordered (0-variables:xi, variables-2*variables:not xi, 2*variables-3*variables: yi, 3*variables-(3*variables + colours): Ci)
    int nodes = 3 * variables + clauseArray.size();
    std::set<std::pair<int, int>> edgesSet;

    //Join all xi to not xi
    for (int i = 0; i < variables; i++) {

        edgesSet.insert(std::pair<int, int>(i + 1, i + variables + 1));
    }

    //Join yi to every other yj and yi to each xj and not xj
    for (int i = 0; i < variables; i++) {
        for (int j = 0; j < variables; j++) {

            if (j > i) {
                edgesSet.insert(std::pair<int, int>(i + 2*variables + 1, j + 2*variables + 1));
            }

            if (i != j) {
                edgesSet.insert(std::pair<int, int>(i + 2*variables + 1, j + 1));
                edgesSet.insert(std::pair<int, int>(i + 2*variables + 1, j + variables + 1));
            }
        }
    }

    //Join Ci to each xj and not xj that isn't in clause i
    for (int i = 0; i < clauseArray.size(); i++) {
        for (int j = 0; j < variables; j++) {

            if (std::find(clauseArray[i].begin(), clauseArray[i].end(), j) == clauseArray[i].end()) {
                edgesSet.insert(std::pair<int, int>(i + 3*variables + 1, j + 1));
            }
            if (std::find(clauseArray[i].begin(), clauseArray[i].end(), (-1)*j) == clauseArray[i].end()) {
                edgesSet.insert(std::pair<int, int>(i + 3*variables + 1, j + variables + 1));
            }
        }
    }

    //Fill the COL object and return it
    col.setEdges(edgesSet);
    col.setNodes(nodes);
    col.setColours(variables + 1);

    return col;
}

//Function to generate a binomial coefficient, (n choose r)
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

//Return the program with an error code and print it
void returnProgram(int returnVal) {

    std::cerr << "Exit with value: " << returnVal << std::endl;
    exit(returnVal);
}
