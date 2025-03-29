#pragma once

#include <cmath>
#include <vec.hpp>
#include <ECS.hpp>

typedef enum CollisionDirection
{
    CollisionUp,
    CollisionDown,
    CollisionLeft,
    CollisionRight
} CollisionDirection;

inline bool ColisionAABB(ECS *obj1, ECS *obj2)
{
    if (obj1->Position.x <= obj2->Position.x + obj2->width && obj1->Position.x + obj1->width >= obj2->Position.x && obj1->Position.y <= obj2->Position.y + obj2->height && obj1->Position.y + obj1->height >= obj2->Position.y)
    {
        return true;
    }
    return false;
}