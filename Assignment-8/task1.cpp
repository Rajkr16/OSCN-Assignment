#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Process {
    string pid;
    int at, bt, ct, tat, wt;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter Process ID, Arrival Time & Burst Time: ";
        cin >> p[i].pid >> p[i].at >> p[i].bt;
    }

    // Sort by Arrival Time
    sort(p.begin(), p.end(), [](Process a, Process b) {
        return a.at < b.at;
    });

    int current_time = 0;
    float total_tat = 0, total_wt = 0;

    for (int i = 0; i < n; i++) {
        if (current_time < p[i].at) {
            current_time = p[i].at; // CPU idle time handling
        }
        p[i].ct = current_time + p[i].bt;
        current_time = p[i].ct;

        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }

    cout << "\n---------------------------------------------------------\n";
    cout << "Process\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "---------------------------------------------------------\n";

    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t"
             << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << endl;
    }

    cout << "---------------------------------------------------------\n";
    cout << "Total Turnaround Time: " << total_tat << endl;
    cout << "Average Turnaround Time: " << total_tat / n << endl;
    cout << "Total Waiting Time: " << total_wt << endl;
    cout << "Average Waiting Time: " << total_wt / n << endl;

    return 0;
}
