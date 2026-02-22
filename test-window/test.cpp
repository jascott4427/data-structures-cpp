// Import Packages
#include <SFML/Graphics.hpp> // Includes the 2D graphics tools
#include <vector>            // A dynamic array (like an Arduino array, but smarter)
#include <algorithm>         // Useful for things like std::swap

// Main function loop
int main() {
    // 1. Setup the Window: (Width, Height, Title)
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sorting Visualizer");
    window.setFramerateLimit(60); // Limits the loop to 60 "ticks" per second

    // 2. Data Setup: Create a list of numbers to sort
    std::vector<int> data = {150, 400, 200, 350, 100, 500, 250};
    float barWidth = 50.0f; // How wide each rectangle is

    // 3. The Main Loop (Your 'void loop')
    while (window.isOpen()) {
        
        // CHECK FOR EVENTS (Like clicking the X button)
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // --- SORTING LOGIC GOES HERE ---
        // For now, we just display the static bars.

        // 4. RENDERING (Drawing stuff)
        window.clear(sf::Color::Black); // Wipe the screen black first

        // 1. Use size_t instead of int to match data.size()
        for (std::size_t i = 0; i < data.size(); i++) {
            
            // 2. Explicitly cast the height to float
            float height = static_cast<float>(data[i]);
            sf::RectangleShape bar(sf::Vector2f(barWidth - 5, height));

            // 3. Explicitly cast 'i' to float for position math
            float xPos = static_cast<float>(i) * barWidth;
            float yPos = 600.0f - height;
            
            // 
            bar.setPosition(xPos, yPos);
            bar.setFillColor(sf::Color::Green);
            
            window.draw(bar);
        }

        window.display(); // Push everything we drew to the screen
    }

    return 0;
}
