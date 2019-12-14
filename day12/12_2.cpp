#include <iostream>
#include <vector>
#include <numeric>
#include <array>
#include <map>

int findRepeat(std::array<int, 8>& dimension) {
    std::map<std::array<int, 8>, int> visited;
    visited.insert({dimension, 0});
    int ret = 0;
    do {
        ret++;
        for(int i = 0; i < 4; i++) {
            for(int j = i + 1; j < 4; j++) {
                if (dimension[i] > dimension[j]) {
                    dimension[i+4]--;
                    dimension[j+4]++;
                } else if (dimension[i] < dimension[j]) {
                    dimension[j+4]--;
                    dimension[i+4]++;
                }
            }
        }

        for(int i = 0; i < 4; i++) {
            dimension[i] += dimension[i+4];
        }

    } while(visited.insert({dimension, 0}).second);

    return ret;
}

int main() {
    std::array<int, 8> xs{};
    std::array<int, 8> ys{};
    std::array<int, 8> zs{};

    for(int i = 0; i < 4; i++) {
        int x, y, z;
        std::cin >> x >> y >> z;
        xs[i] = x; ys[i] = y; zs[i] = z;
    }

    const int64_t rec_x = findRepeat(xs);
    const int64_t rec_y = findRepeat(ys);
    const int64_t rec_z = findRepeat(zs);

    std::cout << std::lcm(rec_x, std::lcm(rec_y, rec_z)) << '\n';
}