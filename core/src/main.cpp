/*
** EPITECH PROJECT, 2019
** Arcade
** File description:
** Arcade
*/

#include <cstdlib>
#include <ctime>
#include "Arcade.hpp"
#include "arcadeError.hpp"

void arcade(Arcade &arcade)
{
    arcade.setMenu();
    arcade.initLib();
    arcade.initGame();
    arcade.run();
}

int main(int ac, char **av)
{
    std::srand(std::time(nullptr));
    try {
        if (ac < 2)
            throw invalidArguments("One argument is missing");
        else if (ac > 2)
            throw invalidArguments("Too many arguments");
    } catch (invalidArguments const &e) {
        e.displayError();
        return (84);
    }
    try {
        auto a = Arcade(av[1], ac, av);
        arcade(a);
    } catch (fatalError const &f) {
        f.displayError();
        return (84);
    } catch (std::exception const &oui) {
        std::cerr << "An unexpected unknown fatal error occurs" << std::endl;
        return (84);
    }
    return (0);
}