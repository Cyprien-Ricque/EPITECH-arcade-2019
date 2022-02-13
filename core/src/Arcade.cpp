/*
** EPITECH PROJECT, 2019
** arcade
** File description:
** arcade,
*/

#include "Arcade.hpp"

Arcade::Arcade(std::string libName, int &ac, char **av) : _menu(new Menu),
    _ignoreInput(false), _ac(ac), _av(av)
{
    try {
        findLibs();
        findGames();
    } catch (directoryError const &d) {
        throw fatalError(d);
    } catch (errorLibs const &e) {
        throw errorLibs(e);
    }
    std::fstream _fileScore(".scoreArcade");

    if (_fileScore.is_open()) {
        std::string username;
        std::string score;
        std::string game;
        while (std::getline(_fileScore, username, '|') &&
            std::getline(_fileScore, score, '|') &&
            std::getline(_fileScore, game)) {
            this->_scores[game][username] = std::atoi(score.c_str());
        }
    }
    try {
        if (libName.at(0) != '/' && libName.at(0) != '.' &&
            libName.at(0) != '~')
            libName = std::string("./") + libName;
        if (isInMapInd(_libs, libName))
            setCurrentLib(libName);
        else
            setFirstLib(libName);
    } catch (errorLibs const &e) {
        throw fatalError(e);
    }
}

void Arcade::setFirstLib(const std::string &libPath)
{
    if (!exists(libPath))
        throw errorLibs("setFirstLib",
            "libpath not found"); // la lib en paramètre n'existe pas
    _currentLib.first = libPath;
    _currentLib.second = new DLLoader<IGraphicalModule *>(libPath);
}

void Arcade::setCurrentLib(const std::string &libName)
{
    auto it = _libs.find(libName);

    if (it == _libs.end())
        throw errorLibs("setCurrentLib",
            "lib not loaded"); // la lib demandée n'existe pas
    _currentLib.first = it->first;
    _currentLib.second = it->second;
}

void Arcade::setCurrentGame(const std::string &libName)
{
    auto it = _games.find(libName);

    if (it == _games.end())
        throw errorLibs("setCurrentGame",
            "game not loaded"); // la lib demandée n'existe pas
    _currentGame.first = it->first;
    _currentGame.second = it->second;
}

void Arcade::findLibs()
{
    DIR *dir = opendir("./lib/");
    struct dirent *ent;
    std::string libPath;

    if (!dir)
        throw directoryError("findLibs");
    while ((ent = readdir(dir))) {
        if (!std::regex_match(ent->d_name,
            std::regex("^lib_arcade_[^\\s]+.so$")))
            continue;
        libPath = std::string(std::string("./lib/") + ent->d_name);
        _libs[libPath] = new DLLoader<IGraphicalModule *>(libPath);
    }
    closedir(dir);
}

void Arcade::findGames()
{
    DIR *dir = opendir("./games/");
    struct dirent *ent;
    std::string libPath;

    if (!dir)
        throw directoryError("findLibs");
    while ((ent = readdir(dir))) {
        if (!std::regex_match(ent->d_name,
            std::regex("^lib_arcade_[^\\s]+.so$")))
            continue;
        libPath = std::string(std::string("./games/") + ent->d_name);
        _games[libPath] = new DLLoader<IGameModule *>(libPath);
    }
    closedir(dir);
}

void Arcade::switchLib(Arcade::_switch st)
{
    auto it = _libs.find(_currentLib.first);

    if (_libs.size() == 1)
        return;

    endLib();
    if (it == _libs.end()) {
        setCurrentLib(_libs.begin()->first);
    } else if (st == NEXT) {
        if (it == --_libs.end()) {
            setCurrentLib(_libs.begin()->first);
        } else {
            setCurrentLib((++it)->first);
        }
    } else {
        if (it == _libs.begin())
            setCurrentLib((--_libs.end())->first);
        else
            setCurrentLib((--it)->first);
    }
    initLib();
}

void Arcade::switchGame(Arcade::_switch st)
{
    auto it = _games.find(_currentGame.first);

    if (_currentGame.first == "menu")
        return;
    if (_games.size() == 1) {
        std::cerr << "Only one game is loaded" << std::endl;
        return;
    }
    endGame();
    if (it == _games.end())
        setCurrentGame(_games.begin()->first);
    else if (st == NEXT) {
        if (it == --_games.end())
            setCurrentGame(_games.begin()->first);
        else
            setCurrentGame((++it)->first);
    } else {
        if (it == _games.begin())
            setCurrentGame((--_games.end())->first);
        else
            setCurrentGame((--it)->first);
    }
    initGame();
}

