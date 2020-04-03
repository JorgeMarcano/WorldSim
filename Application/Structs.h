#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Space
{
    int x;
    int y;
} Space;

typedef struct Object
{
    Space* location;
    int xSpeed;
    int ySpeed;
} Object;

#define OBJECT_COUNT        10
#define SPACE_X_SIZE        10
#define SPACE_Y_SIZE        10
#define SPACE_COUNT         SPACE_X_SIZE * SPACE_Y_SIZE
#define OBJECT_SPEED_X_MAX  3
#define OBJECT_SPEED_Y_MAX  3

#endif
