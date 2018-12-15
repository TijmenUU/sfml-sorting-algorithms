#include "heapsort.hpp"
#include <cassert>

// Gets the parent index of a flattend binary tree index
unsigned GetParent(unsigned const i) {
  if (i == 0)
    return 0;

  if (i % 2 == 0)
    return (i - 1) / 2;
  return i / 2;
}

// Gets the left child/leaf of a flattend binary tree index
unsigned GetLeftChild(unsigned const i) { return (2u * i) + 1u; }

// Gets the right child/leaf of a flattend binary tree index
unsigned GetRightChild(unsigned const i) { return (2u * i) + 2u; }

void HeapSort::Heapify() {
  if (heapIndex == 0) {
    state = HEAPIFY_INSERT;
    return;
  } else if (heapIndex >= dataSet.size()) {
    state = MAXHEAP;
    heapIndex = 0;
    upperBound = dataSet.size() - 1;
    SwapTop();
    return;
  }

  unsigned const parent = GetParent(heapIndex);
  if (dataSet[heapIndex] > dataSet[parent]) {
    std::swap(dataSet[heapIndex], dataSet[parent]);
    heapIndex = parent;
  } else {
    state = HEAPIFY_INSERT;
  }
}

void HeapSort::SwapTop() {
  std::swap(dataSet[0], dataSet[upperBound]);
  heapIndex = 0;
  --upperBound;
}

void HeapSort::MaxHeap() {
  if (upperBound == 1) {
    if (dataSet[0] > dataSet[1])
      std::swap(dataSet[0], dataSet[1]);

    heapIndex = 0;
    upperBound = 0;
    state = STOP;
    return;
  }

  if (heapIndex >= upperBound) {
    heapIndex = 0;
    --upperBound;
    return;
  }

  unsigned const left = GetLeftChild(heapIndex);
  unsigned const right = GetRightChild(heapIndex);

  if (left < upperBound) {
    // left is valid
    if (right < upperBound) {
      // right is valid
      if (dataSet[left] < dataSet[right]) {
        // right is bigger
        if (dataSet[right] > dataSet[heapIndex]) {
          std::swap(dataSet[right], dataSet[heapIndex]);
          heapIndex = right;
        } else {
          SwapTop();
        }
      } else if (dataSet[left] > dataSet[heapIndex]) {
        // left is bigger
        std::swap(dataSet[left], dataSet[heapIndex]);
        heapIndex = left;
      } else {
        SwapTop();
      }
    } else if (dataSet[left] > dataSet[heapIndex]) {
      std::swap(dataSet[left], dataSet[heapIndex]);
      heapIndex = left;
    } else {
      SwapTop();
    }
  } else {
    SwapTop();
  }
}

void HeapSort::Step() {
  switch (state) {
  case START:
    state = HEAPIFY_CHECK;
    break;

  case HEAPIFY_INSERT:
    ++upperBound;
    heapIndex = upperBound;
    state = HEAPIFY_CHECK;
    // fallthrough
  case HEAPIFY_CHECK:
    Heapify();
    break;

  case MAXHEAP:
    MaxHeap();
    break;

  case STOP:
    return;
  }
}

void HeapSort::Reset() {
  state = START;

  upperBound = 1;
  heapIndex = 0;
}

bool HeapSort::IsDone() const { return state == STOP; }

bool HeapSort::IsHeapifying() const {
  return state == HEAPIFY_CHECK || state == HEAPIFY_INSERT;
}
bool HeapSort::IsSorting() const { return state == MAXHEAP; }

unsigned HeapSort::GetSeperatorIndex() const { return upperBound; }
unsigned HeapSort::GetActiveIndex() const { return heapIndex; }

HeapSort::HeapSort(std::vector<unsigned> &data)
    : Sort(data, Sort::HEAP), state(STOP) {
  assert(data.size() > 1);
}