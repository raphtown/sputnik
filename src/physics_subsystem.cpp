#include "physics_subsystem.h"

#include "transform_component.h"
#include "world.h"

PhysicsSubsystem::PhysicsSubsystem(World *_world) : Subsystem(_world)
{
    require<TransformComponent>();
}

void PhysicsSubsystem::process(unsigned int dt)
{
    for (std::set<Entity>::const_iterator iter = active.begin();
            iter != active.end();
            iter++)
    {
        // Euler integration ought to be enough for anybody. - Bill Gates
        const Entity &entity = *iter;
        TransformComponent *tc = world->get<TransformComponent>(entity);

        tc->position.x += tc->velocity.x * dt;
        tc->position.y += tc->velocity.y * dt;

        tc->velocity.x += tc->acceleration.x * dt;
        tc->velocity.y += tc->acceleration.y * dt;

        tc->acceleration.x = 0;
        tc->acceleration.y = 0;
    }
}

