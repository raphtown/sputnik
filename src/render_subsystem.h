#ifndef _RENDER_SUBSYSTEM_H
#define _RENDER_SUBSYSTEM_H

#include "subsystem.h"

class World;

class RenderSubsystem : public Subsystem
{
protected:
    void process_entity(const Entity &entity);

public:
    RenderSubsystem(World *world);
};

#endif

