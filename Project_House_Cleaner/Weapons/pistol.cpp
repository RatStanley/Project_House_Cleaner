#include "pistol.h"
#include <math.h>

Pistol::Pistol()
{
    DMG = 25;
    max_ammo = 7;
    ammo = max_ammo;
    shot_delay = 10;
    idle = sf::Vector2i(0,0);

    Reload_animation_pos.emplace_back(0,192);
    Reload_animation_pos.emplace_back(48,192);
    Reload_animation_pos.emplace_back(96,192);
    Reload_animation_pos.emplace_back(144,192);
    Reload_animation_pos.emplace_back(192,192);



    shot_animation_pos.emplace_back(0,288);
    shot_animation_pos.emplace_back(48,288);
    shot_animation_pos.emplace_back(96,288);

    muzzle_flash_pos.emplace_back(144,288);
    muzzle_flash_pos.emplace_back(192,288);
    muzzle_flash_pos.emplace_back(240,288);

    Change_Animation_pos.emplace_back(0,96);
    Change_Animation_pos.emplace_back(48,96);

    barrel_one_offset_x = 35;
    barrel_two_offset_x = 65;
    barrel_offset_y = 21;


    if (!shot_Buf.loadFromFile("../Resources/sounds/GUN_FIRE.wav")) // barreta_m9 , 9_mm_gunshot, GUN_FIRE
            std::cout << "Pistol sound error";
    shot_sound.setBuffer(shot_Buf);
}

std::vector<sf::Vector2f> Pistol::hits(std::vector<sf::RectangleShape> walls, sf::Vector2f pos, float rotation)
{
        float angle = (rotation) * (M_PI/180);

        std::vector<sf::Vector2f> temp;
        std::vector<sf::Vector2f> return_vec;


        barrel_point_one.x = pos.x - barrel_one_offset_x;
        barrel_point_one.y = pos.y - barrel_offset_y;

        barrel_point_two.x = pos.x - barrel_two_offset_x;
        barrel_point_two.y = pos.y - barrel_offset_y;

        float x4 = cos(angle)*(barrel_point_one.x - pos.x)-sin(angle)*(barrel_point_one.y-pos.y) + pos.x;
        float y4 = sin(angle)*(barrel_point_one.x - pos.x)+cos(angle)*(barrel_point_one.y - pos.y) + pos.y;
        float x3 = cos(angle)*(barrel_point_two.x - pos.x)-sin(angle)*(barrel_point_two.y-pos.y) + pos.x; ;
        float y3 = sin(angle)*(barrel_point_two.x - pos.x)+cos(angle)*(barrel_point_two.y - pos.y) + pos.y;

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
        hit_show = false;

        return return_vec;
}
