#include "../../omp/EquityCalculator.h"
#include <iostream>
#include <string>

namespace hc {
    typedef std::vector<std::array<uint8_t,2>> comblist;
    typedef std::array<uint8_t,2> comb;
    std::string combtostring(comb&);
    std::string cardtostring(uint8_t);
    void displaycombs(comblist&);

    class Hand {
        private:
            std::string value;
            double equity;
        public:
            Hand(const std::string& val, const double eq) : value(val), equity(eq) {};
            void setequity(double& eq) {
                equity = eq;
            }
            std::string getvalue() { return value; }
    };

    class Range {
        private:
            std::vector<Hand> hands;
            void addhand(const std::string& val, const double& eq) {
                Hand hand(val, eq);
                hands.push_back(hand);
            }
        public:
            void gethands(std::string&);
            void getequties(std::string, std::string);
    };
}