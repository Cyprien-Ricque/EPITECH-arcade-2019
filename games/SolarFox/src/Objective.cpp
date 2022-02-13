/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Created by emilien
*/

#include "Objective.hpp"

Objective::Objective()
{
    this->active = false;
    this->badPowerup = false;
}

void Objective::initObjective(int x, int y)
{
    this->_position[0] = x;
    this->_position[1] = y;
}

std::pair<int, int> Objective::getPosition()
{
    return (std::make_pair(this->_position[0], this->_position[1]));
}

