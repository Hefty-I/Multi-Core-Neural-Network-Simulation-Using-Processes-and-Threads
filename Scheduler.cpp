/*
 * Scheduler.cpp
 * Implementation of Scheduler class
 */

#include "Scheduler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <queue>

Scheduler::Scheduler() : timeQuantum(1.0) {
}

bool Scheduler::readInputFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
        return false;
    }
    
    processes.clear();
    std::string line;
    int processID = 1;
    
    // Read first line for time quantum
    if (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        if (std::getline(ss, token, ',')) {
            timeQuantum = std::stod(token);
        }
    }
    
    // Read process data
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        std::string token;
        
        while (std::getline(ss, token, ',')) {
            double burstTime = std::stod(token);
            if (burstTime > 0) {
                Process p(processID++, 0.0, burstTime, 0);
                processes.push_back(p);
            }
        }
    }
    
    file.close();
    std::cout << "Successfully loaded " << processes.size() << " processes" << std::endl;
    return true;
}

void Scheduler::displayProcesses() const {
    std::cout << "\n=== Loaded Processes ===" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::setw(4) << "PID" 
              << std::setw(8) << "AT"
              << std::setw(8) << "BT" << std::endl;
    std::cout << std::string(20, '-') << std::endl;
    
    for (const auto& p : processes) {
        std::cout << std::setw(4) << p.getPID() 
                  << std::setw(8) << p.getArrivalTime()
                  << std::setw(8) << p.getBurstTime() << std::endl;
    }
}

void Scheduler::displayHeader() const {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::setw(4) << "PID" 
              << std::setw(8) << "AT"
              << std::setw(8) << "BT"
              << std::setw(8) << "CT"
              << std::setw(8) << "WT"
              << std::setw(10) << "TAT"
              << std::setw(10) << "RT" << std::endl;
    std::cout << std::string(54, '-') << std::endl;
}

void Scheduler::displayResults(const std::vector<Process>& procs, const std::string& algorithm) const {
    std::cout << "\n=== " << algorithm << " Results ===" << std::endl;
    displayHeader();
    
    double totalWT = 0, totalTAT = 0, totalRT = 0;
    
    for (const auto& p : procs) {
        p.display();
        totalWT += p.getWaitingTime();
        totalTAT += p.getTurnaroundTime();
        totalRT += p.getResponseTime();
    }
    
    int n = procs.size();
    std::cout << std::string(54, '-') << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average Waiting Time: " << totalWT / n << std::endl;
    std::cout << "Average Turnaround Time: " << totalTAT / n << std::endl;
    std::cout << "Average Response Time: " << totalRT / n << std::endl;
}

void Scheduler::resetProcesses() {
    for (auto& p : processes) {
        p.reset();
    }
}

// ========== SCHEDULING ALGORITHMS ==========

std::vector<Process> Scheduler::fcfsScheduling() {
    std::cout << "\n=== First Come First Serve (FCFS) Scheduling ===" << std::endl;
    resetProcesses();
    
    std::vector<Process> scheduled = processes;
    
    // Sort by arrival time
    std::sort(scheduled.begin(), scheduled.end(), 
              [](const Process& a, const Process& b) {
                  return a.getArrivalTime() < b.getArrivalTime();
              });
    
    double currentTime = 0.0;
    
    // TODO: Implement FCFS logic
    // For each process in order:
    //   1. If currentTime < arrivalTime, wait (currentTime = arrivalTime)
    //   2. Set response time = currentTime - arrivalTime
    //   3. Execute process: currentTime += burstTime
    //   4. Set completion time = currentTime
    //   5. Calculate turnaround time = completionTime - arrivalTime
    //   6. Calculate waiting time = turnaroundTime - burstTime
    
    for (auto& p : scheduled) {
        // Your implementation here
    }
    
    displayResults(scheduled, "FCFS");
    return scheduled;
}

std::vector<Process> Scheduler::sjfScheduling() {
    std::cout << "\n=== Shortest Job First (SJF) Scheduling ===" << std::endl;
    resetProcesses();
    
    std::vector<Process> scheduled = processes;
    
    // TODO: Implement SJF logic
    // Sort by burst time (shortest first)
    // Then apply similar timing calculations as FCFS
    
    std::sort(scheduled.begin(), scheduled.end(),
              [](const Process& a, const Process& b) {
                  return a.getBurstTime() < b.getBurstTime();
              });
    
    double currentTime = 0.0;
    
    for (auto& p : scheduled) {
        // Your implementation here
    }
    
    displayResults(scheduled, "SJF");
    return scheduled;
}

std::vector<Process> Scheduler::priorityScheduling() {
    std::cout << "\n=== Priority Scheduling ===" << std::endl;
    resetProcesses();
    
    std::vector<Process> scheduled = processes;
    
    // TODO: Implement Priority scheduling
    // Sort by priority (lower number = higher priority)
    // Apply timing calculations
    
    std::sort(scheduled.begin(), scheduled.end(),
              [](const Process& a, const Process& b) {
                  return a.getPriority() < b.getPriority();
              });
    
    double currentTime = 0.0;
    
    for (auto& p : scheduled) {
        // Your implementation here
    }
    
    displayResults(scheduled, "Priority");
    return scheduled;
}

std::vector<Process> Scheduler::roundRobinScheduling() {
    std::cout << "\n=== Round Robin Scheduling (TQ: " << timeQuantum << ") ===" << std::endl;
    resetProcesses();
    
    std::vector<Process> scheduled = processes;
    
    // TODO: Implement Round Robin logic
    // 1. Use a queue to manage processes
    // 2. Give each process 'timeQuantum' of CPU time
    // 3. If not finished, move to back of queue
    // 4. Track when each process first gets CPU (for response time)
    // 5. Continue until all processes complete
    
    std::queue<int> readyQueue;
    double currentTime = 0.0;
    
    // Initialize queue with all processes
    for (size_t i = 0; i < scheduled.size(); i++) {
        readyQueue.push(i);
    }
    
    // Your implementation here
    
    displayResults(scheduled, "Round Robin");
    return scheduled;
}

std::vector<Process> Scheduler::srtfScheduling() {
    std::cout << "\n=== Shortest Remaining Time First (SRTF) Scheduling ===" << std::endl;
    resetProcesses();
    
    std::vector<Process> scheduled = processes;
    
    // TODO: Implement SRTF (Preemptive SJF)
    // This is the most complex algorithm
    // 1. At each time unit, check which process has shortest remaining time
    // 2. Execute that process for 1 time unit
    // 3. Update remaining times
    // 4. Repeat until all processes complete
    // 5. Track context switches
    
    double currentTime = 0.0;
    int completed = 0;
    int n = scheduled.size();
    
    // Your implementation here
    
    displayResults(scheduled, "SRTF");
    return scheduled;
}

void Scheduler::runAllAlgorithms() {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "Running All Scheduling Algorithms" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    fcfsScheduling();
    sjfScheduling();
    priorityScheduling();
    roundRobinScheduling();
    srtfScheduling();
}

void Scheduler::displayMenu() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "CPU Scheduling Simulator" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "1. First Come First Serve (FCFS)" << std::endl;
    std::cout << "2. Shortest Job First (SJF)" << std::endl;
    std::cout << "3. Priority Scheduling" << std::endl;
    std::cout << "4. Round Robin (RR)" << std::endl;
    std::cout << "5. Shortest Remaining Time First (SRTF)" << std::endl;
    std::cout << "6. Run All Algorithms" << std::endl;
    std::cout << "7. Display Processes" << std::endl;
    std::cout << "8. Exit" << std::endl;
    std::cout << "\nEnter your choice (1-8): ";
}
