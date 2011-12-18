#ifndef _RENDER_SUBSYSTEM_H
#define _RENDER_SUBSYSTEM_H

#include <allegro5/allegro.h>

#include "entity_component_manager.h"
#include "entity_manager.h"
#include "sprite_component.h"
#include "subsystem.h"
#include "transform_component.h"

class RenderSubsystem : public Subsystem {
protected:
	void processEntity(const Entity &entity);

public:
	RenderSubsystem(EntityManager *em, EntityComponentManager *ecm);
};

#endif
