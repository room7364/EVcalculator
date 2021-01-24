#include "../mylibs/HodlemCalc.h"

namespace hc {

    void displaycombs(comblist& combs) {
        for (int i = 0; i < combs.size(); i++) {
            std::cout << i <<":" << hc::combtostring(combs[i]) << ";";
        }
    }

    std::string combtostring(const std::array<uint8_t,2>& c) {
        return cardtostring(c[0]) + cardtostring(c[1]);
    } 

    std::string cardtostring(uint8_t i) {
        char rank, suit;
        std::string s;

        switch (i / 4)
            {
            case 12 : rank = 'A'; break;
            case 11 : rank = 'K'; break;
            case 10 : rank = 'Q'; break;
            case 9 : rank = 'J'; break;
            case 8 : rank = 'T'; break;
            case 7 : rank = '9'; break;
            case 6 : rank = '8'; break;
            case 5 : rank = '7'; break;
            case 4 : rank = '6'; break;
            case 3 : rank = '5'; break;
            case 2 : rank = '4'; break;
            case 1 : rank = '3'; break;
            case 0 : rank = '2'; break;
            }

        switch(i % 4) 
            {
            case 0 : suit = 's'; break;
            case 1 : suit = 'h'; break;
            case 2 : suit = 'c'; break;
            case 3 : suit = 'd'; break;
            }

        s.push_back(rank);
        s.push_back(suit);
        return s;
    }

}