#ifndef TEMP_H
#define TEMP_H


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

std::vector<std::pair<sf::Vector2f, sf::Vector2f>> rect( const sf::RectangleShape &bryla);
std::vector<std::vector<sf::Vector2f>> intersection_point( const std::vector<std::pair<sf::Vector2f, sf::Vector2f>> &all_lines, const std::vector<sf::Vector2f> &points_enti, const sf::Vector2f &mysz);
std::vector<sf::Vector2f> points_to_cheak(const sf::RectangleShape &bryla);
std::vector<std::vector<sf::Vector2f>> sort_vector(std::vector<std::vector<sf::Vector2f>> points, const sf::Vector2f &mysz);
std::vector<sf::ConvexShape> vector_v2_mask(const std::vector<std::vector<sf::Vector2f>> &points, const std::vector<sf::Vector2f> &vert);

std::vector<sf::Vector2f> off_set(const std::vector<std::pair<sf::Vector2f, sf::Vector2f>> &all_lines, std::vector<std::vector<sf::Vector2f>> points, const sf::Vector2f &mysz);
std::vector<sf::ConvexShape> Done_maska(const std::vector<std::vector<sf::Vector2f>> &points, const std::vector<sf::Vector2f> &vertoff_Set);


#endif // TEMP_H
