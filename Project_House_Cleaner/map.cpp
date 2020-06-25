#include "map.h"
#include <string>
//#include <bits/stdc++.h>

Wall Map::Struct_walls(const sf::RectangleShape &bryla)
{
    Wall Temp;
    Temp.rect = bryla;

    Temp.wall[0] = {
        sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top),                             //lt
        sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top)  //pt
    };
    Temp.wall[1] = {
        sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top),  //pt
        sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height)//pd
    };
    Temp.wall[2] = {
        sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height),//pd
        sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height)//ld
    };
    Temp.wall[3] = {
        sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top),
        sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height)

    };

    Temp.points[0] = sf::Vector2f(bryla.getGlobalBounds().left, bryla.getGlobalBounds().top);
    Temp.points[1] = sf::Vector2f(bryla.getGlobalBounds().left + bryla.getGlobalBounds().width, bryla.getGlobalBounds().top);
    Temp.points[2] = sf::Vector2f(bryla.getGlobalBounds().left + bryla.getGlobalBounds().width, bryla.getGlobalBounds().top + bryla.getGlobalBounds().height);
    Temp.points[3] = sf::Vector2f(bryla.getGlobalBounds().left, bryla.getGlobalBounds().top + bryla.getGlobalBounds().height);
    return Temp;
}

void Map::convert_bitMap_to_grid(const char* file)
{
    map_grid.clear();
    std::vector<Conversion> conversions = { {{0, 0, 0},"1"}, // ściana
                                            {{255, 255, 255}, "0" },//puste pole
                                            {{255,0,0},"2"},//aktywny tp
                                            {{0,255,0},"3"},//drzwi od windy
                                            {{0,0,255},"4"},//zurzyty tp
                                            {{255,0,255},"5"},
                                            {{255,255,0},"6"},
                                          };

    BMP bmp(file);
    std::vector<std::vector<RGB>> image = bmp.bmp_to_grid();

    for (int y = image[0].size()-1; y>=0; y--)
    {
        std::vector<int> temp;
        for (size_t x = 0; x < image.size(); x++)
        {
            for (auto& conversion : conversions)
            {
                if (image[x][y].R == conversion.from.R && image[x][y].G == conversion.from.G && image[x][y].B == conversion.from.B)
                {
                    temp.emplace_back(stoi(conversion.to));
                }
            }
        }
        map_grid.emplace_back(temp);
    }

}

void Map::grid_to_walls()
{
    sf::RectangleShape temp_wall;

    sf::RectangleShape map_borders;
    map_borders.setSize(sf::Vector2f(map_grid[0].size()*pix_size+1000,map_grid.size()*pix_size+1000));
//    std::cout << map_grid[0].size() << "\t" << map_grid.size() << std::endl;
    map_borders.setPosition(map_borders.getSize().x/2,map_borders.getSize().y/2);
    map_borders.setOrigin(map_borders.getSize().x/2,map_borders.getSize().y/2);

    //Struct_wall(map_borders,0);
    window_frame[0] = Struct_walls(map_borders);

    sf::RectangleShape map_frame;
    map_frame.setSize(map_borders.getSize());
    map_frame.setOrigin(map_frame.getSize().x/2,map_frame.getSize().y/2);
    map_frame.setPosition(map_borders.getPosition());
    map_frame.setScale(1.01,1.02);

    //Struct_wall(map_frame,1);
    window_frame[1] = Struct_walls(map_frame);


    for(size_t i = 0; i < map_grid.size(); i++)
    {
        for(size_t j = 0; j <map_grid[i].size(); j++)
        {
            if(map_grid[i][j] == 1)
            {
                temp_wall.setSize(wall_length(i,j));
                temp_wall.setPosition((j* pix_size)+100,(i* pix_size)+100);
                Walls.emplace_back(Struct_walls(temp_wall));
            }
            if(map_grid[i][j] == 3)
            {
                elevator_door(i,j);
            }
            if(map_grid[i][j] == 6)
            {
                enemy_pos.emplace_back(j*pix_size+100,i*pix_size+100);
            }
        }
    }
//    for(size_t i = 0; i < map_grid.size(); i++)
//    {
//        for(size_t j = 0; j <map_grid[i].size(); j++)
//        {
//            if(map_grid[i][j] == 0)
//                std::cout <<"  ";
//            else
//                std::cout << " "<<map_grid[i][j];
//        }
//        std::cout << std::endl;
//    }
}

