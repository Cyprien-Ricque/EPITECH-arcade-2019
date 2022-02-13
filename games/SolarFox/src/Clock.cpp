/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** OOP_arcade_2019,
*/

#include "Clock.hpp"

Clock::Clock()
{
    _start = std::chrono::high_resolution_clock::now();
    _current = std::chrono::high_resolution_clock::now();
    _prev = std::chrono::high_resolution_clock::now();
}

double Clock::getElapsedTime()
{
    _current = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = _current - _prev;
    return diff.count();
}

bool Clock::timePassed(double limit)
{
    return getElapsedTime() >= limit;
}

double Clock::getElapsedTimeFromStart()
{
    _current = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = _current - _start;
    return diff.count();
}

void Clock::mark()
{
    _prev = _current;
    _current = std::chrono::high_resolution_clock::now();
}

void Clock::wait(double limit)
{
    mark();
    while (!timePassed(limit));
}
