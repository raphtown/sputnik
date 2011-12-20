#include "entity_component.h"

EntityComponent::EntityComponent(unsigned short _component_type) : component_type(_component_type)
{
}

EntityComponent::~EntityComponent()
{
}

unsigned short EntityComponent::get_component_type()
{
    return component_type;
}
