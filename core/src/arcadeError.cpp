/*
** EPITECH PROJECT, 2019
** arcade
** File description:
** arcade
*/

#include <arcadeError.hpp>
#include <iostream>
#include <utility>

arcadeError::arcadeError(std::string lib, std::string origin, std::string message) :
            _lib(std::move(lib)), _origin(std::move(origin)), _message(std::move(message))
{
}

void arcadeError::displayError() const
{
    std::cerr << this->_lib << " (" << this->_origin << "): " << this->_message << std::endl;
}

std::string arcadeError::getLib() const
{
    return (this->_lib);
}

std::string arcadeError::getOrigin() const
{
    return (this->_origin);
}

std::string arcadeError::getMessage() const
{
    return (this->_message);
}

errorLibs::errorLibs(std::string origin, std::string message) : arcadeError("core", std::move(origin), std::move(message))
{
}

directoryError::directoryError(std::string origin) : arcadeError("core", std::move(origin), "cannot open directory")
{
}

invalidArguments::invalidArguments(std::string message) :
                arcadeError("Core", "main", std::move(message))
{
}

fatalError::fatalError(const arcadeError& error)
{
    this->_message = error.getMessage();
    this->_lib = error.getLib();
    this->_origin = error.getOrigin();
}

void fatalError::displayError() const
{
    std::cerr << "!! Fatal Error !! " << this->_lib << " (" << this->_origin << "): " << this->_message << std::endl;
}

bufferUninit::bufferUninit(std::string lib, std::string origin) :
                    arcadeError(std::move(lib), std::move(origin), "buffer not initialised")
{
}