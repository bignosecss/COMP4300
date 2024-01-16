#include <iostream>
#include <filesystem>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>

void loadFromFile(const std::string& filename) {
    std::ifstream fin(filename);

    std::string settingsType;
    // Window settings
    int winWidth, winHeight;
    // Font settings
    std::string fontFile;
    int fontSize;
    int fontR, fontG, fontB;

    std::string shapeName;
    float xxPos, yyPos;
    float xxVel, yyVel;
    int shapeR, shapeG, shapeB;
    // Rectangle settings
    float rectWidth, rectHeight;
    // Circle settings
    float radius;

    std::string temp;
    while (fin >> temp) {
        std::cout << "Hello: " << filename << " " << temp << std::endl;
        // if (settingsType == "Window") {
        //     fin >> winWidth >> winHeight;
        // } else if (settingsType == "Font") {
        //     fin >> fontFile >> fontSize >> fontR >> fontG >> fontB;
        // } else if (settingsType == "Rectangle") {
        //     fin >> shapeName;
        //     fin >> xxPos >> yyPos >> xxVel >> yyVel;
        //     fin >> shapeR >> shapeG >> shapeB;
        //     fin >> rectWidth >> rectHeight;
        // } else if (settingsType == "Circle") {
        //     fin >> shapeName;
        //     fin >> xxPos >> yyPos >> xxVel >> yyVel;
        //     fin >> shapeR >> shapeG >> shapeB;
        //     fin >> radius;
        // }
    }
}


int main(int argc, char* argv[]) {

    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    loadFromFile(argv[1]);

    const int wWidth = 800;
    const int wHeight = 600;
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "My SFML");

    // Rectangle
    sf::Vector2f rSize(250.0f, 100.0f);
    sf::RectangleShape rect(rSize);
    sf::Vector2f rectMoveSpeed(0.1f, 0.05f);
    rect.setFillColor(sf::Color(255, 215, 0));
    rect.setPosition(100, 100);
    float accelerate = 1.0f;

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

        if (rect.getGlobalBounds().left <= 0 || rect.getGlobalBounds().left + rect.getSize().x >= wWidth) {
            rectMoveSpeed.x *= -1.0f;
            accelerate += 0.01f;
        }

        if (rect.getGlobalBounds().top <= 0 || rect.getGlobalBounds().top + rect.getSize().y >= wHeight) {
            rectMoveSpeed.y *= -1.0f;
            accelerate += 0.01f;
        }

        rect.setPosition(rect.getPosition().x + rectMoveSpeed.x * accelerate,
                         rect.getPosition().y + rectMoveSpeed.y * accelerate);

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