/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** OOP_arcade_2019,
*/

#ifndef OOP_ARCADE_2019_TEXT_HPP
#define OOP_ARCADE_2019_TEXT_HPP

#include "color.hpp"
#include <string>
#include <vector>

typedef struct text {
    size_t _fontSize;
    std::pair<int, int> _pos;
    std::pair<int, int> _anchor;
    std::string _text;
    color_t _color;
    std::string _font;
}text_t;

#endif //OOP_ARCADE_2019_TEXT_HPP
