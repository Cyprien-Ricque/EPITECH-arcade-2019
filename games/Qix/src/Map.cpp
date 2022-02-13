/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** OOP_arcade_2019,
*/

#include "Map.hpp"

Map::Map(std::pair<int, int> size) : _firePos(-1), _qixPosition(40, 40)
{
    obj_t o = {WALKABLE, NONE};

    _map.resize(size.second, std::vector<obj_t>(size.first, o));

    for (int j = 0; j < static_cast<int>(_map.size()); ++j)
        for (int i = 0; i < static_cast<int>(_map.at(0).size()); ++i)
            if (j < UNIT || j >= SIZE_Y - UNIT || i < UNIT || i >= SIZE_Y - UNIT) {
                _map[j][i].t = BORDER;
                _map[j][i].s = NONE;
            }
    surface = 0;
    _firePos = 0;
}

bool Map::updateFromNewPlayerPos(std::pair<int, int> pos, int& score)
{
    auto tmp = pos;
    tmp.first += UNIT - 1;
    tmp.second += UNIT - 1;

    fireManagement(pos);

    if (pos != prevPos) {
        if (!(pos.first % UNIT) && !(pos.second % UNIT) && _newPath.empty() && posIsType(pos, BORDER)) // New Potential Path
            _startNewPath = pos;

        if (posIsType(pos, WALKABLE) && _newPath.empty()) // New Path
            _newPath.push_back(_startNewPath);

        if (!(pos.first % UNIT) && !(pos.second % UNIT) && // Path end
            ((posIsType(pos, BORDER) && posIsState(pos, NONE)) ||
                (posIsType(tmp, BORDER) && posIsState(tmp, NONE))) &&
            !_newPath.empty()) {

            endPathManagement(pos);

            if (win(score))
                return (true);
        }

        if (posIsType(pos, WALKABLE) && !_newPath.empty()) { // Path Continue
            _newPath.push_back(pos);
            auto aX = _newPath.at(_newPath.size() - 2).first <=
                _newPath.at(_newPath.size() - 1).first ?
                _newPath.at(_newPath.size() - 2).first :
                _newPath.at(_newPath.size() - 1).first;
            auto aY = _newPath.at(_newPath.size() - 2).second <=
                _newPath.at(_newPath.size() - 1).second ?
                _newPath.at(_newPath.size() - 2).second :
                _newPath.at(_newPath.size() - 1).second;
            auto bX = _newPath.at(_newPath.size() - 2).first >
                _newPath.at(_newPath.size() - 1).first ?
                _newPath.at(_newPath.size() - 2).first :
                _newPath.at(_newPath.size() - 1).first;
            auto bY = _newPath.at(_newPath.size() - 2).second >
                _newPath.at(_newPath.size() - 1).second ?
                _newPath.at(_newPath.size() - 2).second :
                _newPath.at(_newPath.size() - 1).second;

            for (auto j = aY; j < bY + UNIT; ++j)
                for (auto i = aX; i < bX + UNIT; ++i)
                    if (posIsType(std::make_pair(i, j), WALKABLE)) {
                        _map[j][i].t = BORDER;
                        _map[j][i].s = CREATE;
                    }
        }
    }
    prevPos3 = prevPos2;
    prevPos2 = prevPos;
    prevPos = pos;
    return (false);
}

void Map::endPathManagement(const std::pair<int, int> &pos)
{
    for (auto &e : _newPath)
        for (int j = e.second; j < e.second + UNIT; ++j)
            for (int i = e.first; i < e.first + UNIT; ++i)
                _map[j][i].s = NONE;

    fill();
    updateBorders();
    _newPath.clear();
    _firePos = 0;
    _startNewPath = pos;
}

void Map::fireManagement(const std::pair<int, int> &pos)
{
    if (pos == prevPos3) { // fire
        if (!_newPath.empty()) {
            _firePos += 2;
            if (_firePos >= static_cast<int>(_newPath.size()))
                _firePos = static_cast<int>(_newPath.size()) - 1;
            for (int e = (UNIT / SPEED) - 1; e < _firePos && e < static_cast<int>(_newPath.size()); ++e)
                for (int j = _newPath.at(e).second; j < _newPath.at(e).second + UNIT; ++j)
                    for (int i = _newPath.at(e).first; i < _newPath.at(e).first + UNIT; ++i)
                        _map[j][i].s = BURNT;
            for (int j = _newPath.at(_firePos).second; j < _newPath.at(_firePos).second + UNIT; ++j)
                for (int i = _newPath.at(_firePos).first; i < _newPath.at(_firePos).first + UNIT; ++i)
                    _map[j][i].s = ON_FIRE;
        }
    }
}

void Map::draw(std::vector<std::vector<color_t>>& bf, float smoothness __attribute__((unused)))
{
    color_t border = {10, 10, 150, 255};
    color_t walkable = {0, 0, 0, 255};
    color_t non_walkable = {150, 150, 150, 255};
    color_t create = {5, 5, 75, 255};
    color_t burnt = {135, 65, 65, 255};
    color_t fire = {255, 50, 50, 255};

    for (int j = 0; j < static_cast<int>(_map.size()); ++j)
        for (int i = 0; i < static_cast<int>(_map.at(0).size()); ++i) {
            if ((_map[j][i].t == BORDER || _map[j][i].t == OLD_BORDER) && _map[j][i].s == NONE)
                bf[j][i] = border;
            if ((_map[j][i].t == BORDER && _map[j][i].s == BURNT))
                bf[j][i] = burnt;
            if ((_map[j][i].t == BORDER && _map[j][i].s == CREATE))
                bf[j][i] = create;
            if ((_map[j][i].t == BORDER && _map[j][i].s == ON_FIRE))
                bf[j][i] = fire;
            if (_map[j][i].t == WALKABLE)
                bf[j][i] = walkable;
            if (_map[j][i].t == NON_WALKABLE)
                bf[j][i] = non_walkable;
        }
}

