#ifndef _PLAYER_COMPONENT_H
#define _PLAYER_COMPONENT_H

#include "entity_component.h"

struct PlayerComponent : public EntityComponent
{
    PlayerComponent(unsigned short component_type);
};

#endif

