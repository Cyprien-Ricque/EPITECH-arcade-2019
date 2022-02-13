/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** OOP_arcade_2019,
*/

#ifndef OOP_ARCADE_2019_MAPDATA_HPP
#define OOP_ARCADE_2019_MAPDATA_HPP

#define RIGHT 6
#define LEFT 5
#define TOP 7
#define BOTTOM 8
#define SPEED 8
#define UNIT 16
#define QIX_MAX_SPEED 13
#define SIZE_X static_cast<int>(512 - UNIT)
#define SIZE_Y static_cast<int>(512 - UNIT)

enum type {
    BORDER,
    OLD_BORDER,
    WALKABLE,
    NON_WALKABLE
};

enum state {
    NONE,
    ON_FIRE,
    CREATE,
    BURNT
};

enum playerState {
    DEAD,
    MOVING,
    STOPPED
};

typedef struct {
    type t;
    state s;
} obj_t;

#endif //OOP_ARCADE_2019_MAPDATA_HPP
