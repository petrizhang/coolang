#include <iostream>

#include "Token.h"
#include "Scanner.h"
#include <sstream>

int main() {
    std::stringstream ss;
    ss << "(*3456*)  1234 abcd class(a,b): true false";

    StringTable strTalbe, idTable;
    Scanner scanner(&ss, strTalbe, idTable);
    std::vector<Token> result;
    scanner.scan(result);
    for (auto &t:result) {
        std::cout << t << std::endl;
    }
    return 0;
}


