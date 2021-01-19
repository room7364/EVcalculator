// Compiling
// g++ main.o ../mylibs/Range.o ../mylibs/combtostring.o ../../lib/ompeval.a -pthread

#include "../mylibs/HodlemCalc.h"

int main() {
    hc::Range r1;
    std::string hands = "22";
    std::string range = "random";
    std::string board = "preflop";
    r1.gethands(hands);
    r1.getequties(range, board);
}