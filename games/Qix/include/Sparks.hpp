/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** OOP_arcade_2019,
*/

#ifndef OOP_ARCADE_2019_SPARKS_HPP
#define OOP_ARCADE_2019_SPARKS_HPP

#include "GameObject.hpp"

class Sparks : public GameObject {
    public:
        Sparks(std::pair<int, int> pos, std::pair<int, int> dir);
        ~Sparks() = default;

        void move(Map& _map, char input = -1) override ;
        void draw(std::vector<std::vector<color_t>>&, float smoothness) override ;

    private:
        std::pair<int, int> _dir;
        std::pair<int, int> getFutureDir(int id);

        std::vector<std::vector<std::vector<color_t >>> _sprites;
        int _spriteNb;
};

#endif //OOP_ARCADE_2019_SPARKS_HPP
