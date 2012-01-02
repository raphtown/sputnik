#include "collide_component.h"

CollideComponent::CollideComponent(unsigned int _component_type) :
        EntityComponent(_component_type), collided(false)
{
}

CollideComponent::~CollideComponent()
{
}

