#include <iostream>
#include <vector>
#include <array>
typedef std::vector<std::array<uint8_t,2>> comblist;
typedef std::array<uint8_t,2> comb;

int main () {
    comblist list1;
    comb comb1;

    comb1 = {'A', 'B'};
    list1.push_back(comb1);

    comb1 = {'C', 'D'};
    list1.push_back(comb1);

    comb1 = {'E', 'F'};
    list1.push_back(comb1);

    for (int i = 0; i < list1.size(); i++) {
        std::cout << i <<":" << list1[i][0] << list1[i][1] << ";";
    }
    std::cout << std::endl;
}