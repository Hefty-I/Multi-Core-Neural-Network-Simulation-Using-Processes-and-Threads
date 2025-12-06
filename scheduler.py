"""
Operating System Project - CPU Scheduling Algorithms
Author: [Your Name]
Date: November 2025
"""

import sys
from typing import List, Tuple

class Process:
    """Represents a process with its properties"""
    def __init__(self, pid: int, arrival_time: float = 0, burst_time: float = 0, priority: int = 0):
        self.pid = pid
        self.arrival_time = arrival_time
        self.burst_time = burst_time
        self.priority = priority
        self.waiting_time = 0
        self.turnaround_time = 0
        self.completion_time = 0
        self.response_time = 0
        self.remaining_time = burst_time

    def __str__(self):
        return f"P{self.pid}: AT={self.arrival_time}, BT={self.burst_time}, WT={self.waiting_time:.2f}, TAT={self.turnaround_time:.2f}"

class CPUScheduler:
    """Main scheduler class implementing various scheduling algorithms"""
    
    def __init__(self):
        self.processes = []
        self.time_quantum = 0
    
    def read_input(self, filename: str = "input.txt") -> bool:
        """
        Read process data from input file
        Expected format:
        - First line: time_quantum, [other parameters]
        - Following lines: process burst times or arrival_time, burst_time pairs
        """
        try:
            with open(filename, 'r') as file:
                lines = file.readlines()
            
            # Parse first line for parameters
            first_line = [float(x.strip()) for x in lines[0].split(',')]
            self.time_quantum = first_line[0] if len(first_line) > 0 else 2.0
            
            # Parse process data
            self.processes = []
            process_id = 1
            
            for i, line in enumerate(lines[1:], 1):
                if line.strip():  # Skip empty lines
                    times = [float(x.strip()) for x in line.split(',') if x.strip()]
                    
                    # Create processes from the line data
                    for j, burst_time in enumerate(times):
                        if burst_time > 0:  # Only add valid processes
                            process = Process(
                                pid=process_id,
                                arrival_time=0,  # Default arrival time
                                burst_time=burst_time
                            )
                            self.processes.append(process)
                            process_id += 1
            
            print(f"Successfully loaded {len(self.processes)} processes")
            return True
            
        except FileNotFoundError:
            print(f"Error: File '{filename}' not found!")
            return False
        except Exception as e:
            print(f"Error reading file: {e}")
            return False
    
    def reset_processes(self):
        """Reset all process timing data for new algorithm execution"""
        for process in self.processes:
            process.waiting_time = 0
            process.turnaround_time = 0
            process.completion_time = 0
            process.response_time = 0
            process.remaining_time = process.burst_time
    
    def fcfs_scheduling(self) -> List[Process]:
        """First Come First Serve scheduling algorithm"""
        print("\n=== First Come First Serve (FCFS) Scheduling ===")
        self.reset_processes()
        
        # Sort by arrival time
        scheduled_processes = sorted(self.processes, key=lambda p: p.arrival_time)
        
        current_time = 0
        for process in scheduled_processes:
            # TODO: Implement FCFS logic
            # Calculate waiting time, turnaround time, completion time
            pass
        
        return scheduled_processes
    
    def sjf_scheduling(self) -> List[Process]:
        """Shortest Job First scheduling algorithm"""
        print("\n=== Shortest Job First (SJF) Scheduling ===")
        self.reset_processes()
        
        # TODO: Implement SJF logic
        # Sort by burst time
        scheduled_processes = sorted(self.processes, key=lambda p: p.burst_time)
        
        return scheduled_processes
    
    def priority_scheduling(self) -> List[Process]:
        """Priority scheduling algorithm"""
        print("\n=== Priority Scheduling ===")
        self.reset_processes()
        
        # TODO: Implement Priority scheduling logic
        # Sort by priority (assuming lower number = higher priority)
        scheduled_processes = sorted(self.processes, key=lambda p: p.priority)
        
        return scheduled_processes
    
    def round_robin_scheduling(self) -> List[Process]:
        """Round Robin scheduling algorithm"""
        print(f"\n=== Round Robin Scheduling (Time Quantum: {self.time_quantum}) ===")
        self.reset_processes()
        
        # TODO: Implement Round Robin logic
        scheduled_processes = self.processes.copy()
        
        return scheduled_processes
    
    def srtf_scheduling(self) -> List[Process]:
        """Shortest Remaining Time First scheduling algorithm"""
        print("\n=== Shortest Remaining Time First (SRTF) Scheduling ===")
        self.reset_processes()
        
        # TODO: Implement SRTF logic (preemptive SJF)
        scheduled_processes = self.processes.copy()
        
        return scheduled_processes
    
    def calculate_metrics(self, processes: List[Process]) -> Tuple[float, float, float]:
        """Calculate average waiting time, turnaround time, and response time"""
        if not processes:
            return 0.0, 0.0, 0.0
        
        total_wt = sum(p.waiting_time for p in processes)
        total_tat = sum(p.turnaround_time for p in processes)
        total_rt = sum(p.response_time for p in processes)
        
        n = len(processes)
        avg_wt = total_wt / n
        avg_tat = total_tat / n
        avg_rt = total_rt / n
        
        return avg_wt, avg_tat, avg_rt
    
    def display_results(self, processes: List[Process], algorithm_name: str):
        """Display scheduling results in a formatted table"""
        print(f"\n{algorithm_name} Results:")
        print("-" * 80)
        print(f"{'PID':<4} {'AT':<6} {'BT':<6} {'CT':<6} {'WT':<6} {'TAT':<6} {'RT':<6}")
        print("-" * 80)
        
        for process in processes:
            print(f"{process.pid:<4} {process.arrival_time:<6.1f} {process.burst_time:<6.1f} "
                  f"{process.completion_time:<6.1f} {process.waiting_time:<6.1f} "
                  f"{process.turnaround_time:<6.1f} {process.response_time:<6.1f}")
        
        avg_wt, avg_tat, avg_rt = self.calculate_metrics(processes)
        print("-" * 80)
        print(f"Average Waiting Time: {avg_wt:.2f}")
        print(f"Average Turnaround Time: {avg_tat:.2f}")
        print(f"Average Response Time: {avg_rt:.2f}")
    
    def run_all_algorithms(self):
        """Run all scheduling algorithms and display results"""
        algorithms = [
            ("FCFS", self.fcfs_scheduling),
            ("SJF", self.sjf_scheduling),
            ("Priority", self.priority_scheduling),
            ("Round Robin", self.round_robin_scheduling),
            ("SRTF", self.srtf_scheduling)
        ]
        
        print("Running all scheduling algorithms...")
        print("=" * 50)
        
        for name, algorithm in algorithms:
            try:
                result = algorithm()
                self.display_results(result, name)
                print()
            except Exception as e:
                print(f"Error in {name} algorithm: {e}")

