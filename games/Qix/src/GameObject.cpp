/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** OOP_arcade_2019,
*/

#include "GameObject.hpp"

GameObject::GameObject()
= default;

std::pair<int, int> GameObject::getPosition(float smoothness)
{
    auto pos = _pos;

    while (pos.first % static_cast<int>(smoothness))
        pos.first += pos.first % static_cast<int>(smoothness) >
            static_cast<int>(smoothness) / 2 ? 1 : -1;
    while (pos.second % static_cast<int>(smoothness))
        pos.second += pos.second % static_cast<int>(smoothness) >
            static_cast<int>(smoothness) / 2 ? 1 : -1;
    return pos;
}

bool GameObject::checkCollision(GameObject &obj, float smoothness)
{
    auto posThis = getPosition(smoothness);
    posThis.first += getBoxOrigin(smoothness).first;
    posThis.second += getBoxOrigin(smoothness).second;

    auto posObj = obj.getPosition(smoothness);
    posObj.first += obj.getBoxOrigin(smoothness).first;
    posObj.second += obj.getBoxOrigin(smoothness).second;

    return GameEngine::CollisionSquare(posThis, getBoxSize(smoothness), posObj, obj.getBoxSize(smoothness));
}

std::pair<int, int> GameObject::getBoxOrigin(float smoothness)
{
    auto boxOrigin = _boxOrigin;

    while (boxOrigin.first % static_cast<int>(smoothness))
        boxOrigin.first += boxOrigin.first % static_cast<int>(smoothness) > smoothness / 2 ? 1 : -1;
    while (boxOrigin.second % static_cast<int>(smoothness))
        boxOrigin.second += boxOrigin.second % static_cast<int>(smoothness) > smoothness / 2 ? 1 : -1;

    return boxOrigin;
}

std::pair<int, int> GameObject::getBoxSize(float smoothness)
{
    auto boxSize = _boxSize;

    while (boxSize.first % static_cast<int>(smoothness))
        boxSize.first += boxSize.first % static_cast<int>(smoothness) > smoothness / 2 ? 1 : -1;
    while (boxSize.second % static_cast<int>(smoothness))
        boxSize.second += boxSize.second % static_cast<int>(smoothness) > smoothness / 2 ? 1 : -1;
    return boxSize;
}

std::pair<int, int> GameObject::getSize(float smoothness)
{
    auto size = _size;

    while (size.first % static_cast<int>(smoothness))
        size.first += size.first % static_cast<int>(smoothness) > smoothness / 2 ? 1 : -1;
    while (size.second % static_cast<int>(smoothness))
        size.second += size.second % static_cast<int>(smoothness) > smoothness / 2 ? 1 : -1;
    return size;
}
