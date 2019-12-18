#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <set>

using namespace std;

class Intcode {
    int                             d_programCounter;
    int                             d_relativeBase;
    unordered_map<int64_t, int64_t> d_memory;
    queue<int64_t>                  d_input;
    queue<int64_t>                  d_output;

    array<int, 4> parseInstruction(int instruction) {
        array<int, 4> ret;
        ret[0] = instruction % 100;
        ret[1] = instruction / 100 % 10;
        ret[2] = instruction / 1000 % 10;
        ret[3] = instruction / 10000 % 10;
        return ret;
    }

    int64_t loadValue (int64_t operand, int mode) {
        if(mode == 0)
            return d_memory[operand];
        else if(mode == 1)
            return operand;
        return d_memory[operand + d_relativeBase];
    }

    void storeValue (int64_t operand, int mode, int64_t value) {
        if(mode == 2) d_memory[operand + d_relativeBase] = value;
        else d_memory[operand] = value;
    }

public:

    Intcode(const vector<int64_t>& program)
    : d_programCounter (0)
    , d_relativeBase   (0)
    , d_memory         ()
    , d_input          ()
    , d_output         ()
    {
        for(int i = 0; i < program.size(); ++i) {
            d_memory.insert({i, program[i]});
        }
    }

    Intcode(const Intcode& rhs)
    : d_programCounter (rhs.d_programCounter)
    , d_relativeBase   (rhs.d_relativeBase)
    , d_memory         (rhs.d_memory)
    , d_input          (rhs.d_input)
    , d_output         (rhs.d_output)
    {
    }

    bool execute()
    {
        while (true) {
            const int raw = d_memory[d_programCounter];
            const auto instruction = parseInstruction(raw);
            const int opcode = instruction[0];
            if (opcode == 99) break;

            const int64_t op1 = d_memory[d_programCounter + 1];
            const int64_t op2 = d_memory[d_programCounter + 2];
            const int64_t op3 = d_memory[d_programCounter + 3];
            const int64_t value1 = loadValue(op1, instruction[1]);
            const int64_t value2 = loadValue(op2, instruction[2]);

            if(opcode == 1) {
                storeValue(op3, instruction[3], value1 + value2);
                d_programCounter += 4;
            }
            else if(opcode == 2) {
                storeValue(op3, instruction[3], value1 * value2);
                d_programCounter += 4;
            }
            else if(opcode == 3) {
                if(d_input.empty()) {
                    return false;
                }
                storeValue(op1, instruction[1], d_input.front());
                d_input.pop();
                d_programCounter += 2;
            }
            else if(opcode == 4) {
                d_output.push(value1);
                d_programCounter += 2;
            }
            else if(opcode == 5) {
                if (value1) d_programCounter = value2;
                else d_programCounter += 3;
            }
            else if(opcode == 6) {
                if (!value1) d_programCounter = value2;
                else d_programCounter += 3;
            }
            else if(opcode == 7) {
                storeValue(op3, instruction[3], value1 < value2 ? 1 : 0);
                d_programCounter += 4;
            }
            else if(opcode == 8) {
                storeValue(op3, instruction[3], value1 == value2 ? 1 : 0);
                d_programCounter += 4;
            }
            else if(opcode == 9) {
                d_relativeBase += value1;
                d_programCounter += 2;
            }
        }
        return true;
    }

    void write(int64_t value) {
        d_input.push(value);
    }

    int64_t read() {
        int64_t temp = d_output.front();
        d_output.pop();
        return temp;
    }

    bool canRead() {
        return !d_output.empty();
    }
};

struct State {
    Intcode computer;
    int depth;
    int x;
    int y;
};

int main(int argc, char** argv)
{
    vector<int64_t> program;
    string input;
    cin >> input;
    stringstream stream(input);

    while (getline(stream, input, ',')) {
        program.push_back(stoll(input));
    }

    vector<pair<int, int>> commands {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

    queue<State> states;
    State init { Intcode(program), 0, 0, 0 };
    states.push(init);

    set<pair<int, int>> visited;
    visited.insert({0, 0});

    while(!states.empty()) {
        const State& state = states.front();
        for(int command = 0; command < commands.size(); command++) {
            Intcode tmp (state.computer);
            tmp.write(command + 1);
            tmp.execute();
            const int res = tmp.read();
            if(res == 2) {
                cout << state.depth + 1 << '\n';
                return 0;
            } else if (res == 1) {
                const pair<int, int> newPos = { state.x + commands[command].first,
                                                state.y + commands[command].second };
                if(visited.find(newPos) == visited.end()) {
                    visited.insert(newPos);
                    states.push(State{ tmp, state.depth + 1, newPos.first, newPos.second });
                }
            }
        }
        states.pop();
    }
}