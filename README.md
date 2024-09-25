Technologies Used: C++, Data Structures (Vectors), Algorithms

Description:
Developed a C++ program that simulates various CPU scheduling algorithms including First Come First Serve (FCFS), Priority Scheduling, Round Robin, and Shortest Job First (SJF) with both preemptive and non-preemptive variants.
Implemented process scheduling algorithms to calculate key performance metrics such as waiting time and turnaround time for a set of user-defined processes.
Integrated user input functionality to allow dynamic selection of scheduling algorithms and process attributes like burst time, arrival time, and priority.
Designed and optimized the program to display process details and performance metrics to aid in understanding different scheduling strategies.

Key Features:
Algorithm Selection: Allows users to choose between five major scheduling algorithms.
Time Metrics Calculation: Calculates and displays average waiting time and turnaround time.
Dynamic Quantum Input for Round Robin: Supports user-defined quantum for Round Robin scheduling.
Preemptive & Non-Preemptive Scheduling: Includes implementations for both preemptive and non-preemptive scheduling techniques.

Working:
The project allows users to simulate different CPU scheduling algorithms (FCFS, Priority Scheduling, Round Robin, SJF Preemptive/Non-Preemptive). The user inputs the number of processes along with their burst time, arrival time, and priority. Based on the selected scheduling algorithm, the program calculates each process's waiting time and turnaround time.

For Round Robin, the user specifies a time quantum, and the processes are executed in a time-shared manner. The results for each scheduling algorithm, including average waiting time and turnaround time, are displayed, helping the user understand the efficiency of different CPU scheduling methods.
