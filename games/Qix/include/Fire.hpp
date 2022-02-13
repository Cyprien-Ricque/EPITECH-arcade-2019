/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** OOP_arcade_2019,
*/

#ifndef OOP_ARCADE_2019_FIRE_HPP
#define OOP_ARCADE_2019_FIRE_HPP

#include "GameObject.hpp"

class Fire : public GameObject {
    public:
        Fire();
        ~Fire() = default;

        void setPosition(std::pair<int, int>);
        void move(Map& _map, char input = -1) override ;
        void draw(std::vector<std::vector<color_t>>&, float smoothness) override ;
};

#endif //OOP_ARCADE_2019_FIRE_HPP
