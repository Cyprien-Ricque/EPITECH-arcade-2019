/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Created by emilien
*/

#include "solarFox.hpp"
#include "GameEngine.hpp"
#include "arcadeError.hpp"

SolarFox::SolarFox()
{
    this->_initGame = false;
}

SolarFox::~SolarFox()
{
}

void SolarFox::init()
{
    std::vector<color_t> line;
    auto size = std::make_pair(1024, 1024);

    this->_texts.clear();
    this->_objective.clear();
    this->_fire.clear();
    this->_starship.reset();
    this->_bf_fire[0] = this->_openBitmap("games/assets/emilien_SolarFox_fire.bmp");
    this->_bf_enemi[0] = this->_openBitmap("games/assets/emilien_SolarFox_enemi.bmp");
    this->_bf_bullet[0] = this->_openBitmap("games/assets/emilien_SolarFox_bullet.bmp");
    this->_bf_starship[0] = this->_openBitmap("games/assets/emilien_SolarFox_starship.bmp");
    this->_bf_badPowerup = this->_openBitmap("games/assets/emilien_SolarFox_badPowerup.bmp");
    this->_bf_objective = this->_openBitmap("games/assets/emilien_SolarFox_objective.bmp");
    this->invertDir = false;
    this->_createBuffers();
    line.reserve(size.first);
    _bf.resize(size.second, std::vector<color_t>(size.first, {0, 0, 0, 255}));
    this->_initGame = true;
    this->_level = 1;
    this->_indicScore = 20;
    this->_initLevel(1);
    this->_difficulty = 150;
    this->_status = 0;
    this->_spaceshipOk = true;
    for (int a = 0; a < 4; ++a) {
        this->pos_enemi[a][0] = this->origin_enemi[a][0];
        this->pos_enemi[a][1] = this->origin_enemi[a][1];
    }
    for (auto &a : this->_bullets)
        a.reset();
}

void SolarFox::run(char input, size_t smoothness)
{
    GameEngine::clearBuffer(this->_bf);
    if (_status == 2) {
        this->_createText("YOU LOST ..",std::make_pair(static_cast<int>(1024) / 2, static_cast<int>(1024) / 3), std::make_pair(0, 0), 50, {230, 230, 230, 255});
        this->_createText("Press R to restart and escape to go back to the menu", std::make_pair(static_cast<int>(1024) / 2, (static_cast<int>(1024) / 3) * 2), std::make_pair(0, 0), 20, {230, 230, 230, 255});
        return;
    }
    this->_clock.wait();
    this->_updateObjective();
    this->_drawStarship();
    this->_createFire(input);
    this->_moveEnemis();
    this->_bulletsUpdate();
    this->_starship.updateStarshipDirection(input);
    this->_spaceshipOk = this->_starship.moveStarship(input);
    this->_updateFire();
    if (!this->_spaceshipOk)
        this->_status = 1;
    this->_smooth = smoothness != 1;
    if (this->_smooth)
        this->_clock.wait();
}

void SolarFox::_updateObjective()
{
    for (auto &c : this->_objective) {
        if (c.badPowerup)
            GameEngine::putIn(this->_bf_badPowerup, this->_bf, c.getPosition());
        int objectivePosition[2] = {c.getPosition().first, c.getPosition().second};
        int pointsObjective[4][2] = {{objectivePosition[0], objectivePosition[1]},              //Top left
                                     {objectivePosition[0] + 48, objectivePosition[1]},         //Top right
                                     {objectivePosition[0], objectivePosition[1] + 48},         //Down left
                                     {objectivePosition[0] + 48, objectivePosition[1] + 48}};   //Down right
        for (auto &a : this->_fire) {
            int firePosition[2] = {a.getPosition().first, a.getPosition().second};
            int pointFire[4][2] = {{firePosition[0] + 5, firePosition[1]},
                                   {firePosition[0] + 11, firePosition[1]},
                                   {firePosition[0] + 5, firePosition[1] + 16},
                                   {firePosition[0] + 11, firePosition[1] + 16}};
            for (auto &b : pointFire) {
                if (b[0] >= pointsObjective[0][0] && b[0] <= pointsObjective[3][0] &&
                    b[1] >= pointsObjective[0][1] && b[1] <= pointsObjective[3][1]) {
                    if (!c.badPowerup) {
                        c.active = false;
                        a.setOff();
                        this->_score += this->_indicScore;
                    } else {
                        this->_status = 2;
                    }
                }
            }
        }
        if (c.active && !c.badPowerup)
            GameEngine::putIn(this->_bf_objective, this->_bf, c.getPosition());
    }
    this->_updateLevels();
}

