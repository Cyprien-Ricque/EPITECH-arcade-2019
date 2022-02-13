/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Created by emilien
*/

#ifndef OOP_ARCADE_2019_BITMAP_READER_HPP
#define OOP_ARCADE_2019_BITMAP_READER_HPP

#include <string>
#include <vector>
#include <fstream>
#include "color.hpp"

struct bitmapHeader {
    uint16_t magic;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offBits;
};

struct bitmapSheader {
    uint32_t sizeInfoStruct;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bitCount;
    uint32_t compression;
    uint32_t imageSize;
    uint32_t xPerMeter;
    uint32_t yPerMeter;
    uint32_t clrUsed;
    uint32_t clrImportant;
};

struct rgbQuad {
    uint8_t rgbBlue;
    uint8_t rgbGreen;
    uint8_t rgbRed;
    uint8_t rgbReserved;
    uint8_t bits64[64];
};

struct pixelData {
    uint8_t B;
    uint8_t G;
    uint8_t R;
};

class bitmapReader {
public:
    explicit bitmapReader(const std::string &);
    ~bitmapReader();
    std::vector<std::vector<color_t>> returnVector();
    bool initBMP() const;

private:
    bool _init;
    void fillVector();
    std::vector<std::vector<color_t>> _dataColors;
    struct bitmapHeader header{};
    struct bitmapSheader sheader{};
    struct rgbQuad rgbData{};
    std::ifstream file_s;
};

#define SIZE_BMP_HEADER (sizeof(struct bitmapHeader) + sizeof(struct bitmapSheader) + sizeof(struct rgbQuad))

#endif //OOP_ARCADE_2019_BITMAP_READER_HPP
