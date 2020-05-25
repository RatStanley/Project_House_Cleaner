#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "temp.h"



int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "window");
    sf::Clock cl;
    window.setFramerateLimit(30);

    sf::RectangleShape ekran;
    ekran.setSize(sf::Vector2f(1280,720));
    ekran.setPosition(0,0);

//    sf::RectangleShape ekran_2;
//    ekran_2.setSize(sf::Vector2f(1260,700));
//    ekran_2.setPosition(10,10);
//    ekran_2.setFillColor(sf::Color(50,50,100));

    sf::RectangleShape ekran_2;
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




    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> lines = rect(ekran);
    std::vector<sf::Vector2f> points = points_to_cheak(ekran);

    std::vector<sf::RectangleShape> walls;
    walls.emplace_back(ekran);
    walls.emplace_back(sth);
    walls.emplace_back(sec);
    walls.emplace_back(new_);
    walls.emplace_back(ekran_2);

    for(auto& wall : walls)
    {
        for(auto& el : rect(wall))
            lines.emplace_back(el);
        for(auto& el : points_to_cheak(wall))
            points.emplace_back(el);

    }

//    for(auto& el : rect(sth))
//        lines.emplace_back(el);
//    for(auto& el : rect(sec))
//        lines.emplace_back(el);
//    for(auto& el : rect(new_))
//        lines.emplace_back(el);

//    for(auto& el : rect(ekran_2))
//        lines.emplace_back(el);

//    for(auto& el : points_to_cheak(sth))
//        points.emplace_back(el);
//    for(auto& el : points_to_cheak(sec))
//        points.emplace_back(el);
//    for(auto& el : points_to_cheak(new_))
//        points.emplace_back(el);

//    for(auto& el : points_to_cheak(ekran_2))
//        points.emplace_back(el);

    std::vector<std::vector<sf::Vector2f>> temp;
    std::vector<sf::RectangleShape> boxys;
    sf::ConvexShape maska;
    std::vector<sf::ConvexShape> maska_vec;

    while(window.isOpen())
    {
        sf::Time el = cl.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        temp = intersection_point(lines, points, window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        temp = sort(temp, window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        boxys = box(temp);
        maska_vec = vector_v2_mask(temp,points);


        for(auto& el: maska_vec)
            window.draw(el);

        window.draw(sth);
        window.draw(sec);
        window.draw(new_);




        for(size_t i = 0; i < temp.size(); i+=1)
        {
            sf::Vertex line[] =
            {
                //sf::Vertex(window.mapPixelToCoords(sf::Mouse::getPosition(window))),
                sf::Vertex(temp[i][0]),
                sf::Vertex(temp[i][temp[i].size()-1])
            };

            window.draw(line, 2, sf::Lines);
        }

        for(auto& el : boxys)
            window.draw(el);

        //std::cout << 1/el.asSeconds() << std::endl;
        window.display();
    }
}

