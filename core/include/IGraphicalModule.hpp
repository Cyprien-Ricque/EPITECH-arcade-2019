/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** OOP_arcade_2019,
*/

#ifndef OOP_ARCADE_2019_I_DISPLAY_MODULE_HPP
#define OOP_ARCADE_2019_I_DISPLAY_MODULE_HPP

#include "text.hpp"
#include "color.hpp"
#include <vector>
#include <iostream>

#define CENTER 0
#define LEFT -1
#define RIGHT 1
#define TOP -1
#define BOTTOM 1


class IGraphicalModule {
    public:
        virtual ~IGraphicalModule() = default;

        /* Display */
        virtual void createWindow(int x, int y, int &ac, char **av) = 0;
        virtual void closeWindow() = 0;
        virtual void display() = 0;
        virtual void drawFramebuffer(std::vector<std::vector<color_t>>) = 0;
        virtual void drawText(text_t) = 0;
        virtual size_t getSmoothness() const = 0;

        /* Input */
        virtual char getInput() const = 0;

        /* Sound */
        virtual void stopSound(std::string sound) = 0;
        virtual void playSound(std::string sound) = 0;
        virtual void setVolume(std::string sound, float volume) = 0;
        virtual float getVolume(std::string sound) const = 0;
        virtual void stopAllSounds() = 0;
};

#endif //OOP_ARCADE_2019_I_DISPLAY_MODULE_HPP