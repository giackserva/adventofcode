#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;
typedef unordered_map<string, vector<string>> Graph;

void search(Graph& graph, vector<string>& visited,
            const string& from, const string& to, int length) {
    if (graph.find(from) == graph.end()) return;
    if (find(visited.begin(), visited.end(), from) != visited.end()) return;
    visited.push_back(from);

    if(from == to) {
        cout << length - 2;
        return;
    }

    for(string children : graph[from]) {
        search(graph, visited, children, to, length + 1);
    }
}

int main() {
    Graph graph;
    string input;
    while(cin >> input) {
        size_t par = input.find(')');
        const string first = input.substr(0, par);
        const string second = input.substr(par + 1);
        graph[first].push_back(second);
        graph[second].push_back(first);
    }

    vector<string> visited;
    search(graph, visited, "YOU", "SAN", 0);
    cout << '\n';
}