bool Map::posIsType(std::pair<int, int> pos, type t)
{
    return _map.at(pos.second).at(pos.first).t == t;
}

bool Map::posIsState(std::pair<int, int> pos, state s)
{
    return _map.at(pos.second).at(pos.first).s == s;
}

void Map::setQixPosition(int x, int y)
{
    _qixPosition = std::make_pair(x, y);
}

bool Map::check(int x, int y, std::vector<std::vector<obj_t>>& tmpMap)
{
    auto tmp = std::make_pair(x, y);

    if (x < 0 || x >= SIZE_X || y < 0 || y >= SIZE_Y)
        return true;

    if (tmpMap[y][x].t != WALKABLE)
        return (true);
    if (GameEngine::Collision(tmp, _unit, _qixPosition))
        return false;
    tmpMap[y][x].t = NON_WALKABLE;
    return (check(x + UNIT, y, tmpMap) && check(x - UNIT, y, tmpMap) && check(x, y + UNIT, tmpMap) && check(x, y - UNIT, tmpMap));
}

void Map::fillCase(int x, int y)
{
    if (x < 0 || x >= SIZE_X || y < 0 || y >= SIZE_Y)
        return;
    if (_map[y][x].t != WALKABLE)
        return;

    for (int j = y; j < y + UNIT; ++j)
        for (int i = x; i < x + UNIT; ++i)
            if (_map[j][i].t == WALKABLE) {
                _map[j][i].t = NON_WALKABLE;
                _map[j][i].s = NONE;
            }
    fillCase(x + UNIT, y);
    fillCase(x - UNIT, y);
    fillCase(x, y + UNIT);
    fillCase(x, y - UNIT);
}

void Map::fill()
{
    std::vector<std::vector<obj_t>> tmp;

    for (auto &e : _newPath) {
        if (e.first % UNIT || e.second % UNIT)
            continue;
        tmp = _map;
        if (check(e.first + UNIT, e.second, tmp))
            fillCase(e.first + UNIT, e.second);
        tmp = _map;
        if (check(e.first - UNIT, e.second, tmp))
            fillCase(e.first - UNIT, e.second);
        tmp = _map;
        if (check(e.first, e.second + UNIT, tmp))
            fillCase(e.first, e.second + UNIT);
        tmp = _map;
        if (check(e.first, e.second - UNIT, tmp))
            fillCase(e.first, e.second - UNIT);
    }
}

bool Map::win(int &score)
{
    int c = 0;

    for (auto &f : _map)
        for (auto &e : f) {
            if (e.t == NON_WALKABLE || e.t == OLD_BORDER)
                ++c;
        }
    score += (c - surface);
    surface = c;
    return c >= SIZE_Y * SIZE_X * 0.75;
}

void Map::updateBorders()
{
    for (int j = 0; j < static_cast<int>(_map.size()); ++j)
        for (int i = 0; i < static_cast<int>(_map.at(0).size()); ++i)
            if (_map[j][i].t == BORDER &&
            (j + UNIT >= SIZE_Y || _map[j + UNIT][i].t != WALKABLE) &&
            (j - UNIT < 0 || _map[j - UNIT][i].t != WALKABLE) &&
            (i + UNIT >= SIZE_X || _map[j][i + UNIT].t != WALKABLE) &&
            (i - UNIT < 0 || _map[j][i - UNIT].t != WALKABLE) &&
            (j + UNIT >= SIZE_Y || i + UNIT >= SIZE_X || _map[j + UNIT][i + UNIT].t != WALKABLE) &&
            (j + UNIT >= SIZE_Y || i - UNIT < 0 || _map[j + UNIT][i - UNIT].t != WALKABLE) &&
            (j - UNIT < 0 || i - UNIT < 0 || _map[j - UNIT][i - UNIT].t != WALKABLE) &&
            (j - UNIT < 0 || i + UNIT >= SIZE_X || _map[j - UNIT][i + UNIT].t != WALKABLE))
                _map[j][i].t = OLD_BORDER;
}

std::pair<int, int> Map::getFirePos()
{
    return _newPath[_firePos];
}

std::pair<int, int> Map::getStartPathPos()
{
    return (_startNewPath);
}

void Map::clearPath()
{
    for (int e = (UNIT / SPEED) - 1; e < static_cast<int>(_newPath.size()); ++e)
        for (int j = _newPath.at(e).second; j < _newPath.at(e).second + UNIT; ++j)
            for (int i = _newPath.at(e).first; i < _newPath.at(e).first + UNIT; ++i) {
                _map[j][i].t = WALKABLE;
                _map[j][i].s = NONE;
            }
    _newPath.clear();
    _firePos = 0;
}

bool Map::checkCollision(std::pair<int, int> _posBox, std::pair<int, int> _sizeBox)
{
    if (static_cast<int>(_newPath.size()) > 2 && _firePos >= static_cast<int>(_newPath.size()) - 1)
        return (true);
    for (auto &e : _newPath) {
        if (GameEngine::CollisionSquare(std::make_pair(e.first, e.second), _unit, _posBox, _sizeBox))
            return (true);
    }
    return (false);
}
