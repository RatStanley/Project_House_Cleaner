#include "temp.h"
#include <math.h>

std::vector<sf::RectangleShape> box(std::vector<std::vector<sf::Vector2f>> punkty)
{
    sf::RectangleShape shape;
    shape.setFillColor(sf::Color(255,255,255));
    shape.setSize(sf::Vector2f(5,5));
    shape.setOrigin(2.5,2.5);

    std::vector<sf::RectangleShape> boxy;

    int tr = 0;

    for(auto& el : punkty)
    {
        for(auto& vec : el)
        {
        shape.setPosition(vec);
        boxy.emplace_back(shape);
        shape.setSize(sf::Vector2f(5+tr,5+tr));
        }
//        shape.setOrigin(5+tr/2,5+tr/2);
//        tr+=1;
    }
    //std::cout << punkty.size() << std::endl;
    return boxy;
}

std::vector<std::pair<sf::Vector2f, sf::Vector2f>> rect(sf::RectangleShape bryla)
{
    std::pair<sf::Vector2f, sf::Vector2f> linia;
    std::vector<std::pair<sf::Vector2f, sf::Vector2f>> all_lines;

    linia = {
        sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top),                             //lt
        sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top)  //pt
    };
    all_lines.emplace_back(linia);
    linia = {
        sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top),  //pt
        sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height)//pd
    };
    all_lines.emplace_back(linia);
    linia = {
        sf::Vector2f(bryla.getGlobalBounds().left+bryla.getGlobalBounds().width,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height),//pd
        sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height)//ld
    };
    all_lines.emplace_back(linia);
    linia = {
        sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top),
        sf::Vector2f(bryla.getGlobalBounds().left,bryla.getGlobalBounds().top + bryla.getGlobalBounds().height)

    };
    all_lines.emplace_back(linia);

    return all_lines;
}

std::vector<std::vector<sf::Vector2f>> intersection_point(std::vector<std::pair<sf::Vector2f, sf::Vector2f>> all_lines, std::vector<sf::Vector2f> points_enti, sf::Vector2f mysz)
{
    float x4 = mysz.x;
    float y4 = mysz.y;

    std::vector<sf::Vector2f> points;
    std::vector<std::vector<sf::Vector2f>> vector_of_lines;
    for(auto& el : points_enti)
    {
        float x3 = el.x;
        float y3 = el.y;

        std::vector<sf::Vector2f> temp;
        //bool edge = false;

        for(auto& wall : all_lines) // wektor z daną prostą
        {
            float x2 = wall.first.x;
            float y2 = wall.first.y;
            float x1 = wall.second.x;
            float y1 = wall.second.y;
            float M_t = (x1-x2)*(y3-y4)-(y1-y2)*(x3-x4);
            float L_t = (x1-x3)*(y3-y4)-(y1-y3)*(x3-x4);

            float m_u = (x1-x2)*(y3-y4)-(y1-y2)*(x3-x4);
            if(M_t != 0 && m_u != 0 )
            {
                float t = L_t/M_t;
                //float u = l_u/m_u;
                if(0<=t && t <= 1 )
                {
                    sf::Vector2f cord(x1+t*(x2-x1),y1+t*(y2-y1));
                    sf::Vector2f rogi_offset(x3-x4,y3-y4);
                    sf::Vector2f cord_offset(cord.x-x4,cord.y-y4);
                    float iloczyn = rogi_offset.x*cord_offset.x+rogi_offset.y*cord_offset.y;
                    if(iloczyn > 0)
                    {
                        bool already_is = false;
                        for(auto& el : points)
                        {
                            if(el == cord)
                                already_is = true;
                        }
                        for(auto& el : temp) //wyłącza przecięcia na rogach
                        {
                            if(el == cord)
                                already_is = true;
                        }
                        if(already_is)
                            continue;
                        temp.emplace_back(cord);
                    }
                }
            }
        }

        if(temp.size() > 1)
        {
            std::sort(temp.begin(), temp.end(), [x4, y4](sf::Vector2f one, sf::Vector2f two) {return pow(x4-one.x,2) + pow(y4-one.y,2) < pow(x4-two.x,2) + pow(y4-two.y,2);});

            for(auto& poin : points_enti)
            {
                //if((temp[0].x == poin.x && temp[0].y == poin.y) || (temp[temp.size()-1].x == poin.x && temp[temp.size()-1].y == poin.y))
                //{
                    vector_of_lines.emplace_back(temp);
                    break;
                //}
            }
        }
        for(auto& el : temp)
            points.emplace_back(el);



    }
    //std::cout << vector_of_lines.size() << std::endl;
    return vector_of_lines;
}

