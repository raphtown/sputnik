#ifndef _SPRITE_COMPONENT_H
#define _SPRITE_COMPONENT_H

#include <cstdlib>

#include "entity_component.h"

struct SpriteComponent : public EntityComponent {
	char *filename;

	SpriteComponent(unsigned short component_type);
	~SpriteComponent();
};

#endif
