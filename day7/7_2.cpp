#include <algorithm>
#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <queue>
#include <tuple>

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

pair<bool, int> execute(vector<int>& memory, int pc, queue<int>& input, queue<int>& output)
{
    while (pc < memory.size()) {
        const int raw = memory[pc];
        const auto instruction = parseInstruction(raw);
        const int opcode = instruction[0];
        if (opcode == 99) break;

        const int op1 = memory[pc+1];
        const int op2 = memory[pc+2];
        const int op3 = memory[pc+3];
        const int value1 = instruction[1] ? op1 : memory[op1];
        const int value2 = instruction[2] ? op2 : memory[op2];

        if(opcode == 1) {
            memory[op3] = value1 + value2;
            pc += 4;
        }
        else if(opcode == 2) {
            memory[op3] = value1 * value2;
            pc += 4;
        }
        else if(opcode == 3) {
            int in;

            if (!input.size()) {
                return { false, pc };
            }

            in = input.front();
            input.pop();
            memory[op1] = in;
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
            memory[op3] = value1 < value2 ? 1 : 0;
            pc += 4;
        }
        else if(opcode == 8) {
            memory[op3] = value1 == value2 ? 1 : 0;
            pc += 4;
        }
    }

    return { true, pc };
}

int main(int argc, char** argv)
{
    vector<int> memory;
    string input;
    cin >> input;
    stringstream stream(input);

    while (getline(stream, input, ',')) {
        memory.push_back(stoi(input));
    }

    string phaseSettings("56789");

    vector<vector<int>> amps;
    queue<pair<int, int>> ops;
    vector<queue<int>> streams;
    string maxPhase = phaseSettings;
    int maxSignal = 0;

    do {
        amps.clear(); amps.resize(5, memory);
        streams.clear(); streams.resize(5);
        for(int i = 0; i < 5; i++) {
            ops.push({i, 0});
            streams[i].push(phaseSettings[i] - '0');
        }
        streams[0].push(0);

        while (ops.size()) {
            bool terminated;
            int amp, pc;
            tie(amp, pc) = ops.front(); ops.pop();
            tie(terminated, pc) =
                execute(amps[amp], pc, streams[amp], streams[(amp + 1) % 5]);
            if(!terminated) ops.push({amp, pc});
        }

        int result = streams[0].front();
        streams[0].pop();

        if (result > maxSignal) {
            maxPhase = phaseSettings;
            maxSignal = result;
        }
    } while(next_permutation(phaseSettings.begin(), phaseSettings.end()));

    cout << maxSignal << ' ' << maxPhase << '\n';
}