void Map::elevator_door(size_t i,size_t j)
{
    sf::RectangleShape temp_door_1;
    sf::RectangleShape temp_door_2;
    sf::RectangleShape temp_tp;
    sf::RectangleShape temp_deadzone;
    bool next;
    static int elev_counter = 0;

//    temp_door_1.setFillColor(sf::Color::Red);
//    temp_door_2.setFillColor(sf::Color::Blue);


    if(map_grid[i][j] == 3 && map_grid[i][j+1] == 3)
    {
        temp_door_1.setSize(sf::Vector2f(pix_size+10+pix_size*0.5,pix_size/2));
        temp_door_2.setSize(sf::Vector2f(pix_size+10+pix_size*0.5,pix_size/2));
        temp_door_1.setPosition((j* pix_size)+90,(i* pix_size)+100+15);
        temp_door_2.setPosition(((j+1)* pix_size)+100+pix_size*0.5,(i* pix_size)+100+15);
        
        map_grid[i][j] = 0;
        map_grid[i][j+1] = 0;
        map_grid[i][j+2] = 0;
    }
    else if(map_grid[i][j] == 3 && map_grid[i+1][j] == 3)
    {
        temp_door_1.setSize(sf::Vector2f(pix_size/2,pix_size+10+pix_size*0.5));
        temp_door_2.setSize(sf::Vector2f(pix_size/2,pix_size+10+pix_size*0.5));
        temp_door_1.setPosition((j* pix_size)+100+15,(i* pix_size)+90);
        temp_door_2.setPosition((j* pix_size)+100+15,((i+1)* pix_size)+100+pix_size*0.5);

        map_grid[i][j] = 0;
        map_grid[i+1][j] = 0;
        map_grid[i+2][j] = 0;
    }
    std::tie(temp_tp, temp_deadzone, next) = tp_space_detect(i,j);
    elev[elev_counter%2] = Elevator(temp_door_1,temp_door_2,temp_tp,temp_deadzone,next);
    elev_counter++;
}

std::tuple<sf::RectangleShape, sf::RectangleShape,bool> Map::tp_space_detect(size_t i, size_t j)
{
    sf::RectangleShape temp_tp;
    sf::RectangleShape temp_deadzone;
    bool next = false;
    temp_deadzone.setSize(sf::Vector2f(pix_size*4,pix_size*4));

    if(map_grid[i+1][j] == 2 || map_grid[i+1][j] == 4)
    {
        if(map_grid[i+1][j] == 4)
            next = true;

        temp_tp.setSize(sf::Vector2f(pix_size*3,pix_size*2.5));
        temp_tp.setPosition(j*pix_size+100,(i+1)*pix_size+100+pix_size*0.5);

        temp_deadzone.setSize(sf::Vector2f(pix_size*4,pix_size*4));
        temp_deadzone.setPosition(j*pix_size+100-pix_size*0.5,i*pix_size+100-pix_size*2.5);

        map_grid[i+1][j] = 0;
        map_grid[i+2][j] = 0;
        map_grid[i+3][j] = 0;

        map_grid[i+1][j+1] = 0;
        map_grid[i+2][j+1] = 0;
        map_grid[i+3][j+1] = 0;

        map_grid[i+1][j+2] = 0;
        map_grid[i+2][j+2] = 0;
        map_grid[i+3][j+2] = 0;

    }
    else if(map_grid[i-1][j] == 2 || map_grid[i-1][j] == 4)
    {
        if(map_grid[i-1][j] == 4)
            next = true;

        temp_tp.setSize(sf::Vector2f(pix_size*3,pix_size*2.5));
        temp_tp.setPosition(j*pix_size+100,(i-3)*pix_size+100);

        temp_deadzone.setSize(sf::Vector2f(pix_size*4,pix_size*4));
        temp_deadzone.setPosition(j*pix_size+100-pix_size*0.5,i*pix_size+100-pix_size*0.5);

        map_grid[i-1][j] = 0;
        map_grid[i-2][j] = 0;
        map_grid[i-3][j] = 0;

        map_grid[i-1][j+1] = 0;
        map_grid[i-2][j+1] = 0;
        map_grid[i-3][j+1] = 0;

        map_grid[i-1][j+2] = 0;
        map_grid[i-2][j+2] = 0;
        map_grid[i-3][j+2] = 0;


    }
    else if(map_grid[i][j+1] == 2 || map_grid[i][j+1] == 4)
    {
//        temp_tp.setPosition(((j+1)* pix_size)+100,(i* pix_size)+100);
        if(map_grid[i][j+1] == 4)
            next = true;

        temp_tp.setSize(sf::Vector2f(pix_size*2.5,pix_size*3));
        temp_tp.setPosition((j+1)*pix_size+100+pix_size*0.5,i*pix_size+100);

        temp_deadzone.setSize(sf::Vector2f(pix_size*4,pix_size*4));
        temp_deadzone.setPosition(j*pix_size+100-pix_size*2.5,i*pix_size+100-pix_size*0.5);

        map_grid[i][j+1] = 0;
        map_grid[i][j+2] = 0;
        map_grid[i][j+3] = 0;

        map_grid[i+1][j+1] = 0;
        map_grid[i+1][j+2] = 0;
        map_grid[i+1][j+3] = 0;

        map_grid[i+2][j+1] = 0;
        map_grid[i+2][j+2] = 0;
        map_grid[i+2][j+3] = 0;

    }
    else if(map_grid[i][j-1] == 2 || map_grid[i][j-1] == 4)
    {
        if(map_grid[i][j-1] == 4)
            next = true;

        temp_tp.setSize(sf::Vector2f(pix_size*2.5,pix_size*3));
        temp_tp.setPosition((j-3)*pix_size+100,i*pix_size+100);

        temp_deadzone.setSize(sf::Vector2f(pix_size*4,pix_size*4));
        temp_deadzone.setPosition(j*pix_size+100-pix_size*0.5,i*pix_size+100-pix_size*0.5);

        map_grid[i][j-1] = 0;
        map_grid[i][j-2] = 0;
        map_grid[i][j-3] = 0;

        map_grid[i+1][j-1] = 0;
        map_grid[i+1][j-2] = 0;
        map_grid[i+1][j-3] = 0;

        map_grid[i+2][j-1] = 0;
        map_grid[i+2][j-2] = 0;
        map_grid[i+2][j-3] = 0;

    }
    return {temp_tp,temp_deadzone,next};
}

