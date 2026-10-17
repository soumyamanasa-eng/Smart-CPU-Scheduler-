# Test Cases and Results

## Test Case 1: Normal Priority Scheduling

**Input**

| Process | Arrival Time | Burst Time | Priority |
|---|---:|---:|---:|
| P1 | 0 | 8 | 3 |
| P2 | 1 | 4 | 5 |
| P3 | 2 | 3 | 7 |

**Expected purpose:** Verify that the scheduler accepts valid process details and produces Gantt charts and performance metrics.

**Observed result:** The program completed successfully and displayed results for both baseline scheduling and dynamic aging.

## Test Case 2: Preemption Through Dynamic Aging

**Input**

| Process | Arrival Time | Burst Time | Priority |
|---|---:|---:|---:|
| P1 | 0 | 15 | 3 |
| P2 | 1 | 4 | 5 |
| P3 | 2 | 3 | 7 |

**Observed result:** With aging enabled, P2's effective priority improved as it waited. P2 preempted P1, and the Gantt chart showed P1 resuming later.

**Baseline average waiting time:** 10.33 time units.

**Aging average waiting time:** 11.00 time units.

**Baseline average response time:** 10.33 time units.

**Aging average response time:** 8.67 time units.

**Conclusion:** Aging changed the execution order and improved average response time for this workload, although average waiting and turnaround times increased slightly.

## Test Case 3: Large Initial Priority Difference

**Input**

| Process | Arrival Time | Burst Time | Priority |
|---|---:|---:|---:|
| P1 | 0 | 12 | 1 |
| P2 | 1 | 3 | 8 |
| P3 | 2 | 3 | 9 |

**Observed result:** P1 completed before P2 and P3. The aging-enabled scheduler displayed priority improvements for the waiting processes, but the execution order did not change.

**Conclusion:** Aging does not necessarily change the Gantt chart for every workload.

## Test Case 4: CPU Idle Time

**Purpose:** Verify behavior when no process has arrived at time zero.

**Input:** Use at least one process with an arrival time greater than zero.

**Expected result:** The Gantt chart should display an IDLE interval before the first process arrives.

## Overall Conclusion

The test cases demonstrate valid-input handling, preemptive scheduling, priority aging, idle-time handling, and performance comparison. Aging can help reduce starvation risk, but its effect depends on the process workload and initial priorities.

