/*
** EPITECH PROJECT, 2020
** arcade
** File description:
** Created by emilien
*/

#include <gtest/gtest.h>
#include "../games/Qix/include/bitmapReader.hpp"

TEST ( bitmap_reader, Test_invalid_C_file )
{
    //bitmapReader("");
}

TEST ( bitmap_reader, Test_valid_file )
{
    bitmapReader oui("../games/assets/emilien_SolarFox_badPowerup.bmp");

    EXPECT_EQ(oui.returnVector().at(0).at(0).a, oui.returnVector().at(0).at(0).a);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return (RUN_ALL_TESTS());
}