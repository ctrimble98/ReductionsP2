#include "reductions.h"

int main(int argc, char const *argv[]) {

    COL col = parseCOL();

    printCOL(col);
    coltosat(col);

    return 0;
}
