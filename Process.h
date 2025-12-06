/*
 * Process.h
 * Operating System Project - CPU Scheduling Algorithms
 * Author: [Your Name]
 * Date: December 2025
 */

#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <iostream>

class Process {
private:
    int pid;                    // Process ID
    double arrivalTime;         // Arrival time
    double burstTime;           // Burst time (CPU time needed)
    double remainingTime;       // Remaining burst time (for preemptive algorithms)
    int priority;               // Priority (lower number = higher priority)
    
    // Calculated values
    double completionTime;      // Time when process completes
    double waitingTime;         // Time spent waiting in ready queue
    double turnaroundTime;      // Total time from arrival to completion
    double responseTime;        // Time from arrival to first CPU allocation

public:
    // Constructor
    Process(int id = 0, double arrival = 0.0, double burst = 0.0, int prio = 0);
    
    // Getters
    int getPID() const { return pid; }
    double getArrivalTime() const { return arrivalTime; }
    double getBurstTime() const { return burstTime; }
    double getRemainingTime() const { return remainingTime; }
    int getPriority() const { return priority; }
    double getCompletionTime() const { return completionTime; }
    double getWaitingTime() const { return waitingTime; }
    double getTurnaroundTime() const { return turnaroundTime; }
    double getResponseTime() const { return responseTime; }
    
    // Setters
    void setPID(int id) { pid = id; }
    void setArrivalTime(double time) { arrivalTime = time; }
    void setBurstTime(double time) { burstTime = time; remainingTime = time; }
    void setRemainingTime(double time) { remainingTime = time; }
    void setPriority(int prio) { priority = prio; }
    void setCompletionTime(double time) { completionTime = time; }
    void setWaitingTime(double time) { waitingTime = time; }
    void setTurnaroundTime(double time) { turnaroundTime = time; }
    void setResponseTime(double time) { responseTime = time; }
    
    // Utility methods
    void reset();
    void display() const;
};

#endif // PROCESS_H
