#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "temp.h"



int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "window");
    sf::Clock cl;
    //window.setFramerateLimit(20);

    sf::RectangleShape ekran;
    ekran.setSize(sf::Vector2f(1280,720));
    ekran.setPosition(0,0);

    sf::RectangleShape sth;
    sth.setSize(sf::Vector2f(25,500));
    sth.setPosition(700,100);
    sth.setFillColor(sf::Color(100,100,100));

    sf::RectangleShape sec;
    sec.setSize(sf::Vector2f(500,25));
    sec.setPosition(10,600);
    sec.setFillColor(sf::Color(100,100,100));


    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> lines = rect(ekran);
    std::vector<sf::Vector2f> points = points_to_cheak(ekran);



    for(auto& el : rect(sth))
        lines.emplace_back(el);
    for(auto& el : rect(sec))
        lines.emplace_back(el);
    for(auto& el : points_to_cheak(sth))
        points.emplace_back(el);
    for(auto& el : points_to_cheak(sec))
        points.emplace_back(el);

    std::vector<sf::Vector2f> temp;
    std::vector<sf::RectangleShape> test;
    sf::ConvexShape maska;

    while(window.isOpen())
    {
        sf::Time el = cl.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        temp = intersection_point(lines, points, window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        temp = sort(temp, window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        test = box(temp);
        //maska = mask(temp);


        //window.draw(maska);
        window.draw(sth);
        window.draw(sec);
        //std::cout << test.size() << std:: endl;
        for(size_t i = 0; i < temp.size(); i+=2)
        {
            sf::Vertex line[] =
            {
                sf::Vertex(window.mapPixelToCoords(sf::Mouse::getPosition(window))),
                //sf::Vertex(temp[i+1]),
                sf::Vertex(temp[i])
            };

            window.draw(line, 2, sf::Lines);
        }


        for(auto& el : test)
            window.draw(el);
        std::cout << 1/el.asSeconds() << std::endl;
        window.display();
    }
}

