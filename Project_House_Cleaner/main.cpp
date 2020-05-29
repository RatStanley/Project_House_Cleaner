#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "maska.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "window");
    sf::Clock cl;

    maska test;

    sf::RectangleShape ekran;
    ekran.setSize(sf::Vector2f(1280,720));
    ekran.setPosition(0,0);

    sf::RectangleShape ekran_2;
    ekran_2.setSize(sf::Vector2f(1260,700));
    ekran_2.setPosition(10,10);
    ekran_2.setFillColor(sf::Color(50,50,100));

    ekran_2.setSize(sf::Vector2f(1300,740));
    ekran_2.setPosition(-10,-10);
    ekran_2.setFillColor(sf::Color(50,50,100));

    sf::RectangleShape sth;
    sth.setSize(sf::Vector2f(25,500));
    sth.setPosition(700,100);
    sth.setFillColor(sf::Color(100,100,100));

    sf::RectangleShape sec;
    sec.setSize(sf::Vector2f(500,25));
    sec.setPosition(10,600);
    sec.setFillColor(sf::Color(100,100,100));

    sf::RectangleShape new_;
    new_.setSize(sf::Vector2f(500,25));
    new_.setPosition(600,600);
    new_.setFillColor(sf::Color(100,100,100));

    sf::RectangleShape new_2;
    new_2.setSize(sf::Vector2f(500,25));
    new_2.setPosition(100,300);
    new_2.setFillColor(sf::Color(100,100,100));

    sf::RectangleShape new_3;
    new_3.setSize(sf::Vector2f(500,25));
    new_3.setPosition(725,200);
    new_3.setFillColor(sf::Color(100,100,100));

    test.rect_to_cheak(ekran);
    test.rect_to_cheak(ekran_2);
    test.rect_to_cheak(sth);
    test.rect_to_cheak(sec);
    test.rect_to_cheak(new_);
    test.rect_to_cheak(new_2);
    test.rect_to_cheak(new_3);


    while(window.isOpen())
    {
        sf::Time el = cl.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        window.draw(sth);
        window.draw(sec);
        window.draw(new_);
        window.draw(new_2);
        window.draw(new_3);

        test.set_pos(ekran,window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        //test.Done_maska();
        for(auto& el : test.Done_maska())
            window.draw(el);

                for(size_t i = 0; i < test.insersection.size(); i+=1)
                {
                    sf::Vertex line1[] =
                    {
                        //sf::Vertex(window.mapPixelToCoords(sf::Mouse::getPosition(window))),
                        sf::Vertex(test.insersection[i][0],sf::Color::Green),
                        sf::Vertex(window.mapPixelToCoords(sf::Mouse::getPosition(window)),sf::Color::Green)
                    };

                    window.draw(line1, 2, sf::Lines);
                }
std::cout << test.off_set_point.size() << std::endl;
                for(size_t i = 0; i < test.off_set_point.size(); i+=1)
                {
                    sf::Vertex line[] =
                    {
                        //sf::Vertex(window.mapPixelToCoords(sf::Mouse::getPosition(window))),
                        sf::Vertex(test.off_set_point[i],sf::Color::Red),
                        sf::Vertex(window.mapPixelToCoords(sf::Mouse::getPosition(window)))
                    };

                    window.draw(line, 2, sf::Lines);
                }

        window.display();
    }
}
