# Smart CPU Scheduler with Dynamic Priority Adjustment

## 1. Project Overview

The Smart CPU Scheduler is a CPU scheduling simulator developed in C. It compares priority scheduling without aging against priority scheduling with dynamic aging.

The objective is to demonstrate how aging gradually improves the effective priority of waiting processes and can reduce the risk of starvation.

## 2. Objectives

- Implement priority-based CPU scheduling.
- Demonstrate dynamic priority adjustment using aging.
- Support preemptive scheduling.
- Generate Gantt charts to show process execution.
- Calculate waiting time, turnaround time, and response time.
- Compare baseline scheduling with aging-enabled scheduling.

## 3. Technologies Used

- Programming language: C
- Operating system: Ubuntu Linux
- Compiler: GCC
- Standard: C11

## 4. Algorithm

The simulator considers each process's arrival time, burst time, and initial priority.

Lower priority numbers represent higher scheduling priority. When aging is enabled, the effective priority improves after every three waiting time units.

Effective priority is calculated as:

`Effective Priority = Initial Priority - (Waiting Time / Aging Interval)`

The effective priority cannot fall below zero.

The scheduler selects the ready process with the best effective priority at each time unit. If another process becomes more important because of aging, it can preempt the running process.

## 5. Compilation and Execution

Compile the program:

```bash
gcc -Wall -Wextra -std=c11 scheduler.c -o scheduler
```

Run the program:

```bash
./scheduler
```

Enter the number of processes, followed by each process's arrival time, burst time, and initial priority.

## 6. Output

The program displays:

- Baseline scheduling results without aging.
- Dynamic aging priority-change messages.
- Gantt charts for both scheduling modes.
- Process completion times.
- Waiting, turnaround, and response times.
- Average performance metrics.

## 7. Testing

The simulator should be tested with different arrival times, burst times, and initial priorities. Compare the Gantt charts and metrics to verify the effect of aging.

## 8. Limitations

This is a scheduling simulator. It does not modify the actual Linux kernel scheduler or change the priorities of real operating-system processes. Its results depend on the input workload and aging interval.

## 9. Conclusion

The project demonstrates preemptive priority scheduling and dynamic aging through a C-based simulation. It provides a way to observe priority changes, compare scheduling behavior, and study starvation prevention.