void Map::cheak_for_intersect()
{
    sf::Vector2f temp;
    std::vector<sf::Vector2f> temp_points;

    sf::RectangleShape box;
    box.setSize(sf::Vector2f(10,10));
    box.setOrigin(5,5);
    intersection_point.clear();
    for(size_t i = 0; i < Walls.size(); i++)
    {
        for(size_t j = i+1; j < Walls.size(); j++)
        {
            if(Walls[i].rect.getGlobalBounds().intersects(Walls[j].rect.getGlobalBounds()))
            {
                for(auto& wall_one : Walls[i].wall)
                {
                    for(auto& wall_two : Walls[j].wall)
                    {
                        temp = intersection(wall_one,wall_two);
                        if(temp != sf::Vector2f(0,0))
                            intersection_point.emplace_back(temp);
                    }
                }

            }
            else
            {
                for(auto& el : Walls[j].points)
                {
                    box.setPosition(el);
                    if(Walls[i].rect.getGlobalBounds().intersects(box.getGlobalBounds()))
                    {
                        for(auto& wall_one : Walls[i].wall)
                        {
                            for(auto& wall_two : Walls[j].wall)
                            {
                                temp = intersection(wall_one,wall_two);
                                if(temp != sf::Vector2f(0,0))
                                    intersection_point.emplace_back(temp);
                            }
                        }
                    }
                }
            }
        }
    }

}

void Map::cheak_for_door_intersect()
{
    sf::Vector2f temp;
    std::vector<sf::Vector2f> temp_points;
    for(auto& el : elev)
    {
        //intersection_point.clear();
        for(size_t i = 0; i < 2; i++)
        {
            for(size_t j = 0; j < Walls.size(); j++)
            {
                if(el.door[i].getGlobalBounds().intersects(Walls[j].rect.getGlobalBounds()))
                {
                    for(auto& wall_one : el.wall)
                    {
                        for(auto& wall_two : Walls[j].wall)
                        {
                            temp = intersection(wall_one,wall_two);
                            if(temp != sf::Vector2f(0,0))
                                intersection_point.emplace_back(temp);
                        }
                    }
                }
            }
        }
    }
}

