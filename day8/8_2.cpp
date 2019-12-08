#include <iostream>
#include <vector>

using namespace std;

int main() {
    string input;
    cin >> input;

    const int height = 6;
    const int width = 25;
    const int layerSize = height * width;
    const int layers = input.size() / layerSize;

    vector<vector<int>> image(height, vector<int>(width, 2));

    for(int i = 0; i < layers; i++) {
        for (int j = 0; j < layerSize; j++) {
            const int col = j / width;
            const int row = j % width;
            if (image[col][row] == 2)
                image[col][row] =  input[i * layerSize + j] - '0';
        }
    }

    for(auto& row : image) {
        for(auto& pixel : row) {
            cout << (pixel ? 'x' : ' ');
        }
        cout << '\n';
    }
}