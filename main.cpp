#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <cmath>
#include <Circle.hpp>

int main()
{
    auto window = new sf::RenderWindow(sf::VideoMode(1000, 1000), "Test");
    Circle circle1(120, { 400, 400 }, { 15, 20 });
    //circle1.m_shape.setFillColor(sf::Color::Red);
    Circle circle2(120, { 120, 120 }, { 20, -7 });
    //circle2.m_shape.setFillColor(sf::Color::Blue);

    sf::Texture texture;
    texture.loadFromFile("apple.png");
    circle1.m_shape.setTexture(&texture);

    sf::Texture texture2;
    texture2.loadFromFile("Newton.jpg");
    circle2.m_shape.setTexture(&texture2);

    Circle* circles[] = { &circle1, &circle2 };

    sf::Clock timer;
    sf::Clock timer2;
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }                               //закрытие окна (крестик)


        window->clear();

        if (timer.getElapsedTime().asMilliseconds() > 30) {
            for each (Circle * circle in circles)
            {
                if (circle->getPosition().x + circle->m_vel.x >= 1000 - circle->getRadius() || circle->getPosition().x + circle->getPosition().x <= 0 + circle->getRadius()) {
                    circle->m_vel.x = -circle->m_vel.x;
                }
                if (circle->getPosition().y + circle->m_vel.y >= 1000 - circle->getRadius() || circle->getPosition().y + circle->getPosition().y <= 0 + circle->getRadius()) {
                    circle->m_vel.y = -circle->m_vel.y;
                }
            }                       //отскок от стен

            sf::Vector2f pos1 = circle1.getPosition();
            sf::Vector2f pos2 = circle2.getPosition();

            if (std::sqrt(
                (pos1.x - pos2.x) * (pos1.x - pos2.x) +
                (pos1.y - pos2.y) * (pos1.y - pos2.y)
            ) <= circle1.getRadius() + circle2.getRadius()) {
                // Направление от первого ко второму
                sf::Vector2f OtoT = { pos2.x - pos1.x, pos2.y - pos1.y };
                OtoT = OtoT / std::sqrt(OtoT.x * OtoT.x + OtoT.y * OtoT.y);
                // То же самое но в противоположном направлении
                sf::Vector2f TtoO = -OtoT;


                // Домножаем на длинну скорости => поворачиваем скорость в направлении против второго шара 
                OtoT *= std::sqrt(circle2.m_vel.x * circle2.m_vel.x + circle2.m_vel.y * circle2.m_vel.y);
                TtoO *= std::sqrt(circle1.m_vel.x * circle1.m_vel.x + circle1.m_vel.y * circle1.m_vel.y);

                // Присваиваем новую скорость
                circle1.m_vel = TtoO;
                circle2.m_vel = OtoT;
            }

            circle1.step();
            circle2.step();

            timer.restart();
        }

        window->draw(circle1);
        window->draw(circle2);

        window->display();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}