std::vector<sf::Vector2f> points_to_cheak(sf::RectangleShape bryla)
{
    std::vector<sf::Vector2f> temp;
    temp.emplace_back(bryla.getGlobalBounds().left, bryla.getGlobalBounds().top);
    temp.emplace_back(bryla.getGlobalBounds().left + bryla.getGlobalBounds().width, bryla.getGlobalBounds().top);
    temp.emplace_back(bryla.getGlobalBounds().left + bryla.getGlobalBounds().width, bryla.getGlobalBounds().top + bryla.getGlobalBounds().height);
    temp.emplace_back(bryla.getGlobalBounds().left, bryla.getGlobalBounds().top + bryla.getGlobalBounds().height);
    return temp;
}

std::vector<std::vector<sf::Vector2f>> sort(std::vector<std::vector<sf::Vector2f>> points_vect, sf::Vector2f mysz)//mysz -> srodek układu
{
    //sf::Vector2f ekran(1280,720); //do przekazania to będze
    ///   2 \  3
    /// ---------
    ///   1 \  4
    ///

    std::vector<std::vector<sf::Vector2f>> sorted;
    std::vector<double> vec_of_angle;
    double angle;
    for(auto& el : points_vect)
    {
        if(el[0].x < mysz.x && el[0].y >= mysz.y)
        {
            angle = 90-atan2(el[0].y - mysz.y,  mysz.x - el[0].x)* 180 / M_PI;// - 180;
        }
        else if(el[0].x <= mysz.x && el[0].y < mysz.y)
        {
            angle = atan2(mysz.y - el[0].y, mysz.x - el[0].x)* 180 / M_PI +90;//  - 180;
        }
        else if(el[0].x > mysz.x && el[0].y <= mysz.y)
        {
            angle =90- atan2(mysz.y - el[0].y,el[0].x - mysz.x)* 180 / M_PI +180;
        }
        else if(el[0].x >= mysz.x && el[0].y > mysz.y)
        {
            angle = atan2(el[0].y - mysz.y,el[0].x - mysz.x)* 180 / M_PI +270;
        }

        vec_of_angle.emplace_back(angle);
        sorted.emplace_back(el);
        if(vec_of_angle.size() != 1)
        {
            for (size_t i = 0; i < vec_of_angle.size() - 1; i++)
            {
                for (size_t j = 0; j < vec_of_angle.size()-i-1; j++)
                {
                    if (vec_of_angle[j] > vec_of_angle[j+1])
                    {
                        std::swap(sorted[j], sorted[j+1]);
                        std::swap(vec_of_angle[j],vec_of_angle[j+1]);
                    }
                }
            }
        }
    }

    return sorted;
}

