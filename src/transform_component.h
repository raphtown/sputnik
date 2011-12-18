#ifndef _TRANSFORM_COMPONENT_H
#define _TRANSFORM_COMPONENT_H

#include "entity_component.h"

struct TransformComponent : public EntityComponent {
	float x, y;
	float rotation;

	TransformComponent(unsigned short component_type);
	~TransformComponent();
};


#endif
