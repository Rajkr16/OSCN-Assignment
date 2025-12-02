#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Process {
    string pid;
    int at, bt;
    int ct, tat, wt;
    bool completed = false;
};

struct GanttBlock {
    string pid;
    int start;
    int end;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    cout << "Enter Process ID, Arrival Time and Burst Time:\n";
    for (int i = 0; i < n; i++) {
        cin >> p[i].pid >> p[i].at >> p[i].bt;
    }

    int completedCount = 0;
    int current_time = 0;
    float total_tat = 0, total_wt = 0;
    vector<GanttBlock> gantt;

    while (completedCount < n) {
        int idx = -1;
        int minBT = 1e9;

        // Find process with minimum BT among arrived and not completed
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= current_time) {
                if (p[i].bt < minBT) {
                    minBT = p[i].bt;
                    idx = i;
                } else if (p[i].bt == minBT) {
                    // Optional: tie-breaking by arrival time or ID
                    if (p[i].at < p[idx].at)
                        idx = i;
                }
            }
        }

        if (idx == -1) {
            // No process has arrived yet → CPU idle
            GanttBlock idleBlock;
            idleBlock.pid = "IDLE";
            idleBlock.start = current_time;
            idleBlock.end = current_time + 1;
            gantt.push_back(idleBlock);
            current_time++;
        } else {
            // Schedule this process
            GanttBlock block;
            block.pid = p[idx].pid;
            block.start = current_time;

            current_time += p[idx].bt;
            block.end = current_time;
            gantt.push_back(block);

            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            p[idx].completed = true;
            completedCount++;

            total_tat += p[idx].tat;
            total_wt += p[idx].wt;
        }
    }

    cout << "\n-------------------------------------------------------------\n";
    cout << "Process\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "-------------------------------------------------------------\n";

    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << "\n";
    }

    cout << "-------------------------------------------------------------\n";
    cout << "Total Turnaround Time   = " << total_tat << "\n";
    cout << "Average Turnaround Time = " << total_tat / n << "\n";
    cout << "Total Waiting Time      = " << total_wt << "\n";
    cout << "Average Waiting Time    = " << total_wt / n << "\n";

    // Print Gantt Chart
    cout << "\nGantt Chart:\n";

    // Top bar
    cout << " ";
    for (auto &g : gantt) {
        cout << "-------";
    }
    cout << "\n|";
    // Process IDs
    for (auto &g : gantt) {
        cout << "  " << setw(3) << g.pid << " |";
    }
    cout << "\n ";
    for (auto &g : gantt) {
        cout << "-------";
    }
    cout << "\n";

    // Time labels
    cout << 0;
    for (auto &g : gantt) {
        cout << setw(7) << g.end;
    }
    cout << "\n";

    return 0;
}
