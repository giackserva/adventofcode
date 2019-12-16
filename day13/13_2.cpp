#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <queue>
#include <unordered_map>

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

int main(int argc, char** argv)
{
    vector<int64_t> program;
    string input;
    cin >> input;
    stringstream stream(input);

    while (getline(stream, input, ',')) {
        program.push_back(stoll(input));
    }

    program[0] = 2;
    Intcode computer {program};
    int score = 0;

    while(true) {
        const bool terminate = computer.execute();
        int ball_x;
        int bar_x;

        while(computer.canRead()) {
            const int x = computer.read();
            const int y = computer.read();
            const int pixel = computer.read();

            if(x == -1 && y == 0) {
                score = pixel;
                continue;
            }

            if (pixel == 4) ball_x = x;
            else if (pixel == 3) bar_x = x;
        }

        if (terminate) break;

        int input = 0;
        if (ball_x < bar_x) input = -1;
        else if (ball_x > bar_x) input = 1;
        computer.write(input);
    }

    cout << score << '\n';
}