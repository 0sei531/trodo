#include "../Headers/TRODO.h"
#include <SDL2/SDL.h>
#include <math.h>
#define RES_X 1920
#define RES_Y 1080

void variant_calculate_d(double *cord, double decrease, int angl) {
    while (data.map[(int)(cord[1] + decrease * data.angles.r_sin[angl]) / 50][(int)cord[0] / 50] == '0'
        && data.map[(int)cord[1] / 50][(int)(cord[0] + decrease * data.angles.r_cos[angl]) / 50] == '0'
        && data.map[(int)(cord[1] + decrease * data.angles.r_sin[angl]) / 50][(int)(cord[0] + decrease * data.angles.r_cos[angl]) / 50] == '0') {
        cord[0] += decrease * data.angles.r_cos[angl]; 
        cord[1] += decrease * data.angles.r_sin[angl];
    }
}

void variant_calculate(double *cord, double decrease, int angl) {
    while (data.map[(int)(cord[1] + decrease * data.angles.r_sin[angl]) / 50][(int)cord[0] / 50] != '1'
        && data.map[(int)cord[1] / 50][(int)(cord[0] + decrease * data.angles.r_cos[angl]) / 50] != '1'
        && data.map[(int)(cord[1] + decrease * data.angles.r_sin[angl]) / 50][(int)(cord[0] + decrease * data.angles.r_cos[angl]) / 50] != '1') {
        cord[0] += decrease * data.angles.r_cos[angl];
        cord[1] += decrease * data.angles.r_sin[angl];
    }
}

void init_angles() {
    double r = -30;
    for (int i = 0; i < RES_X; i++) {
        double angl = data.dir.angle + r;
        data.angles.r_cos[i] = cos(angl * M_PI / 180);
        data.angles.r_sin[i] = sin(angl * M_PI / 180);
        data.angles.r_res_cos[i] = cos(r * M_PI / 180);
        r += 0.04;
    }
    data.angles.pl_cos = cos(data.dir.angle * M_PI / 180);
    data.angles.pl_sin = sin(data.dir.angle * M_PI / 180);
    data.angles.pl_cos_plus_90 = cos((data.dir.angle + 90) * M_PI / 180);
    data.angles.pl_sin_plus_90 = sin((data.dir.angle + 90) * M_PI / 180);
    data.angles.cte_tan = tan(30 * M_PI / 180);
}

void set_rays(SDL_Renderer *renderer) {
    double cord[2];
    for (int i = 0; i < RES_X; i++) {
        data.color[0] = 0;
        cord[0] = data.dir.x + 17;
        cord[1] = data.dir.y + 17;
        data.indx = i;

        // Raycasting calculations
        variant_calculate_d(cord, 45, i);
        variant_calculate_d(cord, 20, i);
        variant_calculate_d(cord, 10, i);
        variant_calculate_d(cord, 1, i);
        variant_calculate_d(cord, 0.1, i);

        data.door.hit_wall = 0;

        // Check for door collision and handle
        if (data.map[(int)(cord[1] + data.angles.r_sin[i]) / 50][(int)cord[0] / 50] == 'H' || 
            data.map[(int)cord[1] / 50][(int)(cord[0] + data.angles.r_cos[i]) / 50] == 'H') {
            data.door.cord[0] = (int)cord[0];
            data.door.cord[1] = (int)cord[1];
            data.color[0] = 1;
            data.door.is_op = !(fabs(cord[0] - data.dir.x - 17) < 90 && fabs(cord[1] - data.dir.y - 17) < 90);

            // Door collision handling
            if (data.map[(int)cord[1] / 50][(int)(cord[0] + data.angles.r_cos[i]) / 50] == 'H' && cord[0] + data.angles.r_cos[i] > cord[0])
                data.door.color[1] = (int)cord[1];
            else if (data.map[(int)cord[1] / 50][(int)(cord[0] + data.angles.r_cos[i]) / 50] == 'H' && cord[0] + data.angles.r_cos[i] < cord[0])
                data.door.color[1] = (int)cord[1];
            else if (data.map[(int)(cord[1] + data.angles.r_sin[i]) / 50][(int)cord[0] / 50] == 'H' && cord[1] + data.angles.r_sin[i] > cord[1])
                data.door.color[1] = (int)cord[0];
            else if (data.map[(int)(cord[1] + data.angles.r_sin[i]) / 50][(int)cord[0] / 50] == 'H' && cord[1] + data.angles.r_sin[i] < cord[1])
                data.door.color[1] = (int)cord[0];

            data.door.rays[i] = sqrt((cord[0] - (double)data.dir.x - 17)*(cord[0] - (double)data.dir.x - 17) + 
                                      (cord[1] - (double)data.dir.y - 17)*(cord[1] - (double)data.dir.y - 17)) * data.angles.r_res_cos[i];

            variant_calculate(cord, 45, i);
            variant_calculate(cord, 20, i);
            variant_calculate(cord, 10, i);
            variant_calculate(cord, 1, i);
            variant_calculate(cord, 0.1, i);

            data.door.hit_wall = data.map[(int)(cord[1]) / 50][(int)(cord[0]) / 50] == 'H';
        }

        SDL_RenderDrawLine(renderer, cord[0], cord[1], cord[0] + 100, cord[1] + 100);

        // Wall detection
        if (data.map[(int)cord[1] / 50][(int)(cord[0] + data.angles.r_cos[i]) / 50] == '1' && cord[0] + data.angles.r_cos[i] > cord[0])
            data.color[1] = (int)cord[1];
        else if (data.map[(int)cord[1] / 50][(int)(cord[0] + data.angles.r_cos[i]) / 50] == '1' && cord[0] + data.angles.r_cos[i] < cord[0])
            data.color[1] = (int)cord[1];
        else if (data.map[(int)(cord[1] + data.angles.r_sin[i]) / 50][(int)cord[0] / 50] == '1' && cord[1] + data.angles.r_sin[i] > cord[1])
            data.color[1] = (int)cord[0];
        else if (data.map[(int)(cord[1] + data.angles.r_sin[i]) / 50][(int)cord[0] / 50] == '1' && cord[1] + data.angles.r_sin[i] < cord[1])
            data.color[1] = (int)cord[0];

        // Calculate ray distance
        data.rays[i] = sqrt((cord[0] - (double)data.dir.x - 17)*(cord[0] - (double)data.dir.x - 17) + 
                             (cord[1] - (double)data.dir.y - 17)*(cord[1] - (double)data.dir.y - 17)) * data.angles.r_res_cos[i];

        data.cord = cord;
        data.design = data.door.map[(int)(cord[1] - data.angles.r_sin[i]) / 50][(int)(cord[0] - data.angles.r_cos[i]) / 50];

        if (i <= RES_X)
            cast_to_3d(i - 1);
    }
    data.light++;
    if (data.light >= 600)
        data.light = 0;
}

