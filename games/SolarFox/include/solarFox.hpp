/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Created by emilien
*/

#ifndef OOP_ARCADE_2019_SOLARFOX_HPP
#define OOP_ARCADE_2019_SOLARFOX_HPP

#include "IGameModule.hpp"
#include "bitmapReader.hpp"
#include "Objective.hpp"
#include "Starship.hpp"
#include "Bullet.hpp"
#include "Clock.hpp"
#include "Fire.hpp"

#include <cstdlib>

class SolarFox : public IGameModule
{
public:
    SolarFox();
    ~SolarFox() override;

    void init() override;
    void run(char input, size_t smoothness) override;

    std::vector<std::vector<color_t>>getFramebuffer() const override;
    std::vector<text_t> getTexts() const override;
    std::vector<std::pair<std::string, float>> getSoundsStart() const override;
    std::vector<std::string>getSoundsStop() const override;
    int getScore() const override;
    bool isOver() const override;

private:
    //Fonctions
    void _moveEnemis();
    void _updateEnemiesPosition(int [4][2]);
    void _bulletsUpdate();
    void _createBuffers();
    void _checkSpaceshipDeath();
    void _createFire(char);
    void _drawStarship();
    void _updateFire();
    void _updateObjective();
    void _initLevel(char);
    void _updateLevels();
    void _createText(std::string text, std::pair<int, int> pos, std::pair<int, int> anchor, int size, color_t c);

    std::vector<std::vector<color_t>> _openBitmap(const std::string &);

    //Variables
    int pos_enemi[4][2]{{32, 32}, {912, 912}, {912, 32}, {32, 912}};
    int origin_enemi[4][2]{{32, 32}, {912, 912}, {912, 32}, {32, 912}};
    std::vector<std::pair<std::string, float>> _soundsStart;
    std::vector<std::vector<color_t>> _bf_starship[4];
    std::vector<std::vector<color_t>> _bf_bullet[4];
    std::vector<std::vector<color_t>> _bf_fire[4];
    std::vector<std::vector<color_t>> _bf_enemi[4];
    std::vector<std::vector<color_t>> _bf_badPowerup;
    std::vector<std::vector<color_t>> _bf_objective;
    std::vector<std::vector<color_t>> _bf;
    std::vector<Objective> _objective;
    std::vector<std::string> _soundsStop;
    std::vector<text_t> _texts;
    std::vector<Fire> _fire;
    Starship _starship;
    Bullet _bullets[17];
    bool _spaceshipOk;
    bool invertDir{};
    int _status{};
    int _score{};
    Clock _clock;
    bool _initGame;
    char _level;
    int _indicScore;
    int _difficulty;
    bool _smooth;
    text_t _text;
};

#endif //OOP_ARCADE_2019_SOLARFOX_HPP
