#ifndef _CONTROLLER_SUBSYSTEM_H
#define _CONTROLLER_SUBSYSTEM_H

#include "allegro_events.h"
#include "subsystem.h"

class World;

class ControllerSubsystem : public Subsystem
{
private:
    AllegroEvents events;

public:
    ControllerSubsystem(World *world);
    
    void process();
};

#endif

