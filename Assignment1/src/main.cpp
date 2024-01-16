#include <iostream>
#include <filesystem>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main(int argc, char* argv[]) {

    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

    sf::RenderWindow window(sf::VideoMode(800, 600), "My SFML");

    // Rectangle
    sf::Vector2f rSize(250.0f, 100.0f);
    sf::RectangleShape rect(rSize);
    sf::Vector2f rectMoveSpeed(0.1f, 0.05f);
    rect.setFillColor(sf::Color(255, 215, 0));

    // 字体
    sf::Font font;
    if (!font.loadFromFile("bin/fonts/coffee-shop-bold-small-cap.ttf")) {
        return -1;
    }
    sf::Text text("Hello World!", font, 24);
    text.setFillColor(sf::Color::Red);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                std::cout << "Key pressed with code = " << event.key.code << std::endl;
                if (event.key.code == sf::Keyboard::X) {
                    rectMoveSpeed *= -1.0f;
                }
            }
        }

        rect.setPosition(rect.getPosition().x + rectMoveSpeed.x, rect.getPosition().y + rectMoveSpeed.y);

        sf::Vector2f centerRect(rect.getPosition().x + rect.getSize().x / 2,
                                rect.getPosition().y + rect.getSize().y / 2);

        text.setPosition(centerRect.x - text.getGlobalBounds().width / 2, 
                         centerRect.y - text.getGlobalBounds().height / 2);

        window.clear();
        window.draw(rect);
        window.draw(text);
        window.display();
    }

    return 0;
}