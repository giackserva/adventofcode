#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include <map>

using namespace std;

pair<int, int> getDirection(char d) {
    if(d == 'U') return { 1, 0 };
    if(d == 'D') return { -1, 0 };
    if(d == 'L') return { 0, -1 };
    if(d == 'R') return { 0, 1 };

    return { 0, 0 };
}

int main(int argc, char** argv)
{
    string input;
    cin >> input;

    map<pair<int, int>, int> grid;

    int x = 0;
    int y = 0;

    int steps = 0;
    stringstream stream(input);
    while(getline(stream, input, ',')) {
        auto [v, h] = getDirection(input[0]);
        for (int i = 0; i < stoi(input.substr(1)); i++) {
            y += v;
            x += h;
            grid[{y,x}] = ++steps;
        }
    }

    x = 0;
    y = 0;

    int res = 1000000;

    steps = 0;
    cin >> input;
    stream = stringstream(input);
    while(getline(stream, input, ',')) {
        auto [v, h] = getDirection(input[0]);
        for (int i = 0; i < stoi(input.substr(1)); i++) {
            y += v;
            x += h;
            steps++;
            if (grid[{y,x}]) {
                res = min(res, grid[{y,x}] + steps );
            }
        }
    }

    cout << res << '\n';
}