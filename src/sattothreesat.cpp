#include "reductions.h"

int main(int argc, char const *argv[]) {

    SAT sat = parseCNF();

    printSAT(sat);
    sattothreesat(sat);

    return 0;
}
