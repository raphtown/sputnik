#ifndef _PLAYER_SUBSYSTEM_H
#define _PLAYER_SUBSYSTEM_H

#include "subsystem.h"

class World;

class PlayerSubsystem : public Subsystem
{
private:
    void process_entity(const Entity &entity);

public:
    PlayerSubsystem(World *world);

    void process();
};
#endif

