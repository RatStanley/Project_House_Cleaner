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

    hero->setPosition(737,590);
//    hero->setPosition(2000,2000);
    view.setCenter(hero->getPosition());

    for(auto& el : mapa->enemy_pos)
    {
        enemy_vec.emplace_back(new Enemy_1(el));
    }
    all_walls = mapa->all_wall_cols;
}

void Game::Game_loop()
{
    while(window->isOpen())
    {
        sf::Time el = clock.restart();
        sf::Event event;
        wall.clear();
        Events(event);

        wall = mapa->Wall_cols;


        for(auto& en : enemy_vec)
            wall.emplace_back(en->hit_box());

        hero->face_to(mouse_pos);
        hero->movement(el,wall);
        Enemy_logic(el);

        hero->update_status(el);

        View_rec.setPosition(hero->getPosition());
        view.setCenter(hero->getPosition());
        window->setView(view);
        mouse_pos = window->mapPixelToCoords(sf::Mouse::getPosition(*window)); // pozycja
        Maska->set_point(*mapa,View_rec,hero->getPosition(),el);
//rysuj
        window->clear(sf::Color(150,150,150));

        for(auto& el : enemy_vec)
            window->draw(*el);
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

void Game::Enemy_logic(sf::Time cl)
{
    if(hero->cheak_if_hit_sth)
    {
        for(auto& point : hero->hit_point)
        {
            for(enemy_it = enemy_vec.begin(); enemy_it != enemy_vec.end();)
            {
                cheak_if_hit((**enemy_it),point, hero->dmg());
                if((*enemy_it)->is_dead)
                {
                    delete *enemy_it;
                    enemy_it = enemy_vec.erase(enemy_it);
                }
                else
                    enemy_it++;

            }
        }
        hero->cheak_if_hit_sth = false;
    }
    for(auto& en : enemy_vec)
    {
        en->change_dir(all_walls);
        en->update_status(cl);
    }
}

void Game::cheak_if_hit(Enemy_1 &ch, sf::Vector2f point, float dmg)
{
    sf::RectangleShape temp;
    temp.setSize(sf::Vector2f(10,10));
    temp.setOrigin(5,5);
    temp.setPosition(point);
    if(ch.hit_box().getGlobalBounds().intersects(temp.getGlobalBounds()))
    {
        ch.hit_hp(dmg);
    }

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
        if(event.key.code == sf::Keyboard::Space)
        {

        }
//        if(event.KeyReleased== sf::Event::KeyReleased)
//        {
//            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
//                    hero->attack();
//        }
    }
}
