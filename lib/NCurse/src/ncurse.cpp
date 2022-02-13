/*
** EPITECH PROJECT, 2020
** ncurse.cpp
** File description:
** OOP_Arcade_2019
*/

#include "ncurse.hpp"

extern "C" IGraphicalModule *newInstance()
{
    return (new NCurse());
}

extern "C" void destroyInstance(IGraphicalModule *ncurses)
{
    delete ncurses;
}

NCurse::NCurse()
{
    _smooth = 16;
}

NCurse::~NCurse()
{
}

void NCurse::resize(int x, int y)
{
    int cofX_tmp = 8;
    int cofY_tmp = 8;

    while (x / cofX_tmp > COLS)
        cofX_tmp *= 2;
    while (y / cofY_tmp > LINES)
        cofY_tmp *= 2;
    while (cofY_tmp <= cofX_tmp)
        cofY_tmp *= 2;
    while (cofY_tmp != cofX_tmp * 2)
        cofX_tmp *= 2;

    if (cofX != cofX_tmp || cofY != cofY_tmp) {

        cofX = cofX_tmp;
        cofY = cofY_tmp;
        wrefresh(_window);
        if ((LINES - (y / cofY)) / 2 < 5)
            _window = newwin((y / cofY) + 1, x / cofX, 0, (COLS - (x / cofX)) / 2);
        else
            _window = newwin((y / cofY) + 1, x / cofX, (LINES - (y / cofY)) / 2, (COLS - (x / cofX)) / 2);
    }
}

void NCurse::createWindow(int x, int y, int &ac __attribute__((unused)), char **av __attribute__((unused)))
{
    setlocale(LC_ALL, "");
    initscr();
    cofX = 8;
    cofY = 8;

    resize(x, y);

    refresh();
    nodelay(_window, TRUE);
    keypad(_window, TRUE);
    curs_set(0);
    noecho();

    start_color();
    use_default_colors();
    init_pair(1, COLOR_YELLOW, -1);
    init_pair(2, COLOR_CYAN, -1);
    init_pair(3, COLOR_RED, -1);
    init_pair(4, COLOR_GREEN, -1);
    init_pair(5, COLOR_MAGENTA, -1);
    init_pair(6, COLOR_WHITE, -1);
    init_pair(7, COLOR_BLUE, -1);
}

void NCurse::closeWindow()
{
    endwin();
}

void NCurse::display()
{
    werase(_window);
}

void NCurse::drawFramebuffer(std::vector<std::vector<color_t>> frameBuffer)
{
    resize(frameBuffer.at(0).size(), frameBuffer.size());

    int y = (static_cast<int>(frameBuffer.size()) / cofY);
    int x = (static_cast<int>(frameBuffer.at(0).size()) / cofX);

    for (int j = 0; j < y; ++j)
        for (int i = 0; i < x; ++i)
            drawChar(i, j, frameBuffer);

//    box(_window, 0, 0);
}

void NCurse::drawText(text_t text)
{
    text._pos.first /= cofX;
    text._pos.second /= cofY;

    if (text._anchor.first == CENTER)
        text._pos.first -= (text._text.size() / 2);
    if (text._anchor.first == RIGHT)
        text._pos.first -= (text._text.size());

    int color = getColor(text._color.a * 255, text._color.b * 255, text._color.r * 255, text._color.g * 255);

    wattron(_window, COLOR_PAIR(color));
    mvwprintw(_window, text._pos.second, text._pos.first, text._text.data());
    wattroff(_window, COLOR_PAIR(color));
}

size_t NCurse::getSmoothness() const
{
    return _smooth;
}

/* Input */

char NCurse::getInput() const
{
    nodelay(_window, TRUE);
    keypad(_window, TRUE);

    char tmp = 0;
    char input = -1;

    while (tmp != -1) {
        input = tmp;
        tmp = static_cast<char>(wgetch(_window));
    }
    if (input == 0)
        input = -1;

    if (input == 27)
        return (1);
    if (input == 7)
        return (2);
    if (input == 10)
        return (3);
    if (input == 4)
        return (5);
    if (input == 5)
        return (6);
    if (input == 3)
        return (7);
    if (input == 2)
        return (8);

    return (input);
}

/* Sound */

void NCurse::stopSound(std::string sound __attribute__((unused)))
{
}

void NCurse::playSound(std::string sound __attribute__((unused)))
{
}

void NCurse::setVolume(std::string sound __attribute__((unused)), float volume __attribute__((unused)))
{
}

float NCurse::getVolume(std::string sound __attribute__((unused))) const
{
    return (0);
}

void NCurse::stopAllSounds()
{
}

bool exist(color_t c)
{
    return c.a > 0 && (c.g > 0 || c.r > 0 || c.b > 0);
}

