/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Created by emilien
*/

#ifndef OOP_ARCADE_2019_FIRE_HPP
#define OOP_ARCADE_2019_FIRE_HPP

#include <vector>

class Fire {
public:
    explicit Fire();

    void reset();
    bool getInit() const;
    void setOff();
    int getDirection() const;
    void updatePosition();
    void initFire(int, int, char);
    std::pair<int, int> getPosition() const;
private:
    int _position[2]{};
    int _originPositions[2]{};
    char _direction;
    bool _init;
};

#endif //OOP_ARCADE_2019_FIRE_HPP
