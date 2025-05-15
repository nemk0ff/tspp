#include <iostream>
#include "ExpressionParser.h"

int main() {
    std::cout << std::fixed;
    std::cout.precision(6);

    std::string s;
    getline(std::cin, s);

    ExpressionParser p;

    try {
        std::cout << p.parse(s) << std::endl;
    } catch (const char *s) {
        std::cerr << s << std::endl;
        std::cout << "Error." << std::endl;
    } catch (std::string &s) {
        std::cerr << s << std::endl;
        std::cout << "Error." << std::endl;
    }

    return 0;
}