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

Scheduler::Scheduler() : timeQuantum(1.0)
{
}

bool Scheduler::readInputFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
        return false;
    }

    processes.clear();
    std::string line;
    int processID = 1;

    // Read first line for time quantum
    if (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string token;
        if (std::getline(ss, token, ','))
        {
            timeQuantum = std::stod(token);
        }
    }

    // Read process data
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string token;

        while (std::getline(ss, token, ','))
        {
            double burstTime = std::stod(token);
            if (burstTime > 0)
            {
                Process p(processID++, 0.0, burstTime, 0);
                processes.push_back(p);
            }
        }
    }

    file.close();
    std::cout << "Successfully loaded " << processes.size() << " processes" << std::endl;
    return true;
}

void Scheduler::displayProcesses() const
{
    std::cout << "\n=== Loaded Processes ===" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::setw(4) << "PID"
              << std::setw(8) << "AT"
              << std::setw(8) << "BT" << std::endl;
    std::cout << std::string(20, '-') << std::endl;

    for (const auto &p : processes)
    {
        std::cout << std::setw(4) << p.getPID()
                  << std::setw(8) << p.getArrivalTime()
                  << std::setw(8) << p.getBurstTime() << std::endl;
    }
}

void Scheduler::displayHeader() const
{
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

void Scheduler::displayResults(const std::vector<Process> &procs, const std::string &algorithm) const
{
    std::cout << "\n=== " << algorithm << " Results ===" << std::endl;
    displayHeader();

    double totalWT = 0, totalTAT = 0, totalRT = 0;

    for (const auto &p : procs)
    {
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

void Scheduler::resetProcesses()
{
    for (auto &p : processes)
    {
        p.reset();
    }
}

// ========== SCHEDULING ALGORITHMS ==========

std::vector<Process> Scheduler::fcfsScheduling()
{
    std::cout << "\n=== First Come First Serve (FCFS) Scheduling ===" << std::endl;
    resetProcesses();

    std::vector<Process> scheduled = processes;

    // Sort by arrival time
    std::sort(scheduled.begin(), scheduled.end(),
              [](const Process &a, const Process &b)
              {
                  return a.getArrivalTime() < b.getArrivalTime();
              });

    double currentTime = 0.0;

    // FCFS: Execute processes in order of arrival
    for (auto &p : scheduled)
    {
        // If CPU is idle, wait for the process to arrive
        if (currentTime < p.getArrivalTime())
        {
            currentTime = p.getArrivalTime();
        }

        // Response time = time when process first gets CPU - arrival time
        double responseTime = currentTime - p.getArrivalTime();
        p.setResponseTime(responseTime);

        // Execute the process
        currentTime += p.getBurstTime();

        // Completion time = time when process finishes
        p.setCompletionTime(currentTime);

        // Turnaround time = completion time - arrival time
        double turnaroundTime = currentTime - p.getArrivalTime();
        p.setTurnaroundTime(turnaroundTime);

        // Waiting time = turnaround time - burst time
        double waitingTime = turnaroundTime - p.getBurstTime();
        p.setWaitingTime(waitingTime);
    }

    displayResults(scheduled, "FCFS");
    return scheduled;
}

std::vector<Process> Scheduler::sjfScheduling()
{
    std::cout << "\n=== Shortest Job First (SJF) Scheduling ===" << std::endl;
    resetProcesses();

    std::vector<Process> scheduled = processes;

    // TODO: Implement SJF logic
    // Sort by burst time (shortest first)
    // Then apply similar timing calculations as FCFS

    std::sort(scheduled.begin(), scheduled.end(),
              [](const Process &a, const Process &b)
              {
                  return a.getBurstTime() < b.getBurstTime();
              });

    double currentTime = 0.0;

    // SJF: Execute processes in order of shortest burst time
    for (auto &p : scheduled)
    {
        // If CPU is idle, wait for the process to arrive
        if (currentTime < p.getArrivalTime())
        {
            currentTime = p.getArrivalTime();
        }

        // Response time = time when process first gets CPU - arrival time
        double responseTime = currentTime - p.getArrivalTime();
        p.setResponseTime(responseTime);

        // Execute the process
        currentTime += p.getBurstTime();

        // Completion time = time when process finishes
        p.setCompletionTime(currentTime);

        // Turnaround time = completion time - arrival time
        double turnaroundTime = currentTime - p.getArrivalTime();
        p.setTurnaroundTime(turnaroundTime);

        // Waiting time = turnaround time - burst time
        double waitingTime = turnaroundTime - p.getBurstTime();
        p.setWaitingTime(waitingTime);
    }

    displayResults(scheduled, "SJF");
    return scheduled;
}

std::vector<Process> Scheduler::priorityScheduling()
{
    std::cout << "\n=== Priority Scheduling ===" << std::endl;
    resetProcesses();

    std::vector<Process> scheduled = processes;

    // Sort by priority (lower number = higher priority)
    std::sort(scheduled.begin(), scheduled.end(),
              [](const Process &a, const Process &b)
              {
                  return a.getPriority() < b.getPriority();
              });

    double currentTime = 0.0;

    for (auto &p : scheduled)
    {
        // If current time is less than arrival time, CPU is idle
        if (currentTime < p.getArrivalTime())
        {
            currentTime = p.getArrivalTime();
        }

        // Response time = time when process starts - arrival time
        double responseTime = currentTime - p.getArrivalTime();
        p.setResponseTime(responseTime);

        // Process executes for its burst time
        currentTime += p.getBurstTime();

        // Completion time = time when process finishes
        p.setCompletionTime(currentTime);

        // Turnaround time = completion time - arrival time
        double turnaroundTime = currentTime - p.getArrivalTime();
        p.setTurnaroundTime(turnaroundTime);

        // Waiting time = turnaround time - burst time
        double waitingTime = turnaroundTime - p.getBurstTime();
        p.setWaitingTime(waitingTime);
    }

    displayResults(scheduled, "Priority");
    return scheduled;
}

std::vector<Process> Scheduler::roundRobinScheduling()
{
    std::cout << "\n=== Round Robin Scheduling (TQ: " << timeQuantum << ") ===" << std::endl;
    resetProcesses();

    std::vector<Process> scheduled = processes;
    std::queue<int> readyQueue;
    std::vector<bool> inQueue(scheduled.size(), false);
    std::vector<bool> firstTime(scheduled.size(), true);
    double currentTime = 0.0;
    int completed = 0;
    int n = scheduled.size();

    // Add processes that have arrived at time 0
    for (size_t i = 0; i < scheduled.size(); i++)
    {
        if (scheduled[i].getArrivalTime() <= currentTime)
        {
            readyQueue.push(i);
            inQueue[i] = true;
        }
    }

    while (completed < n)
    {
        if (readyQueue.empty())
        {
            // Find next process to arrive
            double nextArrival = 1e9;
            for (size_t i = 0; i < scheduled.size(); i++)
            {
                if (scheduled[i].getRemainingTime() > 0 && !inQueue[i])
                {
                    nextArrival = std::min(nextArrival, scheduled[i].getArrivalTime());
                }
            }
            currentTime = nextArrival;

            // Add newly arrived processes
            for (size_t i = 0; i < scheduled.size(); i++)
            {
                if (scheduled[i].getArrivalTime() <= currentTime &&
                    scheduled[i].getRemainingTime() > 0 && !inQueue[i])
                {
                    readyQueue.push(i);
                    inQueue[i] = true;
                }
            }
            continue;
        }

        int idx = readyQueue.front();
        readyQueue.pop();
        inQueue[idx] = false;

        // Set response time when process first gets CPU
        if (firstTime[idx])
        {
            double responseTime = currentTime - scheduled[idx].getArrivalTime();
            scheduled[idx].setResponseTime(responseTime);
            firstTime[idx] = false;
        }

        // Execute for time quantum or remaining time (whichever is smaller)
        double execTime = std::min(timeQuantum, scheduled[idx].getRemainingTime());
        scheduled[idx].setRemainingTime(scheduled[idx].getRemainingTime() - execTime);
        currentTime += execTime;

        // Check for newly arrived processes during execution
        for (size_t i = 0; i < scheduled.size(); i++)
        {
            if (i != (size_t)idx && scheduled[i].getArrivalTime() <= currentTime &&
                scheduled[i].getRemainingTime() > 0 && !inQueue[i])
            {
                readyQueue.push(i);
                inQueue[i] = true;
            }
        }

        // If process is complete
        if (scheduled[idx].getRemainingTime() == 0)
        {
            completed++;
            scheduled[idx].setCompletionTime(currentTime);
            double turnaroundTime = currentTime - scheduled[idx].getArrivalTime();
            scheduled[idx].setTurnaroundTime(turnaroundTime);
            double waitingTime = turnaroundTime - scheduled[idx].getBurstTime();
            scheduled[idx].setWaitingTime(waitingTime);
        }
        else
        {
            // Process not finished, put back in queue
            readyQueue.push(idx);
            inQueue[idx] = true;
        }
    }

    displayResults(scheduled, "Round Robin");
    return scheduled;
}

std::vector<Process> Scheduler::srtfScheduling()
{
    std::cout << "\n=== Shortest Remaining Time First (SRTF) Scheduling ===" << std::endl;
    resetProcesses();

    std::vector<Process> scheduled = processes;
    double currentTime = 0.0;
    int completed = 0;
    int n = scheduled.size();
    std::vector<bool> firstTime(n, true);
    int lastProcess = -1;

    while (completed < n)
    {
        // Find process with shortest remaining time among arrived processes
        int shortest = -1;
        double minRemaining = 1e9;

        for (int i = 0; i < n; i++)
        {
            if (scheduled[i].getArrivalTime() <= currentTime &&
                scheduled[i].getRemainingTime() > 0 &&
                scheduled[i].getRemainingTime() < minRemaining)
            {
                minRemaining = scheduled[i].getRemainingTime();
                shortest = i;
            }
        }

        // If no process available, jump to next arrival
        if (shortest == -1)
        {
            double nextArrival = 1e9;
            for (int i = 0; i < n; i++)
            {
                if (scheduled[i].getRemainingTime() > 0)
                {
                    nextArrival = std::min(nextArrival, scheduled[i].getArrivalTime());
                }
            }
            currentTime = nextArrival;
            continue;
        }

        // Set response time when process first gets CPU
        if (firstTime[shortest])
        {
            double responseTime = currentTime - scheduled[shortest].getArrivalTime();
            scheduled[shortest].setResponseTime(responseTime);
            firstTime[shortest] = false;
        }

        // Execute for a small time unit (0.01 for precision)
        double execTime = 0.01;
        if (scheduled[shortest].getRemainingTime() < execTime)
        {
            execTime = scheduled[shortest].getRemainingTime();
        }

        scheduled[shortest].setRemainingTime(scheduled[shortest].getRemainingTime() - execTime);
        currentTime += execTime;

        // If process completed
        if (scheduled[shortest].getRemainingTime() < 0.0001)
        { // Using small epsilon for floating point comparison
            completed++;
            scheduled[shortest].setCompletionTime(currentTime);
            double turnaroundTime = currentTime - scheduled[shortest].getArrivalTime();
            scheduled[shortest].setTurnaroundTime(turnaroundTime);
            double waitingTime = turnaroundTime - scheduled[shortest].getBurstTime();
            scheduled[shortest].setWaitingTime(waitingTime);
            scheduled[shortest].setRemainingTime(0); // Ensure it's exactly 0
        }

        lastProcess = shortest;
    }

    displayResults(scheduled, "SRTF");
    return scheduled;
}

void Scheduler::runAllAlgorithms()
{
    std::cout << "\n"
              << std::string(60, '=') << std::endl;
    std::cout << "Running All Scheduling Algorithms" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    fcfsScheduling();
    sjfScheduling();
    priorityScheduling();
    roundRobinScheduling();
    srtfScheduling();
}

void Scheduler::displayMenu()
{
    std::cout << "\n"
              << std::string(50, '=') << std::endl;
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
