#ifndef _TRANSFORM_COMPONENT_H
#define _TRANSFORM_COMPONENT_H

#include "entity_component.h"

struct Vector
{
    float x;
    float y;
};

struct TransformComponent : public EntityComponent
{
    Vector position, velocity, acceleration;
    float rotation;

    TransformComponent(unsigned short component_type);
    ~TransformComponent();
};


#endif
