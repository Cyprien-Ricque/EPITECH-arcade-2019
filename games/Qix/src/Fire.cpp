/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** OOP_arcade_2019,
*/

#include "Fire.hpp"

Fire::Fire() : GameObject()
{
}

void Fire::move(Map &_map __attribute__((unused)), char input __attribute__((unused)))
{
}

void Fire::draw(std::vector<std::vector<color_t>> &bf __attribute__((unused)), float smoothness __attribute__((unused)))
{
}

void Fire::setPosition(std::pair<int, int> pos)
{
    _pos = pos;
}
