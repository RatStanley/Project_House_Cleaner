#include "game.h"
#include <string>

Game::Game()
{
    window = new sf::RenderWindow(sf::VideoMode(1280, 720), "window");
    window->setFramerateLimit(60);
    Maska = new maska;
    mapa = new Map("../Resources/map_folder/MAP1.bmp");// test.bmp lub map_1.bmp test1 door_test
    hero = new Hero;
    end_game = false;

    view.setSize(1280,720);
    View_rec.setSize(sf::Vector2f(1280,720));
    View_rec.setPosition(View_rec.getSize().x/2,View_rec.getSize().y/2);
    View_rec.setOrigin(View_rec.getSize().x/2,View_rec.getSize().y/2);

    font.loadFromFile("../Resources/fonts/arial.ttf");

    hero->setPosition(737,590);
    view.setCenter(hero->getPosition());

    for(auto& el : mapa->enemy_pos)
    {
        enemy_vec.emplace_back(new Enemy_1(el,mapa->all_wall_cols));
    }

    if (!particle_tex.loadFromFile("../Resources/texture/spritesheet_particle.png"))
    {
        std::cout << "Could not load texture" << std::endl;
    }
    particle.setTexture(particle_tex);
    particle.setScale(2,2);
    particle.setTextureRect(sf::IntRect(0,0,48,48));
    particle.setOrigin(24,24);
    for(auto& hud : hud_info)
        hud.setFont(font);
}

void Game::Game_loop()
{
    while(window->isOpen())
    {
        sf::Time el = clock.restart();
        sf::Event event;
        wall.clear();
        Events(event);

        if(mapa->end_game || end_game)
            break;
        wall = mapa->Wall_cols;
        anime_particle(el);

        for(auto& en : enemy_vec)
            wall.emplace_back(en->hit_box());

        mouse_pos = window->mapPixelToCoords(sf::Mouse::getPosition(*window)); // pozycja myszki
        hero->face_to(mouse_pos);
        hero->movement(el,wall);
        Enemy_logic(el);

        hero->update_status(el);

        View_rec.setPosition(hero->getPosition());
        view.setCenter(hero->getPosition());
        window->setView(view);
        Maska->set_point(*mapa,View_rec,hero->getPosition(),el);
        hud();
        Draw();
//        std::cout << 1/el.asSeconds() << std::endl;
    }
}

void Game::set_enemy()
{
    for(auto& el : mapa->enemy_pos)
    {
        enemy_vec.emplace_back(new Enemy_1(el,mapa->all_wall_cols));
    }
//    all_walls = mapa->all_wall_cols;
    std::cout << "Enemy on Map : " << enemy_vec.size() << std::endl;
}

void Game::Enemy_logic(sf::Time cl)
{
    if(hero->cheak_if_hit_sth)
    {
        for(auto& point : hero->hit_point)
        {
            particle.setPosition(point);
            particle.setRotation(rand()%360);
            particle.setColor(sf::Color(0,0,0));
//            float temp_size = 1 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1-2)));
//            particle.setScale(temp_size,temp_size);
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
            particle_vec.emplace_back(new std::pair<sf::Sprite,int>(particle,0));
        }
        hero->cheak_if_hit_sth = false;
    }
    for(auto& en : enemy_vec)
    {
        en->new_hero_pos(hero->getPosition());
        en->see_hero_();
        en->change_dir();
        en->update_status(cl);
        if(en->cheak_if_hit_sth)
        {

            for(auto& point : en->hit_point)
            {
                particle.setPosition(point);
                particle.setRotation(rand()%360);
                particle.setColor(sf::Color(0,0,0));

                cheak_if_hit(*hero, point, en->dmg);

                particle_vec.emplace_back(new std::pair<sf::Sprite,int>(particle,0));
            }
        }


    }
}

void Game::cheak_if_hit(Character &ch, sf::Vector2f point, float dmg)
{
    sf::RectangleShape temp;
    temp.setSize(sf::Vector2f(10,10));
    temp.setOrigin(5,5);
    temp.setPosition(point);
    if(ch.hit_box().getGlobalBounds().intersects(temp.getGlobalBounds()))
    {
        ch.hit_hp(dmg);
        particle.setColor(sf::Color::Red);
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
        if(event.key.code == sf::Keyboard::E)
        {
            if(mapa->elev[0].tp_space.getGlobalBounds().contains(hero->getPosition()) && mapa->elev[0].used == false && enemy_vec.size() == 0)
            {
                mapa->set_new_Map(mapa->elev[0].level);
                for(auto& el : enemy_vec)
                    delete el;
                enemy_vec.clear();
                set_enemy();
            }
            if(mapa->elev[1].tp_space.getGlobalBounds().contains(hero->getPosition()) && mapa->elev[1].used == false && enemy_vec.size() == 0)
            {
                mapa->set_new_Map(mapa->elev[1].level);
                for(auto& el : enemy_vec)
                    delete el;
                enemy_vec.clear();
                set_enemy();
            }
        }
        if(event.key.code == sf::Keyboard::Escape)
            end_game = true;
        if(event.key.code == sf::Keyboard::Space)
        {

        }
    }
}

void Game::Draw()
{
    window->clear(sf::Color(25,25,25));
    for(auto& el : particle_vec)
        window->draw(el->first);

    for(auto& el : enemy_vec)
        window->draw(*el);

    for(auto& el : Maska->Vec_mask())
        window->draw(el);

    for(auto& el : hud_info)
        window->draw(el);

//        mapa->test_Draw(*window); //debug
    window->draw(*hero);
    window->display();
}

void Game::anime_particle(sf::Time cl)
{
    frame_time += cl;
    for(par_it = particle_vec.begin(); par_it < particle_vec.end();)
    {
        if(frame_time.asSeconds() > 0.040)
        {

            if((*par_it)->second < 5)
            {
                (*par_it)->first.setTextureRect(sf::IntRect(48*(*par_it)->second,0,48,48));
                (*par_it)->second++;
            }
            else
            {
                delete *par_it;
                par_it = particle_vec.erase(par_it);
            }
        }
        par_it++;
    }
    if(frame_time.asSeconds()> 0.060)
        frame_time = sf::Time::Zero;
}

void Game::hud()
{
    hud_info[0].setString("Enemy left : " + std::to_string(enemy_vec.size()));
    hud_info[0].setPosition(View_rec.getGlobalBounds().left,View_rec.getGlobalBounds().top);

    hud_info[1].setString("Ammo : " + hero->info_to_hud("ammo"));
    hud_info[1].setPosition(View_rec.getGlobalBounds().left + View_rec.getGlobalBounds().width - 150,
                            View_rec.getGlobalBounds().top+View_rec.getGlobalBounds().height - 80);

    hud_info[2].setString("HP : " + hero->info_to_hud("hp"));
    hud_info[2].setPosition(View_rec.getGlobalBounds().left + View_rec.getGlobalBounds().width - 150,
                            View_rec.getGlobalBounds().top+View_rec.getGlobalBounds().height - 40);
}
