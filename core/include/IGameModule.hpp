/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** OOP_arcade_2019,
*/

#ifndef OOP_ARCADE_2019_I_GAME_MODULE_HPP
#define OOP_ARCADE_2019_I_GAME_MODULE_HPP

#include "text.hpp"
#include "color.hpp"

#include <vector>
#include <iostream>
#include <utility>

class IGameModule {
    public:
        IGameModule() = default;
        virtual ~IGameModule() = default;

        virtual void init() = 0;
        virtual void run(char input, size_t smoothness) = 0;

        virtual std::vector<std::vector<color_t>> getFramebuffer() const = 0;
        virtual std::vector<text_t> getTexts() const = 0;
        virtual std::vector<std::pair<std::string, float>> getSoundsStart() const = 0;
        virtual std::vector<std::string> getSoundsStop() const = 0;

        virtual int getScore() const = 0;
        virtual bool isOver() const = 0;
};

#endif //OOP_ARCADE_2019_I_GAME_MODULE_HPP
