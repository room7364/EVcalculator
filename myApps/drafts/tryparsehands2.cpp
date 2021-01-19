#include <string>
#include <locale>
#include <iostream>

int main() {
    std::string text = "22+";
    
    // Turn to lowercase and remove spaces and control chars.
    std::locale loc;
    std::string s;
    for (char c: text) {
        if (std::isgraph(c, loc))
            s.push_back(std::tolower(c, loc));
    }

    std::cout << s << std::endl;

    unsigned c1 = 4 * r1 + s1;

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

    switch(c) {
        case 's': return 0;
        case 'h': return 1;
        case 'c': return 2;
        case 'd': return 3;
        default: return ~0u;
    }
}