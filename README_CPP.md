# CPU Scheduling Simulator - C++ Implementation

## Project Structure

```
Project/
├── main.cpp          - Main program entry point
├── Process.h         - Process class header
├── Process.cpp       - Process class implementation
├── Scheduler.h       - Scheduler class header
├── Scheduler.cpp     - Scheduler algorithms implementation
├── Makefile          - Build configuration
├── input.txt         - Input data file
└── README_CPP.md     - This file
```

## Compilation Instructions

### Option 1: Using Makefile (Recommended)
```bash
# Build the project
make

# Run the program
make run

# Clean build files
make clean

# Rebuild from scratch
make rebuild
```

### Option 2: Manual Compilation
```bash
# Compile all files
g++ -std=c++11 -Wall -Wextra -g main.cpp Process.cpp Scheduler.cpp -o scheduler

# Run the program
./scheduler          # On Linux/Mac
scheduler.exe        # On Windows
```

### Option 3: Using Visual Studio (Windows)
1. Create a new C++ Console Application project
2. Add all `.cpp` and `.h` files to the project
3. Make sure `input.txt` is in the same directory as the executable
4. Build and run (F5)

## Input File Format

The `input.txt` file should contain:
- **First line**: Time quantum (for Round Robin)
  - Example: `1.2, 0.5`
- **Following lines**: Process burst times (comma-separated)
  - Example: `0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8`

## Implemented Algorithms

1. **FCFS** - First Come First Serve
2. **SJF** - Shortest Job First
3. **Priority** - Priority-based scheduling
4. **Round Robin** - Time-sliced scheduling
5. **SRTF** - Shortest Remaining Time First (Preemptive SJF)

## Classes

### Process Class
Represents a single process with properties:
- `pid` - Process ID
- `arrivalTime` - When process arrives
- `burstTime` - CPU time needed
- `remainingTime` - Time left (for preemptive)
- `priority` - Priority level
- Calculated: `completionTime`, `waitingTime`, `turnaroundTime`, `responseTime`

### Scheduler Class
Manages all processes and implements algorithms:
- `readInputFile()` - Loads processes from file
- `fcfsScheduling()` - FCFS implementation
- `sjfScheduling()` - SJF implementation
- `priorityScheduling()` - Priority implementation
- `roundRobinScheduling()` - RR implementation
- `srtfScheduling()` - SRTF implementation
- `displayResults()` - Show formatted output

## What You Need to Implement

Each scheduling algorithm has a skeleton with TODO comments. You need to:

### 1. FCFS (Easiest - Start Here)
```cpp
for (auto& p : scheduled) {
    if (currentTime < p.getArrivalTime()) {
        currentTime = p.getArrivalTime();
    }
    p.setResponseTime(currentTime - p.getArrivalTime());
    currentTime += p.getBurstTime();
    p.setCompletionTime(currentTime);
    p.setTurnaroundTime(p.getCompletionTime() - p.getArrivalTime());
    p.setWaitingTime(p.getTurnaroundTime() - p.getBurstTime());
}
```

### 2. SJF
- Similar to FCFS but processes are pre-sorted by burst time
- Use same timing calculation logic

### 3. Priority
- Similar to FCFS but processes are pre-sorted by priority
- Lower priority number = higher priority

### 4. Round Robin
- Use a queue to cycle through processes
- Give each process `timeQuantum` of CPU time
- If remaining time > 0, add back to queue

### 5. SRTF (Most Complex)
- Check at each time unit for shortest remaining time
- Preempt current process if shorter one arrives
- Track context switches

## Key Formulas

```
Completion Time (CT) = Time when process finishes
Turnaround Time (TAT) = CT - Arrival Time
Waiting Time (WT) = TAT - Burst Time
Response Time (RT) = First CPU Time - Arrival Time
```

## Example Output

```
=== First Come First Serve (FCFS) Scheduling ===
 PID      AT      BT      CT      WT     TAT      RT
------------------------------------------------------
   1    0.00    0.10    0.10    0.00    0.10    0.00
   2    0.00    0.20    0.30    0.10    0.30    0.10
   3    0.00    0.30    0.60    0.30    0.60    0.30
------------------------------------------------------
Average Waiting Time: 0.13
Average Turnaround Time: 0.33
Average Response Time: 0.13
```

## Testing

1. Test with small datasets first (3-5 processes)
2. Verify calculations manually
3. Compare different algorithms on same input
4. Check edge cases (equal burst times, priorities)

## Debugging Tips

- Print `currentTime` at each step
- Verify sorting is working correctly
- Check for off-by-one errors in loops
- Make sure all time calculations use correct formula
- Test each algorithm independently

## Common Errors to Avoid

1. **Integer division** - Use `double` for all time values
2. **Not resetting processes** - Call `resetProcesses()` before each algorithm
3. **Wrong sort order** - Make sure comparators are correct
4. **Queue management** - In Round Robin, don't lose processes
5. **Preemption logic** - SRTF needs careful handling of context switches

Good luck! 🚀
