#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

// pull sorter main
#include "Sorter.hpp"

// bubble sorter is a type of sorter
class BubbleSorter : public Sorter 
{
public:
    using Sorter::Sorter;

    void sortLogic(int delayMs) override {
        for (size_t i = 0; i < data.size() - 1 && keepRunning; i++) {
            for (size_t j = 0; j < data.size() - i - 1 && keepRunning; j++) {
                activeA = static_cast<int>(j);
                activeB = static_cast<int>(j + 1);
                
                if (data[j] > data[j + 1]) std::swap(data[j], data[j + 1]);
                
                std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
            }
        }
        activeA = -1; activeB = -1;
    }
};

class SelectionSorter : public Sorter {
public:
    using Sorter::Sorter;

    void sortLogic(int delayMs) override {
        for (size_t i = 0; i < data.size() && keepRunning; i++) {
            size_t minIdx = i;
            for (size_t j = i + 1; j < data.size() && keepRunning; j++) {
                activeA = static_cast<int>(i);
                activeB = static_cast<int>(j);
                
                if (data[j] < data[minIdx]) minIdx = j;
                
                std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
            }
            std::swap(data[i], data[minIdx]);
        }
        activeA = -1; activeB = -1;
    }
};

#endif
