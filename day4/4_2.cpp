#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool isValid(int n) {
    vector<int> occ(10, 0);
    int prev = 10;
    while(n > 0) {
        const int curr = n % 10;
        if(curr > prev) return false;
        occ[curr]++;
        n /= 10;
        prev = curr;
    }
    return any_of(occ.begin(), occ.end(), [](int i){ return i == 2; });
}

int main() {
    int count = 0;
    for (int i = 248345; i <= 746315; i++)
        count += isValid(i);
    cout << count << '\n';
}