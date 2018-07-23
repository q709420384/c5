//
// Created by sanyie on 18-6-22.
//

#ifndef STRATEGY_TEST_WEAPON_H
#define STRATEGY_TEST_WEAPON_H

#include <iostream>
using std::cout;
using std::endl;

class Weapon
{
public:
    Weapon()
    {}
    virtual ~Weapon() {}
    virtual void useWeapon() = 0;
};

class Sword : public Weapon
{
    void useWeapon()
    {
        cout << "宝剑挥舞" << endl;
    }
};

class Knife : public Weapon
{
    void useWeapon()
    {
        cout << "匕首刺杀" << endl;
    }
};

class Axe : public Weapon
{
    void useWeapon()
    {
        cout << "斧头劈砍" << endl;
    }
};

class BowAndArrow : public Weapon
{
    void useWeapon()
    {
        cout << "弓箭射击" << endl;
    }
};

#endif //STRATEGY_TEST_WEAPON_H