sf::Vector2f Map::intersection(std::pair<sf::Vector2f, sf::Vector2f> one, std::pair<sf::Vector2f, sf::Vector2f> two)
{
    float x1 = one.first.x;
    float y1 = one.first.y;
    float x2 = one.second.x;
    float y2 = one.second.y;

    float x3 = two.first.x;
    float y3 = two.first.y;
    float x4 = two.second.x;
    float y4 = two.second.y;

    float M_t = (x1-x2)*(y3-y4)-(y1-y2)*(x3-x4);
    float L_t = (x1-x3)*(y3-y4)-(y1-y3)*(x3-x4);
    float l_u = (x1-x2)*(y1-y3)-(y1-y2)*(x1-x3);
    float m_u = (x1-x2)*(y3-y4)-(y1-y2)*(x3-x4);
    if(M_t != 0 && m_u != 0 )
    {
        float t = L_t/M_t;
        float u = -l_u/m_u;
        if(0<=t && t <= 1 && 0<= u && u <= 1)
        {
            return sf::Vector2f(x3+u*(x4-x3),y3 + u*(y4-y3));
        }
    }
    return sf::Vector2f(0,0);
}

sf::Vector2f Map::wall_length(size_t i,size_t j)
{
    int length = 1;
    int width = 1;
    bool l = true, p = true;
    map_grid[i][j] = 9;
    while(true)
    {
        if(map_grid[j].size()-1 != j && map_grid[i][j+1] == 1 && p == true)
        {
            width++;
            map_grid[i][j+1] = 9;
            j++;
            l = false;
        }
        else if(map_grid.size()-1 != i && map_grid[i+1][j] == 1 && l == true)
        {
            length++;
            map_grid[i+1][j] = 9;
            i++;
            p = false;
        }
        else
            break;
    }
    return sf::Vector2f(width * pix_size,length * pix_size);
}



Map::Map()
{

    sf::RectangleShape map_borders;
    map_borders.setSize(sf::Vector2f(12800,7200));
    map_borders.setPosition(map_borders.getSize().x/2,map_borders.getSize().y/2);
    map_borders.setOrigin(map_borders.getSize().x/2,map_borders.getSize().y/2);

    window_frame[0] = Struct_walls(map_borders);

    sf::RectangleShape map_frame;
    map_frame.setSize(map_borders.getSize());
    map_frame.setOrigin(map_frame.getSize().x/2,map_frame.getSize().y/2);
    map_frame.setPosition(map_borders.getPosition());
    map_frame.setScale(1.01,1.02);

    window_frame[1] = Struct_walls(map_frame);

    sf::RectangleShape sth;
    sth.setSize(sf::Vector2f(25,500));
    sth.setPosition(700,150);
    sth.setFillColor(sf::Color(100,100,100));
    Walls.emplace_back(Struct_walls(sth));

    sf::RectangleShape sec;
    sec.setSize(sf::Vector2f(5000,25));
    sec.setPosition(10,900);
    sec.setFillColor(sf::Color(100,100,100));
    Walls.emplace_back(Struct_walls(sec));

    sf::RectangleShape new_;
    new_.setSize(sf::Vector2f(500,25));
    new_.setPosition(600,600);
    new_.setFillColor(sf::Color(100,100,100));
    Walls.emplace_back(Struct_walls(new_));

    sf::RectangleShape new_2;
    new_2.setSize(sf::Vector2f(500,25));
    new_2.setPosition(100,300);
    new_2.setFillColor(sf::Color(100,100,100));
    Walls.emplace_back(Struct_walls(new_2));

    sf::RectangleShape new_3;
    new_3.setSize(sf::Vector2f(500,25));
    new_3.setPosition(725,200);
    new_3.setFillColor(sf::Color(100,100,100));
    //    new_3.setFillColor(sf::Color::Blue);

    Walls.emplace_back(Struct_walls(new_3));


    cheak_for_intersect();

}

Map::Map(const char *file)
{
    convert_bitMap_to_grid(file);
    grid_to_walls();
    end_game = false;

    elev[0].refresh_walls(0);
    elev[0].refresh_walls(1);
    elev[1].refresh_walls(0);
    elev[1].refresh_walls(1);
//    elev->refresh_walls(1);



    cheak_for_intersect();
    cheak_for_door_intersect();
    for(auto& wal: Walls)
        all_wall_cols.emplace_back(wal.rect);

    all_wall_cols.emplace_back(elev->door[0]);
    all_wall_cols.emplace_back(elev->door[1]);

    map_list.emplace_back("../Resources/map_folder/MAP0.bmp");
    map_list.emplace_back("../Resources/map_folder/MAP1.bmp");
    map_list.emplace_back("../Resources/map_folder/MAP2.bmp");
    map_list.emplace_back("../Resources/map_folder/MAP3.bmp");

}

