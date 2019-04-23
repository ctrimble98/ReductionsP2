#include "reductions.h"

SAT parseCNF() {

    std::string headerLine, token;
    bool isPreamble = true;
    bool comments = true;
    char lineType;
    char delim = ' ';

    int variables, clauses, iter;
    variables = -1;
    clauses = -1;

    std::stringstream iss;

    while (isPreamble && std::getline(std::cin, headerLine)) {

        if (headerLine.length() > 1)  {
            lineType = headerLine[0];
            switch (lineType) {
                case 'c':
                    break;
                case 'p':

                    iter = 0;
                    iss.clear();
                    iss << headerLine;
                    while (std::getline(iss, token, delim)) {

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
                                    returnProgram(1);
                                }
                                break;
                            case 3:

                                try {

                                    clauses = std::stoi(token);
                                } catch (std::invalid_argument) {
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

    if (variables == -1 || clauses == -1) {
        returnProgram(1);
    }

    std::string tempString;
    std::set<int> variablesSeen;
    std::vector<std::vector<int>> clauseArray;
    if (clauses != 0) {
        clauseArray.reserve(clauses);
    }
    std::vector<int> currentClause;
    int var, i;
    i = 0;
    // j = 0;
    while (std::getline(std::cin, tempString)) {

        iss.clear();
        iss << tempString;

        while (std::getline(iss, token, ' ')) {

            try {
                var = std::stoi(token);
                if (var > variables || (var*-1) > variables) {
                    returnProgram(1);
                }
                if (var == 0) {


                    if (i >= clauses) {
                        returnProgram(1);
                    }
                    clauseArray.push_back(currentClause);
                    currentClause.clear();
                    i++;
                }
                else {

                    variablesSeen.insert(std::abs(var));
                    currentClause.push_back(var);
                }
            } catch (std::invalid_argument) {

                returnProgram(1);
            }
        }
    }

    if (currentClause.size() > 0) {
        if (i >= clauses) {
            returnProgram(1);
        }
        clauseArray[i] = currentClause;
        i++;
    }

    if (i < clauses) {
        returnProgram(1);
    }

    SAT sat;

    sat.setVariables(variablesSeen.size());

    sat.setClauses(clauseArray);

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

    if (edgesFound != edgesNo) {
        returnProgram(1);
    }

    COL col;

    col.setNodes(nodes);
    col.setColours(colours);
    col.setEdges(edgesSet);

    return col;
}
