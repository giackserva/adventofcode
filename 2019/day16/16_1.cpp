#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector<int> signal;

    string input;
    cin >> input;
    for(char digit : input)
        signal.push_back(digit - '0');

    const vector<int> pattern {0, 1, 0, -1};

    for(int phase = 0; phase < 100; phase++) {
        for(int j = 0; j < signal.size(); j++) {
            int result = 0;
            for(int z = j; z < signal.size(); z++) {
                const int index = (z + 1) / (j + 1) % pattern.size();
                result += signal[z] * pattern[index];
            }
            signal[j] = abs(result) % 10;
        }
    }

    for(int i = 0; i < 8; i++) {
        cout << signal[i];
    }
    cout << '\n';
}