#ifndef PHYSICS
#define PHYSICS

#include"collider.h"

int collides(collider* a, collider* b)
{
    return(a->x_pos < b->x_pos + b->width && b->x_pos < a->x_pos + a->width && a->y_pos < b->y_pos + b-> height && b->y_pos < a->y_pos + a->height);
}

#endif
