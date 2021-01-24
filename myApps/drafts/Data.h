#include <string>
#include <array>
#include <algorithm>
#include <iostream>

int const NUM_VALUES = 5;
int const NUM_UNITS = 10;

struct Unit {
    int id;
    std::array<double, NUM_VALUES> somevalues;
};

class Data {
    private:        
        std::array<Unit, NUM_UNITS> units;
    public:
        Data();
};

bool comp(const Unit&, const Unit&);