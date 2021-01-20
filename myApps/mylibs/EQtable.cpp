#include "../mylibs/HodlemCalc.h"

namespace hc {

    EQtable::EQtable() {

        omp::CardRange range("random");
        comblist combs = range.combinations();
        for (int i = 0; i < combs.size(); i++) {
            std::string comb = combtostring(combs[i]);
            addhand(comb, 0.0);
        }
    }

    void EQtable::getequties(std::string range, std::string board) {
        for (int i = 0; i < hands.size(); i++) {
            omp::EquityCalculator ec;
            std::vector<omp::CardRange> ranges;
            ranges.push_back(hands[i].getvalue());
            ranges.push_back(range);
            uint64_t board_mask = board == "preflop" ? 0 : omp::CardRange::getCardMask(board);
            ec.start(ranges, board_mask);
            ec.wait();
            auto results = ec.getResults();
            hands[i].setequity(results.equity[0]);
            std::cout << "hand " << i << "from" << hands.size() << "set\n";
        }
    } 

}