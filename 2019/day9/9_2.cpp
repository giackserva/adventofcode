#include <algorithm>
#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <queue>
#include <unordered_map>

using namespace std;

array<int, 4> parseInstruction(int instruction) {
    array<int, 4> ret;
    ret[0] = instruction % 100;
    instruction /= 100;
    ret[1] = instruction % 10;
    instruction /= 10;
    ret[2] = instruction % 10;
    instruction /= 10;
    ret[3] = instruction % 10;
    return ret;
}

void execute(vector<int64_t>& program, queue<int64_t>& input, queue<int64_t>& output)
{
    int pc = 0;
    int relativeBase = 0;
    unordered_map<int64_t, int64_t> memory;
    for(int i = 0; i < program.size(); i++) {
        memory[i] = program[i];
    }

    auto getValue = [&](int64_t op, int mode){
        if(mode == 0)
            return memory[op];
        else if(mode == 1)
            return op;
        return memory[op + relativeBase];
    };

    auto storeValue = [&](int64_t op, int mode, int64_t value) {
        if(mode == 2) memory[op + relativeBase] = value;
        else memory[op] = value;
    };

    while (pc < program.size()) {
        const int raw = memory[pc];
        const auto instruction = parseInstruction(raw);
        const int opcode = instruction[0];
        if (opcode == 99) break;

        const int64_t op1 = memory[pc+1];
        const int64_t op2 = memory[pc+2];
        const int64_t op3 = memory[pc+3];
        const int64_t value1 = getValue(op1, instruction[1]);
        const int64_t value2 = getValue(op2, instruction[2]);

        if(opcode == 1) {
            storeValue(op3, instruction[3], value1 + value2);
            pc += 4;
        }
        else if(opcode == 2) {
            storeValue(op3, instruction[3], value1 * value2);
            pc += 4;
        }
        else if(opcode == 3) {
            storeValue(op1, instruction[1], input.front());
            input.pop();
            pc += 2;
        }
        else if(opcode == 4) {
            output.push(value1);
            pc += 2;
        }
        else if(opcode == 5) {
            if (value1) pc = value2;
            else pc += 3;
        }
        else if(opcode == 6) {
            if (!value1) pc = value2;
            else pc += 3;
        }
        else if(opcode == 7) {
            storeValue(op3, instruction[3], value1 < value2 ? 1 : 0);
            pc += 4;
        }
        else if(opcode == 8) {
            storeValue(op3, instruction[3], value1 == value2 ? 1 : 0);
            pc += 4;
        }
        else if(opcode == 9) {
            relativeBase += value1;
            pc += 2;
        }
    }
}

int main(int argc, char** argv)
{
    vector<int64_t> memory;
    string input;
    cin >> input;
    stringstream stream(input);

    while (getline(stream, input, ',')) {
        memory.push_back(stoll(input));
    }

    queue<int64_t> inputData;
    inputData.push(2);
    queue<int64_t> outputData;
    execute(memory, inputData, outputData);

    while(!outputData.empty()) {
        cout << outputData.front() << '\n';
        outputData.pop();
    }
}