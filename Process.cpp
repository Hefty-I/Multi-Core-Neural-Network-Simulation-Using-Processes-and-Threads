/*
 * Process.cpp
 * Implementation of Process class
 */

#include "Process.h"
#include <iomanip>

Process::Process(int id, double arrival, double burst, int prio)
    : pid(id), arrivalTime(arrival), burstTime(burst), 
      remainingTime(burst), priority(prio),
      completionTime(0), waitingTime(0), 
      turnaroundTime(0), responseTime(0) {
}

void Process::reset() {
    remainingTime = burstTime;
    completionTime = 0;
    waitingTime = 0;
    turnaroundTime = 0;
    responseTime = 0;
}

void Process::display() const {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::setw(4) << pid 
              << std::setw(8) << arrivalTime
              << std::setw(8) << burstTime
              << std::setw(8) << completionTime
              << std::setw(8) << waitingTime
              << std::setw(10) << turnaroundTime
              << std::setw(10) << responseTime
              << std::endl;
}
