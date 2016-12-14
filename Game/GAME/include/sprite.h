#ifndef SPRITE
#define SPRITE

#include<SDL2/SDL.h>

struct sprite
{
    SDL_Texture* texture=NULL;
    int x_pos=0;
    int y_pos=0;
    int width=0;
    int height=0;
};

int set_sprite(struct sprite* to_set, SDL_Texture* texture, int x_pos, int y_pos, int width, int height)
{
    to_set->texture=texture;
    to_set->x_pos=x_pos;
    to_set->y_pos=y_pos;
    to_set->width=width;
    to_set->height=height;
}
#endif
