#include <stdio.h>

// Function to calculate waiting time for each process
void calculateWaitingTime(int processes[], int n, int burstTime[], int waitingTime[]) {
    waitingTime[0] = 0; // First process has no waiting time

    // Calculate waiting time for each process
    for (int i = 1; i < n; i++) {
        waitingTime[i] = waitingTime[i - 1] + burstTime[i - 1];
    }
}

// Function to calculate turnaround time for each process
void calculateTurnaroundTime(int processes[], int n, int burstTime[], int waitingTime[], int turnaroundTime[]) {
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = burstTime[i] + waitingTime[i];
    }
}

// Function to display the scheduling details
void displaySchedulingDetails(int processes[], int n, int burstTime[], int waitingTime[], int turnaroundTime[]) {
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", processes[i], burstTime[i], waitingTime[i], turnaroundTime[i]);
    }
}

// Main function to implement FCFS scheduling
int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], burstTime[n], waitingTime[n], turnaroundTime[n];
    
    // Assign process IDs
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
    }

    // Input burst times
    printf("Enter the burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Burst time for process P%d: ", i + 1);
        scanf("%d", &burstTime[i]);
    }

    // Calculate waiting time and turnaround time
    calculateWaitingTime(processes, n, burstTime, waitingTime);
    calculateTurnaroundTime(processes, n, burstTime, waitingTime, turnaroundTime);

    // Display scheduling details
    displaySchedulingDetails(processes, n, burstTime, waitingTime, turnaroundTime);

    // Calculate average waiting time and turnaround time
    float avgWaitingTime = 0, avgTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        avgWaitingTime += waitingTime[i];
        avgTurnaroundTime += turnaroundTime[i];
    }
    avgWaitingTime /= n;
    avgTurnaroundTime /= n;

    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
    return 0;
}

