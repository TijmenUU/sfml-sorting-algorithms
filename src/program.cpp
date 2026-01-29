#include "program.hpp"
#include "alg/algorithms.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <cassert>

void Program::RandomizeData()
{
    std::uniform_int_distribution<unsigned> dist(8, resolution.y);
    for(unsigned i = 0; i < dataSet.size(); ++i)
    {
        dataSet[i] = (dist(eng));
    }
    chart.Reset();
}

void Program::GetNextSorter()
{
    static unsigned last = 0;
    unsigned const algCount = 5;

    if(last >= algCount)
        last = 0;

    std::printf("Selecting next algorithm... ");
    switch(last)
    {
        case 0:
            std::puts("Quick sort!");
            sorter = std::make_unique<QuickSort>(dataSet);
            break;

        case 1:
            std::puts("Insertion sort!");
            sorter = std::make_unique<InsertionSort>(dataSet);
            break;

        case 2:
            std::puts("Bubble sort!");
            sorter = std::make_unique<BubbleSort>(dataSet);
            break;

        case 3:
            std::puts("Heap sort!");
            sorter = std::make_unique<HeapSort>(dataSet);
            break;

        case 4:
            std::puts("Merge sort!");
            sorter = std::make_unique<MergeSort>(dataSet);
            break;

        default:
            throw std::runtime_error("Unimplemented sorting algorithm requested.");
    }

    sorter->Reset();
    stepTimeElapsed = 0.f;

    ++last;
}

void Program::Randomize()
{
    RandomizeData();
    GetNextSorter();
}

void PrintHelp()
{
    std::printf("KEYBINDS:\n\t(Esc)ape to (Q)uit.\n\t(S)tep\n\t(A)utomatic stepping");
    std::printf(
        "\n\t(D)Toggle auto reset on "
        "completion\n\t(T)est\n\t(F)ullscreen toggle");
    std::printf("\n\t(N)ext");
    std::printf("\n\t(R)andomize dataset (resets current sorting algorithm)\n\n");
}

void Program::HandleInput()
{
    while(const std::optional event = window.pollEvent())
    {
        if(event->is<sf::Event::Closed>())
        {
            window.close();
        }

        if(const auto * keyReleased = event->getIf<sf::Event::KeyReleased>())
        {
            if(keyReleased->code == sf::Keyboard::Key::Q || keyReleased->code == sf::Keyboard::Key::Escape)
            {
                window.close();
            }

            if(keyReleased->code == sf::Keyboard::Key::H)
            {
                PrintHelp();
            }

            if(keyReleased->code == sf::Keyboard::Key::S)
            {
                sorter->Step();
                chart.Update(sorter.get());
            }

            if(keyReleased->code == sf::Keyboard::Key::F)
            {
                fullscreen = !fullscreen;
                if(fullscreen)
                {
                    // TODO: Don't trash multi-monitor setups with this
                    auto const styleFlag = sf::Style::Default;
                    auto const VModes = sf::VideoMode::getFullscreenModes();
                    window.create(VModes.front(), "Sorting Algorithms", styleFlag, sf::State::Fullscreen);
                    window.setVerticalSyncEnabled(true);
                    window.setView(
                        sf::View(
                            sf::Vector2f(resolution.x / 2.f, resolution.y / 2.f),
                            sf::Vector2f(resolution.x, resolution.y)));
                }
                else
                {
                    window.create(sf::VideoMode({resolution.x, resolution.y}), "Sorting Algorithms");
                    window.setVerticalSyncEnabled(true);
                }
            }

            if(keyReleased->code == sf::Keyboard::Key::A)
            {
                autoStep = !autoStep;
                std::printf("Automatically stepping: %s\n", autoStep ? "Yes" : "No");
            }

            if(keyReleased->code == sf::Keyboard::Key::R)
            {
                RandomizeData();
                sorter->Reset();
            }

            if(keyReleased->code == sf::Keyboard::Key::D)
            {
                autoReset = !autoReset;
                std::printf("Automatically resetting: %s\n", autoReset ? "Yes" : "No");
            }

            if(keyReleased->code == sf::Keyboard::Key::N)
            {
                Randomize();
            }

            if(keyReleased->code == sf::Keyboard::Key::P)
            {
                sorter->Debug();
            }
        }
    }
}

void Program::Update()
{
    auto const elapsed = sfclock.restart();

    if(sorter->IsDone())
    {
        if(autoReset)
            Randomize();
    }
    else if(autoStep)
    {
        stepTimeElapsed += elapsed.asSeconds();
        if(stepTimeElapsed > 0.0f)
        {
            stepTimeElapsed = 0.f;
            sorter->Step();
            chart.Update(sorter.get());
        }
    }
}

void Program::Draw()
{
    window.clear(sf::Color::Black);
    window.draw(chart);
    window.display();
}

void Program::Run()
{
    while(window.isOpen())
    {
        HandleInput();
        Update();
        Draw();
    }
}

Program::Program(unsigned const windowWidth, unsigned const windowHeight, unsigned const dataSetSize)
 : window(sf::VideoMode({windowWidth, windowHeight}), "Sorting Algorithms"), fullscreen(false),
   resolution(windowWidth, windowHeight), chart(windowWidth, windowHeight, dataSet), autoStep(true), autoReset(true),
   stepTimeElapsed(0.f)
{
    window.setVerticalSyncEnabled(true);
    PrintHelp();

    dataSet.resize(dataSetSize);

    Randomize();
}
