#include <SFML/Graphics.hpp>
#include "Algorithms.hpp"
#include <memory> // For std::unique_ptr
#include <random>

unsigned int WINDOW_X = 800;
unsigned int WINDOW_Y = 600;

void drawSorter(sf::RenderWindow &window, Sorter &sorter)
{
    float f_WINDOW_X = static_cast<float>(WINDOW_X);
    float f_WINDOW_Y = static_cast<float>(WINDOW_Y);
    float f_data_size = static_cast<float>(sorter.data.size());
    float barWidth = f_WINDOW_X / f_data_size;
    for (size_t i = 0; i < sorter.data.size(); i++)
    {
        // getcurrent val in list
        float val = static_cast<float>(sorter.data[i]);
        float f_i = static_cast<float>(i);

        // Make and move the bar
        sf::RectangleShape bar(sf::Vector2f(barWidth - 2.0f, val));
        bar.setPosition(f_i * barWidth, f_WINDOW_Y - val);

        // Highlight the active elements
        if (i == (size_t)sorter.activeA || i == (size_t)sorter.activeB)
        {
            bar.setFillColor(sf::Color::Red);
        }
        else
        {
            bar.setFillColor(sf::Color::Cyan);
        }

        window.draw(bar);
    }
}

std::vector<int> getRandomData()
{
    return {400, 150, 550, 200, 100, 300, 450, 50, 280, 120};
}

// main needs to return int so system can see what level of error/success we had
int main()
{

    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "Sorting Visualizer");
    window.setFramerateLimit(60);

    // Initial Data
    std::vector<int> data1 = getRandomData();
    std::vector<int> data2 = data1;

    // Use a pointer to the Base class so we can switch algorithms easily
    // We use unique_ptr so C++ handles the "delete" for us automatically
    std::unique_ptr<Sorter> bubble = std::make_unique<BubbleSorter>(data1);
    std::unique_ptr<Sorter> selection = std::make_unique<SelectionSorter>(data2);

    // Set viewports
    sf::View leftView(sf::FloatRect(0, 0, 800, 600));
    sf::View rightView(sf::FloatRect(0, 0, 800, 600));
    leftView.setViewport(sf::FloatRect(0.0f, 0.0f, 0.5f, 1.0f));
    rightView.setViewport(sf::FloatRect(0.5f, 0.0f, 0.5f, 1.0f));

    bool hasStarted {false};

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (!hasStarted) 
            {
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    // Start sorting with a 50ms delay
                bubble->start(50);
                selection->start(50);
                hasStarted = true;
                }
            }
        }

        // Dark grey background
        window.clear(sf::Color(30, 30, 30));

        window.setView(leftView);
        drawSorter(window, *bubble);

        window.setView(rightView);
        drawSorter(window, *selection);

        window.display();
    }

    return 0;
}
