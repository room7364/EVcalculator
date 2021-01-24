#include "Data.h"

Data::Data() {
    // Fill initial values
    for (int i = 0; i < NUM_UNITS; i++) units[i].id = i;
    units[0].somevalues[NUM_VALUES - 1] = 0.23;
    units[1].somevalues[NUM_VALUES - 1] = 0.14;
    units[2].somevalues[NUM_VALUES - 1] = 0.56;
    units[3].somevalues[NUM_VALUES - 1] = 0.33;
    units[4].somevalues[NUM_VALUES - 1] = 0.73;
    units[5].somevalues[NUM_VALUES - 1] = 0.44;
    units[6].somevalues[NUM_VALUES - 1] = 0.66;
    units[7].somevalues[NUM_VALUES - 1] = 0.91;
    units[8].somevalues[NUM_VALUES - 1] = 0.24;
    units[9].somevalues[NUM_VALUES - 1] = 0.38;

    std::sort(units.begin(), units.end(), comp);

    // Fill to complete
    for (int unit = 0; unit < NUM_UNITS; unit++) 
        for (int value = 0; value < NUM_VALUES - 1; value++)
            units[unit].somevalues[value] = 0.0;

        // Send to screen
    for (int unit = 0; unit < NUM_UNITS; unit++) {
        std::cout << "ID=" << units[unit].id << ": ";
        for (int value = 0; value < NUM_VALUES; value++) {
            std::cout << units[unit].somevalues[value] << " ";
        }
        std::cout << std::endl;
    }
}

bool comp(const Unit& left, const Unit& right) {
    return left.somevalues[NUM_VALUES - 1] > right.somevalues[NUM_VALUES - 1] ;
}