#include "sprite_component.h"

SpriteComponent::SpriteComponent(unsigned short component_type) : EntityComponent(component_type)
{
    filename = NULL;
}

SpriteComponent::~SpriteComponent()
{
    if (filename != NULL)
    {
        delete filename;
    }
}
