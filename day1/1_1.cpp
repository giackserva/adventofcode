// https://adventofcode.com/2019/day/1

#include <iostream>
#include <string>

int main()
{
    int sum = 0;
    for (std::string s; std::getline(std::cin, s); ) {
        sum += std::stoi(s) / 3 - 2;
    }
    std::cout << sum << '\n';
}