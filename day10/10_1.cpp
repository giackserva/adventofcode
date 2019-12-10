#include <iostream>
#include <vector>
#include <string>

bool closer(int x1, int y1, int x2, int y2, int x3, int y3) {
    return ((y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1)) <
           ((y3 - y1) * (y3 - y1) + (x3 - x1) * (x3 - x1));
}

bool aligned(int x1, int y1, int x2, int y2, int x3, int y3) {
    return (x3 - x2) * (y2 - y1) == (y3 - y2) * (x2 - x1);
}

bool same(int x1, int y1, int x2, int y2) {
    return x1 == x2 && y1 == y2;
}

int main() {

    std::vector<std::pair<int, int>> asteroids;
    std::string line;
    int col = 0;
    while(std::getline(std::cin, line)) {
        for(int i = 0; i < line.size(); i++) {
            if(line[i] == '#') {
                asteroids.push_back({i, col});
            }
        }
        col++;
    }

    int max = 0;
    int x = 0;
    int y = 0;
    for(const auto[x1, y1] : asteroids) {
        int visible = 0;
        for(const auto[x2, y2] : asteroids) {
            if (same(x1, y1, x2, y2)) continue;

            bool canSee = true;
            for(const auto[x3, y3] : asteroids) {
                if (same(x3, y3, x1, y1) || same(x3, y3, x2, y2)) continue;

                if(closer(x1, y1, x3, y3, x2, y2) &&
                   closer(x2, y2, x3, y3, x1, y1) &&
                   aligned(x1, y1, x2, y2, x3, y3)) {
                   canSee = false;
                   break;
                }
            }
            visible += canSee;
        }

        if(visible > max) {
            max = visible;
            x = x1;
            y = y1;
        }
    }

    std::cout << x << ',' << y << " with " << max << '\n';
}