#ifndef REDUCTIONS_H
#define REDUCTIONS_H

#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stdexcept>
#include <vector>

class SAT {

private:
    int variables;
    std::vector<std::vector<int>> clauses;
public:
    int getVariables() {
        return variables;
    }

    void setVariables(int variables) {
        this->variables = variables;
    }

    std::vector<std::vector<int>> getClauses() {
        return clauses;
    }

    void setClauses(std::vector<std::vector<int>> clauses) {
        this->clauses = clauses;
    }
};

//Miscelaneous function definitions
void returnProgram(int returnVal);

//Parsing function definitions
SAT parseCNF();

//Printing function definitions
void printSAT(SAT sat);

//Reduction function definitions
void sattothreesat(SAT sat);

#endif
