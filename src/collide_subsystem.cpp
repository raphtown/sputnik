#include "collide_subsystem.h"

#include <cmath>
#include <iostream>

#include "collide_component.h"
#include "transform_component.h"
#include "world.h"

CollideSubsystem::CollideSubsystem(World &world) : Subsystem(world)
{
    require<CollideComponent>();
    require<TransformComponent>();
}

static void to_points(const Vector &position, float half_width, float half_height,
        float rotation, Vector points[4])
{
    float c = cos(rotation);
    float s = sin(rotation);

    points[0] = Vector(
        position(0) - (c * half_width - s * half_height),
        position(1) + (s * half_width + c * half_height));
    points[1] = Vector( 
        position(0) + (c * half_width - s * half_height),
        position(1) + (s * half_width + c * half_height));
    points[2] = Vector( 
        position(0) + (c * half_width - s * half_height),
        position(1) - (s * half_width + c * half_height));
    points[3] = Vector( 
        position(0) - (c * half_width - s * half_height),
        position(1) - (s * half_width + c * half_height));
}

static bool are_rects_colliding(const Vector a[4], const Vector b[4])
{
    for (unsigned int i = 1; i < 5; i++)
    {
        Vector edge = a[i % 4] - a[i - 1];
        Vector perp(-edge[1], edge[0]);

        float test = perp.dot(a[(i + 1) % 4] - a[i - 1]);
        int side = (test > 0) - (test < 0);
        
        int count = 0;
        for (unsigned int j = 0; j < 4; j++)
        {
            test = perp.dot(b[j] - a[i - 1]);
            count += (test > 0) - (test < 0);
        }
        
        if (count == 4 * -1 * side)
        {
            return false;
        }
    }

    for (unsigned int i = 1; i < 5; i++)
    {
        Vector edge = b[i % 4] - b[i - 1];
        Vector perp(-edge[1], edge[0]);

        float test = perp.dot(a[(i + 1) % 4] - b[i - 1]);
        int side = (test > 0) - (test < 0);
        
        int count = 0;
        for (unsigned int j = 0; j < 4; j++)
        {
            test = perp.dot(b[j] - b[i - 1]);
            count += (test > 0) - (test < 0);
        }

        if (count == 4 * -1 * side)
        {
            return false;
        }
    }

    return true;
}

void CollideSubsystem::process(unsigned int dt)
{
    for (std::set<Entity>::const_iterator iter = active.begin();
            iter != active.end();
            iter++)
    {
        CollideComponent *cc = world->get<CollideComponent>(*iter);
        cc->collided = false;
    }

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

            Vector a_points[4];
            to_points(at->position, ac->half_width, ac->half_height, at->rotation, a_points);
            Vector b_points[4];
            to_points(bt->position, bc->half_width, bc->half_height, bt->rotation, b_points);
            // ||a - b|| <= (ar * ar + br * br)^2
            if (//(at->position - bt->position).magnitude() <= (ar * ar + 2 * ar * br + br * br) &&
                    are_rects_colliding(a_points, b_points))
            {
                std::cout << at->position << std::endl;
                ac->collided = true;
                bc->collided = true;
                //Vector anew = (bt->velocity * 2 * bw + at->velocity * (aw - bw)) / (aw + bw);
                //Vector bnew = (at->velocity * 2 * aw - bt->velocity * (aw - bw)) / (aw + bw);

                //at->velocity = anew;
                //bt->velocity = bnew;
            }
        }
    }
}

