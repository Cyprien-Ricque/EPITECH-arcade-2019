/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Created by emilien
*/

#include "GameEngine.hpp"
#include "Starship.hpp"

Starship::Starship()
{
    this->position[0] = 480;
    this->position[1] = 480;
    this->direction = 0;
}

bool Starship::moveStarship(char input)
{
    char speed = 16;

    if (input == 'v')
        speed = 32;
    switch (this->direction) {
        case 0:
            if (this->position[1] - speed <= 171) {
                this->position[1] = 171;
                return (false);
            } else {
                this->position[1] -= speed;
            }
            break;
        case 1:
            if (this->position[1] + speed >= 805) {
                this->position[1] = 805;
                return (false);
            } else {
                this->position[1] += speed;
            }
            break;
        case 2:
            if (this->position[0] - speed <= 171) {
                this->position[0] = 171;
                return (false);
            } else {
                this->position[0] -= speed;
            }
            break;
        case 3:
            if (this->position[0] + speed >= 805) {
                this->position[0] = 805;
                return (false);
            } else {
                this->position[0] += speed;
            }
            break;
        default:
            this->direction = 0;
            break;
    }
    return (true);
}

std::pair<int, int> Starship::getPositions()
{
    return (std::make_pair(this->position[0], this->position[1]));
}

void Starship::updateStarshipDirection(char input)
{
    const char tab[4][4] = {{5, 1, 0, 2}, {8, 3, 2, 1}, {6, 0, 1, 3}, {7, 2, 3, 0}};
    for (auto a : tab) {
        if (input == a[0] && (this->direction == a[1] || this->direction == a[2])) {
            this->direction = a[3];
            break;
        }
    }
}

int Starship::getDirection()
{
    return ((int)this->direction);
}

void Starship::reset()
{
    this->position[0] = 480;
    this->position[1] = 480;
    this->direction = 0;
}
