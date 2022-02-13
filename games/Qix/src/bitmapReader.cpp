/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Created by emilien
*/

#pragma pack(1)
#include <iostream>
#include "bitmapReader.hpp"

bitmapReader::bitmapReader(const std::string &file)
{
    this->file_s.open(file, std::ios::in | std::ios::binary);
    size_t filesize;

    this->_init = false;
    if (!file_s.is_open()) {
        std::cerr << "File: " << file << " not found or cannot be open" << std::endl;
        throw std::exception();
    }
    file_s.seekg(0, std::ios::end);
    filesize = file_s.tellg();
    file_s.seekg(0, std::ios::beg);
    if (filesize < SIZE_BMP_HEADER) {
        std::cerr << "Invalid file" << std::endl;
        throw std::exception();
    }
    file_s.read(reinterpret_cast<char *>(&header), sizeof(struct bitmapHeader));
    file_s.read(reinterpret_cast<char *>(&sheader), sizeof(struct bitmapSheader));
    file_s.read(reinterpret_cast<char *>(&rgbData), sizeof(struct rgbQuad));
    if (this->sheader.bitCount != 24) {
        std::cerr << "The file must be a 24bit bmp format" << std::endl;
        throw std::exception();
    }
    if (filesize != header.size) {
        std::cerr << "Invalid file" << std::endl;
        throw std::exception();
    }
    this->_init = true;
    this->fillVector();
    this->file_s.close();
}

bool bitmapReader::initBMP() const
{
    return (this->_init);
}

void bitmapReader::fillVector()
{
    color_t color{.r = 0, .g = 0, .b = 0, .a = 0};
    struct pixelData pixelD{};

    if (!this->_init)
        throw std::exception();
    for (uint32_t a = 0; a < sheader.height; ++a) {
        std::vector<color_t> dataLine;
        for (uint32_t b = 0; b < sheader.width; ++b) {
            file_s.read(reinterpret_cast<char *>(&pixelD), sizeof(struct pixelData));
            color.r = pixelD.R;
            color.b = pixelD.B;
            color.g = pixelD.G;
            color.a = 255;
            if (color.r == 0 && color.g == 0 && color.b == 0)
                color.a = 0;
            dataLine.push_back(color);
        }
        this->_dataColors.insert(this->_dataColors.begin(), std::move(dataLine));
        dataLine.clear();
    }
    this->file_s.close();
}

std::vector<std::vector<color_t>> bitmapReader::returnVector()
{
    return (this->_dataColors);
}

bitmapReader::~bitmapReader()
{
    this->_dataColors.clear();
}