void Arcade::setMenu()
{
    _menu->setGames(extractKeys(_games));
    _menu->setLibs(extractKeys(_libs));
    _menu->setScores(_scores);
    _menu->setName(_currentName);
    _gameModule = dynamic_cast<IGameModule *>(_menu);
    _currentGame.first = "menu";
}

void Arcade::switchMenu()
{
    endGame();
    setMenu();
    initGame();
}

void Arcade::initGame()
{
    if (_currentGame.first != "menu") {
        _currentGame.second->open();
        _gameModule = _currentGame.second->getInstance();
    }
    _gameModule->init();

    if (!_currentName.empty() && (!isInMapInd(_scores, _currentGame.first) ||
        !isInMapInd(_scores[_currentGame.first], _currentName)))
        _scores[_currentGame.first][_currentName] = MIN_SCORE;
}

void Arcade::initLib()
{
    _currentLib.second->open();
    _displayModule = _currentLib.second->getInstance();
    _displayModule->createWindow(1024, 1024, _ac, _av);
}

void Arcade::endLib()
{
    _displayModule->stopAllSounds();
    _displayModule->closeWindow();
    _currentLib.second->close(_displayModule);
}

void Arcade::endGame()
{
    _displayModule->stopAllSounds();
    if (_currentGame.first != "menu")
        _currentGame.second->close(_gameModule);
}

void Arcade::run()
{
    char input = _displayModule->getInput();
    std::vector<text_t> texts;
    std::vector<std::pair<std::string, float>> musicStart;
    std::vector<std::string> musicStop;

    while (inputManager(input) &&
        (_currentGame.first != "menu" || menuManager())) {
        if (_gameModule->isOver())
            switchMenu();

        _gameModule->run(input, _displayModule->getSmoothness());
        _currentScore = _gameModule->getScore();

        if (!_currentName.empty() and _currentGame.first != "menu")
            _scores.at(_currentGame.first).at(_currentName) = _scores.at(_currentGame.first).at(_currentName) <
                    _currentScore ? _currentScore : _scores.at(_currentGame.first).at(_currentName);

        musicStop = _gameModule->getSoundsStop();
        for (auto &e : musicStop)
            _displayModule->stopSound(e);

        musicStart = _gameModule->getSoundsStart();
        for (auto &e : musicStart) {
            _displayModule->playSound(e.first);
            _displayModule->setVolume(e.first, e.second);
        }
        _displayModule->drawFramebuffer(_gameModule->getFramebuffer());
        texts = _gameModule->getTexts();
        for (auto &t : texts)
            _displayModule->drawText(t);
        input = _displayModule->getInput();
        _displayModule->display();
        _clock.wait();
    }
    endGame();
    endLib();
}

bool Arcade::menuManager()
{
    auto todo = _menu->toDo();
    if (todo.first == Menu::GAME && !todo.second.empty()) {
        endGame();
        setCurrentGame(todo.second);
        initGame();
    }
    if (todo.first == Menu::LIB && !todo.second.empty()) {
        endLib();
        setCurrentLib(todo.second);
        initLib();
    }
    _currentName = _menu->getName();
    _ignoreInput = todo.first == Menu::PSEUDO;
    return (true);
}

bool Arcade::inputManager(char &c)
{
    if (!_ignoreInput && (c == 'p' || c == 'o' || c == 'm' || c == 'l')) {
        if (c == 'p')
            switchLib(NEXT);
        if (c == 'o')
            switchLib(PREV);
        if (c == 'm')
            switchGame(NEXT);
        if (c == 'l')
            switchGame(PREV);
    }
    if (c == 1 && !_ignoreInput) {
        c = -1;
        switchMenu();
    }
    if (c == 'r' && !_ignoreInput) {
        c = -1;
        _gameModule->init();
    }
    if (c == 0 || (!_ignoreInput && c == 'q')) {
        c = -1;
        return (false);
    }
    return (true);
}

bool Arcade::exists(const std::string &name)
{
    return (access(name.c_str(), F_OK) != -1);
}