#include "reductions.h"

int main(int argc, char const *argv[]) {

    SAT sat = parseCNF();

    COL col = threesattocol(sat);

    printCOL(col);

    return 0;
}
