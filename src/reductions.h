#ifndef REDUCTIONS_H
#define REDUCTIONS_H

#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>

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

class COL {

private:
    int nodes;
    int colours;
    std::set<std::pair<int, int>> edgesSet;
public:
    int getNodes() {
        return nodes;
    }

    void setNodes(int nodes) {

        this->nodes = nodes;
    }

    int getColours() {

        return colours;
    }

    void setColours(int colours) {

        this->colours = colours;
    }

    std::set<std::pair<int, int>> getEdges() {

        return edgesSet;
    }

    void setEdges(std::set<std::pair<int, int>> edgesSet) {

        this->edgesSet = edgesSet;
    }

};

//Miscelaneous function definitions
void returnProgram(int returnVal);

//Parsing function definitions
SAT parseCNF();
COL parseCOL();

//Printing function definitions
void printSAT(SAT sat);
void printCOL(COL col);

//Reduction function definitions
void sattothreesat(SAT sat);
void coltosat(COL col);
#endif
