"""
Utility functions and classes for the CPU Scheduler project
"""

from typing import List
import matplotlib.pyplot as plt
from scheduler import Process

class GanttChart:
    """Class to create and display Gantt charts for process scheduling"""
    
    def __init__(self):
        self.timeline = []
    
    def add_process(self, process_id: int, start_time: float, end_time: float):
        """Add a process execution block to the timeline"""
        self.timeline.append({
            'pid': process_id,
            'start': start_time,
            'end': end_time,
            'duration': end_time - start_time
        })
    
    def display_text_gantt(self):
        """Display a simple text-based Gantt chart"""
        if not self.timeline:
            print("No processes to display")
            return
        
        print("\nGantt Chart:")
        print("-" * 50)
        
        # Print process blocks
        chart_line = "|"
        time_line = "0"
        
        for block in self.timeline:
            process_label = f" P{block['pid']} "
            chart_line += process_label + "|"
            time_line += f"{' ' * (len(process_label)-1)}{int(block['end'])}"
        
        print(chart_line)
        print(time_line)
        print("-" * 50)
    
    def clear(self):
        """Clear the timeline"""
        self.timeline = []

def validate_input_file(filename: str = "input.txt") -> bool:
    """Validate the format of the input file"""
    try:
        with open(filename, 'r') as file:
            lines = file.readlines()
        
        if not lines:
            print("Error: Input file is empty")
            return False
        
        # Check first line
        try:
            first_line = [float(x.strip()) for x in lines[0].split(',')]
            if len(first_line) < 1:
                print("Error: First line should contain at least time quantum")
                return False
        except ValueError:
            print("Error: First line contains invalid numbers")
            return False
        
        # Check process data lines
        valid_processes = 0
        for i, line in enumerate(lines[1:], 2):
            if line.strip():  # Skip empty lines
                try:
                    times = [float(x.strip()) for x in line.split(',') if x.strip()]
                    if times:
                        valid_processes += len([t for t in times if t > 0])
                except ValueError:
                    print(f"Error: Line {i} contains invalid numbers")
                    return False
        
        if valid_processes == 0:
            print("Error: No valid processes found in input file")
            return False
        
        print(f"Input file validation successful: {valid_processes} processes found")
        return True
        
    except FileNotFoundError:
        print(f"Error: File '{filename}' not found")
        return False
    except Exception as e:
        print(f"Error validating file: {e}")
        return False

def generate_sample_input():
    """Generate a sample input file for testing"""
    sample_content = """2.0, 0.5
0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8
0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7
3.0, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7"""
    
    try:
        with open("sample_input.txt", 'w') as file:
            file.write(sample_content)
        print("Sample input file 'sample_input.txt' created successfully!")
        return True
    except Exception as e:
        print(f"Error creating sample file: {e}")
        return False

def compare_algorithms(scheduler):
    """Compare all algorithms and display performance metrics"""
    algorithms = [
        ("FCFS", scheduler.fcfs_scheduling),
        ("SJF", scheduler.sjf_scheduling),
        ("Round Robin", scheduler.round_robin_scheduling),
    ]
    
    results = {}
    
    print("\n" + "="*60)
    print("ALGORITHM COMPARISON")
    print("="*60)
    
    for name, algorithm in algorithms:
        try:
            processes = algorithm()
            avg_wt, avg_tat, avg_rt = scheduler.calculate_metrics(processes)
            results[name] = {
                'avg_waiting_time': avg_wt,
                'avg_turnaround_time': avg_tat,
                'avg_response_time': avg_rt
            }
        except Exception as e:
            print(f"Error running {name}: {e}")
            results[name] = None
    
    # Display comparison table
    print(f"{'Algorithm':<15} {'Avg WT':<10} {'Avg TAT':<10} {'Avg RT':<10}")
    print("-" * 50)
    
    for alg_name, metrics in results.items():
        if metrics:
            print(f"{alg_name:<15} {metrics['avg_waiting_time']:<10.2f} "
                  f"{metrics['avg_turnaround_time']:<10.2f} "
                  f"{metrics['avg_response_time']:<10.2f}")
        else:
            print(f"{alg_name:<15} {'ERROR':<10} {'ERROR':<10} {'ERROR':<10}")
    
    # Find best algorithm for each metric
    if results:
        valid_results = {k: v for k, v in results.items() if v is not None}
        if valid_results:
            best_wt = min(valid_results.items(), key=lambda x: x[1]['avg_waiting_time'])
            best_tat = min(valid_results.items(), key=lambda x: x[1]['avg_turnaround_time'])
            best_rt = min(valid_results.items(), key=lambda x: x[1]['avg_response_time'])
            
            print("\nBest Algorithms:")
            print(f"Lowest Average Waiting Time: {best_wt[0]} ({best_wt[1]['avg_waiting_time']:.2f})")
            print(f"Lowest Average Turnaround Time: {best_tat[0]} ({best_tat[1]['avg_turnaround_time']:.2f})")
            print(f"Lowest Average Response Time: {best_rt[0]} ({best_rt[1]['avg_response_time']:.2f})")

def export_results_to_file(processes: List[Process], algorithm_name: str, filename: str = None):
    """Export scheduling results to a text file"""
    if filename is None:
        filename = f"{algorithm_name.lower().replace(' ', '_')}_results.txt"
    
    try:
        with open(filename, 'w') as file:
            file.write(f"{algorithm_name} Scheduling Results\n")
            file.write("=" * 50 + "\n\n")
            
            file.write(f"{'PID':<4} {'AT':<6} {'BT':<6} {'CT':<6} {'WT':<6} {'TAT':<6} {'RT':<6}\n")
            file.write("-" * 50 + "\n")
            
            for process in processes:
                file.write(f"{process.pid:<4} {process.arrival_time:<6.1f} {process.burst_time:<6.1f} "
                          f"{process.completion_time:<6.1f} {process.waiting_time:<6.1f} "
                          f"{process.turnaround_time:<6.1f} {process.response_time:<6.1f}\n")
            
            # Calculate averages
            if processes:
                avg_wt = sum(p.waiting_time for p in processes) / len(processes)
                avg_tat = sum(p.turnaround_time for p in processes) / len(processes)
                avg_rt = sum(p.response_time for p in processes) / len(processes)
                
                file.write("-" * 50 + "\n")
                file.write(f"Average Waiting Time: {avg_wt:.2f}\n")
                file.write(f"Average Turnaround Time: {avg_tat:.2f}\n")
                file.write(f"Average Response Time: {avg_rt:.2f}\n")
        
        print(f"Results exported to '{filename}' successfully!")
        return True
        
    except Exception as e:
        print(f"Error exporting results: {e}")
        return False