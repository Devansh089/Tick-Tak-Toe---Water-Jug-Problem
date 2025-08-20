#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;

struct JugState {
    int a, b;
    vector<string> actions;
};

void solveWaterJug(int capA, int capB, int goal) {
    set<pair<int, int>> seen;
    queue<JugState> states;

    states.push({0, 0, {}});
    seen.insert({0, 0});

    while (!states.empty()) {
        JugState current = states.front();
        states.pop();

        int jugA = current.a, jugB = current.b;

        if (jugA == goal || jugB == goal) {
            cout << "Steps to reach target:\n";
            for (const auto& act : current.actions)
                cout << act << "\n";
            cout << "Final State: (" << jugA << ", " << jugB << ")\n";
            return;
        }

        vector<JugState> next;

        // Fill Jug A
        next.push_back({capA, jugB, current.actions});
        next.back().actions.push_back("Fill Jug A");

        // Fill Jug B
        next.push_back({jugA, capB, current.actions});
        next.back().actions.push_back("Fill Jug B");

        // Empty Jug A
        next.push_back({0, jugB, current.actions});
        next.back().actions.push_back("Empty Jug A");

        // Empty Jug B
        next.push_back({jugA, 0, current.actions});
        next.back().actions.push_back("Empty Jug B");

        // Pour A → B
        {
            int transfer = min(jugA, capB - jugB);
            next.push_back({jugA - transfer, jugB + transfer, current.actions});
            next.back().actions.push_back("Pour A → B");
        }

        // Pour B → A
        {
            int transfer = min(jugB, capA - jugA);
            next.push_back({jugA + transfer, jugB - transfer, current.actions});
            next.back().actions.push_back("Pour B → A");
        }

        for (auto& nxt : next) {
            if (!seen.count({nxt.a, nxt.b})) {
                seen.insert({nxt.a, nxt.b});
                states.push(nxt);
            }
        }
    }

    cout << "No solution found.\n";
}

int main() {
    int capacityA, capacityB, target;
    cout << "Capacity of Jug A: ";
    cin >> capacityA;
    cout << "Capacity of Jug B: ";
    cin >> capacityB;
    cout << "Desired amount: ";
    cin >> target;

    if (target > max(capacityA, capacityB)) {
        cout << "Target exceeds both jug capacities.\n";
        return 0;
    }

    solveWaterJug(capacityA, capacityB, target);
    return 0;
}