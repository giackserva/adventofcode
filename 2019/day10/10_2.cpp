#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <queue>

struct Point {
    int x;
    int y;
};

double slope(Point p1, Point p2) {
    if (p1.x - p2.x) return (double) (p2.y - p1.y) / (double) (p1.x - p2.x);
    return std::numeric_limits<double>::infinity();
}

bool closer(Point p1, Point p2, Point p3) {
    return ((p2.y - p1.y) * (p2.y - p1.y) + (p2.x - p1.x) * (p2.x - p1.x)) <
           ((p3.y - p1.y) * (p3.y - p1.y) + (p3.x - p1.x) * (p3.x - p1.x));
}

bool same(Point p1, Point p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

int main() {

    const Point start {20, 21};

    std::vector<std::pair<Point, double>> asteroids;
    std::vector<std::pair<Point, double>> asteroids_left;
    std::string line;
    int col = 0;
    while(std::getline(std::cin, line)) {
        for(int i = 0; i < line.size(); i++) {
            Point curr {i, col};
            if(line[i] == '#' && !same(start, curr)) {
                const std::pair<Point, double> toAdd = {curr, slope(start, curr)};

                if(start.x < curr.x) asteroids.push_back(toAdd);
                else if(start.x > curr.x) asteroids_left.push_back(toAdd);
                else if(start.y > curr.y) asteroids.push_back(toAdd);
                else asteroids_left.push_back(toAdd);
            }
        }
        col++;
    }

    auto comp = [&](const auto& a1, const auto& a2) {
        if (a1.second == a2.second) return closer(start, a1.first, a2.first);
        return a1.second > a2.second;
    };

    std::sort(asteroids.begin(), asteroids.end(), comp);
    std::sort(asteroids_left.begin(), asteroids_left.end(), comp);
    asteroids.insert(asteroids.end(), asteroids_left.begin(), asteroids_left.end());

    double lastSlope = asteroids[0].second;
    std::vector<std::queue<Point>> accumulated;
    accumulated.push_back(std::queue<Point>());
    accumulated.front().push(asteroids[0].first);
    for(int i = 1; i < asteroids.size(); i++) {
        if(lastSlope != asteroids[i].second) {
            lastSlope = asteroids[i].second;
            accumulated.push_back(std::queue<Point>());
        }
        accumulated.back().push(asteroids[i].first);
    }

    int currQueue = -1;
    for(int i = 0; i < asteroids.size(); i++) {
        do {
            currQueue++;
            currQueue %= accumulated.size();
        } while(accumulated[currQueue].empty());

        auto& p = accumulated[currQueue].front();
        accumulated[currQueue].pop();
        std::cout << (i+1) << ": " << p.x << ',' << p.y << '\n';
    }
}