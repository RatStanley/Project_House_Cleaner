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
            if(map_grid[i][j] == 3)
            {
                if(map_grid[i][j+1] == 3 || map_grid[i][j-1] == 3)
                {
                    temp_wall.setSize(sf::Vector2f(pix_size,pix_size/2));
                    temp_wall.setPosition((j* pix_size)+100,(i* pix_size)+100+20);
                }
                else if(map_grid[i+1][j] == 3 || map_grid[i-1][j] == 3)
                {
                    temp_wall.setSize(sf::Vector2f(pix_size/2,pix_size));
                    temp_wall.setPosition((j* pix_size)+100+20,(i* pix_size)+100);
                }
                Struct_wall(temp_wall,2);
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
    sth.setPosition(700,100);
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
    Struct_wall(new_3,2);

}

Map::Map(const char *file)
{
    convert_bitMap_to_grid(file);
    grid_to_walls();
}

void Map::set_curent_visible(sf::RectangleShape view)
{
    point_on_screen.clear();
    walls_on_screen.clear();

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
