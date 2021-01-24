#include "../mylibs/HodlemCalc.h"

namespace hc {

    bool comp(const Hand& left, const Hand& right) {
        return left.equities[NUM_HANDS_ALL - 1] > right.equities[NUM_HANDS_ALL - 1]; 
    }

    EquityTable::EquityTable(std::string& b, double t) : board(b), time(t) {
        std::string filename = "./tables/" + board + "-" + std::to_string(time);

        // Check if such table file exists and read table from it
        std::ifstream ist(filename);
        if (ist.is_open()) {
            std::cout << "Reading table from file " << filename << std::endl;
            for (int handrank = 0; handrank < NUM_HANDS_ALL; handrank++) {
                std::string hand;
                ist >> hand;
                table[handrank].hand = stringtocomb(hand);
                for (int rangerank = 0; rangerank < NUM_HANDS_ALL; rangerank++) {
                    double equity;
                    ist >> equity;
                    table[handrank].equities[rangerank] = equity;
                }
            }
        }

        else {

            std::ofstream ost(filename);
            if (!ost.is_open()) std::runtime_error("It's impossible to open file to write ");

            // Getting hands with theirs eqities against random range
            omp::CardRange allhands("random");
            std::vector<std::array<uint8_t,2>> combslist = allhands.combinations();
            for (int i; i < NUM_HANDS_ALL; i++) {
                table[i].hand = combslist[i];
                table[i].equities[NUM_HANDS_ALL - 1] = calcequity(table[i].hand, allhands);
            }

            // Order table
            std::sort(table.begin(), table.end(), comp);

            // Getting ordered ranges
            std::vector<std::array<uint8_t,2>> combs;
            for (int rank = 0; rank < NUM_HANDS_ALL; rank++) {
                combs.push_back(table[rank].hand);
                orderedranges[rank] = omp::CardRange(combs);
            }

            // Calculating equity table
            std::cout << "Starting calculating equity table for " << board << std::endl;
            for (int handrank = 0; handrank < NUM_HANDS_ALL; handrank++) {
                for (int rangerank = 0; rangerank < NUM_HANDS_ALL - 1; rangerank++) {
                    table[handrank].equities[rangerank] = calcequity(table[handrank].hand, orderedranges[rangerank]);
                }
            std::cout << handrank << " hands from " << NUM_HANDS_ALL << " calculated\n";
            }

            // Writing table to file
            std::cout << "Writing table to file... " << filename << std::endl;
            for (int handrank = 0; handrank < NUM_HANDS_ALL; handrank++) {
                ost << combtostring(table[handrank].hand) << " ";
                for (int rangerank = 0; rangerank < NUM_HANDS_ALL; rangerank++) {
                    double equity;
                    equity = table[handrank].equities[rangerank];
                    ost << equity << " ";
                }
            }
            std::cout << "Done.\n";

        }
    }

    double EquityTable::calcequity(const std::array<uint8_t,2>& hand, const omp::CardRange& range) {
        uint64_t board_mask = board == "preflop" ? 0 : omp::CardRange::getCardMask(board);
        std::vector<omp::CardRange> rangestopass;
        rangestopass.push_back(omp::CardRange(combtostring(hand)));
        rangestopass.push_back(range);
        omp::EquityCalculator ec;
        ec.setTimeLimit(time);
        ec.start(rangestopass, board_mask);
        ec.wait();
        auto results = ec.getResults();
        return results.equity[0];
    }

    double EquityTable::geteq(int hand, int range) {
        return table[hand].equities[range];
    }

    double EquityTable::geteq(std::string& hand, int range) {
        std::array<uint8_t, 2> h = stringtocomb(hand);
        for (int i = 0; i < NUM_HANDS_ALL; i++)
            if (table[i].hand == h)
                return table[i].equities[range];
        return 0;
    }

    std::array<uint8_t, 2> EquityTable::stringtocomb(std::string& hand) {
        omp::CardRange hh(hand);
        std::vector<std::array<uint8_t,2>> hhh = hh.combinations();
        return hhh[0];
    }

}