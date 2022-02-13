/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** OOP_arcade_2019,
*/

#ifndef OOP_ARCADE_2019_SFML_HPP
#define OOP_ARCADE_2019_SFML_HPP

#include "IGraphicalModule.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <unistd.h>

class SFML : public IGraphicalModule {
    public:
        SFML();
        ~SFML();

        /* Display */
        void createWindow(int x, int y, int &ac, char **av) override;
        void closeWindow() override;
        void display() override;
        void drawFramebuffer(std::vector<std::vector<color_t>>) override;
        void drawText(text_t) override;
        size_t getSmoothness() const override;

        /* Input */
        char getInput() const override;

        /* Sound */
        void stopSound(std::string sound) override;
        void playSound(std::string sound) override;
        void setVolume(std::string sound, float volume) override;
        float getVolume(std::string sound) const override;
        void stopAllSounds() override;

    private:
        void vectorToBuffer(std::vector<std::vector<color_t>>&);
        std::pair<int, int> getRealPos(std::pair<int, int> &pos, std::vector<std::vector<color_t>> &bf);
        void reduceMe(std::vector<std::vector<color_t>> &bf);

        sf::RenderWindow *_window;
        std::pair<int, int> _size;

        /* Display */
        // Buffer
        sf::Image _image;
        sf::Texture _texture;
        sf::Sprite _sprite;

        // Text
        sf::Font _font;
        sf::Text _text;
        sf::Text _fakeText;

        std::map<std::string, std::pair<sf::Music *, float>> _soundList;

        std::pair<int, int> _sizeAdd;
        int _coef;
        bool exists(const std::string &name);
};

#endif //OOP_ARCADE_2019_SFML_HPP