int NCurse::drawChar(int x, int y, const std::vector<std::vector<color_t>> &bf)
{
    p1 = 0;
    p2 = 0;

    for (int j = y * cofY; j < (y * cofY) + cofY; ++j)
        for (int i = x * cofX; i < (x * cofX) + cofX; ++i)
            if ((bf[j][i].g > 5 || bf[j][i].r > 5 || bf[j][i].b > 5))
                j < (y * cofY) + cofX ? ++p1 : ++p2;

    if (p1 < 4 && p2 < 4)
        return (' ');
    int color = getColorAvg(x, y, bf);

    x += 1;
    y += 1;
    if (p1 >= 13 && p2 >= 13) {
        wattron(_window, COLOR_PAIR(color));
        mvwprintw(_window, y, x, "%ls", L"#");
        wattroff(_window, COLOR_PAIR(color));
        return ('0');
    }
    if (p1 >= 13 && p2 < 4) {
        wattron(_window, COLOR_PAIR(color));
        mvwprintw(_window, y, x, "%ls", L"”");
        wattroff(_window, COLOR_PAIR(color));
        return ('1');
    }
    if (p1 < 4 && p2 >= 13) {
        wattron(_window, COLOR_PAIR(color));
        mvwprintw(_window, y, x, "%ls", L"„");
        wattroff(_window, COLOR_PAIR(color));
        return ('2');
    }
    if (p1 >= 10 && p2 >= 10) {
        wattron(_window, COLOR_PAIR(color));
        mvwprintw(_window, y, x, "%ls", L"ϴ");
        wattroff(_window, COLOR_PAIR(color));
        return ('3');
    }
    if (p1 >= 10 && p2 < 4) {
        wattron(_window, COLOR_PAIR(color));
        mvwprintw(_window, y, x, "%ls", L"˅");
        wattroff(_window, COLOR_PAIR(color));
        return ('4');
    }
    if (p1 < 4 && p2 >= 10) {
        wattron(_window, COLOR_PAIR(color));
        mvwprintw(_window, y, x, "%ls", L"˯");
        wattroff(_window, COLOR_PAIR(color));
        return ('5');
    }

    if (p1 >= 7 && p2 >= 7) {
        wattron(_window, COLOR_PAIR(color));
        mvwprintw(_window, y, x, "%ls", L"O");
        wattroff(_window, COLOR_PAIR(color));
        return ('6');
    }
    if (p1 >= 7 && p2 < 4) {
        wattron(_window, COLOR_PAIR(color));
        mvwprintw(_window, y, x, "%ls", L"ᐤ");
        wattroff(_window, COLOR_PAIR(color));
        return ('7');
    }
    if (p1 < 4 && p2 >= 7) {
        wattron(_window, COLOR_PAIR(color));
        mvwprintw(_window, y, x, "%ls", L"˳");
        wattroff(_window, COLOR_PAIR(color));
        return ('8');
    }

    if (p1 >= 4 && p2 >= 4) {
        wattron(_window, COLOR_PAIR(color));
        mvwprintw(_window, y, x, "%ls", L"∙");
        wattroff(_window, COLOR_PAIR(color));
        return ('6');
    }
    if (p1 >= 4 && p2 < 4) {
        wattron(_window, COLOR_PAIR(color));
        mvwprintw(_window, y, x, "%ls", L"˙");
        wattroff(_window, COLOR_PAIR(color));
        return ('7');
    }
    if (p1 < 4 && p2 >= 4) {
        wattron(_window, COLOR_PAIR(color));
        mvwprintw(_window, y, x, "%ls", L".");
        wattroff(_window, COLOR_PAIR(color));
        return ('8');
    }
    return (' ');
}



/*    wattron(_window, COLOR_PAIR(3));
    mvwprintw(_window, 10, 10, "%ls %s", L"◢◣◤◥█▀▄▁▂▃▄▅▆▇█▉▊▋▌▍▎"
                                         "U+2590 ▐░▒▓▔▕▖▗▘▙▚▛▜▝▞▟\""
                                         "⧫𝟎≬𝝷⬮˅˯⁎*∗*⁎✺✽|˚|˚|˳|︒|˚|ᐤ|•|｡|„|”|⬤|ᐩ|⋆|ᙿ••ꔷ∙·⦁・   ۬  ᐝ  ۬۬˙˙˙˙.■◼⯀▪🞍⬝🞌",
        "example");
    mvwprintw(_window, 12, 10, "%ls %s",
        L"|▀|▄|>|█|   |„|”|>|⧫|    |˳|ᐤ|>|𝟎|   |˙|.|>|∙|", "choice");
    wattroff(_window, COLOR_PAIR(3));
    mvwprintw(_window, 15, 10, "%ls", L"█");
        //L"|▀|▄|>|█|   |„|”|>|⧫|    |˳|ᐤ|>|𝟎|   |˙|.|>|∙|", "choice");
            //∗•*˙.⁎✺✽⏹

*/