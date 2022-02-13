/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Created by emilien
*/

#ifndef OOP_ARCADE_2019_BULLET_HPP
#define OOP_ARCADE_2019_BULLET_HPP

#include <vector>
#include "IGameModule.hpp"
#include "bitmapReader.hpp"

class Bullet
{
    public:
        explicit Bullet();

        bool isInit();
        void initBullet(char, int);
        void updatePosition();
        char getSide() const;
        std::pair<int, int> getPosition() const;
        void reset();
    private:
        char _affectedSide;
        bool _init;
        int _position[2]{};
};

#endif //OOP_ARCADE_2019_BULLET_HPP
