#include "bubblesort.hpp"
#include <cassert>
#include <cstdio>

void BubbleSort::Step()
{
    if(current <= lowerBound)
    {
        current = dataSet.size() - 1;

        ++lowerBound;

        if(lowerBound >= dataSet.size() - 1)
        {
            ++lowerBound; // for visual purposes!

            state = STOP;
            return;
        }
    }
    else
    {
        if(dataSet[current] < dataSet[current - 1])
            std::swap(dataSet[current], dataSet[current - 1]);
        --current;
    }
}

void BubbleSort::Reset()
{
    state = START;
    lowerBound = 0;
    current = dataSet.size() - 1;
}

bool BubbleSort::IsDone() const { return state == STOP; }

unsigned BubbleSort::GetLowerBound() const { return lowerBound; }
unsigned BubbleSort::GetCurrentIndex() const { return current; }

BubbleSort::BubbleSort(std::vector<unsigned> & data) : Sort(data, BUBBLE), state(STOP) { assert(data.size() > 0); }