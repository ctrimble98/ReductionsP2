#include "reductions.h"

SAT parseCNF() {

    // istream* reader = cin;

    //Read line until start with p -> read chars no whitespace or \n until 0 for each clause

    std::string headerLine, token;
    bool isPreamble = true;
    bool comments = true;
    char lineType;
    char delim = ' ';

    int variables, clauses, iter;

    std::stringstream iss;

    while (isPreamble && std::getline(std::cin, headerLine)) {

        if (headerLine.length() > 1)  {
            lineType = headerLine[0];
            std::cout << lineType << std::endl;
            switch (lineType) {
                case 'c':
                    break;
                case 'p':

                    iter = 0;
                    iss.clear();
                    iss << headerLine;
                    while (std::getline(iss, token, delim)) {

                        std::cout << "Problem token: |" << token << "|" << std::endl;

                        switch (iter) {

                            case 0:

                                if (token != "p") {
                                    returnProgram(1);
                                }
                                break;
                            case 1:

                                if (token != "cnf") {
                                    returnProgram(1);
                                }
                                break;
                            case 2:

                                try {

                                    variables = std::stoi(token);
                                } catch (std::invalid_argument) {

                                    std::cout << "variables failed: " << token << std::endl;
                                    returnProgram(1);
                                }
                                break;
                            case 3:

                                try {

                                    clauses = std::stoi(token);
                                } catch (std::invalid_argument) {

                                    std::cout << "clauses failed: " << token << std::endl;
                                    returnProgram(1);
                                }
                                break;
                            default:
                                returnProgram(1);
                        }
                        iter++;
                    }
                    isPreamble = false;
                    break;

                default:
                    returnProgram(1);
            }
        }
    }
    std::cout << clauses << " " << variables << std::endl;

    std::string tempString;
    std::vector<std::vector<int>> clauseArray(clauses);
    std::vector<int> currentClause;
    int var, i;
    i = 0;
    // j = 0;
    while (std::getline(std::cin, tempString)) {

        std::cout << "Line: " << tempString << std::endl;

        iss.clear();
        iss << tempString;
        std::cout << "Token: " << token << std::endl;

        while (std::getline(iss, token, ' ')) {

            std::cout << "Clause tok: " << token << std::endl;

            try {
                // std::cout << "i=" << i << "j=" << j << std::endl;
                var = std::stoi(token);
                if (var > variables || (var*-1) > variables) {
                    std::cout << "var to large: " << var << std::endl;
                    returnProgram(1);
                }
                if (var == 0) {


                    if (i >= clauses) {
                        returnProgram(1);
                    }
                    clauseArray[i] = currentClause;
                    currentClause.clear();
                    i++;
                    // j = 0;
                }
                else {

                    // if (j < DEF_MAX_CLAUSE) {
                    //     currentClause[j] = var;
                    // } else {

                        currentClause.push_back(var);
                    // }
                    // j++;
                }
                std::cout << "Clause var: " << var << ":" << currentClause[0] << currentClause[1] << currentClause[2] << std::endl;
            } catch (std::invalid_argument) {

                std::cout << "Parsing clauses failed on: " << token << std::endl;
                returnProgram(1);
            }
        }
    }

    std::cout << "CC" << currentClause[0] << std::endl;
    if (currentClause.size() > 0) {
        if (i >= clauses) {
            returnProgram(1);
        }
        clauseArray[i] = currentClause;
    }

    SAT sat;

    sat.setVariables(variables);
    sat.setClauses(clauseArray);

    printSAT(sat);

    return sat;
}