std::vector<sf::ConvexShape> vector_v2_mask(std::vector<std::vector<sf::Vector2f>> points, std::vector<sf::Vector2f> vert)
{
    sf::ConvexShape maska;
    //maska.setFillColor(sf::Color::Black);
    maska.setFillColor(sf::Color(50,50,50));

    std::vector<sf::ConvexShape> vec;
    points.emplace_back(points[0]); // by brało pod uwagę pierwszy punkt

//std::cout << points.size()-1 << std::endl;

    for(size_t i = 1; i < points.size(); i++)
    {
        bool previous = false, present = false, next = false, present_next = false;
        maska.setFillColor(sf::Color(50,50,50));
        size_t idx_first = 0;
        size_t idx_sec = 0;


                size_t off=1;
                size_t off_2=1;
        if(i != points.size()-1)
        {
            for(auto& ver : vert)
            {
                if(points[i][0].x == ver.x && points[i][0].y == ver.y)
                    present = true;
                if(points[i-1][0] == ver)
                    previous = true;
                if(points[i+1][0] == ver)
                    next = true;
            }
            if(present == true)
            {
                for(size_t j = 1; j < points[i].size(); j++)
                {
                    if(j != off)
                        break;
                    for(auto& ver : vert)
                    {
                        if(points[i][j] == ver)
                        {
                            off++;
                            break;
                        }

                    }
                }
            }
            if(previous == true)
            {
                for(size_t j = 1; j < points[i-1].size(); j++)
                {
                    if(j != off_2)
                        break;
                    for(auto& ver : vert)
                    {
                        if(points[i-1][j] == ver)
                        {
                            off_2++;
                            break;
                        }

                    }
                }
            }
        }
        if      (previous == true && present == false && next == true) //mage
        {
//            maska.setFillColor(sf::Color::Magenta);
            if(points[i].size() == points[i-1].size()) //wygląda git
            {

                idx_first = 0;
                idx_sec = 0;
            }
            else if(points[i].size() > points[i-1].size()) //działa
            {
                idx_first = 1;
                idx_sec = 0;
                //maska.setFillColor(sf::Color::Green);

            }
            else // więcej może naprawi
            {
                idx_first = 0;
                idx_sec = 1;
                //maska.setFillColor(sf::Color::White);

            }


        }
        else if(previous == true && present == true && next == true) //yellow
        {
            maska.setFillColor(sf::Color::Yellow);
            if(points[i].size() == points[i-1].size()) //prawie okej z góry jak nachodzą to bug może będzie ok
            {
                idx_first = 1;
                idx_sec = 1;
            }
            else if(points[i].size() > points[i-1].size()) //git
            {
                idx_first = 1;
                idx_sec = 0;
                //maska.setFillColor(sf::Color::Green);
            }
            else            //chyba okej problem dol wiele naprawi
            {
                idx_first = 0;
                idx_sec = 1;
                //maska.setFillColor(sf::Color::White);
            }

            if(off >= 2 && off_2 >= 2)
            {
                maska.setFillColor(sf::Color::Magenta);
                idx_first = off+1;
                idx_sec = off_2+1;
            }
            else if(off_2 >= 2)
            {
                std::cout<<"dwa"<<std::endl;
                maska.setFillColor(sf::Color::Green);
                idx_first = off;
                idx_sec = off_2;
            }
            else if(off >= 2)
            {
                maska.setFillColor(sf::Color::White);
                if(points[i].size() !=off)
                    idx_first = off;

                if(points[i-1].size() !=off_2)
                    idx_sec = off_2;
                std::cout<<off <<"\t"<<off_2<<std::endl;


            }

        }
        else if(previous == true && present == true && next == false) //red
        {
            maska.setFillColor(sf::Color::Red);
            if(points[i].size() == points[i-1].size()) // okej
            {
                idx_first = 1;
                idx_sec = 1;
            }
            else if(points[i].size() > points[i-1].size())// okej
            {
                idx_first = 1;
                idx_sec = 0;
                //maska.setFillColor(sf::Color::Blue);
            }
            else                //???
            {

                idx_first = 0;
                idx_sec = 1;
                //maska.setFillColor(sf::Color(255,10,100));
            }

            if(off >= 2 && off_2 >= 2)
            {
                maska.setFillColor(sf::Color::Blue);
                idx_first = off+1;
                idx_sec = off_2+1;
            }
            else if(off_2 >= 2)
            {
                std::cout<<"dwa"<<std::endl;
                maska.setFillColor(sf::Color(sf::Color(255,200,200)));
                //idx_first = off+1;
                idx_sec = off_2+1;
            }
            else if(off >= 2)
            {
                std::cout<<"dwa"<<std::endl;
                maska.setFillColor(sf::Color::White);
                if(points[i].size() !=off+1)
                    idx_first = off+1;
                else
                    idx_first = off;
                if(points[i-1].size() !=off_2+1)
                    idx_sec = off_2+1;
                else
                    idx_sec = off_2;
            }
        }
        else if(previous == false && present == true && next == true) //blue wyglada ok
        {
            idx_first = 0;
            idx_sec = 0;
//            maska.setFillColor(sf::Color::Blue);
            if(points[i].size() == points[i-1].size()) // okej
            {
                idx_first = 1;
                idx_sec = 1;
            }
            else if(points[i].size() > points[i-1].size())// okej
            {
                idx_first = 1;
                idx_sec = 0;
                //maska.setFillColor(sf::Color::Red);

            }
            else                //???
            {

                idx_first = 0;
                idx_sec = 1;
                //maska.setFillColor(sf::Color(255,10,100));
            }
        }
        else if(previous == false && present == false && next == false)//cyan tu chyba cos nie tak
        {
           maska.setFillColor(sf::Color::Cyan);
            if(points[i].size() == points[i-1].size()) // zjebane
            {
                idx_first = 1;
                idx_sec = 1;
            }
            else if(points[i].size() > points[i-1].size()) // chyba
            {
                idx_first = 1;
                idx_sec = 0;
               // maska.setFillColor(sf::Color::Green);
            }
            else            //chyba okej problem dol wiele naprawi
            {
                idx_first = 0;
                idx_sec = 1;
               // maska.setFillColor(sf::Color::White);
            }
        }
        else if(previous == false && present == false && next == false) //???
        {
//            maska.setFillColor(sf::Color(255,250,200));
            idx_first = 0;
            idx_sec = 0;

//            if(points[i].size() == points[i-1].size()) //
//            {
//                idx_first = 1;
//                idx_sec = 1;
//                //maska.setFillColor(sf::Color::Yellow);
//            }
//            else if(points[i].size() > points[i-1].size()) //git
//            {
//                idx_first = 1;
//                idx_sec = 0;
//                //maska.setFillColor(sf::Color::Green);
//            }
//            else            //chyba okej problem dol wiele naprawi
//            {
//                idx_first = 0;
//                idx_sec = 0;
//                //maska.setFillColor(sf::Color::White);
//            }
        }
        else if(previous == false && present == false && next == true) //dobrze jak jest
        {
//            maska.setFillColor(sf::Color(155,250,100));
            idx_first = 0;
            idx_sec = 0;
        }
        else if(previous == false && present == true && next == false) // ?? bo ja wiem xD chyba lepiej
        {
//            maska.setFillColor(sf::Color(255,100,255));
            if(points[i].size() == points[i-1].size()) // zjebane
            {
                idx_first = 0;
                idx_sec = 0;
                //maska.setFillColor(sf::Color::Yellow);
            }
            else if(points[i].size() > points[i-1].size()) // chyba
            {
                idx_first = 1;
                idx_sec = 0;
                //maska.setFillColor(sf::Color::Green);
            }
            else            //chyba okej problem dol wiele naprawi
            {
                idx_first = 0;
                idx_sec = 0;
                //maska.setFillColor(sf::Color::White);
            }
        }
        else if(previous == true && present == false && next == false) // git git chyba xD
        {
//            maska.setFillColor(sf::Color::White);
            if(points[i].size() == points[i-1].size()) // zjebane
            {
                idx_first = 0;
                idx_sec = 0;
                //maska.setFillColor(sf::Color::Yellow);
            }
            else if(points[i].size() > points[i-1].size()) // chyba
            {
                idx_first = 0;
                idx_sec = 0;
                //maska.setFillColor(sf::Color::Green);
            }
            else            //chyba okej problem dol wiele naprawi
            {
                idx_first = 0;
                idx_sec = 1;
            }
        }

//        if(off >= 2)
//        {
//            std::cout<<"jest"<<std::endl;
//            maska.setFillColor(sf::Color::Magenta);
//            idx_first = off+1;
//            //idx_sec = off_2+1;
//        }
//        if(off_2 >= 2)
//        {
//            std::cout<<"dwa"<<std::endl;
//            maska.setFillColor(sf::Color::White);
//            //idx_first = off+1;
//            idx_sec = off_2+1;
//        }


//            idx_sec = off+1;

        maska.setPointCount(4);
        maska.setPoint(0,points[i][idx_first]);
        maska.setPoint(1,points[i][points[i].size()-1]);
        maska.setPoint(2,points[i-1][points[i-1].size()-1]);
        maska.setPoint(3,points[i-1][idx_sec]);
        vec.emplace_back(maska);
    }
    return vec;
}



