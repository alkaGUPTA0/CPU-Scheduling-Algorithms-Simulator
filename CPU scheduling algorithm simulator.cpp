#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

struct Process {
    int pid;
    int burst_time;
    int arrival_time;
    int priority;
    int waiting_time;
    int turnaround_time;
};

void calculateAverageTimes(const vector<Process>& processes) {
    int total_waiting_time = 0, total_turnaround_time = 0;
    for (const auto& p : processes) {
        total_waiting_time += p.waiting_time;
        total_turnaround_time += p.turnaround_time;
    }

    double avg_waiting_time = (double)total_waiting_time / processes.size();
    double avg_turnaround_time = (double)total_turnaround_time / processes.size();

    cout << "Average Waiting Time: " << avg_waiting_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;
}

void fcfs(vector<Process>& processes) {
    cout << "\n--- First Come First Serve Scheduling ---\n";
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
    });

    int time = 0;
    for (auto& p : processes) {
        if (time < p.arrival_time) time = p.arrival_time;
        p.waiting_time = time - p.arrival_time;
        time += p.burst_time;
        p.turnaround_time = p.waiting_time + p.burst_time;
    }

    calculateAverageTimes(processes);
}

void priorityScheduling(vector<Process>& processes) {
    cout << "\n--- Priority Scheduling ---\n";
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        if (a.priority == b.priority)
            return a.arrival_time < b.arrival_time;
        return a.priority < b.priority;
    });

    int time = 0;
    for (auto& p : processes) {
        if (time < p.arrival_time) time = p.arrival_time;
        p.waiting_time = time - p.arrival_time;
        time += p.burst_time;
        p.turnaround_time = p.waiting_time + p.burst_time;
    }

    calculateAverageTimes(processes);
}

void roundRobin(vector<Process>& processes, int quantum) {
    cout << "\n--- Round Robin Scheduling ---\n";
    vector<int> remaining_time(processes.size());

    int time = 0;
    for (int i = 0; i < processes.size(); i++) {
        remaining_time[i] = processes[i].burst_time;
    }

    while (true) {
        bool done = true;

        for (int i = 0; i < processes.size(); i++) {
            if (remaining_time[i] > 0) {
                done = false;

                if (remaining_time[i] > quantum) {
                    time += quantum;
                    remaining_time[i] -= quantum;
                } else {
                    time += remaining_time[i];
                    processes[i].waiting_time = time - processes[i].burst_time - processes[i].arrival_time;
                    remaining_time[i] = 0;
                }
            }
        }

        if (done)
            break;
    }

    for (auto& p : processes) {
        p.turnaround_time = p.burst_time + p.waiting_time;
    }

    calculateAverageTimes(processes);
}

void sjfNonPreemptive(vector<Process>& processes) {
    cout << "\n--- Shortest Job First (Non-Preemptive) Scheduling ---\n";
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        if (a.arrival_time == b.arrival_time)
            return a.burst_time < b.burst_time;
        return a.arrival_time < b.arrival_time;
    });

    int time = 0;
    vector<Process> readyQueue;
    vector<Process> result;

    while (!processes.empty() || !readyQueue.empty()) {
        while (!processes.empty() && processes.front().arrival_time <= time) {
            readyQueue.push_back(processes.front());
            processes.erase(processes.begin());
        }

        if (!readyQueue.empty()) {
            sort(readyQueue.begin(), readyQueue.end(), [](const Process& a, const Process& b) {
                return a.burst_time < b.burst_time;
            });

            Process current = readyQueue.front();
            readyQueue.erase(readyQueue.begin());

            current.waiting_time = time - current.arrival_time;
            time += current.burst_time;
            current.turnaround_time = current.waiting_time + current.burst_time;

            result.push_back(current);
        } else {
            time++;
        }
    }

    calculateAverageTimes(result);
}

void sjfPreemptive(vector<Process>& processes) {
    cout << "\n--- Shortest Job First (Preemptive) Scheduling ---\n";
    int n = processes.size();
    vector<int> remaining_time(n);
    vector<int> waiting_time(n, 0);
    int completed = 0, time = 0, min_burst = INT_MAX, shortest = 0, finish_time;
    bool found = false;

    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
    }

    while (completed != n) {
        for (int j = 0; j < n; j++) {
            if (processes[j].arrival_time <= time && remaining_time[j] < min_burst && remaining_time[j] > 0) {
                min_burst = remaining_time[j];
                shortest = j;
                found = true;
            }
        }

        if (!found) {
            time++;
            continue;
        }

        remaining_time[shortest]--;
        min_burst = remaining_time[shortest];

        if (min_burst == 0)
            min_burst = INT_MAX;

        if (remaining_time[shortest] == 0) {
            completed++;
            finish_time = time + 1;
            processes[shortest].waiting_time = finish_time - processes[shortest].burst_time - processes[shortest].arrival_time;

            if (processes[shortest].waiting_time < 0)
                processes[shortest].waiting_time = 0;
        }

        time++;
    }

    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
    }

    calculateAverageTimes(processes);
}

void inputProcesses(vector<Process>& processes) {
    int num_processes;
    cout << "Enter the number of processes: ";
    cin >> num_processes;

    for (int i = 0; i < num_processes; i++) {
        Process p;
        p.pid = i + 1;

        cout << "Enter burst time for process " << p.pid << ": ";
        cin >> p.burst_time;

        cout << "Enter arrival time for process " << p.pid << ": ";
        cin >> p.arrival_time;

        cout << "Enter priority for process " << p.pid << " (lower number = higher priority): ";
        cin >> p.priority;

        p.waiting_time = 0;
        p.turnaround_time = 0;

        processes.push_back(p);
    }
}

void selectSchedulingAlgorithm(vector<Process>& processes) {
    int choice;
    cout << "\nSelect the scheduling algorithm:\n";
    cout << "1. First Come First Serve (FCFS)\n";
    cout << "2. Priority Scheduling\n";
    cout << "3. Round Robin\n";
    cout << "4. Shortest Job First (Non-Preemptive)\n";
    cout << "5. Shortest Job First (Preemptive)\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            fcfs(processes);
            break;
        case 2:
            priorityScheduling(processes);
            break;
        case 3: {
            int quantum;
            cout << "Enter the time quantum for Round Robin: ";
            cin >> quantum;
            roundRobin(processes, quantum);
            break;
        }
        case 4:
            sjfNonPreemptive(processes);
            break;
        case 5:
            sjfPreemptive(processes);
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
    }
}

void displayProcesses(const vector<Process>& processes) {
    cout << "PID\tBurst Time\tArrival Time\tPriority\tWaiting Time\tTurnaround Time\n";
    for (const auto& p : processes) {
        cout << p.pid << "\t" << p.burst_time << "\t\t" << p.arrival_time << "\t\t"
             << p.priority << "\t\t" << p.waiting_time << "\t\t" << p.turnaround_time << endl;
    }
}



int main() {
    vector<Process> processes;

    inputProcesses(processes);

    selectSchedulingAlgorithm(processes);

    displayProcesses(processes);

    return 0;
}
