#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
    vector<int> program;
    string input;
    while (getline(cin, input, ',')) {
        program.push_back(stoi(input));
    }

    program[1] = 12;
    program[2] = 2;

    for(int i = 0; i < program.size(); i+=4) {
        const int opcode = program[i];
        if (opcode == 99) break;

        const int op1 = program[i+1];
        const int op2 = program[i+2];
        const int op3 = program[i+3];

        if(opcode == 1) program[op3] = program[op1] + program[op2];
        else if(opcode == 2) program[op3] = program[op1] * program[op2];
    }

    cout << program[0] << '\n';
}