void Map::set_curent_visible(sf::RectangleShape view)
{
    point_on_screen.clear();
    walls_on_screen.clear();
    Wall_cols.clear();

    //    point_on_screen = intersection_point;
    for(auto& el: intersection_point)
    {
        if(view.getGlobalBounds().contains(el))
            point_on_screen.emplace_back(el);
    }

    for(auto& frame : window_frame)
    {
        point_on_screen.emplace_back(frame.points[0]);
        point_on_screen.emplace_back(frame.points[1]);
        point_on_screen.emplace_back(frame.points[2]);
        point_on_screen.emplace_back(frame.points[3]);
        walls_on_screen.emplace_back(frame.wall[0]);
        walls_on_screen.emplace_back(frame.wall[1]);
        walls_on_screen.emplace_back(frame.wall[2]);
        walls_on_screen.emplace_back(frame.wall[3]);
    }
    //    for(size_t i = 0; i < 2; i++)
    //    {
    //        point_on_screen.emplace_back(door[i].points[0]);
    //        point_on_screen.emplace_back(door[i].points[1]);
    //        point_on_screen.emplace_back(door[i].points[2]);
    //        point_on_screen.emplace_back(door[i].points[3]);
    //        walls_on_screen.emplace_back(door[i].wall[0]);
    //        walls_on_screen.emplace_back(door[i].wall[1]);
    //        walls_on_screen.emplace_back(door[i].wall[2]);
    //        walls_on_screen.emplace_back(door[i].wall[3]);
    //    }
    for(auto& ele : elev)
    {
        if(view.getGlobalBounds().intersects(ele.door[0].getGlobalBounds()) || view.getGlobalBounds().intersects(ele.door[1].getGlobalBounds()))
        {
            Wall_cols.emplace_back(ele.door[0]);
            Wall_cols.emplace_back(ele.door[1]);

            for(size_t i = 0; i < 4; i++)
            {
                point_on_screen.emplace_back(ele.points[0][i]);
                point_on_screen.emplace_back(ele.points[1][i]);

            }
            for(auto& wall : ele.wall)
            {
                walls_on_screen.emplace_back(wall);
            }
        }
    }

    for(auto& el : Walls)
    {
        if(view.getGlobalBounds().intersects(el.rect.getGlobalBounds()))
        {
            Wall_cols.emplace_back(el.rect);
            for(size_t i = 0; i < 4; i++)
            {
                point_on_screen.emplace_back(el.points[i]);
                walls_on_screen.emplace_back(el.wall[i]);
            }

        }

    }
}

void Map::test_Draw(sf::RenderWindow &win)
{
//    window_frame[0].rect.setFillColor(sf::Color::Red);

//    win.draw(window_frame[0].rect);

    for(auto& el : Walls)
        win.draw(el.rect);

//    sf::RectangleShape test;
//    test.setSize(sf::Vector2f(10,10));
//    test.setFillColor(sf::Color::Red);
//    test.setOrigin(5,5);
//    for(auto& el : intersection_point)
//    {
//        test.setPosition(el);
//        win.draw(test);
//    }
//        win.draw(elev[0].door[0]);
//        win.draw(elev[0].door[1]);

//        win.draw(elev[1].door[0]);
//        win.draw(elev[1].door[1]);
//    win.draw(elev[0].open_zone);
//    win.draw(elev[1].open_zone);
//    win.draw(elev[0].tp_space);
//    win.draw(elev[1].tp_space);

}

//"../map_folder/door_test2.bmp"
void Map::set_new_Map(int level)
{

    if(level != actual_level && level < map_list.size())
    {
        actual_level = level;
        std::cout << "New Map Level : " << level << std::endl;
        Map *Temp;
        char map[map_list.size()];
        for(size_t i = 0; i< map_list[level].size(); i++)
        {
            map[i] = map_list[level][i];
            std::cout << map_list[level][i];
        }
        Temp = new Map(map);

        Walls = Temp->Walls;
        map_grid = Temp->map_grid;
        intersection_point = Temp->intersection_point;
        window_frame[0] = Temp->window_frame[0];
        window_frame[1] = Temp->window_frame[1];
        elev[0] = Temp->elev[0];
        elev[1] = Temp->elev[1];
        all_wall_cols.clear();

        for(auto& wal: Walls)
            all_wall_cols.emplace_back(wal.rect);
        all_wall_cols.emplace_back(elev->door[0]);
        all_wall_cols.emplace_back(elev->door[1]);
        enemy_pos = Temp->enemy_pos;
        delete Temp;
    }
    else if(level >= map_list.size())
    {
        end_game = true;
    }
}

