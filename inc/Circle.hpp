#pragma once
#include <SFML/Graphics.hpp>

class Circle : public sf::Drawable {
public:
    sf::Vector2f m_vel;
    sf::CircleShape m_shape;

    Circle(float radius, sf::Vector2f pos, sf::Vector2f vel);
    ~Circle();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void step();
    void move(sf::Vector2f offset);
    sf::Vector2f getPosition();
    float getRadius();
};