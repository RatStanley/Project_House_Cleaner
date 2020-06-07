#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

#include "maska.h"
#include "map.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "window");
    window.setFramerateLimit(30);
    sf::Clock cl;


    maska Maska;
    Map mapa("../map_folder/test1.bmp");// test.bmp lub map_1.bmp test1 door_test
//    Map mapa;
    sf::View view;
    view.setSize(1280,720);

    sf::Vector2f mysz;


    sf::RectangleShape View_rec;
    View_rec.setSize(sf::Vector2f(1280,720));
    View_rec.setPosition(View_rec.getSize().x/2,View_rec.getSize().y/2);
    View_rec.setOrigin(View_rec.getSize().x/2,View_rec.getSize().y/2);
    //View_rec.setFillColor(sf::Color::Red);




    while(window.isOpen())
    {
        sf::Time el = cl.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }
//logika

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            view.move(-150*el.asSeconds()*2,0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            view.move(350*el.asSeconds()*2,0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            view.move(0,-150*el.asSeconds()*2);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            view.move(0,150*el.asSeconds()*2);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            if(mapa.elev[0].tp_space.getGlobalBounds().contains(mysz) && mapa.elev[0].used == false)
            {
                mapa.set_new_Map(mapa.elev[0].level);

            }
            if(mapa.elev[1].tp_space.getGlobalBounds().contains(mysz) && mapa.elev[1].used == false)
            {
                mapa.set_new_Map(mapa.elev[1].level);
            }
        }
        window.setView(view);
        mysz = window.mapPixelToCoords(sf::Mouse::getPosition(window)); // pozycja
        Maska.set_point(mapa,View_rec,mysz,el);
        View_rec.setPosition(view.getCenter());
//rysuj
        window.clear(sf::Color::Black);

        for(auto& el : Maska.Vec_mask())
            window.draw(el);

        //mapa.test_Draw(window);

        window.display();
//        std::cout << 1/el.asSeconds() << std::endl;

    }
}

//mapa.test_Draw(window);
//        for(size_t i = 0; i < Maska.insersection.size(); i+=+1)
//        {
//            sf::Vertex line[] =
//            {
////                sf::Vertex(window.mapPixelToCoords(sf::Mouse::getPosition(window))),
//                sf::Vertex(Maska.insersection[i][0]),
//                sf::Vertex(Maska.insersection[i][1])
//            };

//            window.draw(line, 2, sf::Lines);
//        }
//        for(size_t i = 0; i < Maska.off_set_point.size(); i+=+1)
//        {
//            sf::Vertex line[] =
//            {
//                sf::Vertex(window.mapPixelToCoords(sf::Mouse::getPosition(window)),sf::Color::Red),
//                //sf::Vertex(temp[i+1]),
//                sf::Vertex(Maska.off_set_point[i],sf::Color::Red)
//            };

//            window.draw(line, 2, sf::Lines);
//        }
