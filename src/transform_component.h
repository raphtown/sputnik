#ifndef _TRANSFORM_COMPONENT_H
#define _TRANSFORM_COMPONENT_H

#include "entity_component.h"

struct Vector
{
    float x;
    float y;

    inline Vector operator+(const Vector &o)
    {
        Vector n;
        n.x = x + o.x;
        n.y = y + o.y;
        return n;
    }

    inline Vector operator-(const Vector &o)
    {
        Vector n;
        n.x = x - o.x;
        n.y = y - o.y;
        return n;
    }

    inline Vector operator*(float a)
    {
        Vector n;
        n.x = a * x;
        n.y = a * y;
        return n;
    }

    inline Vector operator/(float a)
    {
        Vector n;
        n.x = x / a;
        n.y = y / a;
        return n;
    }

    inline void operator*=(float a)
    {
        x *= a;
        y *= a;
    }

    inline float magnitude()
    {
        return x * x + y * y;
    }
};

struct TransformComponent : public EntityComponent
{
    Vector position, velocity, acceleration;
    float rotation;

    TransformComponent(unsigned short component_type);
    ~TransformComponent();
};


#endif
