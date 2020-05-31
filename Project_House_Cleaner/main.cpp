#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "maska.h"
#include "map.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "window");
//    window.setFramerateLimit(30);
    sf::Clock cl;


    maska Maska;
    Map mapa;

    sf::View view;
    view.setSize(1280,720);



    sf::RectangleShape View_rec;
    View_rec.setSize(sf::Vector2f(1280,720));
    View_rec.setPosition(View_rec.getSize().x/2,View_rec.getSize().y/2);
    View_rec.setOrigin(View_rec.getSize().x/2,View_rec.getSize().y/2);
    View_rec.setFillColor(sf::Color::Red);




sf::Vector2f mysz;
    while(window.isOpen())
    {
        sf::Time el = cl.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            view.move(-150*el.asSeconds()*2,0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            view.move(150*el.asSeconds()*2,0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            view.move(0,-150*el.asSeconds()*2);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            view.move(0,150*el.asSeconds()*2);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            view.move(0,0);

        window.setView(view);
        window.clear(sf::Color::Black);
        View_rec.setPosition(view.getCenter());


        mysz = window.mapPixelToCoords(sf::Mouse::getPosition(window)); // pozycja

        Maska.set_point(mapa,View_rec,mysz);
        for(auto& el : Maska.Vec_mask())
            window.draw(el);

//        for(size_t i = 0; i < Maska.insersection.size(); i+=+1)
//        {
//            sf::Vertex line[] =
//            {
//                sf::Vertex(window.mapPixelToCoords(sf::Mouse::getPosition(window))),
//                //sf::Vertex(temp[i+1]),
//                sf::Vertex(Maska.insersection[i][0])
//            };

//            window.draw(line, 2, sf::Lines);
//        }

        //window.draw(View_rec);

//std::cout << 1/el.asSeconds() << std::endl;
        window.display();
    }
}
