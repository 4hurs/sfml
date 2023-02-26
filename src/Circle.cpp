#include <Circle.hpp>

Circle::Circle(float radius, sf::Vector2f pos, sf::Vector2f vel) {
        m_shape.setRadius(radius);
        m_shape.setOrigin(radius, radius);
        m_shape.setPosition(pos);
        m_vel = vel;
}

Circle::~Circle() {}

void Circle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_shape, states);
}

void Circle::step() {
        m_shape.move(m_vel);
}

void Circle::move(sf::Vector2f offset) {
        m_shape.move(offset);
}

sf::Vector2f Circle::getPosition() {
        return m_shape.getPosition();
}

float Circle::getRadius() {
        return m_shape.getRadius();
}