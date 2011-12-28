#ifndef _PLAYER_CONTROLLER_SUBSYSTEM_H
#define _PLAYER_CONTROLLER_SUBSYSTEM_H

#include "allegro_events.h"
#include "subsystem.h"

class World;


class PlayerControllerSubsystem : public Subsystem
{
private:
    enum PlayerButtons
    {
        MOVE_FORWARD,
        MOVE_BACKWARD,
        ROTATE_LEFT,
        ROTATE_RIGHT,
        NUM_BUTTONS
    };

    AllegroEvents events;
    bool button_states[NUM_BUTTONS];

public:
    PlayerControllerSubsystem(World *world);
    
    void process(unsigned int dt);
};

#endif

