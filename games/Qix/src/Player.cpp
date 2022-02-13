/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** OOP_arcade_2019,
*/

#include "Player.hpp"

Player::Player() : GameObject(), _state(STOPPED), dir(TOP)
{
    _pos = std::make_pair(0, 0);
    _size = std::make_pair(UNIT, UNIT);
    _boxSize = std::make_pair(UNIT, UNIT);
    _boxOrigin = std::make_pair(0, 0);
    _keySave.first = 0;
    _keySave.second = -1;
}

void Player::move(Map &map, char input)
{
    auto potentialPos = _pos;
    auto posToCheck = _pos;
    auto posToCheck2 = _pos;

    _keySave.first--;
    if (input != -1) {
        _keySave.second = input;
        _keySave.first = 2;
    }
    if (_pos.first % (UNIT * 2) || _pos.second % (UNIT * 2))
        input = dir;
    if (input == -1 && _keySave.first >= 0)
        input = _keySave.second;
    if (input == RIGHT) {
        potentialPos.first += SPEED;
        posToCheck = potentialPos;
        posToCheck.first += (UNIT - 1);
        posToCheck2 = posToCheck;
        posToCheck2.first += (UNIT - 1);
        dir = RIGHT;
    }
    if (input == LEFT) {
        potentialPos.first -= SPEED;
        posToCheck = potentialPos;
        posToCheck2 = posToCheck;
        posToCheck2.first -= (UNIT - 1);
        dir = LEFT;
    }
    if (input == TOP) {
        potentialPos.second -= SPEED;
        posToCheck = potentialPos;
        posToCheck2 = posToCheck;
        posToCheck2.second -= (UNIT - 1);
        dir = TOP;
    }
    if (input == BOTTOM) {
        potentialPos.second += SPEED;
        posToCheck = potentialPos;
        posToCheck.second += (UNIT - 1);
        posToCheck2 = posToCheck;
        posToCheck2.second += (UNIT - 1);
        dir = BOTTOM;
    }

    if (_pos.first % (UNIT * 2) || _pos.second % (UNIT * 2) ||

        ((posToCheck2.first >= 0 && posToCheck2.second >= 0) &&
        (posToCheck2.first <= SIZE_X && posToCheck2.second <= SIZE_Y) &&
        map.posIsState(posToCheck2, NONE) &&

        (map.posIsType(posToCheck, WALKABLE) ||
        (map.posIsType(posToCheck, BORDER) && map.posIsState(posToCheck, NONE))) &&

        _pos != posToCheck)) {

        _state = MOVING;
        _pos = potentialPos;
    } else {
        _state = STOPPED;
    }
}

void Player::draw(std::vector<std::vector<color_t>> &bf, float smoothness)
{
    color_t c = {255, 255, 255, 255};

    GameEngine::drawSquare(getPosition(smoothness), getSize(smoothness), c,
        bf);
}

void Player::dies()
{
    _pos = std::make_pair(-1, -1);
    _keySave.first = -1;
    _state = DEAD;
}

void Player::spawn(std::pair<int, int> pos)
{
    _pos.first = pos.first;
    _pos.second = pos.second;
    _state = STOPPED;
}

playerState Player::getState()
{
    return _state;
}
