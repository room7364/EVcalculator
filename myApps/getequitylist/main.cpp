// Compiling
// g++ main.o ../mylibs/OrderedHands.o ../mylibs/combtostring.o ../../lib/ompeval.a -pthread

#include "../mylibs/HodlemCalc.h"

int main() {
    std::string board;
    double time;
    std::cout << "Enter table and time for processing one hand: \n";
    std::cin >> board >> time;
    hc::EquityTable* table = new hc::EquityTable(board, time);
    std::cout << "Table for " << board << " is active now\n";

    std::string input;
    while (std::cin >> input) {

        if (input == "gwr") {
            int rank, range;
            std::cin >> rank >> range;
            std::cout << "Hand with rank " << rank << " is " << table->gethand(rank) 
                      << ". Equity is " << table->geteq(rank, range) << std::endl;
        }

        if (input == "gwh") {
            std::string hand;
            int range;
            std::cin >> hand >> range;
            std::cout << "Hand " << hand << " has " << table->geteq(hand, range) << " equity\n";
        }

        if (input == "status")
            std::cout << "Current board is " << board;

        if (input == "exit") {
            return 0;
        }
    }
}