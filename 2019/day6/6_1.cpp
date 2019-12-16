#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;
typedef unordered_map<string, vector<string>> Tree;

int visit(Tree& tree, const string& node, int depth) {
    int ret = depth;

    if(tree.find(node) == tree.end()) return ret;

    for(string children : tree[node]) {
        ret += visit(tree, children, depth + 1);
    }

    return ret;
}

int main() {
    Tree tree;
    string input;
    while(cin >> input) {
        size_t par = input.find(')');
        tree[input.substr(0, par)].push_back(input.substr(par + 1));
    }

    cout << visit(tree, "COM", 0) << '\n';
}