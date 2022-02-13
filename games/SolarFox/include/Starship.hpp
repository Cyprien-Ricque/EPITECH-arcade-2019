/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Created by emilien
*/

#ifndef OOP_ARCADE_2019_STARSHIP_HPP
#define OOP_ARCADE_2019_STARSHIP_HPP

#include <vector>
#include "IGameModule.hpp"
#include "bitmapReader.hpp"

class Starship
{
    public:
        //Fonctions
        explicit Starship();
        std::pair<int, int> getPositions();
        bool moveStarship(char input);
        void updateStarshipDirection(char input);
        int getDirection();
        void reset();
        //Variables
    private:
        //Fonctions

        //Variables
        int position[2]{};
        char direction;
};

#endif //OOP_ARCADE_2019_STARSHIP_HPP