def main():
    """Main function to run the scheduler"""
    scheduler = CPUScheduler()
    
    # Read input file
    if not scheduler.read_input():
        sys.exit(1)
    
    # Display loaded processes
    print("\nLoaded Processes:")
    for process in scheduler.processes:
        print(process)
    
    # Run scheduling algorithms
    while True:
        print("\n" + "="*50)
        print("CPU Scheduling Simulator")
        print("="*50)
        print("1. First Come First Serve (FCFS)")
        print("2. Shortest Job First (SJF)")
        print("3. Priority Scheduling")
        print("4. Round Robin (RR)")
        print("5. Shortest Remaining Time First (SRTF)")
        print("6. Run All Algorithms")
        print("7. Reload Input File")
        print("8. Exit")
        
        choice = input("\nEnter your choice (1-8): ").strip()
        
        if choice == '1':
            result = scheduler.fcfs_scheduling()
            scheduler.display_results(result, "FCFS")
        elif choice == '2':
            result = scheduler.sjf_scheduling()
            scheduler.display_results(result, "SJF")
        elif choice == '3':
            result = scheduler.priority_scheduling()
            scheduler.display_results(result, "Priority")
        elif choice == '4':
            result = scheduler.round_robin_scheduling()
            scheduler.display_results(result, "Round Robin")
        elif choice == '5':
            result = scheduler.srtf_scheduling()
            scheduler.display_results(result, "SRTF")
        elif choice == '6':
            scheduler.run_all_algorithms()
        elif choice == '7':
            scheduler.read_input()
        elif choice == '8':
            print("Exiting... Goodbye!")
            break
        else:
            print("Invalid choice! Please enter a number between 1-8.")

if __name__ == "__main__":
    main()