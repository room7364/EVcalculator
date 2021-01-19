#include "../mylibs/HodlemCalc.h"

int main()
{
    CardRange range1("JJ+,AK");
    hc::comblist combsr1 = range1.combinations();
    hc::displaycombs(combsr1);
    std::cout << std::endl;
}