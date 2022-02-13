/*
** EPITECH PROJECT, 2019
** arcade
** File description:
** arcade,
*/

#ifndef ARCADE_GAMEENGINE_HPP
#define ARCADE_GAMEENGINE_HPP

#include "color.hpp"
#include "bitmapReader.hpp"

#include <utility>
#include <vector>
#include <iostream>
#include <cmath>

class GameEngine {
public:
    GameEngine() = default;

    static void drawSquare(std::pair<int, int> pos, std::pair<int, int> size, color_t c, std::vector<std::vector<color_t>> &bf);
    static void drawCircle(std::pair<int, int> pos, int radius, color_t c, std::vector<std::vector<color_t>> &bf);

    static std::vector<std::vector<color_t>> returnRotateBuffer90(std::vector<std::vector<color_t>> &bf);
    static void rotateBufferM90(std::vector<std::vector<color_t>> &bf);
    static void rotateBuffer90(std::vector<std::vector<color_t>> &bf);
    static void rotateBuffer180(std::vector<std::vector<color_t>> &bf);

    static void clearBuffer(std::vector<std::vector<color_t>> &bf);

    static void putIn(std::vector<std::vector<color_t>> &src, std::vector<std::vector<color_t>> &dest, std::pair<int, int> pos);
    static bool CollisionSquare(std::pair<int, int> posA, std::pair<int, int> sizeA, std::pair<int, int> posB, std::pair<int, int> sizeB);
    static bool Collision(std::pair<int, int> &posA, std::pair<int, int> &sizeA, std::pair<int, int> &posB);

private:
    static void rotateBuffer(int angle, std::vector<std::vector<color_t>> &bf);
    static int getDistance(std::pair<int, int> a, std::pair<int, int> b);
    static int getAngle(std::pair<int, int> a, std::pair<int, int> b);
    static void resize(std::vector<std::vector<color_t>> &bf);
};

#endif //ARCADE_GAMEENGINE_HPP
