/*
** EPITECH PROJECT, 2019
** Arcade
** File description:
** Arcade
*/

#ifndef OOP_ARCADE_2019_QIX_HPP
#define OOP_ARCADE_2019_QIX_HPP

#include "IGameModule.hpp"
#include "GameEngine.hpp"
#include "Player.hpp"
#include "Sparks.hpp"
#include "QixMonster.hpp"
#include "Fire.hpp"
#include "Map.hpp"
#include "Clock.hpp"
#define WIN 0
#define LOSE 1
#define PLAYING 2

class Qix : public IGameModule {
    public:
        Qix();
        ~Qix() override;

        void init() override;
        void run(char input, size_t smoothness) override;

        std::vector<std::vector<color_t>> getFramebuffer() const override;
        std::vector<text_t> getTexts() const override;
        std::vector<std::pair<std::string, float>> getSoundsStart() const override;
        std::vector<std::string> getSoundsStop() const override;

        int getScore() const override;
        bool isOver() const override;

    private:
        bool collisionSparks(std::vector<Sparks> s, float smoothness);
        void createText(std::string text, std::pair<int, int> pos,
            std::pair<int, int> anchor, int size, color_t c);

        std::pair<int, int> _bfSize;

        std::vector<std::vector<color_t>> _bf;
        std::vector<text_t> _texts;
        std::vector<std::pair<std::string, float>> _soundsStart;
        std::vector<std::string> _soundsStop;

        int _score;
        bool _over;

        Map _map;
        Player _player;
        QixMonster _qix;
        //Fire _fire;
        std::vector<Sparks> _sparks;
        char _status;
        text_t _text;
        Clock _clock;

};

#endif // OOP_ARCADE_2019_QIX_HPP