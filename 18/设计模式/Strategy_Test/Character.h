//
// Created by sanyie on 18-6-22.
//

#ifndef STRATEGY_TEST_CHARACTER_H
#define STRATEGY_TEST_CHARACTER_H

#include "Weapon.h"

class Character
{
protected:
    Weapon* weapon;
public:
    Character()
    {
        this->weapon = nullptr;
    }
    virtual ~Character() {}
    void setWeapon(Weapon* weapon)
    {
        this->weapon=weapon;
    }
    virtual void fight() = 0;
};

class King : public Character  //国王类
{
    void fight()
    {
        this->weapon->useWeapon();
    }
};

class Queen : public Character  //皇后类
{
    void fight()
    {
        this->weapon->useWeapon();
    }
};

class Knight : public Character  //骑士类
{
    void fight()
    {
        this->weapon->useWeapon();
    }
};

#endif //STRATEGY_TEST_CHARACTER_H
