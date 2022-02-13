/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** OOP_arcade_2019,
*/

#ifndef OOP_ARCADE_2019_GAMEOBJECT_HPP
#define OOP_ARCADE_2019_GAMEOBJECT_HPP

#include <utility>
#include <vector>
#include <string>
#include "color.hpp"
#include "mapData.hpp"
#include "Map.hpp"

class GameObject {
    public:
        GameObject();
        ~GameObject() = default;

        virtual std::pair<int, int> getPosition(float smoothness);
        virtual std::pair<int, int> getSize(float smoothness);
        virtual std::pair<int, int> getBoxOrigin(float smoothness);
        virtual std::pair<int, int> getBoxSize(float smoothness);
        virtual void move(Map& _map, char input = -1) = 0;
        virtual bool checkCollision(GameObject&, float smoothness);
        virtual void draw(std::vector<std::vector<color_t>>&, float smoothness) = 0;

    protected:
        std::pair<int, int> _pos;
        std::pair<int, int> _size;
        std::pair<int, int> _boxOrigin;
        std::pair<int, int> _boxSize;
};

#endif //OOP_ARCADE_2019_GAMEOBJECT_HPP
