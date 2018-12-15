#pragma once

#include "sort.hpp"
#include <utility>

// Helper struct that defines a partition (start and end are inclusive)
struct MSortPartition {
  unsigned start, end, size, index;

  void Print() const;

  MSortPartition();
  MSortPartition(unsigned const startIndex, unsigned const endIndex);
};

class MergeSort : public Sort {
private:
  enum State { STOP, START };
  State state;

  std::vector<MSortPartition> partQ1;
  std::vector<MSortPartition> partQ2;
  std::vector<MSortPartition> &readQ, &writeQ;

  // Our temporary write buffer when merging two partitions
  // It is as big as the dataset out of convenience, but it
  // could be dynamically resized to the two partition sizes
  // combined (but I am being lazy here)
  std::vector<unsigned> buffer;
  unsigned bufferIndex;

  MSortPartition left;
  MSortPartition right;

  // Get the next 2 partitions we should merge
  // Returns false when there were not enough
  // partitions left
  bool GetNextPartitions();

public:
  void Step() override;
  void Reset() override;
  bool IsDone() const override;
  void Debug() const override;

  MSortPartition const &GetLeftPartition() const;
  MSortPartition const &GetRightPartition() const;
  std::vector<unsigned> const &GetBuffer() const;

  MergeSort(std::vector<unsigned> &data);
};