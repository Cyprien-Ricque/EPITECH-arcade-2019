/*
** EPITECH PROJECT, 2019
** arcade
** File description:
** arcade,
*/

#include "Menu.hpp"

#include <utility>
#include <regex>

Menu::Menu()
{
    std::vector<color_t> tmp;

    color_t grey = {180, 180, 180, 180};

    for (size_t i = 0; i < 1024; ++i)
        tmp.push_back(grey);
    for (size_t j = 0; j < 1024; ++j)
        _bf.push_back(tmp);
    _username = "";
    _idxCurrentGame = 0;
    _idxCurrentLib = 0;

    _c1 = {179, 144, 61, 255};
    _c2 = {100, 81, 179, 255};
    _c3 = {206, 92, 255, 255};
    _c4 = {6, 103, 170, 255};
    _soundsStart.emplace_back("games/assets/cyprien_menu_music", 10);
}

void Menu::setCurrentGame(char input)
{
    if (input == 5)
        _idxCurrentGame = _idxCurrentGame <= 0 ? static_cast<int>(_games.size()) - 1 : _idxCurrentGame - 1;
    if (input == 6)
        _idxCurrentGame = _idxCurrentGame + 1 >= static_cast<int>(_games.size()) ? 0 : _idxCurrentGame + 1;
    if (input == 3)
        _toDo = std::make_pair(GAME, _games.at(_idxCurrentGame));
}

void Menu::setCurrentLib(char input)
{
    if (input == 5)
        _idxCurrentLib = _idxCurrentLib <= 0 ? static_cast<int>(_libs.size()) - 1 : _idxCurrentLib - 1;
    if (input == 6)
        _idxCurrentLib = _idxCurrentLib + 1 >= static_cast<int>(_libs.size()) ? 0 : _idxCurrentLib + 1;
    if (input == 3)
        _toDo = std::make_pair(LIB, _libs.at(_idxCurrentLib));
}

void Menu::createText(std::string text, std::pair<int, int> pos, std::pair<int, int> anchor, int size, color_t c)
{
    _text._font = std::string("games/assets/cyprien_menu_arial.ttf");
    _text._text = std::move(text);
    _text._fontSize = size * 1.7;
    _text._color.r = c.r;
    _text._color.g = c.g;
    _text._color.b = c.b;
    _text._color.a = c.a;
    _text._anchor.first = anchor.first;
    _text._anchor.second = anchor.second;
    _text._pos = pos;
    _texts.push_back(_text);
}

void Menu::run(char input, size_t smoothness __attribute__((unused)))
{
    GameEngine::clearBuffer(_bf);
    _texts.clear();
    _clock.wait();

    _toDo.second = "";
    _switch(input);
    displayScores();
}

std::vector<std::vector<color_t>> Menu::getFramebuffer() const
{
    return _bf;
}

void Menu::init()
{
    _toDo.first = GAME;
    _toDo.second = "";
}

std::pair<Menu::concern, std::string> Menu::toDo()
{
    return _toDo;
}

void Menu::setGames(std::vector<std::string> games)
{
    _games = std::move(games);
}

void Menu::setLibs(std::vector<std::string> libs)
{
    _libs = std::move(libs);
}

std::vector<text_t> Menu::getTexts() const
{
    return _texts;
}

std::vector<std::pair<std::string, float>> Menu::getSoundsStart() const
{
    return _soundsStart;
}

std::vector<std::string> Menu::getSoundsStop() const
{
    return _soundsStop;
}

int Menu::getScore() const
{
    return 0;
}

bool Menu::isOver() const
{
    return false;
}

void Menu::usernameManagement(char input)
{
    if (input >= 'a' and input <= 'z' and _username.size() < 15)
        _username.push_back(input);
    if (input == 2 and !_username.empty())
        _username  = _username.substr(0, _username.length() - 1);
}

void Menu::setScores(std::map<std::string, std::map<std::string, int>> scores)
{
    std::ofstream output(".scoreArcade");

    if (output.is_open()) {
        for (auto &a : scores) {
            for (auto &b : a.second) {
                output << b.first << "|" << b.second << "|" << a.first << std::endl;
            }
        }
        output.close();
    }
    _scores = std::move(scores);
}

void Menu::_switch(char input)
{
    if (_toDo.first == GAME && input == 7) {
        _toDo.first = LIB;
        _toDo.second = "";
        input = -1;
    }
    if (_toDo.first == LIB && input == 7) {
        _toDo.first = PSEUDO;
        _toDo.second = "";
        input = -1;
    }
    if (_toDo.first == LIB && input == 8) {
        _toDo.first = GAME;
        _toDo.second = "";
        input = -1;
    }
    if (_toDo.first == PSEUDO && (input == 8 || input == 1 || input == 3)) {
        _toDo.first = LIB;
        _toDo.second = "";
        input = -1;
    }
    if (_toDo.first == GAME) {
        setCurrentGame(input);
        createText(getLibName(_games.at(_idxCurrentGame)), std::make_pair(512, 512), std::make_pair(0, 0), 48, _c1);
        createText(getLibName(_libs.at(_idxCurrentLib)), std::make_pair(512, 350), std::make_pair(0, 0), 48, _c2);
        createText(std::string("Username: [ ") + _username + std::string(" ]"), std::make_pair(512, 100), std::make_pair(0, 0), 24, _c2);
    }
    if (_toDo.first == LIB) {
        setCurrentLib(input);
        createText(getLibName(_games.at(_idxCurrentGame)), std::make_pair(512, 512), std::make_pair(0, 0), 48, _c2);
        createText(getLibName(_libs.at(_idxCurrentLib)), std::make_pair(512, 350), std::make_pair(0, 0), 48, _c1);
        createText(std::string("Username: [ ") + _username + std::string(" ]"), std::make_pair(512, 100), std::make_pair(0, 0), 24, _c2);
    }
    if (_toDo.first == PSEUDO) {
        usernameManagement(input);
        createText(getLibName(_games.at(_idxCurrentGame)), std::make_pair(512, 512), std::make_pair(0, 0), 48, _c2);
        createText(getLibName(_libs.at(_idxCurrentLib)), std::make_pair(512, 350), std::make_pair(0, 0), 48, _c2);
        createText(std::string("Username: [ ") + _username + std::string(" ]"), std::make_pair(512, 100), std::make_pair(0, 0), 24, _c1);
    }
}

std::string Menu::getName() const
{
    return (_username);
}

void Menu::setName(std::string name)
{
    _username = name;
}

void Menu::displayScores()
{
    int x = 400;
    int y = 720;
    int displayed = 0;

    createText("Scores:", std::make_pair(x, y - 20), std::make_pair(-1, 0), 18, _c3);
    if (!isInMapInd(_scores, _games.at(_idxCurrentGame)))
        return;

    std::vector<std::string> players = extractKeys(_scores.at(_games.at(_idxCurrentGame)));
    std::multimap<int, std::string> multimap;

    for (auto &e : players)
        multimap.insert(std::make_pair(_scores.at(_games.at(_idxCurrentGame)).at(e), e));

    for (auto &&pair : reverse(multimap)) {
        if (++displayed > 5)
            break;
        createText(pair.second, std::make_pair(x, y += 30), std::make_pair(-1, -1), 15, _c3);
        createText(std::to_string(pair.first), std::make_pair(x + 200, y), std::make_pair(-1, -1), 15, _c4);
    }
}

std::string Menu::getLibName(const std::string &lib)
{
    std::smatch m;
    std::regex_search(lib, m, std::regex("lib_arcade_([^/.]+).so$"));

    return std::string(m[1]);
}