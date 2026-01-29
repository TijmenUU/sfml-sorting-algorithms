#pragma once
#include "sort.hpp"

class InsertionSort : public Sort {
protected:
    enum State
    {
        START,
        STOP,
        SORTING
    };
    State state;
    unsigned index;
    unsigned currentIndex;
    unsigned referenceIndex;

public:
    void Step() override;
    void Reset() final;
    bool IsDone() const override;

    unsigned GetIndex() const;
    unsigned GetCurrentIndex() const;

    InsertionSort(std::vector<unsigned> & data);
};