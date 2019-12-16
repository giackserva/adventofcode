#include <iostream>
#include <array>
#include <limits>

using namespace std;

int main() {
    string input;
    cin >> input;

    const int height = 6;
    const int width = 25;
    const int layerSize = height * width;
    const int layers = input.size() / layerSize;

    int min = numeric_limits<int>::max();
    int res = 0;

    for(int i = 0; i < layers; i++) {
        array<int, 3> count{0,0,0};
        for (int j = 0; j < layerSize; j++) {
            count[input[i * layerSize + j] - '0']++;
        }
        if(count[0] < min) {
            min = count[0];
            res = count[1] * count[2];
        }
    }

    cout << res << '\n';
}