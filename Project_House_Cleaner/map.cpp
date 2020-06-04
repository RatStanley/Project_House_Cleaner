#include "map.h"
#include <string>
void Map::Struct_wall(const sf::RectangleShape &bryla, int id)
{
    Wall Temp;
    if(id == 0 || id == 1) // deklaracja ramek
    {
        window_frame[id].rect = bryla;

        window_frame[id].wall[0] = {
            sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top),                             //lt
            sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top)  //pt
        };
        window_frame[id].wall[1] = {
            sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top),  //pt
            sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height)//pd
        };
        window_frame[id].wall[2] = {
            sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height),//pd
            sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height)//ld
        };
        window_frame[id].wall[3] = {
            sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top),
            sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height)

        };

        window_frame[id].points[0] = sf::Vector2f(bryla.getGlobalBounds().left, bryla.getGlobalBounds().top);
        window_frame[id].points[1] = sf::Vector2f(bryla.getGlobalBounds().left + bryla.getGlobalBounds().width, bryla.getGlobalBounds().top);
        window_frame[id].points[2] = sf::Vector2f(bryla.getGlobalBounds().left + bryla.getGlobalBounds().width, bryla.getGlobalBounds().top + bryla.getGlobalBounds().height);
        window_frame[id].points[3] = sf::Vector2f(bryla.getGlobalBounds().left, bryla.getGlobalBounds().top + bryla.getGlobalBounds().height);
    }
    else if(id == 2)
    {
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
        Walls.emplace_back(Temp);
    }
    else if(id == 3 || id == 4 || id == 5)
    {
        door[id-3].rect = bryla;

        door[id-3].wall[0] = {
            sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top),                             //lt
            sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top)  //pt
        };
        door[id-3].wall[1] = {
            sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top),  //pt
            sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height)//pd
        };
        door[id-3].wall[2] = {
            sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height),//pd
            sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height)//ld
        };
        door[id-3].wall[3] = {
            sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top),
            sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height)

        };

        door[id-3].points[0] = sf::Vector2f(bryla.getGlobalBounds().left, bryla.getGlobalBounds().top);
        door[id-3].points[1] = sf::Vector2f(bryla.getGlobalBounds().left + bryla.getGlobalBounds().width, bryla.getGlobalBounds().top);
        door[id-3].points[2] = sf::Vector2f(bryla.getGlobalBounds().left + bryla.getGlobalBounds().width, bryla.getGlobalBounds().top + bryla.getGlobalBounds().height);
        door[id-3].points[3] = sf::Vector2f(bryla.getGlobalBounds().left, bryla.getGlobalBounds().top + bryla.getGlobalBounds().height);
    }


}

