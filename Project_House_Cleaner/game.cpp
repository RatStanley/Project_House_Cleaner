#include "game.h"

Game::Game()
{
    window = new sf::RenderWindow(sf::VideoMode(1280, 720), "window");
    window->setFramerateLimit(60);
    Maska = new maska;
    mapa = new Map("../map_folder/MAP1.bmp");// test.bmp lub map_1.bmp test1 door_test
    hero = new Hero;
    view.setSize(1280,720);
    View_rec.setSize(sf::Vector2f(1280,720));
    View_rec.setPosition(View_rec.getSize().x/2,View_rec.getSize().y/2);
    View_rec.setOrigin(View_rec.getSize().x/2,View_rec.getSize().y/2);

    hero->setPosition(737,629);
//    hero->setPosition(2000,2000);
    view.setCenter(hero->getPosition());
}

void Game::Game_loop()
{
    while(window->isOpen())
    {
        sf::Time el = clock.restart();
        sf::Event event;
        Events(event);

        hero->movement(el,mapa->Wall_cols);

//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
//        {
////            view.move(-150*el.asSeconds()*2,0);
//            hero->move(-150*el.asSeconds()*2,0);
//        }
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
//        {
////            view.move(150*el.asSeconds()*2,0);
//            hero->move(150*el.asSeconds()*2,0);
//        }
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
//        {
////            view.move(0,-150*el.asSeconds()*2);
//            hero->move(0,-150*el.asSeconds()*2);
//        }
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
//        {
////            view.move(0,150*el.asSeconds()*2);
//            hero->move(0,150*el.asSeconds()*2);
//        }
//        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
//            hero->attack();

        hero->face_to(mouse_pos);
//        hero->setPosition(view.getCenter());
        hero->update_status(el);

        hero->colision(mapa->Wall_cols);

        View_rec.setPosition(hero->getPosition());
        view.setCenter(hero->getPosition());
        window->setView(view);
        mouse_pos = window->mapPixelToCoords(sf::Mouse::getPosition(*window)); // pozycja
        Maska->set_point(*mapa,View_rec,hero->getPosition(),el);
//rysuj
        window->clear(sf::Color(150,150,150));
        for(auto& el : Maska->Vec_mask())
            window->draw(el);
//        mapa->test_Draw(*window); //debug

        window->draw(*hero);
        window->display();
//        std::cout << 1/el.asSeconds() << std::endl;
    }
}

void Game::set_enemy()
{

}

void Game::Events(sf::Event event)
{
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
        if(event.key.code == sf::Keyboard::Num1)
            hero->Weapon_Change(1);
        if(event.key.code == sf::Keyboard::Num2)
            hero->Weapon_Change(2);
        if(event.key.code == sf::Keyboard::Num3)
            hero->Weapon_Change(3);
        if(event.key.code == sf::Keyboard::R)
            hero->reload();
        if(event.key.code == sf::Keyboard::E)//(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            if(mapa->elev[0].tp_space.getGlobalBounds().contains(hero->getPosition()) && mapa->elev[0].used == false)
            {
                mapa->set_new_Map(mapa->elev[0].level);

            }
            if(mapa->elev[1].tp_space.getGlobalBounds().contains(hero->getPosition()) && mapa->elev[1].used == false)
            {
                mapa->set_new_Map(mapa->elev[1].level);
            }
        }
    }
}
