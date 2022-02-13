/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** OOP_arcade_2019,
*/

#ifndef OOP_ARCADE_2019_PLAYER_HPP
#define OOP_ARCADE_2019_PLAYER_HPP

#include "GameObject.hpp"

class Player : public GameObject {
    public:
        Player();
        ~Player() = default;

        void move(Map& map, char input = -1) override ;
        void draw(std::vector<std::vector<color_t>>&, float smoothness) override ;
        playerState getState();
        void dies();
        void spawn(std::pair<int, int> pos);

    private:
        playerState _state;
        char dir;
        std::pair<int, char> _keySave;
};

#endif //OOP_ARCADE_2019_PLAYER_HPP
