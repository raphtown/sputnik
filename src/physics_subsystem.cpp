#include "physics_subsystem.h"

#include "transform_component.h"
#include "world.h"
#include "vector.h"

PhysicsSubsystem::PhysicsSubsystem(World &_world) : Subsystem(_world)
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

        tc->position += tc->velocity * dt;
        tc->velocity += tc->acceleration * dt;

        tc->acceleration << 0, 0;
    }
}

