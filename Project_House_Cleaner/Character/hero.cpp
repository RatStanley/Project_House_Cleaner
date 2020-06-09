#include "hero.h"

#include <iostream>

Hero::Hero()
{
    load_texture("../texture/MainCharacter.png");
}

void Hero::movement()
{

}

void Hero::attack()
{
    std::cout<<"strzal" << std::endl;
//    setTextureRect()
}
