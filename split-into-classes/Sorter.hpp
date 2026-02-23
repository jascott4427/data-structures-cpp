// If not defined: define the file (so wew dont read twice)
#ifndef SORTER_HPP
#define SORTER_HPP // not tabbed because preprocesser directives must have # as first line

// The 'Vector' tool is a list that can change size
#include <vector>

// The 'Thread' allows two threads to be going at once
#include <thread>

// The 'Atomic' is necessary to safely share variables between two threads
#include <atomic>

// The 'Chrono' brings in clock and timing tools
#include <chrono>

// Create a base sorter class for all sorting algorithms to share
class Sorter
{

    // public: can be seen by the rest of the program
public:
    // dynamic vecotrs that must declare type to hold
    std::vector<int> data;

    // initialize thread for sorter to run in background
    std::thread sortThread;

    // safely store variables without allowing other threads to overrite data
    std::atomic<int> activeA{-1}; //-1 starts it at null
    std::atomic<int> activeB{-1};
    // std::atomic<bool> startRunning{false};
    std::atomic<bool> keepRunning{true};

    // Constructor: when we make the class, it inputs an int vector which is
    Sorter(std::vector<int> d)
        : // Put member initializers here
          data(d)
    {
        // put things here if needed to run before
        // program starts, but after setting up variables
    }

    // Destructor: denoted by ~
    // Clean up the thread when the object is destroyed
    // virtual: cleans up class with in class
    virtual ~Sorter()
    {
        keepRunning = false;
        // wait for this to finish up before deleting it
        if (sortThread.joinable())
            sortThread.join();
    }

    // This is the "blueprint" function
    virtual void sortLogic(int delayMs) = 0;

    void start(int delayMs)
    {
        // Starts the sortLogic in a background thread
        sortThread = std::thread(&Sorter::sortLogic, this, delayMs);
    }
};
// ifndef needs matching #endif
#endif
