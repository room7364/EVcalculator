#include "CardRange.h"
#include "../../omp/Constants.h"
#include "../../omp/Util.h"
#include <locale>
#include <algorithm>
#include <cassert>

using namespace omp;

CardRange::CardRange(const std::string& text)
{
    // Turn to lowercase and remove spaces and control chars.
    std::locale loc;
    std::string s;
    for (char c: text) {
        if (std::isgraph(c, loc))
            s.push_back(std::tolower(c, loc));
    }

    const char* p = s.data();
    while(parseHand(p) && parseChar(p, ','))
          ;

    if (s == "random")
        addAll();

    removeDuplicates();
}

// Parses a single hand and advances pointer p.
bool CardRange::parseHand(const char*&p)
{
    const char* backtrack = p;

    bool explicitSuits = false;
    unsigned r1, r2, s1, s2;
    if (!parseRank(p, r1))
        return false;
    explicitSuits = parseSuit(p, s1);
    if (!parseRank(p, r2)) {
        p = backtrack;
        return false;
    }
    if (explicitSuits && !parseSuit(p, s2)) {
        p = backtrack;
        return false;
    }
    // К этому моменту точно запарсили ранги двух карт в r1 & r2.
    // Если масти в строке были указаны явно, то установлено
    // explicitSuits = true и масти запарсили в s1 & s2

    if (explicitSuits) {
        unsigned c1 = 4 * r1 + s1, c2 = 4 * r2 + s2;
        if (c1 == c2) {
            p = backtrack;
            return false;
        }
        addCombo(c1, c2);
    } 
    // Если масти были указаны явно, то карты получают номера c1 & c2
    // и в диапазон добавляется одна комбинация из карт c1 & c2
    
    else if (!explicitSuits) {
        bool suited = true, offsuited = true;
        if (parseChar(p, 'o'))
            suited = false;
        else if (parseChar(p, 's'))
            offsuited = false;
        if (parseChar(p, '+'))
            addCombosPlus(r1, r2, suited, offsuited);
        else
            addCombos(r1, r2, suited, offsuited);
    }

    return true;
}

// Parse a rank from 2 to A.
bool CardRange::parseRank(const char*&p, unsigned& rank)
{
    rank = charToRank(*p);
    if (rank == ~0u)
        return false;
    ++p;
    return true;
}

unsigned CardRange::charToRank(char c)
{
    switch(c) {
        case 'a': return 12;
        case 'k': return 11;
        case 'q': return 10;
        case 'j': return 9;
        case 't': return 8;
        case '9': return 7;
        case '8': return 6;
        case '7': return 5;
        case '6': return 4;
        case '5': return 3;
        case '4': return 2;
        case '3': return 1;
        case '2': return 0;
        default: return ~0u;
    }
}

void CardRange::addCombo(unsigned c1, unsigned c2)
{
    omp_assert(c1 != c2);
    if (c1 >> 2 < c2 >> 2 || (c1 >> 2 == c2 >> 2 && (c1 & 3) < (c2 & 3)))
        std::swap(c1, c2);
    mCombinations.push_back({(uint8_t)c1, (uint8_t)c2});
}