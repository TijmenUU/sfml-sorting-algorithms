#include "insertionsort.hpp"
#include <cassert>
#include <cstdio>

void InsertionSort::Step() {
  if (currentIndex >= dataSet.size()) {
    state = STOP;
    return;
  } else if (dataSet[currentIndex] < dataSet[referenceIndex]) {
    std::swap(dataSet[currentIndex], dataSet[referenceIndex]);
    currentIndex = referenceIndex;
    referenceIndex = currentIndex - 1;
  } else {
    currentIndex = 0;
  }

  if (currentIndex == 0) {
    ++index;
    currentIndex = index;
    referenceIndex = index - 1;
  }
}

void InsertionSort::Reset() {
  state = START;
  index = 1;
  currentIndex = index;
  referenceIndex = 0;
}

bool InsertionSort::IsDone() const { return state == STOP; }

unsigned InsertionSort::GetIndex() const { return index; }

unsigned InsertionSort::GetCurrentIndex() const { return currentIndex; }

InsertionSort::InsertionSort(std::vector<unsigned> &data)
    : Sort(data, Sort::INSERTION), state(STOP) {
  assert(dataSet.size() != 0); // We're not dealing with that
}