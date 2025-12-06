/*
 * main.cpp
 * Operating System Project - CPU Scheduling Algorithms
 * Author: [Your Name]
 * Date: December 2025
 */

#include "Scheduler.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

int main()
{
    Scheduler scheduler;

    // Read input file
    cout << "CPU Scheduling Simulator" << endl;
    cout << "========================" << endl;

    if (!scheduler.readInputFile("input.txt"))
    {
        cerr << "Failed to read input file. Exiting..." << endl;
        return 1;
    }

    // Display loaded processes
    scheduler.displayProcesses();

    // Main menu loop
    int choice;
    bool running = true;

    while (running)
    {
        scheduler.displayMenu();
        cin >> choice;

        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            scheduler.fcfsScheduling();
            break;
        case 2:
            scheduler.sjfScheduling();
            break;
        case 3:
            scheduler.priorityScheduling();
            break;
        case 4:
            scheduler.roundRobinScheduling();
            break;
        case 5:
            scheduler.srtfScheduling();
            break;
        case 6:
            scheduler.runAllAlgorithms();
            break;
        case 7:
            scheduler.displayProcesses();
            break;
        case 8:
            cout << "\nExiting... Goodbye!" << endl;
            running = false;
            break;
        default:
            cout << "Invalid choice! Please enter a number between 1-8." << endl;
        }

        if (running)
        {
            cout << "\nPress Enter to continue...";
            cin.get();
        }
    }

    return 0;
}
