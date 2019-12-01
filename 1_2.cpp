#include <iostream>
#include <string>

int fuelForMass(int mass)
{
    int fuel = 0;
    for(;;) {
        mass = mass / 3 - 2;
        if (mass > 0) fuel += mass;
        else break;
    }
    return fuel;
}

int main()
{
    int sum = 0;
    for (std::string s; std::getline(std::cin, s); ) {
        sum += fuelForMass(std::stoi(s));
    }
    std::cout << sum << '\n';
}