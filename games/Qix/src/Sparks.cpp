/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** OOP_arcade_2019,
*/

#include "Sparks.hpp"

Sparks::Sparks(std::pair<int, int> pos, std::pair<int, int> dir)
{
    _dir = dir;
    _pos = pos;
    auto bmr = new bitmapReader("./games/assets/cyprien_qix_sparks.bmp");
    _sprites.push_back(bmr->returnVector());

    auto bmr2 = new bitmapReader("./games/assets/cyprien_qix_sparks2.bmp");
    _sprites.push_back(bmr2->returnVector());

    _size = std::make_pair(_sprites.at(0).at(0).size(), _sprites.at(0).size());
    _spriteNb = 0;
    _boxOrigin = std::make_pair(0, 0);
    _boxSize = std::make_pair(UNIT, UNIT);
}

std::pair<int, int> Sparks::getFutureDir(int id)
{
    if (id == 0)
        return (_dir);

    auto futureDir = _dir;

    if (id == 1) {
        futureDir.first = _dir.first ? 0 : -SPEED;
        futureDir.second = _dir.second ? 0 : -SPEED;
    }
    if (id == 2) {
        futureDir.first = _dir.first ? 0 : SPEED;
        futureDir.second = _dir.second ? 0 : SPEED;
    }
    return (futureDir);
}

void Sparks::move(Map &_map, char input __attribute__((unused)))
{
    char dir = 0;
    auto futurePos = _pos;
    auto futurePos2 = _pos;
    auto futureDir = _dir;
    char allow = 0;

    if (_pos.second % UNIT || _pos.first % UNIT) {
        _pos.first += _dir.first;
        _pos.second += _dir.second;
        return;
    }
    do {
        dir = (rand() % 3);
        allow = (rand() % 5);
        futurePos = _pos;
        futureDir = getFutureDir(dir);
        futurePos.first += futureDir.first;
        futurePos.second += futureDir.second;
        futurePos2 = futurePos;
        futurePos2.first += _size.first - 1;
        futurePos2.second += _size.second - 1;
        } while (!((futurePos.first >= 0 && futurePos.first + _size.first - 1 < SIZE_X && futurePos.second >= 0 && futurePos.second + _size.second - 1 < SIZE_Y) &&
    ((_map.posIsType(futurePos, BORDER) && _map.posIsState(futurePos, NONE)) || (!allow && _map.posIsType(futurePos, OLD_BORDER))) &&
    ((_map.posIsType(futurePos2, BORDER) && _map.posIsState(futurePos2, NONE)) || ( !allow && _map.posIsType(futurePos2, OLD_BORDER)))));
    _pos = futurePos;
    _dir = futureDir;
}

void Sparks::draw(std::vector<std::vector<color_t>> &bf, float smoothness)
{
    auto pos = getPosition(smoothness);
    _pos.first += getBoxOrigin(smoothness).first;
    _pos.second += getBoxOrigin(smoothness).second;

    GameEngine::putIn(_sprites.at(_spriteNb), bf, pos);
    _spriteNb = _spriteNb ? 0 : 1;
}
