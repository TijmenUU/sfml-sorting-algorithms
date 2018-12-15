#pragma once
#include "sort.hpp"
#include <cstdint>
#include <stack>

// Helper struct used to define a partition and some additional meta data. Used
// to enable single stepping the algorithm (in both partitioning and insertion
// sorting phases)
struct QSortState {
private:
  unsigned lower;
  unsigned upper;

public:
  unsigned divider;
  unsigned current;
  unsigned index;

  unsigned GetLowerBound() const;
  unsigned GetUpperBound() const;

  QSortState();
  QSortState(unsigned const lowerBound, unsigned const upperBound);
};

// Selection sort + Partitioning hybrid algorithm
class QuickSort : public Sort {
protected:
  enum State { PARTITION, SORTING, START, STOP };
  State state;

  QSortState stateData;

  std::stack<QSortState> partitions;
  std::stack<QSortState> sortRanges;

  void CreatePartition(int64_t const lower, int64_t const upper);
  void Partition();
  void Sort();

public:
  void Step() override;
  void Reset() final;
  bool IsDone() const override;
  bool IsPartitioning() const;
  bool IsSorting() const;

  // void Debug() const override;

  QSortState const &GetState() const;

  QuickSort(std::vector<unsigned> &data);
};
