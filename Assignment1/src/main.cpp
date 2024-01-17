#include <iostream>
#include <filesystem>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>

class MyRectangle {
public:
    sf::RectangleShape m_rect;
    sf::Vector2f       m_position;
    sf::Vector2f       m_rectMoveSpeed;
    sf::Vector2f       m_size;
    MyRectangle(const sf::Vector2f& size, int R, int G, int B)
        : m_rect(size) {
        m_rect.setFillColor(sf::Color(R, G, B));
    }

    void setRectPosition(const sf::Vector2f& pos) {
        m_rect.setPosition(pos);
    }

    void setRectMoveSpeed(const sf::Vector2f& speed) {
        m_rectMoveSpeed = speed;
    }

    // collision detection and update the position
    void updateRect(const sf::RenderWindow& window) {
        // 窗口碰撞检测
        if (m_rect.getGlobalBounds().left <= 0 || 
            m_rect.getGlobalBounds().left + m_rect.getSize().x > window.getSize().x) {
            m_rectMoveSpeed.x *= -1.0f;
        }
        if (m_rect.getGlobalBounds().top <= 0 ||
            m_rect.getGlobalBounds().top + m_rect.getSize().y >= window.getSize().y) {
            m_rectMoveSpeed.y *= -1.0f;
        }
        // 更新矩形的位置
        m_rect.setPosition(m_rect.getPosition() + m_rectMoveSpeed);
    }

    void drawRect(sf::RenderWindow& window) {
        window.draw(m_rect);
    }
};

int main(int argc, char* argv[]) {

    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

    const int wWidth = 1280;
    const int wHeight = 720;
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "My SFML");

    // two rectangles
    MyRectangle myRect1(sf::Vector2f(100, 60), 144, 238, 144);
    myRect1.setRectPosition(sf::Vector2f(100, 60));
    myRect1.setRectMoveSpeed(sf::Vector2f(1.0f, 0.5f));
    MyRectangle myRect2(sf::Vector2f(150, 120), 255, 69, 0);
    myRect2.setRectPosition(sf::Vector2f(300, 200));
    myRect2.setRectMoveSpeed(sf::Vector2f(-0.5f, -1.0f));

    std::vector<MyRectangle> myRects;
    myRects.push_back(myRect1);
    myRects.push_back(myRect2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                std::cout << "Key pressed with code = " << event.key.code << std::endl;
                if (event.key.code == sf::Keyboard::X) {
                    // reverse the direction of speed
                    for (auto& rect : myRects) {
                        rect.m_rectMoveSpeed *= -1.0f;
                    }
                }
            }
        }

        // 更新所有矩形
        for (auto& rect : myRects) {
            rect.updateRect(window);
        }

        window.clear();

        // 画出所有矩形
        for (auto& rect : myRects) {
            rect.drawRect(window);
        }

        window.display();
    }

    return 0;
}