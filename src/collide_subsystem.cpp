#include "collide_subsystem.h"

#include <cmath>

#include "debug.h"

#include "collide_component.h"
#include "transform_component.h"
#include "world.h"

#include <iostream>

struct Projection
{
    float min, max;
};

CollideSubsystem::CollideSubsystem(World &world) : Subsystem(world)
{
    require<CollideComponent>();
    require<TransformComponent>();
}

static void to_points(const Vector &position, float hw, float hh,
        float rotation, Vector points[4])
{
    float c = cos(rotation);
    float s = sin(rotation);

    points[0] = Vector(position(0) + (c * -hw - s *  hh), position(1) + (s * -hw + c *  hh));
    points[1] = Vector(position(0) + (c *  hw - s *  hh), position(1) + (s *  hw + c *  hh));
    points[2] = Vector(position(0) + (c *  hw - s * -hh), position(1) + (s *  hw + c * -hh));
    points[3] = Vector(position(0) + (c * -hw - s * -hh), position(1) + (s * -hw + c * -hh));
}

static Projection project(const Vector points[4], const Vector &axis)
{
    Projection p;
    p.min = points[0].dot(axis);
    p.max = p.min;

    for (unsigned int i = 1; i < 4; i++)
    {
        float d = points[i].dot(axis);
        if (d < p.min)
        {
            p.min = d;
        }
        else if (d > p.max)
        {
            p.max = d;
        }
    }

    return p;
}

static float get_overlap(const Projection &p1, const Projection &p2)
{
    if (p1.min >= p2.min && p1.max <= p2.max)
    {
        return p1.max - p1.min;
    }
    else if (p2.min >= p1.min && p2.max <= p1.max)
    {
        return p2.max - p2.min;
    }
    else if (p1.min <= p2.min && p1.max <= p2.max)
    {
        return p1.max - p2.min;
    }
    else if (p2.min <= p1.min && p2.max <= p1.max)
    {
        return p2.max - p1.min;
    }
    else
    {
        SPUTNIK_ASSERT(true, "Unhandled overlap case");
        return 0;
    }
}

static bool are_rects_colliding(const Vector a[4], const Vector b[4], Vector &mtv)
{
    Vector smallest;
    float smallest_overlap = -1;

    for (unsigned int i = 1; i < 5; i++)
    {
        Vector edge = a[i % 4] - a[i - 1];
        Vector axis(-edge[1], edge[0]);
        axis /= axis.norm();

        Projection p1 = project(a, axis);
        Projection p2 = project(b, axis);

        if (p1.max < p2.min || p1.min > p2.max)
        {
            return false;
        }
        else
        {
            float overlap = get_overlap(p1, p2);
            if (smallest_overlap == -1 || overlap < smallest_overlap)
            {
                smallest = axis;
                smallest_overlap = overlap;
            }
        }
    }

    for (unsigned int i = 1; i < 5; i++)
    {
        Vector edge = b[i % 4] - b[i - 1];
        Vector axis(-edge[1], edge[0]);
        axis /= axis.norm();

        Projection p1 = project(a, axis);
        Projection p2 = project(b, axis);

        if (p1.max < p2.min || p1.min > p2.max)
        {
            return false;
        }
        else
        {
            float overlap = get_overlap(p1, p2);
            if (overlap < smallest_overlap)
            {
                smallest = axis;
                smallest_overlap = overlap;
            }
        }
    }

    mtv = smallest * smallest_overlap;

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

            Vector mtv;
            // ||a - b|| <= (ar * ar + br * br)^2
            if (//(at->position - bt->position).magnitude() <= (ar * ar + 2 * ar * br + br * br) &&
                    are_rects_colliding(a_points, b_points, mtv))
            {
                mtv /= 1.5f;
                at->position -= mtv;
                bt->position += mtv;

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

