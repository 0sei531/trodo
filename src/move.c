#include <SDL2/SDL.h>
#include "../Headers/structs.h"
#include "../Headers/TRODO.h"
#include <math.h>

#define ABS(X) ((X > 0)? X : -X)

void up()
{
    int x, y;
    int map_x_right = (int)(data.dir.x + 17) / 50;
    int map_y_right = (int)(data.dir.y + 17) / 50;
    int map_x_left = (int)(data.dir.x + 15) / 50;
    int map_y_left = (int)(data.dir.y + 15) / 50;

    x = round(data.dir.x + (7 + data.speed) * data.angles.pl_cos);
    y = round(data.dir.y + (7 + data.speed) * data.angles.pl_sin);

    int map_x_new_right = (int)(x + 17) / 50;
    int map_y_new_right = (int)(y + 17) / 50;
    int map_x_new_left = (int)(x + 15) / 50;
    int map_y_new_left = (int)(y + 15) / 50;

    if (data.map[map_y_new_right][map_x_new_right] != '1'
        && data.map[map_y_new_right][map_x_right] != '1'
        && data.map[map_y_right][map_x_new_right] != '1'
        && data.map[map_y_new_left][map_x_new_left] != '1'
        && data.map[map_y_new_left][map_x_left] != '1'
        && data.map[map_y_left][map_x_new_left] != '1')
    {
        data.dir.x = x;
        data.dir.y = y;
    }
    else if (data.map[map_y_right][map_x_new_right] != '1'
            && data.map[map_y_left][map_x_new_left] != '1')
        data.dir.x = x;
    else if (data.map[map_y_new_right][map_x_right] != '1'
            && data.map[map_y_new_left][map_x_left] != '1')
        data.dir.y = y;
}

void down()
{
    int x, y;
    int map_x_right = (int)(data.dir.x + 17) / 50;
    int map_y_right = (int)(data.dir.y + 17) / 50;
    int map_x_left = (int)(data.dir.x + 15) / 50;
    int map_y_left = (int)(data.dir.y + 15) / 50;

    x = round(data.dir.x - 7 * data.angles.pl_cos);
    y = round(data.dir.y - 7 * data.angles.pl_sin);

    int map_x_new_right = (int)(x + 17) / 50;
    int map_y_new_right = (int)(y + 17) / 50;
    int map_x_new_left = (int)(x + 15) / 50;
    int map_y_new_left = (int)(y + 15) / 50;

    if (data.map[map_y_new_right][map_x_new_right] != '1'
        && data.map[map_y_new_right][map_x_right] != '1'
        && data.map[map_y_right][map_x_new_right] != '1'
        && data.map[map_y_new_left][map_x_new_left] != '1'
        && data.map[map_y_new_left][map_x_left] != '1'
        && data.map[map_y_left][map_x_new_left] != '1')
    {
        data.dir.x = x;
        data.dir.y = y;
    }
    else if (data.map[map_y_right][map_x_new_right] != '1'
            && data.map[map_y_left][map_x_new_left] != '1')
        data.dir.x = x;
    else if (data.map[map_y_new_right][map_x_right] != '1'
            && data.map[map_y_new_left][map_x_left] != '1')
        data.dir.y = y;
}

void right_angle()
{
    data.dir.s--;
    if (data.dir.s < 0)
        data.dir.s = 16 * ANGLES - 1;

    data.dir.angle += ANGLE * (data.mouse.on ? 1 : 0);
    if (data.dir.angle >= 360)
        data.dir.angle -= 360.0;
    init_angles();
}

void left_angle()
{
    data.dir.s++;
    data.dir.s = fmodf(data.dir.s, (int)(16 * ANGLES));

    data.dir.angle -= ANGLE * (data.mouse.on ? 1 : 0);
    if (data.dir.angle < 0)
        data.dir.angle += 360.0;
    init_angles();
}

void right()
{
    int x, y;
    int map_x_right = (int)(data.dir.x + 17) / 50;
    int map_y_right = (int)(data.dir.y + 17) / 50;
    int map_x_left = (int)(data.dir.x + 15) / 50;
    int map_y_left = (int)(data.dir.y + 15) / 50;

    x = round(data.dir.x + 7 * data.angles.pl_cos_plus_90);
    y = round(data.dir.y + 7 * data.angles.pl_sin_plus_90);

    int map_x_new_right = (int)(x + 17) / 50;
    int map_y_new_right = (int)(y + 17) / 50;
    int map_x_new_left = (int)(x + 15) / 50;
    int map_y_new_left = (int)(y + 15) / 50;

    if (data.map[map_y_new_right][map_x_new_right] != '1'
        && data.map[map_y_new_right][map_x_right] != '1'
        && data.map[map_y_right][map_x_new_right] != '1'
        && data.map[map_y_new_left][map_x_new_left] != '1'
        && data.map[map_y_new_left][map_x_left] != '1'
        && data.map[map_y_left][map_x_new_left] != '1')
    {
        data.dir.x = x;
        data.dir.y = y;
    }
    else if (data.map[map_y_right][map_x_new_right] != '1'
            && data.map[map_y_left][map_x_new_left] != '1')
        data.dir.x = x;
    else if (data.map[map_y_new_right][map_x_right] != '1'
            && data.map[map_y_new_left][map_x_left] != '1')
        data.dir.y = y;
}

void left()
{
    int x, y;
    int map_x_right = (int)(data.dir.x + 17) / 50;
    int map_y_right = (int)(data.dir.y + 17) / 50;
    int map_x_left = (int)(data.dir.x + 15) / 50;
    int map_y_left = (int)(data.dir.y + 15) / 50;

    x = round(data.dir.x - 7 * data.angles.pl_cos_plus_90);
    y = round(data.dir.y - 7 * data.angles.pl_sin_plus_90);

    int map_x_new_right = (int)(x + 17) / 50;
    int map_y_new_right = (int)(y + 17) / 50;
    int map_x_new_left = (int)(x + 15) / 50;
    int map_y_new_left = (int)(y + 15) / 50;

    if (data.map[map_y_new_right][map_x_new_right] != '1'
        && data.map[map_y_new_right][map_x_right] != '1'
        && data.map[map_y_right][map_x_new_right] != '1'
        && data.map[map_y_new_left][map_x_new_left] != '1'
        && data.map[map_y_new_left][map_x_left] != '1'
        && data.map[map_y_left][map_x_new_left] != '1')
    {
        data.dir.x = x;
        data.dir.y = y;
    }
    else if (data.map[map_y_right][map_x_new_right] != '1'
            && data.map[map_y_left][map_x_new_left] != '1')
        data.dir.x = x;
    else if (data.map[map_y_new_right][map_x_right] != '1'
            && data.map[map_y_new_left][map_x_left] != '1')
        data.dir.y = y;
}
