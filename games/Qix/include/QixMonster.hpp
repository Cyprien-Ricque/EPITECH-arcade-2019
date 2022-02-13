/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** OOP_arcade_2019,
*/

#ifndef OOP_ARCADE_2019_QIXMONSTER_HPP
#define OOP_ARCADE_2019_QIXMONSTER_HPP

#include "GameObject.hpp"

class QixMonster : public GameObject {
    public:
        QixMonster();
        ~QixMonster() = default;

        void move(Map& _map, char input = -1) override;
        void draw(std::vector<std::vector<color_t>>&, float smoothness) override;

    private:
        bool newPosIsOK(int x, int y, Map &map);
        std::pair<int, int> findNewPos();

        std::pair<int, int> dir;
        std::vector<std::vector<color_t>> sprite;
        int countDir;
};

#endif //OOP_ARCADE_2019_QIXMONSTER_HPP
