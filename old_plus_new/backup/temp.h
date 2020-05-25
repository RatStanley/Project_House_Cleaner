#ifndef TEMP_H
#define TEMP_H


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

std::vector<sf::RectangleShape> box(std::vector<sf::Vector2f> punkty);
std::vector<std::pair<sf::Vector2f, sf::Vector2f>> rect(sf::RectangleShape bryla);
std::vector<sf::Vector2f> intersection_point(std::vector<std::pair<sf::Vector2f, sf::Vector2f>> all_lines, std::vector<sf::Vector2f> points_enti, sf::Vector2f mysz);
std::vector<sf::Vector2f> points_to_cheak(sf::RectangleShape bryla);
std::vector<sf::Vector2f> sort(std::vector<sf::Vector2f> points, sf::Vector2f mysz);
sf::ConvexShape mask(std::vector<sf::Vector2f> points);
#endif // TEMP_H
