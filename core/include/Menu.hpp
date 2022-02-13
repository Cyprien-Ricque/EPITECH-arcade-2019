/*
** EPITECH PROJECT, 2019
** arcade
** File description:
** arcade,
*/

#ifndef ARCADE_MENU_HPP
#define ARCADE_MENU_HPP

#include "IGameModule.hpp"
#include "GameEngine.hpp"
#include "Clock.hpp"
#include <map>
#include <algorithm>

#define MIN_SCORE -9999

class Menu : public IGameModule {
    public:
        Menu();
        ~Menu() = default;
        void run(char input, size_t smoothness) override;
        std::vector<std::vector<color_t>> getFramebuffer() const override;
        void init() override;

        enum concern {
            GAME,
            LIB,
            PSEUDO
        };

        std::pair<concern, std::string> toDo();
        void setGames(std::vector<std::string>);
        void setLibs(std::vector<std::string>);
        void setScores(std::map<std::string, std::map<std::string, int>>);
        void setName(std::string);

        std::vector<text_t> getTexts() const override;
        std::vector<std::pair<std::string, float>> getSoundsStart() const override;
        std::vector<std::string> getSoundsStop() const override;

        int getScore() const override;
        std::string getName() const;
        bool isOver() const override;

    private:
        void setCurrentGame(char input);
        void setCurrentLib(char input);
        void createText(std::string text, std::pair<int, int> pos, std::pair<int, int> anchor, int size, color_t c);
        void _switch(char);
        void usernameManagement(char);
        void displayScores();
        static std::string getLibName(const std::string &lib);

        std::vector<std::vector<color_t>> _bf;

        std::pair<concern, std::string> _toDo;

        std::vector<std::string> _games;
        std::vector<std::string> _libs;
        int _idxCurrentGame;
        int _idxCurrentLib;

        std::vector<text_t> _texts;
        text_t _text;

        std::vector<std::pair<std::string, float>> _soundsStart;
        std::vector<std::string> _soundsStop;

        int _score;
        Clock _clock;

        std::string _username;

        std::map<std::string, std::map<std::string, int>> _scores;

        color_t _c1;
        color_t _c2;
        color_t _c3;
        color_t _c4;
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

template<typename K, typename V>
std::multimap<V,K> invertMap(std::map<K,V> const &map)
{
    std::multimap<V,K> multimap;

    for (auto const &pair: map) {
        multimap.insert(std::make_pair(pair.second, pair.first));
    }

    return multimap;
}

// -------------------------------------------------------------------
// --- Reversed iterable

template <typename T>
struct reversion_wrapper { T& iterable; };

template <typename T>
auto begin (reversion_wrapper<T> w) { return std::rbegin(w.iterable); }

template <typename T>
auto end (reversion_wrapper<T> w) { return std::rend(w.iterable); }

template <typename T>
reversion_wrapper<T> reverse (T&& iterable) { return { iterable }; }

#endif //ARCADE_MENU_HPP
