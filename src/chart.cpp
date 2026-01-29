#include "chart.hpp"
#include "alg/algorithms.hpp"
#include <cassert>

void Chart::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    for(auto & bar: bars)
    {
        target.draw(bar, states);
    }
}

void Chart::Reset()
{
    barWidth = static_cast<float>(size.x) / static_cast<float>(dataRef.size());
    bars.clear();
    for(unsigned i = 0; i < dataRef.size(); ++i)
    {
        sf::RectangleShape & bar = bars.emplace_back();

        auto const length = dataRef[i];
        bar.setSize(sf::Vector2f(barWidth, length));
        bar.setPosition({barWidth * i, static_cast<float>(size.y - length)});
        bar.setFillColor(sf::Color::White);
    }
}

void Chart::Update(Sort const * sorterPtr)
{
    // Easy but suboptimal. Now we reiterate over every bar, whilst just iterating
    // over changed bars would be more efficient!
    for(unsigned i = 0; i < dataRef.size(); ++i)
    {
        auto const length = dataRef[i];
        auto & bar = bars[i];
        bar.setSize(sf::Vector2f(barWidth, length));

        auto const pos = bar.getPosition();
        bar.setPosition({pos.x, static_cast<float>(size.y - length)});

        // bar.setFillColor(sf::Color::White);
    }

    switch(sorterPtr->type)
    {
        case Sort::BUBBLE:
        {
            auto const * bsPtr = dynamic_cast<BubbleSort const *>(sorterPtr);
            auto const sorted = bsPtr->GetLowerBound();

            for(unsigned i = 0; i < sorted; ++i)
                bars[i].setFillColor(sf::Color::Green);
            for(unsigned i = sorted; i < bars.size(); ++i)
                bars[i].setFillColor(sf::Color::Red);

            if(!bsPtr->IsDone())
            {
                auto const curIdx = bsPtr->GetCurrentIndex();
                bars[curIdx].setFillColor(sf::Color::Blue);
            }
        }
        break;

        case Sort::QSORT:
        {
            auto const * qsPtr = dynamic_cast<QuickSort const *>(sorterPtr);
            auto const & state = qsPtr->GetState();

            if(qsPtr->IsPartitioning())
            {
                for(unsigned i = 0; i < state.GetLowerBound(); ++i)
                {
                    bars[i].setFillColor(sf::Color::White);
                }

                for(unsigned i = state.GetLowerBound(); i < state.GetUpperBound(); ++i)
                {
                    bars[i].setFillColor(sf::Color::Blue);
                }
                bars[state.GetUpperBound()].setFillColor(sf::Color::Yellow);

                for(unsigned i = state.GetUpperBound() + 1; i < dataRef.size(); ++i)
                {
                    bars[i].setFillColor(sf::Color::White);
                }
            }
            else if(qsPtr->IsSorting())
            {
                for(unsigned i = state.GetLowerBound(); i < state.index; ++i)
                {
                    bars[i].setFillColor(sf::Color::Green);
                }
            }
        }
        break;

        case Sort::INSERTION:
        {
            auto const * isPtr = dynamic_cast<InsertionSort const *>(sorterPtr);
            auto sortedIndex = isPtr->GetIndex();

            if(sortedIndex >= dataRef.size())
                sortedIndex = dataRef.size() - 1;

            for(unsigned i = 0; i <= sortedIndex; ++i)
            {
                bars[i].setFillColor(sf::Color::Green);
            }
            for(unsigned i = sortedIndex + 1; i < dataRef.size(); ++i)
            {
                bars[i].setFillColor(sf::Color::Red);
            }

            auto const currIndex = isPtr->GetCurrentIndex();
            if(currIndex < dataRef.size())
                bars[currIndex].setFillColor(sf::Color::Blue);
        }
        break;

        case Sort::HEAP:
        {
            auto const * hsPtr = dynamic_cast<HeapSort const *>(sorterPtr);
            auto const seperatorIdx = hsPtr->GetSeperatorIndex() + 1U;
            auto const activeIdx = hsPtr->GetActiveIndex();

            if(hsPtr->IsHeapifying())
            {
                for(unsigned i = 0; i < seperatorIdx; ++i)
                {
                    bars[i].setFillColor(sf::Color::Blue);
                }
                bars[activeIdx].setFillColor(sf::Color::Yellow);
            }
            else if(hsPtr->IsSorting())
            {
                for(unsigned i = 0; i < seperatorIdx; ++i)
                {
                    bars[i].setFillColor(sf::Color::Blue);
                }
                bars[activeIdx].setFillColor(sf::Color::Yellow);
                for(unsigned i = seperatorIdx; i < dataRef.size(); ++i)
                {
                    bars[i].setFillColor(sf::Color::Green);
                }
            }
        }
        break;

        case Sort::MERGE:
        {
            auto const * msPtr = dynamic_cast<MergeSort const *>(sorterPtr);
            auto const & leftPart = msPtr->GetLeftPartition();
            auto const & rightPart = msPtr->GetRightPartition();
            auto const & buffer = msPtr->GetBuffer();

            for(unsigned i = leftPart.start; i < rightPart.end; ++i)
            {
                bars[i].setFillColor(sf::Color::Blue);
            }
            // TODO: merge these two loops or put the identical loop body in
            // a function!
            for(unsigned i = leftPart.start; i < leftPart.index; ++i)
            {
                auto & bar = bars[i];
                auto const length = buffer[i];

                bar.setSize(sf::Vector2f(barWidth, length));
                auto const pos = bar.getPosition();
                bar.setPosition({pos.x, static_cast<float>(size.y - length)});
                bar.setFillColor(sf::Color::Green);
            }
            for(unsigned i = rightPart.start; i < rightPart.index; ++i)
            {
                auto & bar = bars[i];
                auto const length = buffer[i];

                bar.setSize(sf::Vector2f(barWidth, length));
                auto const pos = bar.getPosition();
                bar.setPosition({pos.x, static_cast<float>(size.y - length)});
                bar.setFillColor(sf::Color::Green);
            }
        }
        break;

        default:
            break;
    }
}

Chart::Chart(unsigned const chartWidth, unsigned const chartHeight, std::vector<unsigned> const & data)
 : size(chartWidth, chartHeight), barWidth(0.f), dataRef(data)
{ }
