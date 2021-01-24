#include "../mylibs/HodlemCalc.h"

namespace hc {

    OrderedHands::OrderedHands(const std::string& b, double t) : board(b), time(t) {
        std::cout << "Getting ordered hands\n";
        std::string filename = "./" + board + "-" + std::to_string(time) + "/ordered-hands";

        std::ifstream ist(filename);
        std::cout << "Loading from file... ";
        if (ist) {
            std::string val;
            double eq;
            for (int i = 0; ist >> val >> eq; i++) {
                hands[i].setvalue(val);
                hands[i].setequity(eq);
            }
        std::cout << "Done.\n";
        }
        else {
            std::ofstream ost(filename);
            if (!ost) std::runtime_error("It's impossible to open file to output ");
            std::cout << "Calculating...\n";

            omp::CardRange range("random");
            comblist combs = range.combinations();
            for (int i = 0; i < NUM_HANDS_ALL; i++) {

                std::string comb = combtostring(combs[i]);
                hands[i].setvalue(comb);
                double equity = calcequity(comb);
                hands[i].setequity(equity);

                if ((i + 1) % 68 == 0) std::cout << i * 100 / NUM_HANDS_ALL << "% calculated\n";
            }

            std::sort(hands.begin(), hands.end(), Hand::greater());

            for (int i = 0; i < NUM_HANDS_ALL; i++) {
                ost << hands[i].getvalue() << " " << hands[i].getequity() << " ";
            }
        }
    }

    double OrderedHands::calcequity(const std::string& hand) {

        omp::EquityCalculator ec;
        std::vector<omp::CardRange> ranges;
        ranges.push_back(omp::CardRange(hand));
        ranges.push_back(omp::CardRange("random"));
        uint64_t board_mask = board == "preflop" ? 0 : omp::CardRange::getCardMask(board);
        ec.setTimeLimit(time);
        ec.start(ranges, board_mask);
        ec.wait();
        auto results = ec.getResults();

        return results.equity[0];
    }
    
}