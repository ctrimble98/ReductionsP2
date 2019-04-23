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

COL parseCOL() {

    int targetType = 0;
    int iter, nodes, edgesNo, colours;
    std::set<std::pair<int, int>> edgesSet;
    std::string line, token, lineType;
    std::stringstream iss;
    bool comment;
    int start, dest, edgesFound;
    start = 0;
    dest = 0;
    edgesFound = 0;

    while(std::getline(std::cin, line)) {

        iter = 0;
        iss.clear();
        iss << line;

        comment = false;
        while (std::getline(iss, token, ' ')) {

            if (!comment) {
                try {

                    if (token == "c") {
                        comment = true;
                    } else {

                        switch (targetType) {
                            case 0:
                                switch (iter) {

                                    case 0:
                                        if (token != "p") {
                                            returnProgram(1);
                                        }
                                        break;
                                    case 1:
                                        if (token != "edge") {
                                            returnProgram(1);
                                        }
                                        break;
                                    case 2:
                                        nodes = stoi(token);
                                        break;
                                    case 3:
                                        edgesNo = stoi(token);
                                        targetType++;
                                        iter = 0;
                                        break;
                                    default:
                                        returnProgram(1);
                                }
                                break;
                            case 1:
                                switch (iter) {

                                    case 0:
                                        if (token != "colours") {
                                            returnProgram(1);
                                        }
                                        break;
                                    case 1:
                                        colours = stoi(token);
                                        targetType++;
                                        iter = 0;
                                        break;
                                    default:
                                        returnProgram(1);
                                }
                                break;
                            case 2:
                                switch (iter) {

                                    case 0:
                                        if (token != "e") {
                                            returnProgram(1);
                                        }
                                        break;
                                    case 1:
                                        start = stoi(token);
                                        if (start < 0 || start > nodes) {
                                            returnProgram(1);
                                        }
                                        break;
                                    case 2:

                                        dest = stoi(token);
                                        bool result;
                                        if (start < dest) {
                                            result = edgesSet.insert(std::pair<int, int>(start, dest)).second;
                                        } else {
                                            result = edgesSet.insert(std::pair<int, int>(dest, start)).second;
                                        }
                                        edgesFound++;

                                        if (!result || edgesFound > edgesNo) {
                                            returnProgram(1);
                                        }
                                        iter = 0;
                                        break;
                                    default:
                                        returnProgram(1);
                                }
                                break;
                        }
                    }
                    iter++;
                } catch (std::invalid_argument) {

                    returnProgram(1);
                }
            }
        }
    }

    //TODO check edge number

    if (edgesFound != edgesNo) {
        returnProgram(1);
    }

    COL col;

    col.setNodes(nodes);
    col.setColours(colours);
    col.setEdges(edgesSet);

    return col;
}
