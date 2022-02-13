/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** OOP_arcade_2019,
*/

#include "QixMonster.hpp"

QixMonster::QixMonster() : GameObject(), countDir(0)
{
    auto bmr = new bitmapReader("./games/assets/cyprien_qix_monster.bmp");
    sprite = bmr->returnVector();

    _size = std::make_pair(sprite.at(0).size(), sprite.size());
    _boxSize = std::make_pair(sprite.at(0).size(), sprite.size());
    _boxOrigin = std::make_pair(0, 0);
    _pos = std::make_pair(SIZE_X / 2 - _size.first / 2, SIZE_Y / 2 - _size.second / 2);
}

void QixMonster::move(Map &_map, char input __attribute__((unused)))
{
    std::pair<int, int> futurePos;

    do {
        futurePos = findNewPos();
    } while (!newPosIsOK(futurePos.first, futurePos.second, _map));
    _pos = futurePos;
}

void QixMonster::draw(std::vector<std::vector<color_t>> &bf, float smoothness)
{
    GameEngine::putIn(sprite, bf, getPosition(smoothness));
}

bool QixMonster::newPosIsOK(int x, int y, Map& map)
{
    if (x < 0 || y < 0 || x + _size.first >= SIZE_X || y + _size.second >= SIZE_Y)
        return (false);
    for (int j = y + _boxOrigin.second; j < y + _boxOrigin.second + _boxSize.second; ++j)
        for (int i = x + _boxOrigin.first; i < x + _boxOrigin.first + _boxSize.first; ++i)
            if (!map.posIsType(std::make_pair(i, j), WALKABLE) && !map.posIsType(std::make_pair(i, j), BORDER))
                return (false);
    return (true);
}

std::pair<int, int> QixMonster::findNewPos()
{
    std::pair<int, int> pos = _pos;
    int _rand;

    if (countDir) {
        countDir--;
        _rand = rand() % 3;
        pos.first += (dir.first + _rand) % QIX_MAX_SPEED;
        pos.second += (dir.second - _rand) % QIX_MAX_SPEED;
        return (pos);
    }
    dir.first = (rand() % (QIX_MAX_SPEED * 2)) - QIX_MAX_SPEED;
    dir.second = (rand() % (QIX_MAX_SPEED * 2)) - QIX_MAX_SPEED;
    pos.first = _pos.first + dir.first;
    pos.second = _pos.second + dir.second;
    countDir = 15;
    return (pos);
}