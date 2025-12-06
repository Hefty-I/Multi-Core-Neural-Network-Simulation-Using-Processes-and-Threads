# Operating System Project - CPU Scheduling

This project implements various CPU scheduling algorithms for an Operating Systems course.

## Files Structure
- `scheduler.py` - Main scheduler implementation with all algorithms
- `utils.py` - Utility functions for validation, comparison, and export
- `input.txt` - Input data file with process information
- `README.md` - This file

## Input File Format
The input file should contain:
- **First line**: Time quantum and other parameters (comma-separated)
  - Example: `1.2, 0.5`
- **Following lines**: Process burst times (comma-separated)
  - Example: `0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8`

## Implemented Algorithms

### 1. First Come First Serve (FCFS)
- Non-preemptive
- Processes executed in order of arrival
- Simple but may cause convoy effect

### 2. Shortest Job First (SJF)
- Non-preemptive
- Executes shortest burst time process first
- Optimal for average waiting time

### 3. Priority Scheduling
- Can be preemptive or non-preemptive
- Higher priority processes execute first
- May cause starvation of low-priority processes

### 4. Round Robin (RR)
- Preemptive
- Each process gets equal time quantum
- Good for time-sharing systems

### 5. Shortest Remaining Time First (SRTF)
- Preemptive version of SJF
- Process with shortest remaining time executes
- Optimal for average waiting time (preemptive)

## How to Run

1. Make sure you have Python 3.6+ installed
2. Place your input data in `input.txt`
3. Run the main program:
   ```bash
   python scheduler.py
   ```

## Usage

The program provides an interactive menu:
1. Run individual algorithms
2. Compare all algorithms
3. Export results to files
4. Generate sample input files

## Key Metrics Calculated

- **Waiting Time (WT)**: Time spent waiting in ready queue
- **Turnaround Time (TAT)**: Total time from arrival to completion
- **Response Time (RT)**: Time from arrival to first execution
- **Completion Time (CT)**: Time when process finishes execution

## Formulas Used

- `Turnaround Time = Completion Time - Arrival Time`
- `Waiting Time = Turnaround Time - Burst Time`
- `Response Time = First CPU Time - Arrival Time`

## Example Output

```
=== First Come First Serve (FCFS) Scheduling ===

PID  AT     BT     CT     WT     TAT    RT    
--------------------------------------------------
1    0.0    0.1    0.1    0.0    0.1    0.0   
2    0.0    0.2    0.3    0.1    0.3    0.1   
3    0.0    0.3    0.6    0.3    0.6    0.3   
--------------------------------------------------
Average Waiting Time: 0.13
Average Turnaround Time: 0.33
Average Response Time: 0.13
```

## TODO (For Students)

The skeleton code provides the structure, but you need to implement:

1. **Algorithm Logic**: Complete the scheduling algorithms in `scheduler.py`
2. **Process Timing**: Calculate waiting time, turnaround time, response time
3. **Gantt Chart**: Implement visual timeline representation
4. **Input Parsing**: Improve input file handling based on your specific requirements
5. **Error Handling**: Add robust error checking and validation

## Tips for Implementation

1. Start with FCFS as it's the simplest
2. Test with small datasets first
3. Verify calculations manually for small examples
4. Use the Gantt chart to visualize process execution
5. Compare your results with theoretical expectations

## Common Issues

- **Process arrival times**: Make sure to handle different arrival times correctly
- **Time quantum**: For Round Robin, ensure proper time slice handling
- **Preemption**: SRTF and preemptive priority need careful context switching
- **Tie-breaking**: Define rules when processes have same burst time/priority

## Grading Criteria (Typical)

- Correct implementation of algorithms (60%)
- Proper calculation of metrics (20%)
- Code quality and documentation (10%)
- Input/output handling (10%)

Good luck with your project! 🚀