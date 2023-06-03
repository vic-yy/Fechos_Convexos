#include <iostream>
#include <sstream>
#include <vector>

std::string transformNumbers(int a, int b) {
    std::stringstream ss;
    ss << a << ";" << b;
    return ss.str();
}

int main() {
    std::vector<std::pair<int, int>> pairs;

    int numPairs;
    std::cout << "Quantos pares de números você deseja inserir? ";
    std::cin >> numPairs;

    for (int i = 0; i < numPairs; i++) {
        int a, b;
        // std::cout << "Insira o par de números " << (i + 1) << ": ";
        std::cin >> a >> b;
        pairs.push_back(std::make_pair(a, b));
    }

    // std::cout << "Formato transformado:" << std::endl;

    for (const auto& pair : pairs) {
        int a = pair.first;
        int b = pair.second;
        std::string transformed = transformNumbers(a, b);
        std::cout << transformed << std::endl;
    }

    return 0;
}
