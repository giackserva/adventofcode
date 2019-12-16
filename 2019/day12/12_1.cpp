#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

struct Moon {
    int x, y, z;
    int vel_x, vel_y, vel_z;

    void updatePosition() {
        x += vel_x;
        y += vel_y;
        z += vel_z;
    }

    int energy() {
        return (abs(x) + abs(y) + abs(z))
                * (abs(vel_x) + abs(vel_y) + abs(vel_z));
    }
};

void updateVelocity(Moon& first, Moon& second) {
    if (first.x > second.x) {
        first.vel_x--;
        second.vel_x++;
    } else if(first.x < second.x) {
        first.vel_x++;
        second.vel_x--;
    }
    if (first.y > second.y) {
        first.vel_y--;
        second.vel_y++;
    } else if(first.y < second.y) {
        first.vel_y++;
        second.vel_y--;
    }
    if (first.z > second.z) {
        first.vel_z--;
        second.vel_z++;
    } else if(first.z < second.z) {
        first.vel_z++;
        second.vel_z--;
    }
}

int main() {
    std::vector<Moon> moons(4);
    std::string input;

    for(Moon& moon : moons) {
        int x, y, z;
        std::cin >> x >> y >> z;
        moon.x = x; moon.vel_x = 0;
        moon.y = y; moon.vel_y = 0;
        moon.z = z; moon.vel_z = 0;
    }

    for(int step = 1; step <= 1000; step++) {

        for(int i = 0; i < moons.size(); i++) {
            for(int j = i + 1; j < moons.size(); j++) {
                updateVelocity(moons[i], moons[j]);
            }
        }

        for_each(moons.begin(), moons.end(), [](Moon& m) { m.updatePosition(); });
    }

    const int energy = std::accumulate(moons.begin(), moons.end(), 0,
        [](int acc, Moon& m){ return acc + m.energy(); });

    std::cout << energy << '\n';
}