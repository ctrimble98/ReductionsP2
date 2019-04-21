#include "reductions.h"

void parseCNF() {

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

    std::vector<std::vector<int>> clauseArray(clauses);
    std::vector<int> currentClause(10);
    int i, var;
    i = 0;
    while (std::getline(std::cin, token, delim)) {

        try {

            var = std::stoi(token);
            if (var > variables || (var*-1) > variables) {
                returnProgram(1);
            }
            currentClause.at(i) = var;

            std::cout << "Clause var: " << var << std::endl;
            i++;
        } catch (std::invalid_argument) {

            std::cout << "Parsing clauses failed on: " << token << std::endl;
            returnProgram(1);
        }
    }

    // char c;
    // while (std::cin >> c) {
    //
    //     std::cout << c;
    // }
}
