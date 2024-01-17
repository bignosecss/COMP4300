#include <iostream>
#include <filesystem>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>

class MyShape {
public:
    sf::RectangleShape   m_rect;
    sf::CircleShape      m_circle;
    sf::Vector2f         m_speed;

    virtual void setPosition(const sf::Vector2f& position) = 0;
    virtual void setMoveSpeed(const sf::Vector2f& speed)  = 0;
    virtual void update(const sf::RenderWindow& window) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void loadFromFile(const std::string& filename) = 0;
};

class MyRectangle : public MyShape {
public:
    std::vector<std::shared_ptr<MyRectangle>> m_rects;
    std::vector<std::string>                  m_rectNames;

    MyRectangle() {}

    MyRectangle(const sf::Vector2f& size, int R, int G, int B)
        : MyShape() {
        m_rect.setSize(size);
        m_rect.setFillColor(sf::Color(R, G, B));
    }

    void setPosition(const sf::Vector2f& pos) override {
        m_rect.setPosition(pos);
    }

    void setMoveSpeed(const sf::Vector2f& speed) override {
        m_speed = speed;
    }

    // collision detection and update the position
    void update(const sf::RenderWindow& window) override {
        // 窗口碰撞检测
        if (m_rect.getGlobalBounds().left <= 0 || 
            m_rect.getGlobalBounds().left + m_rect.getSize().x > window.getSize().x) {
            m_speed.x *= -1.0f;
        }
        if (m_rect.getGlobalBounds().top <= 0 ||
            m_rect.getGlobalBounds().top + m_rect.getSize().y >= window.getSize().y) {
            m_speed.y *= -1.0f;
        }
        // 更新矩形的位置
        m_rect.setPosition(m_rect.getPosition() + m_speed);
    }

    void draw(sf::RenderWindow& window) override {
        window.draw(m_rect);
    }

    void loadFromFile(const std::string& filename) override {
        std::ifstream fin(filename);

        std::string settingType;
        // rectangle
        std::string rectName;
        float       xxPos, yyPos;
        float       xxVel, yyVel;
        int         R, G, B;
        float       rectWidth, rectHeight;

        while (fin >> settingType) {
            if (settingType == "Rectangle") {
                fin >> rectName;
                fin >> xxPos >> yyPos;
                fin >> xxVel >> yyVel;
                fin >> R >> G >> B;
                fin >> rectWidth >> rectHeight;

                // store the rectangles
                std::shared_ptr<MyRectangle> rect = std::make_shared<MyRectangle>(sf::Vector2f(rectWidth, rectHeight), R, G, B);
                rect->setPosition(sf::Vector2f(xxPos, yyPos));
                rect->setMoveSpeed(sf::Vector2f(xxVel, yyVel));
                m_rects.push_back(rect);
                m_rectNames.push_back(rectName);
                // print all info
                std::cout << rectName << " ";
                std::cout << xxPos << " " << yyPos << " " << xxVel << " " << yyVel << " ";
                std::cout << R << " " << G << " " << B << " ";
                std::cout << rectWidth << " " << rectHeight << std::endl;
            }
        }
    }
};

class MyCircle : public MyShape {
public:
    std::vector<std::string>               m_circleNames;
    sf::Vector2f                           m_circleMoveSpeed;
    std::vector<std::shared_ptr<MyCircle>> m_circles;

    MyCircle() {}

    MyCircle(float r, int R, int G, int B)
        : MyShape() {
        m_circle.setRadius(r);
        m_circle.setFillColor(sf::Color(R, G, B));
    }

    void setPosition(const sf::Vector2f& pos) override {
        m_circle.setPosition(pos);
    }

    void setMoveSpeed(const sf::Vector2f& speed) override {
        m_speed = speed;
    }

    void update(const sf::RenderWindow& window) override {
        // 窗口碰撞检测
        if (m_circle.getGlobalBounds().left <= 0 ||
            m_circle.getGlobalBounds().left + m_circle.getRadius() * 2 >= window.getSize().x) {
           m_speed.x *= -1.0f;
        }
        if (m_circle.getGlobalBounds().top <= 0 ||
            m_circle.getGlobalBounds().top + m_circle.getRadius() * 2 >= window.getSize().y) {
           m_speed.y *= -1.0f;
        }
        // 更新圆的位置
        m_circle.setPosition(m_circle.getPosition() + m_speed);
    }

    void draw(sf::RenderWindow& window) override {
        window.draw(m_circle);
    }

    void loadFromFile(const std::string& filename) override {
        std::ifstream fin(filename);

        std::string settingType;
        // cirrcle
        std::string circleName;
        float       xxPos, yyPos;
        float       xxVel, yyVel;
        int         R, G, B;
        float       radius;

        while (fin >> settingType) {
            if (settingType == "Circle") {
                fin >> circleName;
                fin >> xxPos >> yyPos;
                fin >> xxVel >> yyVel;
                fin >> R >> G >> B;
                fin >> radius;

                // store the circles
                std::shared_ptr<MyCircle> circle = std::make_shared<MyCircle>(radius, R, G, B);
                circle->setPosition(sf::Vector2f(xxPos, yyPos));
                circle->setMoveSpeed(sf::Vector2f(xxVel, yyVel));
                m_circles.push_back(circle);
                m_circleNames.push_back(circleName);
                // print all info
                std::cout << circleName << " ";
                std::cout << xxPos <<  " " << yyPos <<  " " << xxVel <<  " " << yyVel << " ";
                std::cout << R <<  " " << G <<  " " << B <<  " " << radius << std::endl;
            }
        }
    }
};

int main(int argc, char* argv[]) {

    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    if (argc != 3) {
        std::cout << "The 1st cmd argument is the path to the DATA file." << std::endl;
        std::cout << "The 2nd cmd argument is the path to the FONT file." << std::endl;
        return -1;
    }

    const int wWidth = 800;
    const int wHeight = 600;
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "My SFML");

    // all shapes
    MyRectangle rect;
    MyCircle    circle;
    rect.loadFromFile(argv[1]);
    circle.loadFromFile(argv[1]);

    // fonts
    sf::Font font;
    if (!font.loadFromFile(argv[2])) {
        return EXIT_FAILURE;
    }
    // rectangle texts
    std::vector<sf::Text> rectTexts;
    for (auto& rectName : rect.m_rectNames) {
        sf::Text text(rectName, font, 14);
        rectTexts.push_back(text);
    }
    // circle texts
    std::vector<sf::Text> circlrTexts;
    for (auto& circleName : circle.m_circleNames) {
        sf::Text text(circleName, font, 14);
        circlrTexts.push_back(text);
    }

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
                    for (auto& shape : rect.m_rects) {
                        shape->m_speed *= -1.0f;
                    }
                    for (auto& shape : circle.m_circles) {
                        shape->m_speed *= -1.0f;
                    }
                }
            }
        }

        window.clear();
        // 更新并画出所有图形
        for (auto& shape : rect.m_rects) {
            shape->update(window);
            shape->draw(window);
        }
        for (auto& shape : circle.m_circles) {
            shape->update(window);
            shape->draw(window);
        }
        // 打印文本
        for (auto& text : rectTexts) {
            text.setPosition(std::rand() % 400, std::rand() % 400 - 200);
            window.draw(text);
        }
        for (auto& text : circlrTexts) {
            text.setPosition(std::rand() % 400 - 200, std::rand() % 400);
            window.draw(text);
        }
        window.display();
    }

    return 0;
}