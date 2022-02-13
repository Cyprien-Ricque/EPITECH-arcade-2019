/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Created by emilien
*/

#include "GameEngine.hpp"
#include "Bullet.hpp"

Bullet::Bullet()
{
    this->_init = false;
    this->_affectedSide = -1;
    this->_position[0] = -1;
    this->_position[1] = -1;
}

void Bullet::reset()
{
    this->_init = false,
    this->_affectedSide = -1;
    this->_position[0] = -1;
    this->_position[1] = -1;
}

bool Bullet::isInit()
{
    return (this->_init);
}

void Bullet::initBullet(char side, int position)
{
    position += 48;
    if (position < 219 || position > 757)
        return;
    switch (side) {
        case 0:
            this->_position[0] = position;
            this->_position[1] = 171;
            this->_affectedSide = side;
            this->_init = true;
            break;
        case 1:
            this->_position[0] = position;
            this->_position[1] = 805;
            this->_affectedSide = side;
            this->_init = true;
            break;
        case 2:
            this->_position[0] = 805;
            this->_position[1] = position;
            this->_affectedSide = side;
            this->_init = true;
            break;
        case 3:
            this->_position[0] = 171;
            this->_position[1] = position;
            this->_affectedSide = side;
            this->_init = true;
            break;
        default:
            this->_affectedSide = -1;
            this->_init = false;
            break;
    }
}

void Bullet::updatePosition()
{
    switch (this->_affectedSide) {
        case 0:
            this->_position[1] += 16;
            if (this->_position[1] >= 805)
                this->reset();
            break;
        case 1:
            this->_position[1] -= 16;
            if (this->_position[1] <= 171)
                this->reset();
            break;
        case 2:
            this->_position[0] -= 16;
            if (this->_position[0] <= 171)
                this->reset();
            break;
        case 3:
            this->_position[0] += 16;
            if (this->_position[0] >= 805)
                this->reset();
            break;
        default:
            this->reset();
            break;
    }
}

std::pair<int, int> Bullet::getPosition() const
{
    return (std::make_pair(this->_position[0], this->_position[1]));
}

char Bullet::getSide() const
{
    return (this->_affectedSide);
}