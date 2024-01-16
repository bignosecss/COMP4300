#include <iostream>
#include <filesystem>
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main(int argc, char* argv[]) {

    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

    sf::RenderWindow window(sf::VideoMode(800, 600), "My SFML");

    // 字体
    sf::Font font;
    if (!font.loadFromFile("bin/fonts/Wizard-2Omwv.otf")) {
        return -1;
    }
    sf::Text text("Hello World!", font, 24);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setPosition(420.f, 200.f);
    text.setRotation(45.f);
    text.rotate(10.f);
    float rotation = text.getRotation();
    text.scale(1.5f, 2.0f);
    std::cout << "The text rotate: " << rotation << std::endl;

    // texture
    sf::Texture texture;
    if (!texture.loadFromFile("bin/images/Jordan.jpg", sf::IntRect(10, 10, 320, 320))) {
        return -1;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.draw(text);
        window.draw(sprite);
        window.display();
    }

    return 0;
}