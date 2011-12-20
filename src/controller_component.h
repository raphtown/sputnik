#ifndef _CONTROLLER_COMPONENT_H
#define _CONTROLLER_COMPONENT_H

#include "entity_component.h"

struct ControllerComponent : public EntityComponent
{
    bool key_w;
    bool key_a;
    bool key_s;
    bool key_d;

    ControllerComponent(unsigned short component_type);
};

#endif