void Map::convert_bitMap_to_grid(const char* file) // funcka zczytuje grid z bitmapy
{
    map_grid.clear();
    std::vector<Conversion> conversions = { {{0, 0, 0},"1"}, // ściana
    {{255, 255, 255}, "0" },//puste pole
    {{255,0,0},"2"},//pozycja startowa
    {{0,255,0},"3"},
    {{0,0,255},"4"},
    };

    BMP bmp(file);
    std::vector<std::vector<RGB>> image = bmp.foo();
    for (int y = image[0].size()-1; y>=0; y--)
    {
        std::vector<int> temp;
        for (int x = 0; x < image.size(); x++)
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
    map_borders.setSize(sf::Vector2f(map_grid[0].size()+100*pix_size,map_grid.size()+100*pix_size));
    map_borders.setPosition(map_borders.getSize().x/2,map_borders.getSize().y/2);
    map_borders.setOrigin(map_borders.getSize().x/2,map_borders.getSize().y/2);

    Struct_wall(map_borders,0);

    sf::RectangleShape map_frame;
    map_frame.setSize(map_borders.getSize());
    map_frame.setOrigin(map_frame.getSize().x/2,map_frame.getSize().y/2);
    map_frame.setPosition(map_borders.getPosition());
    map_frame.setScale(1.01,1.02);

    Struct_wall(map_frame,1);

    for(size_t i = 0; i < map_grid.size(); i++)
    {
        for(size_t j = 0; j <map_grid[i].size(); j++)
        {
            if(map_grid[i][j] == 1)
            {
                temp_wall.setSize(wall_length(i,j));
                temp_wall.setPosition((j* pix_size)+100,(i* pix_size)+100);
                Struct_wall(temp_wall,2);
            }
            if(map_grid[i][j] == 2)
            {
                elevator.setSize(sf::Vector2f(pix_size*2,pix_size*2));
                elevator.setPosition((j* pix_size)+100,(i* pix_size)+100);
                map_grid[i][j] = 0;
                map_grid[i+1][j] = 0;
                map_grid[i][j+1] = 0;
                map_grid[i+1][j+1] = 0;
            }
            if(map_grid[i][j] == 3)
            {
                elevator_dor(i,j);
            }
        }
    }
    for(size_t i = 0; i < map_grid.size(); i++)
    {
        for(size_t j = 0; j <map_grid[i].size(); j++)
        {
            if(map_grid[i][j] == 0)
                std::cout <<" ";
            else
                std::cout << map_grid[i][j];
        }
        std::cout << std::endl;
    }
}

void Map::elevator_dor(size_t i,size_t j)
{
    sf::RectangleShape temp_wall;
    temp_wall.setFillColor(sf::Color::Red);

    if(map_grid[i][j] == 3 && map_grid[i][j+1] == 3)
    {
        temp_wall.setSize(sf::Vector2f(pix_size+10,pix_size/2));
        temp_wall.setPosition((j* pix_size)+90,(i* pix_size)+100+20);
        Struct_wall(temp_wall,3);

        temp_wall.setSize(sf::Vector2f(pix_size+10,pix_size/2));
        temp_wall.setPosition(((j+1)* pix_size)+100,(i* pix_size)+100+20);
        Struct_wall(temp_wall,4);

        temp_wall.setSize(sf::Vector2f(pix_size*4,pix_size*4));
        temp_wall.setPosition(((j-1)* pix_size)+100,((i-4)* pix_size)+100+20);
        Struct_wall(temp_wall,5);

        map_grid[i][j] = 0;
        map_grid[i][j+1] = 0;

    }
    else if(map_grid[i][j] == 3 && map_grid[i+1][j] == 3)
    {
        temp_wall.setSize(sf::Vector2f(pix_size/2,pix_size+10));
        temp_wall.setPosition((j* pix_size)+100+20,(i* pix_size)+90);
        Struct_wall(temp_wall,3);

        temp_wall.setSize(sf::Vector2f(pix_size/2,pix_size+10));
        temp_wall.setPosition((j* pix_size)+100+20,((i+1)* pix_size)+100);
        Struct_wall(temp_wall,4);

        temp_wall.setSize(sf::Vector2f(pix_size*4,pix_size*4));
        temp_wall.setPosition(((j-4)* pix_size)+100+60,((i-1)* pix_size)+100);
        Struct_wall(temp_wall,5);

        map_grid[i+1][j] = 0;
        map_grid[i][j] = 0;
    }
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

    sf::RectangleShape box;
    box.setSize(sf::Vector2f(10,10));
    box.setOrigin(5,5);
    //intersection_point.clear();
    for(size_t i = 0; i < 2; i++)
    {
        for(size_t j = 0; j < Walls.size(); j++)
        {
            if(door[i].rect.getGlobalBounds().intersects(Walls[j].rect.getGlobalBounds()))
            {
                for(auto& wall_one : door[i].wall)
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
    map_grid[i][j] = 5;
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
                map_grid[i+1][j] = 7;
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

    Struct_wall(map_borders,0);

    sf::RectangleShape map_frame;
    map_frame.setSize(map_borders.getSize());
    map_frame.setOrigin(map_frame.getSize().x/2,map_frame.getSize().y/2);
    map_frame.setPosition(map_borders.getPosition());
    map_frame.setScale(1.01,1.02);

    Struct_wall(map_frame,1);

    sf::RectangleShape sth;
    sth.setSize(sf::Vector2f(25,500));
    sth.setPosition(700,150);
    sth.setFillColor(sf::Color(100,100,100));
    Struct_wall(sth,2);

    sf::RectangleShape sec;
    sec.setSize(sf::Vector2f(5000,25));
    sec.setPosition(10,900);
    sec.setFillColor(sf::Color(100,100,100));
    Struct_wall(sec,2);

    sf::RectangleShape new_;
    new_.setSize(sf::Vector2f(500,25));
    new_.setPosition(600,600);
    new_.setFillColor(sf::Color(100,100,100));
    Struct_wall(new_,2);

    sf::RectangleShape new_2;
    new_2.setSize(sf::Vector2f(500,25));
    new_2.setPosition(100,300);
    new_2.setFillColor(sf::Color(100,100,100));
    Struct_wall(new_2,2);

    sf::RectangleShape new_3;
    new_3.setSize(sf::Vector2f(500,25));
    new_3.setPosition(725,200);
    new_3.setFillColor(sf::Color(100,100,100));
//    new_3.setFillColor(sf::Color::Blue);

    Struct_wall(new_3,2);


    cheak_for_intersect();

}

Map::Map(const char *file)
{
    convert_bitMap_to_grid(file);
    grid_to_walls();
    cheak_for_intersect();
    cheak_for_door_intersect();
}

void Map::set_curent_visible(sf::RectangleShape view)
{
    point_on_screen.clear();
    walls_on_screen.clear();

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
    for(size_t i = 0; i < 2; i++)
    {
        point_on_screen.emplace_back(door[i].points[0]);
        point_on_screen.emplace_back(door[i].points[1]);
        point_on_screen.emplace_back(door[i].points[2]);
        point_on_screen.emplace_back(door[i].points[3]);
        walls_on_screen.emplace_back(door[i].wall[0]);
        walls_on_screen.emplace_back(door[i].wall[1]);
        walls_on_screen.emplace_back(door[i].wall[2]);
        walls_on_screen.emplace_back(door[i].wall[3]);
    }
    for(auto& el : Walls)
    {
        if(view.getGlobalBounds().intersects(el.rect.getGlobalBounds()))
        {
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


    for(auto& el : Walls)
        win.draw(el.rect);

    sf::RectangleShape test;
    test.setSize(sf::Vector2f(10,10));
    test.setFillColor(sf::Color::Red);
    test.setOrigin(5,5);
    for(auto& el : intersection_point)
    {
        test.setPosition(el);
        win.draw(test);
    }
//    win.draw(door[0].rect);
//    win.draw(door[1].rect);
}

void Map::door_move(sf::Vector2f pos, sf::Time cl)
{
    if(door[2].rect.getGlobalBounds().contains(pos))
    {
        if(door_open_ > 1.5)
        {
            if(door[0].points[0].x == door[1].points[0].x)
            {
                door[0].rect.move(0,-80*cl.asSeconds());
                door[1].rect.move(0,80*cl.asSeconds());
            }
            else if(door[0].points[0].y == door[1].points[0].y)
            {
                door[0].rect.move(-80*cl.asSeconds(),0);
                door[1].rect.move(80*cl.asSeconds(),0);
            }
            door_open_ = door_open_ - cl.asSeconds();
            Struct_wall(door[0].rect,3);
            Struct_wall(door[1].rect,4);
        }
    }
    else
    {
        if(door_open_ < 2)
        {
            if(door[0].points[0].x == door[1].points[0].x)
            {
                door[0].rect.move(0,80*cl.asSeconds());
                door[1].rect.move(0,-80*cl.asSeconds());


            }
            else if(door[0].points[0].y == door[1].points[0].y)
            {
                door[0].rect.move(80*cl.asSeconds(),0);
                door[1].rect.move(-80*cl.asSeconds(),0);
            }
            door_open_ +=cl.asSeconds();
            Struct_wall(door[0].rect,3);
            Struct_wall(door[1].rect,4);
        }
    }
}
