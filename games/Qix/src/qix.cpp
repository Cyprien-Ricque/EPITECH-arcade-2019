/*
** EPITECH PROJECT, 2019
** Arcade
** File description:
** Arcade
*/

#include "qix.hpp"

Qix::Qix() : _bfSize(std::make_pair(SIZE_X + UNIT, SIZE_Y + UNIT)), _map(std::make_pair(SIZE_X, SIZE_Y))
{
    _sparks.push_back(*(new Sparks(std::make_pair(SIZE_X - UNIT - UNIT, SIZE_Y - UNIT), std::make_pair(-(SPEED), 0))));
    _sparks.push_back(*(new Sparks(std::make_pair(SIZE_X - UNIT, SIZE_Y - UNIT - UNIT), std::make_pair(0, -(SPEED)))));
}

Qix::~Qix()
{
}

void Qix::init()
{
    color_t black = {0, 0, 0, 0};

    _over = false;
    _score = 0;
    _status = PLAYING;
    _bf.resize(_bfSize.second, std::vector<color_t>(_bfSize.first, black));
    _sparks[0] = (*(new Sparks(std::make_pair(SIZE_X - UNIT - UNIT, SIZE_Y - UNIT), std::make_pair(-(SPEED), 0))));
    _sparks[1] = (*(new Sparks(std::make_pair(SIZE_X - UNIT, SIZE_Y - UNIT - UNIT), std::make_pair(0, -(SPEED)))));
    _player = Player();
    _qix = QixMonster();
    _texts.clear();
    _map = Map(std::make_pair(SIZE_X, SIZE_Y));
}

void Qix::run(char input, size_t smoothness)
{
    GameEngine::clearBuffer(_bf);
    _texts.clear();

    if (_status == WIN)
        createText("YOU WON !", std::make_pair(SIZE_X / 2, SIZE_Y / 3), std::make_pair(0, 0), 30, {230, 230, 230, 255});
    if (_status == LOSE)
        createText("YOU LOST ..", std::make_pair(SIZE_X / 2, SIZE_Y / 3), std::make_pair(0, 0), 30, {230, 230, 230, 255});

    if (_status == PLAYING) {
        auto posBoxQix = _qix.getPosition(smoothness);
        posBoxQix.first += _qix.getBoxOrigin(smoothness).first;
        posBoxQix.second += _qix.getBoxOrigin(smoothness).second;
        if (_player.checkCollision(_qix, smoothness) ||
            _map.checkCollision(posBoxQix, _qix.getBoxSize(smoothness))) {
            _player.dies();
            _map.clearPath();
            _player.spawn(_map.getStartPathPos());
            _score -= 1000;
        } else if (collisionSparks(_sparks, smoothness)) {
            _player.dies();
            _map.clearPath();
            _player.spawn(std::make_pair(0, 0));
            _status = LOSE;
            _score -= 100000;
        } else {
            _player.move(_map, input);
        }

        _qix.move(_map);
        for (auto &e : _sparks)
            e.move(_map);

        _map.setQixPosition(_qix.getPosition(smoothness).first +
                _qix.getBoxSize(smoothness).first / 2,
            _qix.getPosition(smoothness).second +
                _qix.getBoxSize(smoothness).second / 2);
        if (_map.updateFromNewPlayerPos(_player.getPosition(smoothness),_score)) {
            _status = WIN;
            _score += 100000;
        }
    } else {
        createText("Press R to restart",
            std::make_pair(SIZE_X / 2, (SIZE_Y / 3) * 2), std::make_pair(0, 0),
            18, {230, 230, 230, 255});
        createText("and escape to go back to the menu",
            std::make_pair(SIZE_X / 2, (SIZE_Y / 3) * 2 + 30), std::make_pair(0, 0),
            18, {230, 230, 230, 255});
    }
    _map.draw(_bf, smoothness);
    _player.draw(_bf, smoothness);
    _qix.draw(_bf, smoothness);
    for (auto &e : _sparks)
        e.draw(_bf, smoothness);
    _clock.wait();
}

std::vector<std::vector<color_t>> Qix::getFramebuffer() const
{
    return _bf;
}

std::vector<text_t> Qix::getTexts() const
{
    return _texts;
}

std::vector<std::pair<std::string, float>> Qix::getSoundsStart() const
{
    return _soundsStart;
}

std::vector<std::string> Qix::getSoundsStop() const
{
    return _soundsStop;
}

int Qix::getScore() const
{
    return _score / 100;
}

bool Qix::isOver() const
{
    return (_over);
}

bool Qix::collisionSparks(std::vector<Sparks> s, float smoothness)
{
    for (auto &e : s) {
        if (e.checkCollision(_player, smoothness))
            return (true);
    }
    return (false);
}

void Qix::createText(std::string text, std::pair<int, int> pos, std::pair<int, int> anchor, int size, color_t c)
{
    _text._font = std::string("games/assets/cyprien_menu_arial.ttf");
    _text._text = std::move(text);
    _text._fontSize = size;
    _text._color.r = c.r;
    _text._color.g = c.g;
    _text._color.b = c.b;
    _text._color.a = c.a;
    _text._anchor.first = anchor.first;
    _text._anchor.second = anchor.second;
    _text._pos = pos;
    _texts.push_back(_text);
}

extern "C" IGameModule *newInstance()
{
    return (new Qix());
}

extern "C" void destroyInstance(IGameModule *qix)
{
    delete qix;
}