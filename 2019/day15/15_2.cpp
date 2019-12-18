#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <set>
#include <map>
#include <thread>

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

void render(const vector<vector<char>>& grid) {
    for(int y = 49; y >=0; y--) {
        for(int x = 0; x < 50; x++) {
            cout << grid[x][y];
        }
        cout << '\n';
    }
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

    vector<pair<int, int>> commands {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

    const int size = 50;
    const int init_x = size / 2;
    const int init_y = size / 2;
    queue<State> states;
    State init { Intcode(program), 0, init_x, init_y };
    states.push(init);

    set<pair<int, int>> visited;
    visited.insert({init_x, init_y});

    vector<vector<char>> grid (size, vector<char>(size, ' '));
    grid[init_x][init_y] = 'O';

    int oxygen_x;
    int oxygen_y;

    while(!states.empty()) {
        const State& state = states.front();
        for(int command = 0; command < commands.size(); command++) {
            Intcode tmp (state.computer);
            tmp.write(command + 1);
            tmp.execute();
            const int res = tmp.read();
            const int newX = state.x + commands[command].first;
            const int newY = state.y + commands[command].second;
            if(res == 0) {
                grid[newX][newY] = '#';
            } else {
                auto [ignore, inserted] = visited.insert({newX, newY});
                if(inserted) {
                    states.push(State{ tmp, state.depth + 1, newX, newY });
                    if (res == 2) {
                        oxygen_x = newX;
                        oxygen_y = newY;
                    }
                    grid[newX][newY] = res == 2 ? '*': '.';
                }
            }
        }
        states.pop();
    }

    int res = 0;
    queue<pair<pair<int, int>, int>> search;
    search.push({ {oxygen_x, oxygen_y}, res});

    visited.clear();

    while(!search.empty()) {
        auto& [pos, depth] = search.front();
        res = max(res, depth);
        for(int command = 0; command < commands.size(); command++) {
            const int newX = pos.first + commands[command].first;
            const int newY = pos.second + commands[command].second;
            if(grid[newX][newY] == '#') continue;
            auto [ignore, inserted] = visited.insert({newX, newY});
            if(inserted) {
                search.push({ {newX, newY}, depth + 1 });
            }
        }

        search.pop();
    }

    cout << res << '\n';
}
