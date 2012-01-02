#ifndef _COLLIDE_SUBSYSTEM_H
#define _COLLIDE_SUBSYSTEM_H

#include "subsystem.h"

class World;

class CollideSubsystem : public Subsystem
{
public:
    CollideSubsystem(World &world);

    void process(unsigned int dt);
};

#endif

