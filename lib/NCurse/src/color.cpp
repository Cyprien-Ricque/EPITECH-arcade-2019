/*
** EPITECH PROJECT, 2020
** color.cpp
** File description:
** OOP_Arcade_2019
*/

#include "ncurse.hpp"

std::vector<std::vector<color_t>> NCurse::initBlock()
{
    std::vector<std::vector<color_t>> block;
    std::vector<color_t> line;
    color_t temp = {0, 0, 0, 0};

    for (int i = 0; i < 16; i++) {
        line.push_back(temp);
    }
    for (int i = 0; i < 16; i++) {
        block.push_back(line);
    }
    return block;
}

int NCurse::getColor(int a __attribute__((unused)), int b, int r, int g)
{
    int max = b;

    if (r >= max)
        max = r;
    if (g >= max)
        max = g;

    int fact = max / 255;

    b = b == 0 ? b : b / fact;
    g = g == 0 ? g : g / fact;
    r = r == 0 ? r : r / fact;

    for (int i = 255; i >= 0; i -= 15) {
        if (r >= i) {
            if (g >= i) {
                if (b >= i)
                    return 6;
                return 1;
            }
            if (b >= i)
                return 5;
            return 3;
        } else if (g >= i) {
            if (b >= i)
                return 2;
            return 4;
        } else if (b >= i)
            return 7;
    }
    return 0;
}

int NCurse::getColorAvg(int x, int y, const std::vector<std::vector<color_t>> &bf)
{
    int r = 0;
    int g = 0;
    int b = 0;
    int a = 0;

    for (int j = y * cofY; j < (y * cofY) + cofY; ++j)
        for (int i = x * cofX; i < (x * cofX) + cofX; ++i) {
            r += bf[j][i].r;
            g += bf[j][i].g;
            b += bf[j][i].b;
            a += bf[j][i].a;
        }
    return getColor(a * 255, b * 255, r * 255, g * 255);
}