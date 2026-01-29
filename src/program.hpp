#pragma once
#include "alg/sort.hpp"
#include "chart.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <random>
#include <vector>

class Program {
private:
    sf::RenderWindow window;
    bool fullscreen;
    sf::Clock sfclock;
    std::default_random_engine eng;
    sf::Vector2u resolution;

    std::vector<unsigned> dataSet;
    std::unique_ptr<Sort> sorter;
    Chart chart;

    bool autoStep, autoReset;
    float stepTimeElapsed;

    // Randomizes the data AND resets the chart object
    void RandomizeData();
    // Switches to the next sorting algorithm
    void GetNextSorter();
    // void RandomizeData() + GetNextSorter()
    void Randomize();

    void HandleInput();
    void Update();
    void Draw();

public:
    void Run();

    Program(unsigned const windowWidth, unsigned const windowHeight, unsigned const dataSetSize = 50);
};
