#include <iostream>
#include <vector>
#include <string>

using namespace std;

int execute(vector<int> memory, int noun, int verb)
{
    memory[1] = noun;
    memory[2] = verb;

    for(int i = 0; i < memory.size(); i+=4) {
        const int opcode = memory[i];
        if (opcode == 99) break;

        const int op1 = memory[i+1];
        const int op2 = memory[i+2];
        const int op3 = memory[i+3];

        if(opcode == 1) memory[op3] = memory[op1] + memory[op2];
        else if(opcode == 2) memory[op3] = memory[op1] * memory[op2];
    }

    return memory[0];
}

int main(int argc, char** argv)
{
    vector<int> memory;
    string input;
    while (getline(cin, input, ',')) {
        memory.push_back(stoi(input));
    }

    for(int i = 0; i < memory.size(); i++) {
        for(int j = 0; j < memory.size(); j++) {
            if (execute(memory, i, j) == 19690720) {
                cout << i * 100 + j << '\n';
                return 0;
            }
        }
    }
}