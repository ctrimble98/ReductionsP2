#include "reductions.h"

// Function to parse a DIMACs .cnf file into a SAT object
SAT parseCNF() {

    std::string headerLine, token;
    bool isPreamble = true;
    bool comments = true;
    char lineType;

    int variables, clauses, iter;
    variables = -1;
    clauses = -1;

    std::stringstream iss;

    //Loop through processing the preamble
    while (isPreamble && std::getline(std::cin, headerLine)) {

        //If the line is empty, ignore it
        if (headerLine.length() > 1)  {

            //Get the line type (Valid preamble lines start with 'p' or 'c')
            lineType = headerLine[0];
            switch (lineType) {

                //Ignore the line if it's a comment
                case 'c':
                    break;

                //If the line is a problem line, process it
                case 'p':

                    //Set a variable to track how far along the problem line you are
                    iter = 0;

                    //Clear the string stream and then place the current line in it to be tokenised
                    iss.clear();
                    iss << headerLine;

                    //Iterate through each token in the line
                    while (std::getline(iss, token, ' ')) {

                        switch (iter) {

                            case 0:

                                //The first token must be 'p'
                                if (token != "p") {
                                    returnProgram(1);
                                }
                                break;
                            case 1:

                                //The first token must be 'cnf'
                                if (token != "cnf") {
                                    returnProgram(1);
                                }
                                break;
                            case 2:

                                //Set the number of variables. If this fails, exit the program
                                try {
                                    variables = std::stoi(token);
                                } catch (std::invalid_argument) {
                                    returnProgram(1);
                                }
                                break;
                            case 3:

                                //Set the number of variables. If this fails, exit the program
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

    //Check if the variables and clauses were set (In case of no problem line)
    if (variables == -1 || clauses == -1) {
        returnProgram(1);
    }

    //Set a string to hold a line, make a set to store seen variables and make a vector to store clauses
    std::string tempString;
    std::set<int> variablesSeen;
    std::vector<std::vector<int>> clauseArray;
    if (clauses != 0) {
        clauseArray.reserve(clauses);
    }

    std::vector<int> currentClause;
    int var, i;

    //Use i to track how many clauses have been made
    i = 0;

    //Loop through each line of the clauses
    while (std::getline(std::cin, tempString)) {

        //Tokenise the line and iterate through each token
        iss.clear();
        iss << tempString;
        while (std::getline(iss, token, ' ')) {

            //Check if the token is a valid integer and in the correct range
            try {
                var = std::stoi(token);
                if (var > variables || (var*-1) > variables) {
                    returnProgram(1);
                }

                //If the token is zero, add the current clause to the list
                if (var == 0) {

                    if (i >= clauses) {
                        returnProgram(1);
                    }
                    clauseArray.push_back(currentClause);
                    currentClause.clear();
                    i++;
                }
                else {

                    //Add the current variable to the set and then add it to the clause
                    variablesSeen.insert(std::abs(var));
                    currentClause.push_back(var);
                }
            } catch (std::invalid_argument) {

                returnProgram(1);
            }
        }
    }

    //Check if there is an unfinished clause and if there is, store it
    if (currentClause.size() > 0) {
        if (i >= clauses) {
            returnProgram(1);
        }
        clauseArray[i] = currentClause;
        i++;
    }

    //If there are too few clauses, exit
    if (i < clauses) {
        returnProgram(1);
    }

    //Set up the sat object to be returned, and return it
    SAT sat;
    sat.setVariables(variablesSeen.size());
    sat.setClauses(clauseArray);

    return sat;
}

//Function to parse a DIMACs .col file into a COL object
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

        //Loop through each token on the line
        comment = false;
        while (std::getline(iss, token, ' ')) {

            if (!comment) {
                try {

                    //Ignore the line if its a comment
                    if (token == "c") {
                        comment = true;
                    } else {

                        //Switch between the line types
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

                                        //Insert the edge with nodes in ascending order to avoid duplicates
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

    //Check if the correct number of edges have been found
    if (edgesFound != edgesNo) {
        returnProgram(1);
    }

    //Fill the COL object and return it
    COL col;

    col.setNodes(nodes);
    col.setColours(colours);
    col.setEdges(edgesSet);

    return col;
}
