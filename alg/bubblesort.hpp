#pragma once
#include "sort.hpp"

class BubbleSort : public Sort {
private:
  enum State { START, STOP, SORTING };
  State state;
  unsigned lowerBound;
  unsigned current;

public:
  void Step() override;
  void Reset() final;
  bool IsDone() const override;

  unsigned GetLowerBound() const;
  unsigned GetCurrentIndex() const;

  BubbleSort(std::vector<unsigned> &data);
};