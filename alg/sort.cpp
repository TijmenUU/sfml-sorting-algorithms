#include "sort.hpp"
#include <cstdio>

void Sort::Debug() const { std::puts("DEBUG: Not implemented."); }

Sort::Sort(std::vector<unsigned> &data, Type const t)
    : dataSet(data), type(t) {}
