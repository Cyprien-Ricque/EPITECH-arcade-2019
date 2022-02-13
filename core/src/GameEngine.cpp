/*
** EPITECH PROJECT, 2019
** arcade
** File description:
** arcade,
*/

#include "GameEngine.hpp"

void GameEngine::drawSquare(std::pair<int, int> pos, std::pair<int, int> size, color_t c, std::vector<std::vector<color_t>> &bf)
{
    for (int j = pos.second; j < pos.second + size.second; ++j)
        for (int i = pos.first; i < pos.first + size.first; ++i)
            bf.at(j).at(i) = c;
}

void GameEngine::drawCircle(std::pair<int, int> pos, int radius, color_t c, std::vector<std::vector<color_t>> &bf)
{
    for (int j = pos.second - radius; j < pos.second + radius; ++j)
        for (int i = pos.first - radius; i < pos.first + radius; ++i)
            if (getDistance(pos, std::make_pair(i > pos.first ? i + 1 : i, j > pos.second ? j + 1 : j)) <= radius)
                bf.at(j).at(i) = c;

}

int GameEngine::getDistance(std::pair<int, int> a, std::pair<int, int> b)
{
    //std::cout << static_cast<int>(std::sqrt(std::pow(b.first - a.first, 2) + std::pow(b.second - a.second, 2))) << std::endl;
    //std::cout << (std::sqrt(std::pow(b.first - a.first, 2) + std::pow(b.second - a.second, 2))) << std::endl;

    return static_cast<int>(std::sqrt(std::pow(b.first - a.first, 2) + std::pow(b.second - a.second, 2)));
}

void GameEngine::rotateBuffer(int angle __attribute__((unused)), std::vector<std::vector<color_t>> &bf)
{
    auto center = std::make_pair(bf.at(0).size() / 2, bf.size() / 2);
    int tmpAngle __attribute__((unused));
    int tmpDist __attribute__((unused));

    for (std::size_t j = 0; j < bf.size(); ++j) {
        for (std::size_t i = 0; i < bf.at(0).size(); ++i) {
            tmpAngle = getAngle(center, std::make_pair(i, j));
            tmpDist = getDistance(center, std::make_pair(i, j));
        }
    }
}

std::vector<std::vector<color_t>> GameEngine::returnRotateBuffer90(std::vector<std::vector<color_t>> &bf)
{
    resize(bf);
    auto output = bf;

    auto center = std::pair<float, float>((static_cast<float>(bf.at(0).size()) / 2) - 0.5 , (static_cast<float>(bf.size()) / 2) - 0.5);

    for (std::size_t j = 0; j < bf.size(); ++j) {
        for (std::size_t i = 0; i < bf.at(0).size(); ++i) {
            if (i <= center.first && j <= center.second)
                output.at(i).at(center.first + (center.second - j)) = bf.at(j).at(i);
            if (i > center.first && j <= center.second)
                output.at(center.second + (i - center.first)).at(center.first + (center.second - j)) = bf.at(j).at(i);
            if (i > center.first && j > center.second)
                output.at(center.second + (i - center.first)).at(center.second - (j - center.second)) = bf.at(j).at(i);
            if (i <= center.first && j > center.second)
                output.at(i).at(center.first - (j - center.second)) = bf.at(j).at(i);
        }
    }
    return (output);
}

void GameEngine::rotateBufferM90(std::vector<std::vector<color_t>> &bf)
{
    resize(bf);

    auto tmp = bf;
    auto center = std::pair<float, float>((static_cast<float>(bf.at(0).size()) / 2) - 0.5 , (static_cast<float>(bf.size()) / 2) - 0.5);

    for (std::size_t j = 0; j < tmp.size(); ++j)
        for (std::size_t i = 0; i < tmp.at(0).size(); ++i) {
            if (i <= center.first && j <= center.second)
                bf.at(i).at(center.first + (center.second - j)) = tmp.at(j).at(i);
            if (i > center.first && j <= center.second)
                bf.at(center.second + (i - center.first)).at(center.first + (center.second - j)) = tmp.at(j).at(i);
            if (i > center.first && j > center.second)
                bf.at(center.second + (i - center.first)).at(center.second - (j - center.second)) = tmp.at(j).at(i);
            if (i <= center.first && j > center.second)
                bf.at(i).at(center.first - (j - center.second)) = tmp.at(j).at(i);
        }
}


void GameEngine::rotateBuffer90(std::vector<std::vector<color_t>> &bf)
{
    rotateBufferM90(bf);
    rotateBufferM90(bf);
    rotateBufferM90(bf);
}


void GameEngine::rotateBuffer180(std::vector<std::vector<color_t>> &bf)
{
    rotateBufferM90(bf);
    rotateBufferM90(bf);
}

int GameEngine::getAngle(std::pair<int, int> a __attribute__((unused)), std::pair<int, int> b __attribute__((unused)))
{
    return (0);
}

void GameEngine::clearBuffer(std::vector<std::vector<color_t>> &bf)
{
    color_t c = {0, 0, 0, 0};

    for (auto &e : bf)
        for (auto &f : e)
            f = c;
}

void GameEngine::putIn(std::vector<std::vector<color_t>> &src, std::vector<std::vector<color_t>> &dest, std::pair<int, int> pos)
{
    for (std::size_t j = 0; j < src.size() - 1; ++j)
        for (std::size_t i = 0; i < src.at(0).size() - 1; ++i)
            if (src.at(j).at(i).a != 255)
                dest.at(pos.second + j).at(pos.first + i) = src.at(j).at(i);
}

void GameEngine::resize(std::vector<std::vector<color_t>> &bf)
{
    color_t c = {0, 0, 0, 255};
    std::vector<color_t> tmp;

    while (bf.size() > bf.at(0).size())
        for (auto &e : bf)
            e.push_back(c);
    if (bf.size() < bf.at(0).size())
        for (auto &e __attribute__((unused)) : bf.at(0))
            tmp.push_back(c);
    while (bf.size() < bf.at(0).size())
        bf.push_back(tmp);

}

bool GameEngine::Collision(std::pair<int, int> &posA, std::pair<int, int> &sizeA, std::pair<int, int> &posB)
{
    return
        (posB.first >= posA.first && posB.first <= posA.first + sizeA.first) &&
            (posB.second >= posA.second && posB.second <= posA.second + sizeA.second);
}

bool GameEngine::CollisionSquare(std::pair<int, int> posA, std::pair<int, int> sizeA, std::pair<int, int> posB, std::pair<int, int> sizeB)
{
    std::pair<int, int> point = posB;

    if (Collision(posA, sizeA, point))
        return (true);
    point.first += sizeB.first;
    if (Collision(posA, sizeA, point))
        return (true);
    point.second += sizeB.second;
    if (Collision(posA, sizeA, point))
        return (true);
    point.first -= sizeB.first;
    if (Collision(posA, sizeA, point))
        return (true);

    point = posA;
    if (Collision(posB, sizeB, point))
        return (true);
    point.first += sizeA.first;
    if (Collision(posB, sizeB, point))
        return (true);
    point.second += sizeA.second;
    if (Collision(posB, sizeB, point))
        return (true);
    point.first -= sizeA.first;
    return Collision(posB, sizeB, point);
}