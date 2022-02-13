/*
** EPITECH PROJECT, 2019
** Arcade
** File description:
** Arcade
*/

#ifndef OOP_ARCADE_2019_ARCAD_HPP
#define OOP_ARCADE_2019_ARCAD_HPP

#include "DLLoader.hpp"
#include "IGraphicalModule.hpp"
#include "IGameModule.hpp"
#include "arcadeError.hpp"
#include "Menu.hpp"
#include <dirent.h>
#include <regex>
#include <fstream>
#include <cstdio>
#include <unistd.h>

class Arcade {
    public:
        Arcade(std::string libName, int &ac, char **av);
        ~Arcade() = default;

        enum _switch {
            NEXT,
            PREV
        };

        void switchLib(_switch st);
        void switchGame(_switch st);
        void switchMenu();

        void findLibs();
        void findGames();

        void init();
        void initGame();
        void initLib();
        void endLib();
        void endGame();

        void run();
        bool inputManager(char &c);
        bool menuManager();
        void setMenu();

    private:
        void setCurrentLib(const std::string &);
        void setFirstLib(const std::string &);
        void setCurrentGame(const std::string &);

        bool exists(const std::string& name);

        /* Libs / Games Management */
        IGraphicalModule *_displayModule;
        IGameModule *_gameModule;
        std::pair<std::string, DLLoader<IGraphicalModule *> *> _currentLib;
        std::pair<std::string, DLLoader<IGameModule *> *> _currentGame;

        std::map<std::string, DLLoader<IGraphicalModule *> *> _libs;
        std::map<std::string, DLLoader<IGameModule *> *> _games;

        Menu *_menu;

        std::map<std::string, std::map<std::string, int>> _scores;
        std::string _currentName;
        int _currentScore;

        bool _ignoreInput;

        Clock _clock;

        int &_ac;
        char **_av;
};

#endif /* OOP_ARCADE_2019_ARCAD_HPP */