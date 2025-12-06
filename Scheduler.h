/*
 * Scheduler.h
 * CPU Scheduler class with various scheduling algorithms
 * Author: [Your Name]
 * Date: December 2025
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Process.h"
#include <vector>
#include <string>

class Scheduler {
private:
    std::vector<Process> processes;
    double timeQuantum;
    
    // Helper methods
    void displayHeader() const;
    void displayResults(const std::vector<Process>& procs, const std::string& algorithm) const;
    void calculateMetrics(std::vector<Process>& procs);
    
public:
    Scheduler();
    
    // Input/Output
    bool readInputFile(const std::string& filename);
    void displayProcesses() const;
    void displayMenu();
    
    // Scheduling Algorithms
    std::vector<Process> fcfsScheduling();
    std::vector<Process> sjfScheduling();
    std::vector<Process> priorityScheduling();
    std::vector<Process> roundRobinScheduling();
    std::vector<Process> srtfScheduling();
    
    // Utility
    void runAllAlgorithms();
    void resetProcesses();
    
    // Getters
    double getTimeQuantum() const { return timeQuantum; }
    size_t getProcessCount() const { return processes.size(); }
};

#endif // SCHEDULER_H
