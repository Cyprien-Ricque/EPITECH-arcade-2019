/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** OOP_arcade_2019,
*/

#include "sfml.hpp"

extern "C" IGraphicalModule *newInstance()
{
    return new SFML();
}

extern "C" void destroyInstance(IGraphicalModule *sfml)
{
    delete sfml;
}

SFML::SFML()
{
}

SFML::~SFML()
{
    for (auto &i : this->_soundList) {
        delete i.second.first;
    }
}

/* Display */

void SFML::createWindow(int x, int y, int &ac __attribute__((unused)), char **av __attribute__((unused)))
{
    _window = new sf::RenderWindow(sf::VideoMode(x, y), "Arcade", sf::Style::Titlebar | sf::Style::Close);
    _window->setPosition({int(sf::VideoMode::getDesktopMode().width / 2 - x / 2), int(sf::VideoMode::getDesktopMode().height / 2 - y / 2)});

    _size.first = x;
    _size.second = y;

    _coef = 1;
    _sprite.setPosition(0, 0);
    _image.create(_size.first, _size.second, sf::Color(0, 0, 0));
}

void SFML::closeWindow()
{
    _window->close();
}

void SFML::display()
{
    _window->display();
    _window->clear();
}

void SFML::drawFramebuffer(std::vector<std::vector<color_t>> bf)
{
    _coef = 1;
    _sizeAdd.first = _size.first / 2 - bf.at(0).size() / 2;
    _sizeAdd.second = _size.second / 2 - bf.size() / 2;
    while (static_cast<int>(bf.size()) > _size.second &&
        static_cast<int>(bf.at(0).size()) > _size.first) {
        reduceMe(bf);
        _coef *= 2;
    }
    vectorToBuffer(bf);
    _texture.loadFromImage(_image);
    _sprite.setTexture(_texture);
    _sprite.setPosition(_sizeAdd.first, _sizeAdd.second);
    _window->draw(_sprite);
}

void SFML::drawText(text_t t)
{
    t._fontSize /= _coef;
    t._pos.first /= _coef;
    t._pos.first += _sizeAdd.first;
    t._pos.second /= _coef;
    t._pos.second += _sizeAdd.second;
    _font.loadFromFile(t._font);
    _text.setString(t._text);
    _text.setFont(_font);
    _text.setCharacterSize(t._fontSize);
    _text.setFillColor(sf::Color(t._color.r, t._color.g, t._color.b, t._color.a));

    _fakeText.setString("pA");
    _fakeText.setFont(_font);
    _fakeText.setCharacterSize(t._fontSize);
    _fakeText.setFillColor(sf::Color(t._color.r, t._color.g, t._color.b, t._color.a));

    auto size = std::make_pair(_text.getGlobalBounds().width, _fakeText.getGlobalBounds().height);
    if (t._anchor.first == CENTER)
        size.first /= 2;
    if (t._anchor.second == CENTER)
        size.second /= 2;
    if (t._anchor.first == LEFT)
        size.first = 0;
    if (t._anchor.second == TOP)
        size.second = 0;

    _text.setPosition((t._pos.first - size.first), (t._pos.second - size.second));
    _window->draw(_text);
}

size_t SFML::getSmoothness() const
{
    return 1;
}

/* Input */

char SFML::getInput() const
{
    sf::Event event{};
    char input = -1;

    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return (0);
        if (event.type == sf::Event::KeyPressed && (event.key.code >= 71 && event.key.code <= 74))
            input = (static_cast<char>(event.key.code - 66));
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            input = 1;
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace)
            input = 2;
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            input = 3;
        if (event.type == sf::Event::KeyPressed && (event.key.code >= 0 && event.key.code <= 26))
            input = static_cast<char>(event.key.code + 'a');
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            input = (static_cast<char>(' '));
    }
    return (input);
}

/* Sound */

void SFML::stopSound(std::string sound)
{
    if (this->_soundList.count(sound) <= 0)
        return;
    this->_soundList.at(sound).first->stop();
    delete this->_soundList.at(sound).first;
}

void SFML::playSound(std::string sound)
{
    if (this->_soundList.count(sound) > 0 and this->_soundList.at(sound).first->getStatus() == sf::Music::Playing)
        return;

    auto *newMusic = new sf::Music();

    if (!newMusic->openFromFile(sound + ".wav")) {
        delete newMusic;
        return;
    }
    this->_soundList.insert(std::make_pair(sound, std::make_pair(newMusic, 50.0)));
    this->_soundList[sound].first->play();
    this->_soundList[sound].first->setVolume(this->_soundList[sound].second);
}

void SFML::setVolume(std::string sound, float volume)
{
    if (this->_soundList.count(sound) <= 0)
        return;
    this->_soundList.at(sound).second = volume;
    this->_soundList.at(sound).first->setVolume(volume);
}

float SFML::getVolume(std::string sound) const
{
    if (this->_soundList.count(sound) <= 0)
        return (0);
    return (this->_soundList.at(sound).second);
}

void SFML::stopAllSounds()
{
    for (auto &i : this->_soundList) {
        i.second.first->stop();
    }
}

void SFML::vectorToBuffer(std::vector<std::vector<color_t>> &bf)
{
    for (size_t j = 0; (j < bf.size() || j < _image.getSize().y) && j < _image.getSize().y; ++j)
        for (size_t i = 0; (i < bf.at(0).size() || i < _image.getSize().x) && i < _image.getSize().x; ++i)
            j < bf.size() && i < bf.at(0).size() ? _image.setPixel(i, j, sf::Color(bf.at(j).at(i).r, bf.at(j).at(i).g, bf.at(j).at(i).b)) : _image.setPixel(i, j, sf::Color(0, 0, 0));
}

std::pair<int, int> SFML::getRealPos(std::pair<int, int> &pos, std::vector<std::vector<color_t>> &bf)
{
    return std::make_pair(pos.first * _size.first / bf.at(0).size(),
        pos.second * _size.second / bf.size());
}

void SFML::reduceMe(std::vector<std::vector<color_t>> &bf)
{
    for (int j = 0; j < static_cast<int>(bf.size()); ++j) {
        bf.erase(bf.begin() + j);
        for (int i = 0; i < static_cast<int>(bf.at(0).size()); ++i)
            bf.at(j).erase(bf.at(j).begin() + i);
    }
}

bool SFML::exists(const std::string &name)
{
    return (access(name.c_str(), F_OK) != -1);
}