void SolarFox::_updateLevels()
{
    for (auto &obj : this->_objective) {
        if (obj.active)
            return;
    }
    this->_indicScore += 20;
    this->_difficulty -= 20;
    this->_score += 200;
    if (this->_difficulty < 40)
        this->_difficulty = 40;
    switch (this->_level) {
        case 1:
            this->_objective.clear();
            ++this->_level;
            this->_initLevel(2);
            break;
        case 2:
            this->_objective.clear();
            this->_initLevel(3);
            break;
        default:
            break;
    }
}

void SolarFox::_initLevel(char level)
{
    const int tabLevel1[3][3] = {{512, 304, 0}, {512, 512, 1}, {512, 704, 0}};
    const int tabLevel2[6][3] = {{304, 304, 0}, {304, 512, 1}, {304, 704, 0},
                                 {704, 304, 0}, {704, 512, 1}, {704, 704, 0}};
    const int tabLevel3[9][3] = {{304, 304, 0}, {304, 512, 1}, {304, 704, 0},
                                 {512, 304, 0}, {512, 512, 1}, {512, 704, 0},
                                 {704, 304, 0}, {704, 512, 1}, {704, 704, 0}};

    if (level == 1)
        for (auto i : tabLevel1) {
            Objective newObjective;

            if (i[2] == 1) {
                newObjective.badPowerup = true;
                newObjective.active = false;
            } else {
                newObjective.active = true;
            }
            newObjective.initObjective(i[0], i[1]);
            this->_objective.push_back(newObjective);
        }
    else if (level == 2)
        for (auto i : tabLevel2) {
            Objective newObjective;

            if (i[2] == 1) {
                newObjective.badPowerup = true;
                newObjective.active = false;
            } else {
                newObjective.active = true;
            }
            newObjective.initObjective(i[0], i[1]);
            this->_objective.push_back(newObjective);
        }
    else
        for (auto i : tabLevel3) {
            Objective newObjective;

            if (i[2] == 1) {
                newObjective.badPowerup = true;
                newObjective.active = false;
            } else {
                newObjective.active = true;
            }
            newObjective.initObjective(i[0], i[1]);
            this->_objective.push_back(newObjective);
        }
}

void SolarFox::_updateFire()
{
    if (this->_fire.empty())
        return;
    auto it = this->_fire.begin();

    while (it != this->_fire.end()) {
        it->updatePosition();
        if (!it->getInit()) {
            it = this->_fire.erase(it);
        } else {
            GameEngine::putIn(this->_bf_fire[it->getDirection()], this->_bf, it->getPosition());
            ++it;
        }
    }
}

void SolarFox::_createFire(char input)
{
    if (input == 'f') {
        Fire newFire;
        std::pair<int, int> oui = this->_starship.getPositions();

        newFire.initFire(oui.first, oui.second, static_cast<char>(this->_starship.getDirection()));
        this->_fire.push_back(newFire);
    }
}

void SolarFox::_drawStarship()
{
    GameEngine::putIn(this->_bf_starship[this->_starship.getDirection()], this->_bf, this->_starship.getPositions());
}

void SolarFox::_bulletsUpdate()
{
    this->_checkSpaceshipDeath();
    for (auto & _bullet : this->_bullets) {
        if (!this->_bullets->isInit() && std::rand() % this->_difficulty == 0) {
            char enemi = std::rand() % 4;
            if (enemi < 2)
                _bullet.initBullet(enemi, pos_enemi[(int)enemi][0]);
            else
                _bullet.initBullet(enemi, pos_enemi[(int)enemi][1]);
        }
        if (_bullet.isInit()) {
            GameEngine::putIn(this->_bf_bullet[static_cast<int>(_bullet.getSide())], this->_bf, _bullet.getPosition());
            _bullet.updatePosition();
        }
    }
}

void SolarFox::_moveEnemis()
{
    int counter = 0;

    for (auto &a : pos_enemi) {
        GameEngine::putIn(this->_bf_enemi[counter], this->_bf, std::make_pair(a[0], a[1]));
        ++counter;
    }
    this->_updateEnemiesPosition(this->pos_enemi);
}

std::vector<std::vector<color_t>> SolarFox::getFramebuffer() const
{
    return (this->_bf);
}

std::vector<text_t> SolarFox::getTexts() const
{
    return (this->_texts);
}

std::vector<std::pair<std::string, float>> SolarFox::getSoundsStart() const
{
    return (this->_soundsStart);
}

std::vector<std::string> SolarFox::getSoundsStop() const
{
    return (this->_soundsStop);
}

int SolarFox::getScore() const
{
    return (this->_score);
}

bool SolarFox::isOver() const
{
    return (false);
}

std::vector<std::vector<color_t>> SolarFox::_openBitmap(const std::string &file)
{
    bitmapReader bufferR(file);

    if (!bufferR.initBMP()) {
        throw bufferUninit("SolarFox", "init");
    }
    return (bufferR.returnVector());
}

