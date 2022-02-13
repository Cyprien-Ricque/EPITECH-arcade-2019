/*
** EPITECH PROJECT, 2019
** arcade
** File description:
** arcade
*/

#ifndef OOP_ARCADE_2019_ARCADEERROR_HPP
#define OOP_ARCADE_2019_ARCADEERROR_HPP

#include <exception>
#include <string>

class arcadeError : public std::exception
{
public:
    arcadeError(std::string lib, std::string origin, std::string message);

    void displayError() const;
    std::string getLib() const;
    std::string getOrigin() const;
    std::string getMessage() const;
private:
    std::string _lib;
    std::string _origin;
    std::string _message;
};

class errorLibs : public arcadeError
{
public:
    explicit errorLibs(std::string origin, std::string message);
};

class directoryError : public arcadeError
{
public:
    explicit directoryError(std::string origin);
};

class invalidArguments : public arcadeError
{
public:
    explicit invalidArguments(std::string message);
};

class fatalError : public std::exception
{
public:
    explicit fatalError(const arcadeError& error);
    void displayError() const;
private:
    std::string _message;
    std::string _lib;
    std::string _origin;
};

class bufferUninit : public arcadeError
{
public:
    bufferUninit(std::string lib, std::string origin);
};

#endif //OOP_ARCADE_2019_ARCADEERROR_HPP
