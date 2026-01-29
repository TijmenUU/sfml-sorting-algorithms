#pragma once
#include <vector>

// Abstract / virtual class of a sorting algorithm
class Sort {
protected:
    std::vector<unsigned> & dataSet;

public:
    enum Type
    {
        QSORT,
        INSERTION,
        BUBBLE,
        HEAP,
        MERGE
    };
    Type const type;

    virtual void Step() = 0;
    virtual void Reset() = 0;
    virtual bool IsDone() const = 0;

    virtual void Debug() const;

    Sort(std::vector<unsigned> & data, Type const t);
    virtual ~Sort() = default;
};
