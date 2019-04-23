#include "reductions.h"

int main(int argc, char const *argv[]) {

    SAT sat = parseCNF();

    sat = sattothreesat(sat);

    printSAT(sat);
    return 0;
}
