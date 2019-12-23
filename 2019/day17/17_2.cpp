#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <algorithm>

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

void print(const vector<vector<char>>& grid) {
    for(auto& row : grid) {
        for(char c : row) {
            cout << c;
        }
        cout << '\n';
    }
}

bool isValid(const vector<vector<char>>& grid, int x, int y) {
    return y < grid.size() && y >= 0 &&
           x < grid.front().size() && x >= 0;
}

int main(int argc, char** argv)
{
    vector<int64_t> program;
    string input;
    cin >> input;
    stringstream stream(input);

    while (getline(stream, input, ',')) {
        program.push_back(stoll(input));
    }

    Intcode computer(program);
    computer.execute();

    vector<vector<char>> grid(1, vector<char>());
    int x, y;
    const vector<pair<int, int>> directions {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    while(computer.canRead()) {
        const char curr = static_cast<char>(computer.read());
        if (curr == '\n') grid.push_back(vector<char>());
        else {
            grid.back().push_back(curr);
            if(curr == '^') {
                y = grid.size() - 1;
                x = grid.back().size() - 1;
            }
        }
    }
    while(grid.back().empty()) grid.pop_back();

    vector<string> moves;
    int curr = 0;
    int dir = 0;

    while (true) {
        int tempX = x + directions[dir].second;
        int tempY = y + directions[dir].first;
        if(isValid(grid, tempX, tempY) && grid[tempY][tempX] == '#') {
            curr++;
            x = tempX;
            y = tempY;
        } else {
            if(curr > 0) {
                moves.push_back(to_string(curr));
                curr = 0;
            }
            tempX = x + directions[(dir + 1) % 4].second;
            tempY = y + directions[(dir + 1) % 4].first;
            if(isValid(grid, tempX, tempY) && grid[tempY][tempX] == '#') {
                dir = (dir + 1) % 4;
                moves.push_back("R");
            } else {
                tempX = x + directions[dir == 0 ? 3 : dir - 1].second;
                tempY = y + directions[dir == 0 ? 3 : dir - 1].first;
                if(isValid(grid, tempX, tempY) && grid[tempY][tempX] == '#') {
                    dir = dir == 0 ? 3 : dir - 1;
                    moves.push_back("L");
                } else {
                    break;
                }
            }
        }
    }

    for_each(moves.begin(), moves.end(), [](auto s){cout << s;});
    cout << '\n';

    // figured these out by hand
    string routine = "A,B,A,B,C,B,C,A,C,C\n";
    string funA = "R,12,L,10,L,10\n";
    string funB = "L,6,L,12,R,12,L,4\n";
    string funC = "L,12,R,12,L,6\n";

    program[0] = 2;
    computer = Intcode(program);

    auto write = [&computer](string s) {
        for(char c : s) {
            computer.write(c);
        }
    };

    write(routine);
    write(funA);
    write(funB);
    write(funC);
    write("n\n");
    computer.execute();

    while(computer.canRead()) {
        cout << computer.read() << '\n';
    }
}