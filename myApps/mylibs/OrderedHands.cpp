#include "../mylibs/HodlemCalc.h"

namespace hc {

    OrderedHands::OrderedHands(const std::string& b, double t) : board(b), time(t) {
        std::ofstream ost { board + "-" + std::to_string(time) };
        if (!ost) std::runtime_error("It's impossible to open file to output ");

        omp::CardRange range("random");
        comblist combs = range.combinations();
        for (int i = 0; i < NUM_HANDS_ALL; i++) {
            // auto begin = std::chrono::steady_clock::now();

            std::string comb = combtostring(combs[i]);
            hands[i].setvalue(comb);
            double equity = calcequity(comb);
            hands[i].setequity(equity);

            if ((i + 1) % 68 == 0) std::cout << i * 100 / NUM_HANDS_ALL << "% calculated\n";

            // auto end = std::chrono::steady_clock::now();
            // auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            // std::cout << "Overall: " << elapsed_ms.count() << " ms\n";
        }

        std::sort(hands.begin(), hands.end());

        for (int i = 0; i < NUM_HANDS_ALL; i++) {
            ost << hands[i].getvalue() << " " << hands[i].getequity() << " ";
        }
    }

    double OrderedHands::calcequity(const std::string& hand) {
        // auto begin = std::chrono::steady_clock::now();

        omp::EquityCalculator ec;
        std::vector<omp::CardRange> ranges;
        ranges.push_back(omp::CardRange(hand));
        ranges.push_back(omp::CardRange("random"));
        uint64_t board_mask = board == "preflop" ? 0 : omp::CardRange::getCardMask(board);
        ec.setTimeLimit(time);
        ec.start(ranges, board_mask);
        ec.wait();
        auto results = ec.getResults();

        // auto end = std::chrono::steady_clock::now();
        // auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        // std::cout << "calcequity(): " << elapsed_ms.count() << " ms\n";
        return results.equity[0];
    }
    
}

/*#include <iostream>
#include <chrono>
int main() {
  auto begin = std::chrono::steady_clock::now();
  getchar(); 
  auto end = std::chrono::steady_clock::now();
  
  auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
  std::cout << "The time: " << elapsed_ms.count() << " ms\n";
}*/