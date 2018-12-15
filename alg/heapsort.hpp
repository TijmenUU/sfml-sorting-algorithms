#pragma once
#include "sort.hpp"
#include <queue>

class HeapSort : public Sort {
private:
  enum State { START, HEAPIFY_INSERT, HEAPIFY_CHECK, MAXHEAP, STOP };
  State state;

  unsigned upperBound;
  unsigned heapIndex;

  void Heapify();
  void SwapTop();
  void MaxHeap();

public:
  void Step() override;
  void Reset() final;
  bool IsDone() const override;

  bool IsHeapifying() const;
  bool IsSorting() const;

  // 2 meanings, depending on what we're doing:
  // - Heapifying: 0 to it shows the heap
  // - Sorting: it to dataSet.size() shows the sorted elems
  unsigned GetSeperatorIndex() const;
  unsigned GetActiveIndex() const;

  HeapSort(std::vector<unsigned> &data);
};