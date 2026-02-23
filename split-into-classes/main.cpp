#include <SFML/Graphics.hpp>
#include "Algorithms.hpp"
#include <memory> // For std::unique_ptr

// main needs to return int so system can see what level of error/success we had
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sorting Visualizer");
    window.setFramerateLimit(60);

    // Initial Data
    std::vector<int> myData = {400, 150, 550, 200, 100, 300, 450, 50, 280, 120};

    // Use a pointer to the Base class so we can switch algorithms easily
    // We use unique_ptr so C++ handles the "delete" for us automatically
    std::unique_ptr<Sorter> currentSorter = std::make_unique<SelectionSorter>(myData);

    // Start sorting with a 50ms delay
    currentSorter->start(50);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear(sf::Color(30, 30, 30)); // Dark grey background

        float barWidth = 800.0f / static_cast<float>(currentSorter->data.size());

        for (size_t i = 0; i < currentSorter->data.size(); i++) {
            float val = static_cast<float>(currentSorter->data[i]);
            sf::RectangleShape bar(sf::Vector2f(barWidth - 2.0f, val));
            
            bar.setPosition(static_cast<float>(i) * barWidth, 600.0f - val);

            // Highlight the active elements
            if (i == (size_t)currentSorter->activeA || i == (size_t)currentSorter->activeB) {
                bar.setFillColor(sf::Color::Red);
            } else {
                bar.setFillColor(sf::Color::Cyan);
            }

            window.draw(bar);
        }

        window.display();
    }

    return 0;
}
