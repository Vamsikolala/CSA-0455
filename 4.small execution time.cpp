#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 100

typedef struct {
    int pid;         // Process ID
    int arrivalTime; // Arrival time
    int burstTime;   // Burst time
    int waitingTime; // Waiting time
    int turnaroundTime; // Turnaround time
    bool completed;  // Flag to check if process is completed
} Process;

// Function to sort processes based on arrival time
void sortByArrivalTime(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

// Function to find the next process to execute based on SJF
int findNextProcess(Process processes[], int n, int currentTime) {
    int minBurstTime = __INT_MAX__;
    int nextProcessIndex = -1;
    for (int i = 0; i < n; i++) {
        if (!processes[i].completed && processes[i].arrivalTime <= currentTime) {
            if (processes[i].burstTime < minBurstTime) {
                minBurstTime = processes[i].burstTime;
                nextProcessIndex = i;
            }
        }
    }
    return nextProcessIndex;
}

// Main function to implement SJF Scheduling
int main() {
    int n;
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time for process P%d: ", processes[i].pid);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for process P%d: ", processes[i].pid);
        scanf("%d", &processes[i].burstTime);
        processes[i].completed = false;
    }

    // Sort processes by arrival time
    sortByArrivalTime(processes, n);

    // Variables to track current time and total waiting/turnaround time
    int currentTime = 0, completedProcesses = 0;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    // Process scheduling loop
    while (completedProcesses < n) {
        int nextProcessIndex = findNextProcess(processes, n, currentTime);

        if (nextProcessIndex == -1) {
            // No process is ready, increment time
            currentTime++;
        } else {
            // Execute the next process
            Process *p = &processes[nextProcessIndex];
            p->waitingTime = currentTime - p->arrivalTime;
            p->turnaroundTime = p->waitingTime + p->burstTime;
            currentTime += p->burstTime;
            p->completed = true;

            // Update totals
            totalWaitingTime += p->waitingTime;
            totalTurnaroundTime += p->turnaroundTime;
            completedProcesses++;
        }
    }

    // Display results
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", 
               processes[i].pid, 
               processes[i].arrivalTime, 
               processes[i].burstTime, 
               processes[i].waitingTime, 
               processes[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);

    return 0;
}

