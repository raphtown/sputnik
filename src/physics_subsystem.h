#ifndef _PHYSICS_SUBSYSTEM_H
#define _PHYSICS_SUBSYSTEM_H

#include "subsystem.h"

class World;

class PhysicsSubsystem : public Subsystem
{
public:
    PhysicsSubsystem(World *world);
    void process(unsigned int dt);
};

#endif

