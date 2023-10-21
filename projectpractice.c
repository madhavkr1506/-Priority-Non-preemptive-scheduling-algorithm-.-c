#include <stdio.h>

int main() {
    int n;  // Number of Processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int CPU = 0;         // CPU Current time
    int allTime = 0;     // Time needed to finish all processes

    int arrivaltime[n];
    int bursttime[n];
    int priority[n];
    int ATt[n];
    int NoP = n;        // Number of Processes
    int PPt[n];
    int waitingTime[n];
    int turnaroundTime[n];
    int completionTime[n];  // Added an array to store completion times
    int i = 0;

    for (i = 0; i < n; i++) {
        printf("Enter Arrival Time for Process %d: ", i + 1);
        scanf("%d", &arrivaltime[i]);
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &bursttime[i]);
        printf("Enter Priority for Process %d: ", i + 1);
        scanf("%d", &priority[i]);

        PPt[i] = priority[i];
        ATt[i] = arrivaltime[i];
    }

    int LAT = 0;        // Last Arrival Time
    for (i = 0; i < n; i++)
        if (arrivaltime[i] > LAT)
            LAT = arrivaltime[i];

    int MAX_P = 0;      // Max Priority
    for (i = 0; i < n; i++)
        if (PPt[i] > MAX_P)
            MAX_P = PPt[i];

    int ATi = 0;         // Pointing to Arrival Time index
    int P1 = PPt[0];     // Pointing to 1st priority Value
    int P2 = PPt[0];     // Pointing to 2nd priority Value

    int j = -1;
    while (NoP > 0 && CPU <= 1000) {
        for (i = 0; i < n; i++) {
            if ((ATt[i] <= CPU) && (ATt[i] != (LAT + 10))) {
                if (PPt[i] != (MAX_P + 1)) {
                    P2 = PPt[i];
                    j = 1;

                    if (P2 < P1) {
                        j = 1;
                        ATi = i;
                        P1 = PPt[i];
                        P2 = PPt[i];
                    }
                }
            }
        }

        if (j == -1) {
            CPU = CPU + 1;
            continue;
        } else {
            waitingTime[ATi] = CPU - ATt[ATi];
            CPU = CPU + bursttime[ATi];
            turnaroundTime[ATi] = CPU - ATt[ATi];
            completionTime[ATi] = CPU; // Store the completion time
            ATt[ATi] = LAT + 10;
            j = -1;
            PPt[ATi] = MAX_P + 1;
            ATi = 0;            // Pointing to Arrival Time index
            P1 = MAX_P + 1;     // Pointing to 1st priority Value
            P2 = MAX_P + 1;     // Pointing to 2nd priority Value
            NoP = NoP - 1;
        }
    }

    printf("\nProcess_Number\tBurst_Time\tPriority\tArrival_Time\tCompletion_Time\tWaiting_Time\tTurnaround_Time\n\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, bursttime[i], priority[i], arrivaltime[i], completionTime[i], waitingTime[i], turnaroundTime[i]);
    }

    float AvgWT = 0;    // Average waiting time
    float AVGTaT = 0;   // Average Turnaround time
    for (i = 0; i < n; i++) {
        AvgWT = waitingTime[i] + AvgWT;
        AVGTaT = turnaroundTime[i] + AVGTaT;
    }

    printf("Average waiting time = %f\n", AvgWT / n);
    printf("Average turnaround time = %f\n", AVGTaT / n);
    return 0;
}
