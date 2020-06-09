#include "weapon.h"

Weapon::Weapon()
{

}

Weapon::~Weapon()
{
    delete Reload_animation_pos;
    delete shot_animation_pos;
}
