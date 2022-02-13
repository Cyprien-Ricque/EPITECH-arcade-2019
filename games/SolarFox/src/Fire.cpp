/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Created by emilien
*/

#include <iostream>
#include "Fire.hpp"

Fire::Fire()
{
    this->_direction = -1;
    this->_position[0] = -1;
    this->_position[1] = -1;
    this->_init = false;
}

void Fire::initFire(int x, int y, char direction)
{
    this->_direction = direction;

    switch (direction) {
        case 0:
            x += 16;
            y += 16;
            break;
        case 1:
            x += 16;
            break;
        case 2:
            y += 16;
            x += 16;
            break;
        case 3:
            y += 16;
            break;
        default:
            break;
    }
    this->_position[0] = x;
    this->_position[1] = y;
    this->_originPositions[0] = x;
    this->_originPositions[1] = y;
    this->_init = true;
}

int Fire::getDirection() const
{
    return (static_cast<int>(this->_direction));
}

void Fire::updatePosition()
{
    if (!this->_init)
        return;
    switch (this->_direction) {
        case 1:
            this->_position[1] += 50;
            if (this->_originPositions[1] + 200 < this->_position[1] || this->_position[1] >= 805)
                this->reset();
            break;
        case 0:
            this->_position[1] -= 50;
            if (this->_originPositions[1] - 200 > this->_position[1] || this->_position[1] <= 171)
                this->reset();
            break;
        case 2:
            this->_position[0] -= 50;
            if (this->_originPositions[0] - 200 > this->_position[0] || this->_position[0] <= 171)
                this->reset();
            break;
        case 3:
            this->_position[0] += 50;
            if (this->_originPositions[0] + 200 < this->_position[0] || this->_position[0] >= 805)
                this->reset();
            break;
        default:
            this->reset();
            return;
    }
}

std::pair<int, int> Fire::getPosition() const
{
    return (std::make_pair(_position[0], _position[1]));
}

void Fire::reset()
{
    this->_position[0] = -1;
    this->_position[1] = -1;
    this->_direction = -1;
    this->_init = false;
}

bool Fire::getInit() const
{
    return (this->_init);
}

void Fire::setOff()
{
    this->_init = false;
}