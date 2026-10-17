
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100
#define AGING_INTERVAL 3

typedef struct {
    int pid;
    int arrival;
    int burst;
    int priority;
    int remaining;
    int waiting;
    int completion;
    int first_start;
    int finished;
    int last_reported_priority;
} Process;


int effective_priority(Process *p, int aging) {
    if (!aging)
        return p->priority;

    int improvement = p->waiting / AGING_INTERVAL;
    int effective = p->priority - improvement;

    if (effective < 0)
        effective = 0;

    return effective;
}

void simulate(Process original[], int n, int aging) {
    Process p[MAX];
    memcpy(p, original, n * sizeof(Process));

    int total_burst = 0;
    int max_arrival = 0;
    int completed = 0;
    int time = 0;

    for (int i = 0; i < n; i++) {
        total_burst += p[i].burst;
        if (p[i].arrival > max_arrival)
            max_arrival = p[i].arrival;
    }

    int capacity = total_burst + max_arrival + 1;
    int *timeline = malloc((size_t)capacity * sizeof(int));

    if (timeline == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    for (int i = 0; i < capacity; i++)
        timeline[i] = -1;

    printf("\n========================================\n");
    printf("MODE: %s\n",
           aging ? "DYNAMIC AGING ON" : "AGING OFF (BASELINE)");
    printf("========================================\n");

    while (completed < n && time < capacity) {
        int selected = -1;
        int best = 2147483647;

        /* Select the ready process with the best effective priority. */
        for (int i = 0; i < n; i++) {
            if (p[i].finished || p[i].arrival > time)
                continue;

            int priority = effective_priority(&p[i], aging);

            if (selected == -1 || priority < best ||
                (priority == best &&
                 p[i].arrival < p[selected].arrival)) {
                selected = i;
                best = priority;
            }
        }

        /* No process is ready: CPU remains idle for one time unit. */
        if (selected == -1) {
            timeline[time] = -1;
            time++;
            continue;
        }

        /* Record the first time each process gets the CPU. */
        if (p[selected].first_start == -1)
            p[selected].first_start = time;

        timeline[time] = p[selected].pid;

        /* Other ready processes wait and gain priority through aging. */
        for (int i = 0; i < n; i++) {
            if (i == selected || p[i].finished ||
                p[i].arrival > time)
                continue;

            p[i].waiting++;

            int current = effective_priority(&p[i], aging);

            if (aging &&
                current < p[i].last_reported_priority) {
                printf("[Time %d] P%d priority improved: %d -> %d"
                       " (waiting = %d)\n",
                       time + 1, p[i].pid,
                       p[i].last_reported_priority,
                       current, p[i].waiting);

                p[i].last_reported_priority = current;
            }
        }

        /* Execute the selected process for one time unit. */
        p[selected].remaining--;
        time++;

        if (p[selected].remaining == 0) {
            p[selected].finished = 1;
            p[selected].completion = time;
            completed++;
        }
    }

    /* Derive final waiting time from turnaround minus burst. */
    double total_waiting = 0;
    double total_turnaround = 0;
    double total_response = 0;

    printf("\nGANTT CHART:\n");
    printf("0");

    int previous = timeline[0];

    for (int t = 1; t <= time; t++) {
        if (t == time || timeline[t] != previous) {
            if (previous == -1)
                printf(" --IDLE-- ");
            else
                printf(" --P%d-- ", previous);

            printf("%d", t);

            if (t < time)
                previous = timeline[t];
        }
    }

    printf("\n\nPROCESS RESULTS:\n");
    printf("%-8s %-8s %-8s %-10s %-10s %-12s %-10s\n",
           "PID", "Arrival", "Burst", "Priority",
           "Completion", "Waiting", "Turnaround");
    printf("%-8s %-8s %-8s %-10s %-10s %-12s %-10s\n",
           "", "", "", "", "", "", "");

    for (int i = 0; i < n; i++) {
        int turnaround = p[i].completion - p[i].arrival;
        int waiting = turnaround - p[i].burst;
        int response = p[i].first_start - p[i].arrival;

        /* Waiting is computed from the standard scheduling formula. */
        p[i].waiting = waiting;

        total_waiting += waiting;
        total_turnaround += turnaround;
        total_response += response;

        printf("P%-7d %-8d %-8d %-10d %-10d %-12d %-10d\n",
               p[i].pid, p[i].arrival, p[i].burst,
               p[i].priority, p[i].completion,
               waiting, turnaround);

        printf("        Response time: %d\n", response);
    }

    printf("\nAverage waiting time: %.2f\n",
           total_waiting / n);
    printf("Average turnaround time: %.2f\n",
           total_turnaround / n);
    printf("Average response time: %.2f\n",
           total_response / n);

    free(timeline);
}

int main(void) {
    Process p[MAX];
    int n;

    printf("========================================\n");
    printf(" SMART CPU SCHEDULER\n");
    printf(" Dynamic Priority Adjustment using Aging\n");
    printf("========================================\n");
    printf("Lower priority number = higher priority\n");
    printf("Aging interval = %d waiting time units\n",
           AGING_INTERVAL);

    printf("\nEnter number of processes (1-%d): ", MAX);

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("\nProcess P%d\n", p[i].pid);

        printf("Arrival time (0-100000): ");
        if (scanf("%d", &p[i].arrival) != 1 ||
            p[i].arrival < 0 || p[i].arrival > 100000) {
            printf("Invalid arrival time.\n");
            return 1;
        }

        printf("Burst time (1-100000): ");
        if (scanf("%d", &p[i].burst) != 1 ||
            p[i].burst < 1 || p[i].burst > 100000) {
            printf("Invalid burst time.\n");
            return 1;
        }

        printf("Initial priority (0-100000): ");
        if (scanf("%d", &p[i].priority) != 1 ||
            p[i].priority < 0 || p[i].priority > 100000) {
            printf("Invalid priority.\n");
            return 1;
        }

        p[i].remaining = p[i].burst;
        p[i].waiting = 0;
        p[i].completion = 0;
        p[i].first_start = -1;
        p[i].finished = 0;
        p[i].last_reported_priority = p[i].priority;
    }

    printf("\nRunning comparison with the same processes...\n");

    simulate(p, n, 0);
    simulate(p, n, 1);

    printf("\nComparison completed.\n");

    return 0;
}
