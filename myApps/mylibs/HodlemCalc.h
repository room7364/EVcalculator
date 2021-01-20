#include "../../omp/EquityCalculator.h"
#include <iostream>
#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <stdexcept>

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
            //Hand(const std::string& val, const double eq) : value(val), equity(eq) {};

            void setequity(double eq) { equity = eq; }

            double getequity() { return equity; }

            std::string getvalue() { return value; }

            void setvalue(const std::string& val) { value = val;}

            bool operator<(Hand& second) { return equity < second.equity; }
    };

    // Object of Range class stores pairs "hand - equity"

        // Format of strings assigning ranges:
            // K4 : all suited and offsuited combos with specified ranks
            // K4s : suited combos
            // K4o : offsuited combos
            // Kc4d : specific suits
            // K4o+ : specified hand and all similar hands with a better kicker (K4 to KQ)
            // 44+ : pocket pair and all higher pairs
            // K4+,Q8s,84 : multiple hands can be combined with comma
            // random : all hands
            // Spaces and non-matching characters in the end are ignored. The expressions are case-insensitive.

        // gethands() fills object with hand values.
            // parameter is string assigning range for this Range object

        // getequities() adds an equity value to each hand
            // first parameter is string assigning range oppositing to which equities calculated
            // second parameter is string assigning board cards
                // board cards are set as follows "2c8hAh"; suits: 's', 'h', 'c', 'd'
/* UNUSED
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

    class EQtable {
    private:
        std::vector<Hand> hands;
        void addhand(const std::string& val, const double& eq) {
            Hand hand(val, eq);
            hands.push_back(hand);
        }
        void getequties();
    public:
        EQtable();
    }; */

    class OrderedHands {
    private:
        static const int NUM_HANDS_ALL = 1326;

        std::array<Hand, NUM_HANDS_ALL> hands;

        std::string board;

        double time;

        double calcequity(const std::string&);
    public:
        OrderedHands(const std::string&, double);
    };

}