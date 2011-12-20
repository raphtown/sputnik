#include "player_subsystem.h"

#include "controller_component.h"
#include "player_component.h"
#include "transform_component.h"
#include "world.h"

PlayerSubsystem::PlayerSubsystem(World *_world) : Subsystem(_world)
{
    require<ControllerComponent>();
    require<PlayerComponent>();
    require<TransformComponent>();
}

void PlayerSubsystem::process_entity(const Entity &entity)
{
    ControllerComponent *cc = world->get<ControllerComponent>(entity);
    TransformComponent *tc = world->get<TransformComponent>(entity);

    if (cc->key_w)
    {
        tc->x += 10;
    }
    else if (cc->key_s)
    {
        tc->x -= 10;
    }
}

void PlayerSubsystem::process()
{
    for (std::set<Entity>::const_iterator iter = active.begin(); iter != active.end(); iter++)
    {
        process_entity(*iter);
    }
}

