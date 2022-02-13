/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** OOP_arcade_2019,
*/

#ifndef OOP_ARCADE_2019_MAP_HPP
#define OOP_ARCADE_2019_MAP_HPP

#include <iostream>
#include <vector>
#include "mapData.hpp"
#include "color.hpp"
#include "GameEngine.hpp"

class Map {
    public:
        Map(std::pair<int, int> size);
        void draw(std::vector<std::vector<color_t>>&, float smoothness);
        bool updateFromNewPlayerPos(std::pair<int, int> pos, int &score);
        std::pair<int, int> getFirePos();
        void setQixPosition(int x, int y);
        bool posIsType(std::pair<int, int>, type);
        bool posIsState(std::pair<int, int>, state);
        std::pair<int, int> getStartPathPos();
        void clearPath();
        bool checkCollision(std::pair<int, int> _posBox, std::pair<int, int> _sizeBox);

    private:
        void fill();
        void fillCase(int, int);
        bool check(int, int, std::vector<std::vector<obj_t>>&);
        bool win(int &score);
        std::vector<std::vector<obj_t>> _map;
        void updateBorders();
        void fireManagement(const std::pair<int, int> &pos);
        void endPathManagement(const std::pair<int, int> &pos);

        std::pair<int, int> _startNewPath;
        std::vector<std::pair<int, int>> _newPath;

        int _firePos;
        std::pair<int, int> prevPos;
        std::pair<int, int> prevPos2;
        std::pair<int, int> prevPos3;
        std::pair<int, int> _qixPosition;

        std::pair<int, int> _unit = std::make_pair(UNIT, UNIT);
        int surface;
};

#endif //OOP_ARCADE_2019_MAP_HPP
