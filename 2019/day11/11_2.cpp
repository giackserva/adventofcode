#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <map>

using namespace std;

array<int, 4> parseInstruction(int instruction) {
    array<int, 4> ret;
    ret[0] = instruction % 100;
    ret[1] = instruction / 100 % 10;
    ret[2] = instruction / 1000 % 10;
    ret[3] = instruction / 10000 % 10;
    return ret;
}

array<int, 3> execute(unordered_map<int64_t,int64_t>& memory,
        int pc, int relativeBase, queue<int64_t>& input, queue<int64_t>& output)
{
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

    while (true) {
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
            if(input.empty()) {
                return {0, pc, relativeBase};
            }
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
    return {1, pc, relativeBase};
}

int main(int argc, char** argv)
{
    unordered_map<int64_t, int64_t> memory;
    string input;
    cin >> input;
    stringstream stream(input);

    int i = 0;
    while (getline(stream, input, ',')) {
        memory[i++] = stoll(input);
    }

    queue<int64_t> inputData;
    queue<int64_t> outputData;
    int pc = 0;
    int relativeBase = 0;
    bool terminated = false;
    map<pair<int, int>, int> grid;
    int pos_x = 0;
    int pos_y = 0;
    grid[{pos_x, pos_y}] = 1;
    vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int currDir = 0;

    do {
        const int color = grid[{pos_x, pos_y}];
        inputData.push(color);
        auto ret = execute(memory, pc, relativeBase, inputData, outputData);
        terminated = ret[0];
        pc = ret[1];
        relativeBase = ret[2];
        if(!outputData.empty()) {
            grid[{pos_x, pos_y}] = outputData.front();
            outputData.pop();
            currDir += outputData.front() ? outputData.front() : -1;
            if (currDir == -1) currDir = 3;
            currDir %= 4;
            outputData.pop();

            pos_x += dirs[currDir].first;
            pos_y += dirs[currDir].second;
        }
    } while (!terminated);

    for(int y = 10; y > -10; y--) {
        for(int x = -10; x < 50; x++) {
            cout << (grid[{x, y}] ? 'x' : ' ');
        }
        cout << '\n';
    }
}