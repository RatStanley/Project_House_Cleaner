#include "shotgun.h"
#include <math.h>

ShotGun::ShotGun()
{
    DMG = 25;
    angle = 0;
    rays_count = 5;
    max_ammo = 7;
    ammo = max_ammo;
    shot_delay = 20;
    idle = sf::Vector2i(0,32);

    for(size_t i = 0; i < 6; i++)
    {
        Reload_animation_pos.emplace_back(48*i,224); // do zmiany
    }


    shot_animation_pos.emplace_back(0,320);
    shot_animation_pos.emplace_back(48,320);
    shot_animation_pos.emplace_back(96,320);

    muzzle_flash_pos.emplace_back(144,320);
    muzzle_flash_pos.emplace_back(192,320);
    muzzle_flash_pos.emplace_back(240,320);


    Change_Animation_pos.emplace_back(0,128);
    Change_Animation_pos.emplace_back(48,128);

    barrel_one_offset_x = 15;
    barrel_two_offset_x = 62;
    barrel_offset_y = 19;

    if (!shot_Buf.loadFromFile("../sounds/shotgun-mossberg.wav"))
            std::cout << "problem";
    shot_sound.setBuffer(shot_Buf);
}

void ShotGun::Reload_Animation()
{
    if(animation_time.asSeconds() > 0.110)
    {
        if(current_frame >= Reload_animation_pos.size() && ammo == max_ammo)
        {
            current_Frame = idle;
            anim_type = Animation_type::idle;
            current_frame = 0;
        }
        else if(current_frame == 4 && ammo != max_ammo)
        {
            current_Frame = Reload_animation_pos[current_frame];
            ammo++;
            if(ammo != max_ammo)
                current_frame = 2;
            std::cout <<ammo << std::endl;
        }
        else
        {
            current_Frame = Reload_animation_pos[current_frame];
            current_frame++;
        }
        animation_time = sf::Time::Zero;
    }
}
std::vector<sf::Vector2f> ShotGun::hits(std::vector<sf::RectangleShape> walls, sf::Vector2f pos, float rotation)
{
    float angle = (rotation) * (M_PI/180);

    std::vector<sf::Vector2f> return_vec;


    barrel_point_one.x = pos.x - barrel_one_offset_x;
    barrel_point_one.y = pos.y - barrel_offset_y;

    barrel_point_two.x = pos.x - barrel_two_offset_x;
    barrel_point_two.y = pos.y - barrel_offset_y;

    for(float i = -10; i <= 10; i+=5)
    {
        std::vector<sf::Vector2f> temp;
        float temp_angle = angle + (i*(M_PI/180));


        float x4 = cos(angle)*(barrel_point_one.x - pos.x)-sin(temp_angle)*(barrel_point_one.y-pos.y) + pos.x;
        float y4 = sin(angle)*(barrel_point_one.x - pos.x)+cos(temp_angle)*(barrel_point_one.y - pos.y) + pos.y;
        float x3 = cos(temp_angle)*(barrel_point_two.x - pos.x)-sin(temp_angle)*(barrel_point_two.y-pos.y) + pos.x; ;
        float y3 = sin(temp_angle)*(barrel_point_two.x - pos.x)+cos(temp_angle)*(barrel_point_two.y - pos.y) + pos.y;

        for(auto& wall : walls)
        {
            std::pair<sf::Vector2f, sf::Vector2f> wall_[4];
            wall_[0] = {
                sf::Vector2f(wall.getGlobalBounds().left,wall.getGlobalBounds().top),                             //lt
                sf::Vector2f(wall.getGlobalBounds().left+wall.getGlobalBounds().width,wall.getGlobalBounds().top)  //pt
            };
            wall_[1] = {
                sf::Vector2f(wall.getGlobalBounds().left+wall.getGlobalBounds().width,wall.getGlobalBounds().top),  //pt
                sf::Vector2f(wall.getGlobalBounds().left+wall.getGlobalBounds().width,wall.getGlobalBounds().top + wall.getGlobalBounds().height)//pd
            };
            wall_[2] = {
                sf::Vector2f(wall.getGlobalBounds().left+wall.getGlobalBounds().width,wall.getGlobalBounds().top + wall.getGlobalBounds().height),//pd
                sf::Vector2f(wall.getGlobalBounds().left,wall.getGlobalBounds().top + wall.getGlobalBounds().height)//ld
            };
            wall_[3] = {
                sf::Vector2f(wall.getGlobalBounds().left,wall.getGlobalBounds().top),
                sf::Vector2f(wall.getGlobalBounds().left,wall.getGlobalBounds().top + wall.getGlobalBounds().height)
            };
            for(auto& one : wall_)
            {
                float x1 = one.first.x;
                float y1 = one.first.y;
                float x2 = one.second.x;
                float y2 = one.second.y;

                sf::Vector2f temp_val = hit_place(x1,y1,x2,y2,x3,y3,x4,y4);
                if(temp_val != sf::Vector2f(0,0))
                    temp.emplace_back(temp_val);
            }
        }
        if(temp.size() > 0)
            std::sort(temp.begin(), temp.end(), [x4, y4](sf::Vector2f one, sf::Vector2f two) {return pow(x4-one.x,2) + pow(y4-one.y,2) < pow(x4-two.x,2) + pow(y4-two.y,2);});
        if(temp.size() == 0)
            temp.emplace_back(sf::Vector2f(0,0));

        return_vec.emplace_back(temp[0]);
    }
    hit_show = false;

    return return_vec;
}
