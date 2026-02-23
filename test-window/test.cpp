#include <SFML/Graphics.hpp>
#include <vector>
#include <thread> // For std::thread
#include <atomic> // For thread-safe variables

// These are our "Global" (shared) variables
std::vector<int> data = {100, 50, 200, 150, 300, 10, 80};
std::atomic<int> indexA(-1); // The first index being compared
std::atomic<int> indexB(-1); // The second index being compared
std::atomic<bool> isSorting(false);

// --- THE SORTING FUNCTION (Runs on Thread 2) ---
void bubbleSort()
{
    isSorting = true;
    for (size_t i = 0; i < data.size() - 1; i++)
    {
        for (size_t j = 0; j < data.size() - i - 1; j++)
        {
            // Tell the UI thread what we are looking at
            indexA = (int)j;
            indexB = (int)j + 1;

            if (data[j] > data[j + 1])
            {
                std::swap(data[j], data[j + 1]);
            }

            // CONTROL SPEED: If you don't sleep at all,
            // it sorts millions of items in a blink.
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
    indexA = -1; // Reset highlights when done
    indexB = -1;
    isSorting = false;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Threaded Sorting");

    // Start the sorting thread immediately
    // In a real app, you'd trigger this with a button press
    std::thread sortThread(bubbleSort);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();

        // DRAWING LOGIC
        for (size_t i = 0; i < data.size(); i++)
        {
            float h = static_cast<float>(data[i]);
            sf::RectangleShape bar(sf::Vector2f(40, h));
            bar.setPosition(i * 50.0f, 600.0f - h);

            // COLOR CODING
            if (i == (size_t)indexA || i == (size_t)indexB)
            {
                bar.setFillColor(sf::Color::Red); // Active comparison
            }
            else
            {
                bar.setFillColor(sf::Color::Green);
            }

            window.draw(bar);
        }

        window.display();
    }

    // CLEANUP: If the window closes, we must wait for the thread to finish
    // or "detach" it so it doesn't crash the program.
    if (sortThread.joinable())
    {
        sortThread.detach();
    }

    return 0;
}
