/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** OOP_arcade_2019,
*/

#ifndef OOP_ARCADE_2019_OPENGL_HPP
#define OOP_ARCADE_2019_OPENGL_HPP

#include "IGraphicalModule.hpp"
#include "GL/freeglut.h"
#include "GL/gl.h"
//#include <ft2build.h>
//#include <freetype/config/ftconfig.h>
//#include <freetype/freetype.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <cstring>
#include <sndfile.h>
#include <iomanip>
#include <map>
#include <algorithm>
#include <unistd.h>

int _key = -1;
void displayUnused(void);
void keyboard(unsigned char touche, int x __attribute__((unused)), int y __attribute__((unused)));
void keyboardSpecial(int touche, int x __attribute__((unused)), int y __attribute__((unused)));

class opengl : public IGraphicalModule {
    public:
        opengl();
        ~opengl();

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
        std::vector<std::vector<color_t>> _bf;
        std::pair<int, int> _windowSize;
        void reduceMe(std::vector<std::vector<color_t>> &bf);

        bool InitOpenAL();
        void GetDevices(std::vector<std::string> &Devices);

        std::map<std::string, std::pair<ALuint, ALuint>> _sounds;
        void ShutdownOpenAL();

        int _coef;
        bool exists(const std::string &name);
};

template<typename T, typename L>
std::vector<T> extractKeys(std::map<T, L> const &map)
{
    std::vector<T> vector;

    for (auto const &element : map)
        vector.push_back(element.first);
    return vector;
}

template<typename T, typename L>
bool isInMapInd(std::map<T, L> const &map, T ind)
{
    std::vector<T> vector = extractKeys(map);

    return std::find(vector.begin(), vector.end(), ind) != vector.end();
}

#endif //OOP_ARCADE_2019_OPENGL_HPP
