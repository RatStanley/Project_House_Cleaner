#include "game.h"

Game::Game()
{
    window = new sf::RenderWindow(sf::VideoMode(1280, 720), "window");
    window->setFramerateLimit(30);
    Maska = new maska;
    mapa = new Map("../map_folder/MAP1.bmp");// test.bmp lub map_1.bmp test1 door_test
    hero = new Hero;
    view.setSize(1280,720);
    View_rec.setSize(sf::Vector2f(1280,720));
    View_rec.setPosition(View_rec.getSize().x/2,View_rec.getSize().y/2);
    View_rec.setOrigin(View_rec.getSize().x/2,View_rec.getSize().y/2);
}

void Game::Game_loop()
{
    while(window->isOpen())
    {
        sf::Time el = clock.restart();
        sf::Event event;
        Events(event);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            view.move(-150*el.asSeconds()*2,0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            view.move(150*el.asSeconds()*2,0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            view.move(0,-150*el.asSeconds()*2);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            view.move(0,150*el.asSeconds()*2);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            if(mapa->elev[0].tp_space.getGlobalBounds().contains(mouse_pos) && mapa->elev[0].used == false)
            {
                mapa->set_new_Map(mapa->elev[0].level);

            }
            if(mapa->elev[1].tp_space.getGlobalBounds().contains(mouse_pos) && mapa->elev[1].used == false)
            {
                mapa->set_new_Map(mapa->elev[1].level);
            }
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            hero->attack();

        window->setView(view);
        mouse_pos = window->mapPixelToCoords(sf::Mouse::getPosition(*window)); // pozycja
        Maska->set_point(*mapa,View_rec,hero->getPosition(),el);
        hero->setPosition(view.getCenter());
        hero->update_status(el);
        View_rec.setPosition(view.getCenter());
        hero->face_to(mouse_pos);
//rysuj
        window->clear(sf::Color(50,50,50));
//        mapa.test_Draw(window); debug
        for(auto& el : Maska->Vec_mask())
            window->draw(el);
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
    }
}
