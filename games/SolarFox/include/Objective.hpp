/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Created by emilien
*/

#ifndef OOP_ARCADE_2019_OBJECTIVE_HPP
#define OOP_ARCADE_2019_OBJECTIVE_HPP

#include <vector>

class Objective {
public:
    Objective();
    void initObjective(int, int);
    std::pair<int, int> getPosition();
    bool active;
    bool badPowerup;
private:
    int _position[2]{};
};

#endif //OOP_ARCADE_2019_OBJECTIVE_HPP
