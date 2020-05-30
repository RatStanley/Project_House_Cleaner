#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "maska.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "window");
    window.setFramerateLimit(30);
    sf::Clock cl;


    maska Maska;
    sf::View view;
    view.setSize(1280,720);


    sf::RectangleShape map_borders;
    map_borders.setSize(sf::Vector2f(12800,7200));
    map_borders.setPosition(map_borders.getSize().x/2,map_borders.getSize().y/2);
    map_borders.setOrigin(map_borders.getSize().x/2,map_borders.getSize().y/2);


    sf::RectangleShape map_frame;
    map_frame.setSize(map_borders.getSize());
    map_frame.setOrigin(map_frame.getSize().x/2,map_frame.getSize().y/2);
    map_frame.setPosition(map_borders.getPosition());
    map_frame.setScale(1.01,1.02);


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

    Maska.set_Map_Bond(map_borders,map_frame); // by działało dodaj te dwie do .rect_to_cheak

    Maska.rect_to_cheak(sth);
    Maska.rect_to_cheak(sec);
    Maska.rect_to_cheak(new_);
    Maska.rect_to_cheak(new_2);
    Maska.rect_to_cheak(new_3);




    while(window.isOpen())
    {
        sf::Time el = cl.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            view.move(-150*el.asSeconds(),0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            view.move(150*el.asSeconds(),0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            view.move(0,-150*el.asSeconds());
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            view.move(0,150*el.asSeconds());
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            view.move(0,0);

        window.setView(view);
        window.clear(sf::Color::Black);


        window.draw(sth);
        window.draw(sec);
        window.draw(new_);
        window.draw(new_2);
        window.draw(new_3);


        Maska.set_pos(view,window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        for(auto& el : Maska.Vec_mask())
            window.draw(el);

        for(size_t i = 0; i < Maska.insersection.size(); i+=+1)
        {
            sf::Vertex line[] =
            {
                sf::Vertex(window.mapPixelToCoords(sf::Mouse::getPosition(window))),
                //sf::Vertex(temp[i+1]),
                sf::Vertex(Maska.insersection[i][0])
            };

            window.draw(line, 2, sf::Lines);
        }



        window.display();
    }
}
