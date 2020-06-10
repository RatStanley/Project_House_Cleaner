#ifndef PISTOL_H
#define PISTOL_H

#include "weapon.h"

class Pistol : public Weapon
{
public:
    Pistol();
    void Reload_Animation(sf::Time tm);
};

#endif // PISTOL_H
