#include "quicksort.hpp"
#include <random>
#include <utility>

QSortState::QSortState() : lower(0), upper(0), divider(0), current(0), index(0) { }

QSortState::QSortState(unsigned const lowerBound, unsigned const upperBound)
 : lower(lowerBound), upper(upperBound), divider(lowerBound), current(lowerBound), index(lowerBound)
{ }

unsigned QSortState::GetLowerBound() const { return lower; }
unsigned QSortState::GetUpperBound() const { return upper; }

void QuickSort::CreatePartition(int64_t const lower, int64_t const upper)
{
    unsigned const sizeLimit = 10;
    auto const size = upper - lower;
    if(size < sizeLimit)
    {
        if(size < 1)
            return;
        sortRanges.emplace(lower, upper);

        // Setup for insertion sort, which takes the first element as already
        // "sorted"
        auto & item = sortRanges.top();
        ++item.current;
        ++item.index;
    }
    else
    {
        partitions.emplace(lower, upper);
    }
}

unsigned GetPivotIndex(unsigned const min, unsigned const max)
{
    static std::default_random_engine eng;
    std::uniform_int_distribution<unsigned> dist(min, max);

    return dist(eng);
}

void QuickSort::Partition()
{
    if(stateData.current == stateData.GetUpperBound())
    { // We're done
        // Put pivot back in its place
        std::swap(dataSet[stateData.divider], dataSet[stateData.GetUpperBound()]);

        CreatePartition(stateData.GetLowerBound(), stateData.divider);
        CreatePartition(stateData.divider + 1, stateData.GetUpperBound());

        if(partitions.empty())
        {
            state = SORTING;
            return;
        }

        // Prepare a new partition
        stateData = partitions.top();
        partitions.pop();

        return;
    }
    else if(stateData.GetLowerBound() == stateData.current)
    { // First iteration
        // Setup pivot in upper
        auto const pivotIdx = GetPivotIndex(stateData.GetLowerBound(), stateData.GetUpperBound());
        std::swap(dataSet[pivotIdx], dataSet[stateData.GetUpperBound()]);
    }

    // Partition
    if(dataSet[stateData.current] < dataSet[stateData.GetUpperBound()])
    {
        if(stateData.current != stateData.divider)
        {
            std::swap(dataSet[stateData.current], dataSet[stateData.divider]);
        }
        ++stateData.divider;
    }
    ++stateData.current;
}

void QuickSort::Sort()
{ // Insertion sort
    if(stateData.current > stateData.GetUpperBound())
    {
        if(sortRanges.empty())
        {
            state = STOP;
            return;
        }

        stateData = sortRanges.top();
        sortRanges.pop();
        return;
    }
    else if(dataSet[stateData.current] < dataSet[stateData.divider])
    {
        std::swap(dataSet[stateData.current], dataSet[stateData.divider]);
        stateData.current = stateData.divider;
        stateData.divider = stateData.current - 1;
    }
    else
    {
        stateData.current = stateData.GetLowerBound();
    }

    if(stateData.current <= stateData.GetLowerBound())
    {
        ++stateData.index;
        stateData.current = stateData.index;
        stateData.divider = stateData.index - 1;
    }
}

void QuickSort::Step()
{
    switch(state)
    {
        case STOP:
            return;

        case START:
            stateData = QSortState(0, dataSet.size() - 1);
            state = PARTITION;
            break;

        case PARTITION:
            Partition();
            break;

        case SORTING:
            QuickSort::Sort();
            break;
    }

    return;
}

void QuickSort::Reset()
{
    state = START;

    while(!partitions.empty())
    {
        partitions.pop();
    };
    while(!sortRanges.empty())
    {
        sortRanges.pop();
    };
}

bool QuickSort::IsDone() const { return state == STOP; }

bool QuickSort::IsPartitioning() const { return state == PARTITION; }

bool QuickSort::IsSorting() const { return state == SORTING; }

QSortState const & QuickSort::GetState() const { return stateData; }

QuickSort::QuickSort(std::vector<unsigned> & data) : Sort::Sort(data, Sort::QSORT), state(STOP) { }
