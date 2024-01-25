#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

class Shape {
public:
    virtual ~Shape() = default;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;

    const sf::Vector2f& getPosition() const {
        return m_position;
    }

    const sf::Vector2f& getVelocity() const {
        return m_velocity;
    }
protected:
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
};

class Rectangle : public Shape {
public:
    Rectangle(float width, float height, const sf::Vector2f& initPos, const sf::Vector2f& initVel)
        : m_width(width), m_height(height) {
        m_position = initPos;
        m_velocity = initVel;
    }

    static void setWindowSize(sf::Vector2f size) {
        windowSize = size;
    }

    void update() override {
        m_position += m_velocity;

        if (m_position.x <= 0 || m_position.x + m_width >= windowSize.x) {
            m_velocity.x *= -1.0f;
        }
        if (m_position.y <= 0 || m_position.y + m_height >= windowSize.y) {
            m_velocity.y *= -1.0f;
        }
    }

    void draw(sf::RenderWindow& window) const override {
        sf::RectangleShape rect(sf::Vector2f(m_width, m_height));
        rect.setPosition(m_position);
        window.draw(rect);
    }
private:
    float m_width;
    float m_height;

    static sf::Vector2f windowSize;
};

class Circle : public Shape {
public:
    Circle(float radius, const sf::Vector2f& initPos, const sf::Vector2f& initVel)
        : m_radius(radius) {
        m_position = initPos;
        m_velocity = initVel;
    }

    static void setWindowSize(sf::Vector2f size) {
        windowSize = size;
    }

    void update() override {
        m_position += m_velocity;

        if (m_position.x <= 0 || m_position.x + m_radius * 2 >= windowSize.x) {
            m_velocity.x *= -1.0f;
        }
        if (m_position.y <= 0 || m_position.y + m_radius * 2 >= windowSize.y) {
            m_velocity.y *= -1.0f;
        }
    }

    void draw(sf::RenderWindow& window) const override {
        sf::CircleShape circle(m_radius);
        circle.setPosition(m_position);
        window.draw(circle);
    }
private:
    float m_radius;
    static sf::Vector2f windowSize;
};

sf::Vector2f Rectangle::windowSize;
sf::Vector2f Circle::windowSize;
class RenderWindow {
public:
    RenderWindow(sf::Vector2f size, const std::vector<std::shared_ptr<Shape>>& shapes)
        : m_window(sf::VideoMode(static_cast<unsigned int>(size.x), static_cast<unsigned int>(size.y)), "SFML Window")
        , m_shapes(shapes) {
        Circle::setWindowSize(size);
        Rectangle::setWindowSize(size);
    }

    void run() {
        while (m_window.isOpen()) {
            handleEvents();
            updateShapes();
            render();
        }
    }

private:
    sf::RenderWindow m_window;
    std::vector<std::shared_ptr<Shape>> m_shapes;

    void handleEvents() {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }
        }
    }

    void updateShapes() {
        for (auto& shape : m_shapes) {
            shape->update();
        }
    }

    void render() {
        m_window.clear();

        for (const auto& shape : m_shapes) {
            shape->draw(m_window);
        }

        m_window.display();
    }
};

int main(int argc, char** argv) {
    std::shared_ptr<Rectangle> rect = std::make_shared<Rectangle>(50.0f, 30.0f, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(5.0f, 2.0f));
    std::shared_ptr<Circle> circle = std::make_shared<Circle>(20.0f, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(3.0f, 5.0f));
    
    std::vector<std::shared_ptr<Shape>> shapes;
    shapes.push_back(rect);
    shapes.push_back(circle);

    RenderWindow window(sf::Vector2f(800, 600), shapes);
    window.run();

    return 0;
}