void SolarFox::_updateEnemiesPosition(int pos[4][2])
{
    int value = 0;

    //0 et 1 de droite à gauche
    //2 et 3 de haut en bas
    if (this->invertDir)
        value = -16;
    else
        value = 16;
    pos[0][0] += value;
    pos[1][0] -= value;
    pos[2][1] += value;
    pos[3][1] -= value;
    if (pos[0][0] >= 912)
        this->invertDir = true;
    else if (pos[0][0] <= 32)
        this->invertDir = false;
}

void SolarFox::_createBuffers()
{
    GameEngine::rotateBuffer180(this->_bf_enemi[0]);
    GameEngine::rotateBuffer180(this->_bf_bullet[0]);
    GameEngine::rotateBuffer180(this->_bf_starship[0]);
    //GameEngine::rotateBuffer180(this->_bf_fire[0]);

    //Setup buffer positions for the enemi object
    this->_bf_enemi[2] = GameEngine::returnRotateBuffer90(this->_bf_enemi[0]);
    this->_bf_enemi[1] = GameEngine::returnRotateBuffer90(this->_bf_enemi[2]);
    this->_bf_enemi[3] = GameEngine::returnRotateBuffer90(this->_bf_enemi[1]);

    //Setup buffer position for the bullet object
    this->_bf_bullet[2] = GameEngine::returnRotateBuffer90(this->_bf_bullet[0]);
    this->_bf_bullet[1] = GameEngine::returnRotateBuffer90(this->_bf_bullet[2]);
    this->_bf_bullet[3] = GameEngine::returnRotateBuffer90(this->_bf_bullet[1]);

    //Setup buffer position for the fire object
    this->_bf_fire[3] = GameEngine::returnRotateBuffer90(this->_bf_fire[0]);
    this->_bf_fire[1] = GameEngine::returnRotateBuffer90(this->_bf_fire[3]);
    this->_bf_fire[2] = GameEngine::returnRotateBuffer90(this->_bf_fire[1]);

    //Setup buffer positions for the starship object
    this->_bf_starship[2] = GameEngine::returnRotateBuffer90(this->_bf_starship[0]);
    this->_bf_starship[1] = GameEngine::returnRotateBuffer90(this->_bf_starship[2]);
    this->_bf_starship[3] = GameEngine::returnRotateBuffer90(this->_bf_starship[1]);
    GameEngine::rotateBuffer180(this->_bf_starship[0]);
    GameEngine::rotateBuffer180(this->_bf_starship[1]);
}

void SolarFox::_checkSpaceshipDeath()
{
    int spaceshipPosition[2] = {this->_starship.getPositions().first, this->_starship.getPositions().second};
    int pointsSpaceship[2][2] = {{spaceshipPosition[0], spaceshipPosition[1]},              //Top left
                                 {spaceshipPosition[0] + 48, spaceshipPosition[1] + 48}};   //Down right

    for (auto &a : this->_bullets) {
        int bulletPosition[2] = {a.getPosition().first, a.getPosition().second};
        int pointBullet[2][2] = {{bulletPosition[0], bulletPosition[1]},
                                 {bulletPosition[0] + 16, bulletPosition[1] + 16}};
        for (auto &b : pointBullet) {
            if (b[0] >= pointsSpaceship[0][0] && b[0] <= pointsSpaceship[1][0] &&
                b[1] >= pointsSpaceship[0][1] && b[1] <= pointsSpaceship[1][1]) {
                this->_status = 2;
            }
        }
        for (auto &c : this->_fire) {
            int firePosition[2] = {c.getPosition().first, c.getPosition().second};
            int pointFire[2][2] = {{firePosition[0], firePosition[1]},
                                    {firePosition[0], firePosition[1]}};
            for (auto &d : pointFire) {
                if (d[0] >= pointBullet[0][0] - 16 && d[0] <= pointBullet[1][0] + 32 &&
                    d[1] >= pointBullet[0][1] - 16 && d[1] <= pointBullet[1][1] + 32) {
                    a.reset();
                }
            }
        }
    }
}

void SolarFox::_createText(std::string text, std::pair<int, int> pos, std::pair<int, int> anchor, int size, color_t c)
{
    _text._font = std::string("games/assets/cyprien_menu_arial.ttf");
    _text._text = std::move(text);
    _text._fontSize = size;
    _text._color.r = c.r;
    _text._color.g = c.g;
    _text._color.b = c.b;
    _text._color.a = c.a;
    _text._anchor.first = anchor.first;
    _text._anchor.second = anchor.second;
    _text._pos = pos;
    _texts.push_back(_text);
}


extern "C" IGameModule *newInstance()
{
    return (new SolarFox());
}

extern "C" void destroyInstance(IGameModule *solarfox)
{
    delete solarfox;
}