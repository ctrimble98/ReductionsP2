#include "reductions.h"

int main(int argc, char const *argv[]) {

    COL col = parseCOL();

    printCOL(col);
    SAT sat = coltosat(col);

    printSAT(sat);

    return 0;
}
