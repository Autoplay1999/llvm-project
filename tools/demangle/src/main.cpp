#include "llvm/Demangle/Demangle.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            std::cout << llvm::demangle(argv[i]) << "\n";
        }
    } else {
        std::string line;
        while (std::getline(std::cin, line)) {
            std::cout << llvm::demangle(line) << "\n";
        }
    }
    return 0;
}
