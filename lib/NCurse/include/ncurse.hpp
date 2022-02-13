/*
** EPITECH PROJECT, 2020
** ncurse.hpp
** File description:
** OOP_Arcade_2019
*/

#ifndef NCURSE_HPP
#define NCURSE_HPP

#include <ncurses.h>
#include <cstdlib>
#include <fstream>

#include "IGraphicalModule.hpp"
#include "text.hpp"
#include "unistd.h"
#include "color.hpp"

class NCurse : public IGraphicalModule {
    public:
        NCurse();
        ~NCurse();

        /* Display */
        void createWindow(int x, int y, int &ac, char **av) override;
        void closeWindow() override;
        void display() override;
        void drawFramebuffer(std::vector<std::vector<color_t>>) override;
        void drawText(text_t) override;
        size_t getSmoothness() const override;

        /* Input */
        char getInput() const override;

        /* Sound */
        void stopSound(std::string sound) override;
        void playSound(std::string sound) override;
        void setVolume(std::string sound, float volume) override;
        float getVolume(std::string sound) const override;
        void stopAllSounds() override;

    private:
        //void fillCanvas(std::vector<std::vector<color_t>>, std::vector<std::vector<color_t>>);
        int drawChar(int x, int y, const std::vector<std::vector<color_t>> &bf);
        int getColor(int a, int b, int r, int g);
        void resize(int x, int y);
        std::vector<std::vector<color_t>> initBlock();
        int getColorAvg(int x, int y, const std::vector<std::vector<color_t>> &bf);

        WINDOW *_window;

        char **_map;

        size_t _smooth;

        int p1;
        int p2;

        int cofX;
        int cofY;

        std::vector <std::string> _canvas;
        std::vector <std::string> _colors;
};

#endif