#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>

int main() {
    // SFML 3.0 uses sf::Vector2u for size
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML + ImGui UCRT64");
    window.setFramerateLimit(60);
    
    // Check if Init succeeds (SFML 3.0 requirement)
    if (!ImGui::SFML::Init(window)) return -1;

    sf::Clock deltaClock;
    while (window.isOpen()) {
        // SFML 3.0 Event handling loop
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Hello, SFML 3.0!");
        if (ImGui::Button("Look Ma, no errors!")) { /* logic */ }
        ImGui::End();

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