bool Map::outside_map(sf::Vector2f pos)
{
    if(window_frame[0].rect.getGlobalBounds().contains(pos))
        return false;
    return true;
}

Elevator::Elevator(sf::RectangleShape &door_1,
                   sf::RectangleShape &door_2,
                   sf::RectangleShape &tp_space,
                   sf::RectangleShape &open_zone,
                   bool used)
{
    this->door[0] = door_1;
    this->refresh_walls(0);
    this->door[1] = door_2;
    this->refresh_walls(1);
    this->tp_space = tp_space;
    this->open_zone = open_zone;
    this->used = used;
    static int entry = 0;
    if(used == false)
        entry++;
    this->level = entry;
    
}

void Elevator::refresh_walls(size_t i)
{
    points[i][0] = sf::Vector2f(door[i].getGlobalBounds().left, door[i].getGlobalBounds().top);
    points[i][1] = sf::Vector2f(door[i].getGlobalBounds().left + door[i].getGlobalBounds().width, door[i].getGlobalBounds().top);
    points[i][2] = sf::Vector2f(door[i].getGlobalBounds().left + door[i].getGlobalBounds().width, door[i].getGlobalBounds().top + door[i].getGlobalBounds().height);
    points[i][3] = sf::Vector2f(door[i].getGlobalBounds().left, door[i].getGlobalBounds().top + door[i].getGlobalBounds().height);
    
    int off = 0;

    if(i == 1)
        off = 4;
    
    wall[off] = {
        sf::Vector2f(door[i].getGlobalBounds().left,door[i].getGlobalBounds().top),                             //lt
        sf::Vector2f(door[i].getGlobalBounds().left+door[i].getGlobalBounds().width,door[i].getGlobalBounds().top)  //pt
    };
    wall[off+1] = {
        sf::Vector2f(door[i].getGlobalBounds().left+door[i].getGlobalBounds().width,door[i].getGlobalBounds().top),  //pt
        sf::Vector2f(door[i].getGlobalBounds().left+door[i].getGlobalBounds().width,door[i].getGlobalBounds().top + door[i].getGlobalBounds().height)//pd
    };
    wall[off+2] = {
        sf::Vector2f(door[i].getGlobalBounds().left+door[i].getGlobalBounds().width,door[i].getGlobalBounds().top + door[i].getGlobalBounds().height),//pd
        sf::Vector2f(door[i].getGlobalBounds().left,door[i].getGlobalBounds().top + door[i].getGlobalBounds().height)//ld
    };
    wall[off+3] = {
        sf::Vector2f(door[i].getGlobalBounds().left,door[i].getGlobalBounds().top),
        sf::Vector2f(door[i].getGlobalBounds().left,door[i].getGlobalBounds().top + door[i].getGlobalBounds().height)

    };
}

//std::pair<sf::RectangleShape, sf::RectangleShape>
void Elevator::door_move(sf::Vector2f pos, sf::Time cl)
{
    if(open_zone.getGlobalBounds().contains(pos))
    {
        if(door_gape > 1.7)
        {
            if(points[0][0].x == points[1][0].x)
            {
                door[0].move(0,-80*cl.asSeconds());
                door[1].move(0,80*cl.asSeconds());
            }
            else if(points[0][0].y == points[1][0].y)
            {
                door[0].move(-80*cl.asSeconds(),0);
                door[1].move(80*cl.asSeconds(),0);
            }
            door_gape = door_gape - cl.asSeconds();
            refresh_walls(0);
            refresh_walls(1);
        }
    }
    else
    {
        if(used == false)
        {
            if(door_gape < 2.5)
            {
                if(points[0][0].x == points[1][0].x)
                {
                    door[0].move(0,80*cl.asSeconds());
                    door[1].move(0,-80*cl.asSeconds());


                }
                else if(points[0][0].y == points[1][0].y)
                {
                    door[0].move(80*cl.asSeconds(),0);
                    door[1].move(-80*cl.asSeconds(),0);
                }
                door_gape +=cl.asSeconds();

                refresh_walls(0);
                refresh_walls(1);
            }
        }
    }
//    return {door[0],door[1]};
}

