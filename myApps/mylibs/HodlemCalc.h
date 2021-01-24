#include "../../omp/EquityCalculator.h"
#include <iostream>
#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <stdexcept>

namespace hc {

    typedef std::vector<std::array<uint8_t,2>> comblist;
    std::string combtostring(const std::array<uint8_t,2>&);
    std::string cardtostring(uint8_t);
    void displaycombs(comblist&);
    static const int NUM_HANDS_ALL = 1326;

    /* class Hand {
        private:
            std::string value;
            double equity;
        public:
            //Hand(const std::string& val, const double eq) : value(val), equity(eq) {};

            void setequity(double eq) { equity = eq; }

            double getequity() { return equity; }

            std::string getvalue() { return value; }

            void setvalue(const std::string& val) { value = val;}

            bool operator<(Hand& second) { return equity < second.equity; }

            static friend greater(const Hand& left, const Hand& right) { return left.equity > right.equity; }
    };

    class OrderedHands {
        private:

            std::array<Hand, NUM_HANDS_ALL> hands;

            std::string board;

            double time;

            double calcequity(const std::string&);
        public:
            OrderedHands(const std::string&, double);

            std::string getvalue(int rank) { return hands[rank].getvalue; }
    }; */

    struct Hand {
        std::array<uint8_t, 2> hand;
        std::array<double, NUM_HANDS_ALL> equities;
    };

    bool comp(const Hand& left, const Hand& right);

    class EquityTable {
        private:
            std::string board;
            
            std::array<Hand, NUM_HANDS_ALL> table;

            std::array<omp::CardRange, NUM_HANDS_ALL> orderedranges;

            double time;

            double calcequity(const std::array<uint8_t,2>&, const omp::CardRange&);

            std::array<uint8_t, 2> stringtocomb(std::string&);
        public:
            EquityTable(std::string&, double);
            double geteq(std::string&, int);
            double geteq(int, int);
            std::string gethand(int rank) { return combtostring(table[rank].hand); };
    };

}