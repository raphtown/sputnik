#include "collide_subsystem.h"

#include "collide_component.h"
#include "transform_component.h"
#include "world.h"

CollideSubsystem::CollideSubsystem(World &world) : Subsystem(world)
{
    require<CollideComponent>();
    require<TransformComponent>();
}

void CollideSubsystem::process(unsigned int dt)
{
    // yes this is n^2
    for (std::set<Entity>::const_iterator iter = active.begin();
            iter != active.end();
            iter++)
    {
        Entity a = *iter;
        CollideComponent *ac = world->get<CollideComponent>(a);
        TransformComponent *at = world->get<TransformComponent>(a);

        float ar = ac->radius;
        float aw = ac->weight;

        std::set<Entity>::const_iterator jiter = iter;
        jiter++;
        for ( ;
                jiter != active.end();
                jiter++)
        {
            Entity b = *jiter;
            CollideComponent *bc = world->get<CollideComponent>(b);
            TransformComponent *bt = world->get<TransformComponent>(b);

            float br = bc->radius;
            float bw = bc->weight;

            // ||a - b|| <= (ar * ar + br * br)^2
            if ((at->position - bt->position).magnitude() <= (ar * ar + 2 * ar * br + br * br))
            {
                Vector anew = (bt->velocity * 2 * bw + at->velocity * (aw - bw)) / (aw + bw);
                Vector bnew = (at->velocity * 2 * aw - bt->velocity * (aw - bw)) / (aw + bw);

                at->velocity = anew;
                bt->velocity = bnew;
            }
        }
    }
}

