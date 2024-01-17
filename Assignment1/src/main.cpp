#include <iostream>
#include <filesystem>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>

class MyShape {
public:
    virtual void setPosition(const sf::Vector2f& position) = 0;
    virtual void setMoveSpeed(const sf::Vector2f& speed)  = 0;
    virtual void update(const sf::RenderWindow& window) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};

class MyRectangle : public MyShape {
public:
    sf::RectangleShape m_rect;
    sf::Vector2f       m_rectMoveSpeed;

    MyRectangle(const sf::Vector2f& size, int R, int G, int B)
        : m_rect(size) {
        m_rect.setFillColor(sf::Color(R, G, B));
    }

    void setPosition(const sf::Vector2f& pos) override {
        m_rect.setPosition(pos);
    }

    void setMoveSpeed(const sf::Vector2f& speed) override {
        m_rectMoveSpeed = speed;
    }

    // collision detection and update the position
    void update(const sf::RenderWindow& window) override {
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

    void draw(sf::RenderWindow& window) override {
        window.draw(m_rect);
    }
};

class MyCircle : public MyShape {
public:
    sf::CircleShape m_circle;
    sf::Vector2f m_circleMoveSpeed;

    MyCircle(float r, int R, int G, int B)
        : m_circle(r) {
        m_circle.setFillColor(sf::Color(R, G, B));
    }

    void setPosition(const sf::Vector2f& pos) override {
        m_circle.setPosition(pos);
    }

    void setMoveSpeed(const sf::Vector2f& speed) override {
        m_circleMoveSpeed = speed;
    }

    void update(const sf::RenderWindow& window) override {
        // 窗口碰撞检测
        if (m_circle.getGlobalBounds().left <= 0 ||
            m_circle.getGlobalBounds().left + m_circle.getRadius() * 2 >= window.getSize().x) {
           m_circleMoveSpeed.x *= -1.0f;
        }
        if (m_circle.getGlobalBounds().top <= 0 ||
            m_circle.getGlobalBounds().top + m_circle.getRadius() * 2 >= window.getSize().y) {
           m_circleMoveSpeed.y *= -1.0f;
        }
        // 更新圆的位置
        m_circle.setPosition(m_circle.getPosition() + m_circleMoveSpeed);
    }

    void draw(sf::RenderWindow& window) override {
        window.draw(m_circle);
    }
};

int main(int argc, char* argv[]) {

    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

    const int wWidth = 1280;
    const int wHeight = 720;
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "My SFML");

    // two rectangles
    std::shared_ptr<MyRectangle> myRect1 = std::make_shared<MyRectangle>(sf::Vector2f(100, 60), 144, 238, 144);
    myRect1->setPosition(sf::Vector2f(100, 60));
    myRect1->setMoveSpeed(sf::Vector2f(1.0f, 0.5f));
    std::shared_ptr<MyRectangle> myRect2 = std::make_shared<MyRectangle>(sf::Vector2f(150, 120), 255, 69, 0);
    myRect2->setPosition(sf::Vector2f(300, 200));
    myRect2->setMoveSpeed(sf::Vector2f(-0.5f, -1.0f));

    // two circles
    std::shared_ptr<MyCircle> myCircle1 = std::make_shared<MyCircle>(20.0f, 255, 0, 0);
    myCircle1->setPosition(sf::Vector2f(200, 200));
    myCircle1->setMoveSpeed(sf::Vector2f(1.25, 0.75));
    std::shared_ptr<MyCircle> myCircle2 = std::make_shared<MyCircle>(30.0f, 255, 215, 0);
    myCircle2->setPosition(sf::Vector2f(150, 100));
    myCircle2->setMoveSpeed(sf::Vector2f(-0.5f, -0.75f));

    std::vector<std::shared_ptr<MyRectangle>> myRects;
    myRects.push_back(myRect1);
    myRects.push_back(myRect2);
    std::vector<std::shared_ptr<MyCircle>> myCircles;
    myCircles.push_back(myCircle1);
    myCircles.push_back(myCircle2);

    // std::vector<MyShape> shapes;
    // shapes.push_back(myRect1);
    // shapes.push_back(myRect2);
    // shapes.push_back(myCircle1);
    // shapes.push_back(myCircle2);

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
                        rect->m_rectMoveSpeed *= -1.0f;
                    }
                    for(auto& circle : myCircles) {
                        circle->m_circleMoveSpeed *= -1.0f;
                    }
                }
            }
        }

        // 更新所有图形
        for (auto& rect : myRects) {
            rect->update(window);
        }
        for (auto& circle : myCircles) {
            circle->update(window);
        }

        window.clear();

        // 画出所有图形
        for (auto& rect : myRects) {
            rect->draw(window);
        }
        for (auto& circle : myCircles) {
            circle->draw(window);
        }

        window.display();
    }

    return 0;
}