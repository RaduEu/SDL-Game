#ifndef GAMEOBJECT
#define GAMEOBJECT

#include"sprite.h"
#include"rigidbody.h"
#include"collider.h"
#include"physics.h"
#include"util.h"

struct game_object
{
    int x_pos=0;
    int y_pos=0;
    struct sprite* sprite;
    struct collider* collider;
};

#endif
