#include <iostream>
#include "Character.h"
#include "Weapon.h"
using std::cout;
using std::endl;

int main()
{
    Character** characters = new Character*[3];
    Weapon** weapons = new Weapon*[4];
    characters[0] = new King();
    characters[1] = new Queen();
    characters[2] = new Knight();

    weapons[0] = new Sword();
    weapons[1] = new Knife();
    weapons[2] = new Axe();
    weapons[3] = new BowAndArrow();

    characters[0]->setWeapon(weapons[0]);
    characters[1]->setWeapon(weapons[1]);
    characters[2]->setWeapon(weapons[2]);

    for(int i = 0; i < 3; ++i)
    {
        characters[i]->fight();
    }

    characters[2]->setWeapon(weapons[3]);
    characters[2]->fight();
    delete[] characters;
    delete[] weapons;
}