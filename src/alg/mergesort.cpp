#include "mergesort.hpp"
#include <cstdio>

void MSortPartition::Print() const
{
    std::printf("Start: %u\nEnd  : %u\nSize : %u\nIndex: %u\n", start, end, size, index);
}

MSortPartition::MSortPartition() : start(0U), end(0U), size(0U), index(0U) { }

MSortPartition::MSortPartition(unsigned const startIndex, unsigned const endIndex)
 : start(startIndex), end(endIndex), size(endIndex - startIndex), index(startIndex)
{ }

bool MergeSort::GetNextPartitions()
{
    if(readQ.size() < 2)
    {
        if(readQ.size() == 1)
        {
            writeQ.push_back(readQ.front());
            readQ.clear();
        }

        std::swap(readQ, writeQ);
        if(readQ.size() < 2)
        {
            // Write the final results
            dataSet = buffer;
            return false;
        }
    }

    left = readQ.front();
    readQ.erase(readQ.begin());

    right = readQ.front();
    readQ.erase(readQ.begin());

    bufferIndex = left.start;

    return true;
}

void MergeSort::Step()
{
    if(left.index >= left.end && right.index >= right.end)
    {
        writeQ.emplace_back(left.start, right.end);
        // Copy the results to the actual dataset
        for(unsigned i = left.start; i < right.end; ++i)
        {
            dataSet[i] = buffer[i];
        }

        if(!GetNextPartitions())
        {
            state = STOP;
            return;
        }
    }
    else
    {
        if(left.index == left.end)
        {
            buffer[bufferIndex] = dataSet[right.index];
            ++right.index;
        }
        else if(right.index == right.end)
        {
            buffer[bufferIndex] = dataSet[left.index];
            ++left.index;
        }
        else
        {
            if(dataSet[left.index] < dataSet[right.index])
            {
                buffer[bufferIndex] = dataSet[left.index];
                ++left.index;
            }
            else
            {
                buffer[bufferIndex] = dataSet[right.index];
                ++right.index;
            }
        }

        ++bufferIndex;
    }
}

void MergeSort::Reset()
{
    if(dataSet.size() < 2)
        return;

    state = START;

    partQ1.clear();
    partQ2.clear();
    readQ = partQ1;
    writeQ = partQ2;

    for(unsigned i = 0; i < dataSet.size(); ++i)
    {
        readQ.emplace_back(i, i + 1U);
    }

    buffer.resize(dataSet.size());
    bufferIndex = 0U;

    GetNextPartitions();
}

bool MergeSort::IsDone() const { return state == STOP; }

void MergeSort::Debug() const
{
    std::puts("LEFT");
    left.Print();
    std::puts("RIGHT");
    right.Print();
    std::printf("writeQ size: %u\n", writeQ.size());
    std::printf("readQ  size: %u\n", readQ.size());
}

MSortPartition const & MergeSort::GetLeftPartition() const { return left; }
MSortPartition const & MergeSort::GetRightPartition() const { return right; }
std::vector<unsigned> const & MergeSort::GetBuffer() const { return buffer; }

MergeSort::MergeSort(std::vector<unsigned> & data)
 : Sort(data, Sort::Type::MERGE), state(STOP), partQ1(), partQ2(), readQ(partQ1), writeQ(partQ2)
{ }