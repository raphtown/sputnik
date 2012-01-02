#ifndef _COLLIDE_COMPONENT_H
#define _COLLIDE_COMPONENT_H

#include "entity_component.h"

struct CollideComponent : public EntityComponent
{
    unsigned int half_width;
    unsigned int half_height;
    float radius;
    float weight;

    bool collided;

    CollideComponent(unsigned int component_type);
    ~CollideComponent();
};

#endif

