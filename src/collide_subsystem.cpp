#include "collide_subsystem.h"

#include <cmath>

#include "collide_component.h"
#include "transform_component.h"
#include "world.h"

CollideSubsystem::CollideSubsystem(World &world) : Subsystem(world)
{
    require<CollideComponent>();
    require<TransformComponent>();
}

static bool are_rects_colliding(
        float a_x, float a_y, float a_half_width, float a_half_height, float a_rotation,
        float b_x, float b_y, float b_half_width, float b_half_height, float b_rotation)
{
    float a_cos = cos(a_rotation);
    float a_sin = sin(a_rotation);
    float b_cos = cos(b_rotation);
    float b_sin = sin(b_rotation);

    // TL TR BR BL
    float a_points[][2] = { 
        {
            a_x - (a_cos * a_half_width - a_sin * a_half_height),
            a_y + (a_sin * a_half_width + a_cos * a_half_height),
        },
        {
            a_x + (a_cos * a_half_width - a_sin * a_half_height),
            a_y + (a_sin * a_half_width + a_cos * a_half_height),
        },
        {
            a_x + (a_cos * a_half_width - a_sin * a_half_height),
            a_y - (a_sin * a_half_width + a_cos * a_half_height),
        },
        {
            a_x - (a_cos * a_half_width - a_sin * a_half_height),
            a_y - (a_sin * a_half_width + a_cos * a_half_height),
        },
    };
    float b_points[][2] = { 
        {
            b_x - (b_cos * b_half_width - b_sin * b_half_height),
            b_y + (b_sin * b_half_width + b_cos * b_half_height),
        },
        {
            b_x + (b_cos * b_half_width - b_sin * b_half_height),
            b_y + (b_sin * b_half_width + b_cos * b_half_height),
        },
        {
            b_x + (b_cos * b_half_width - b_sin * b_half_height),
            b_y - (b_sin * b_half_width + b_cos * b_half_height),
        },
        {
            b_x - (b_cos * b_half_width - b_sin * b_half_height),
            b_y - (b_sin * b_half_width + b_cos * b_half_height),
        },
    };

    for (unsigned int i = 1; i < 5; i++)
    {
        float edge[2] = { 
            a_points[i % 4][0] - a_points[i - 1][0],
            a_points[i % 4][1] - a_points[i - 1][1],
        };
        float perp[2] = { -edge[1], edge[0] };

        float sides = 0;
        for (unsigned int j = 0; j < 4; j++)
        {
            float test = 
                perp[0] * (a_points[j][0] - a_points[i - 1][0]) +
                perp[1] * (a_points[j][1] - a_points[i - 1][1]);
            sides += (test > 0) - (test < 0);
        }
        for (unsigned int j = 0; j < 4; j++)
        {
            float test = 
                perp[0] * (b_points[j][0] - a_points[i - 1][0]) +
                perp[1] * (b_points[j][1] - a_points[i - 1][1]);
            sides += (test > 0) - (test < 0);
        }

        if (sides == -1 || sides == 1)
        {
            return false;
        }
    }

    for (unsigned int i = 1; i < 5; i++)
    {
        float edge[2] = { 
            b_points[i % 4][0] - b_points[i - 1][0],
            b_points[i % 4][1] - b_points[i - 1][1],
        };
        float perp[2] = { -edge[1], edge[0] };

        float sides = 0;
        for (unsigned int j = 0; j < 4; j++)
        {
            float test = 
                perp[0] * (a_points[j][0] - b_points[i - 1][0]) +
                perp[1] * (a_points[j][1] - b_points[i - 1][1]);
            sides += (test > 0) - (test < 0);
        }
        for (unsigned int j = 0; j < 4; j++)
        {
            float test = 
                perp[0] * (b_points[j][0] - b_points[i - 1][0]) +
                perp[1] * (b_points[j][1] - b_points[i - 1][1]);
            sides += (test > 0) - (test < 0);
        }

        if (sides == -1 || sides == 1)
        {
            return false;
        }
    }

    return true;
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
            if ((at->position - bt->position).magnitude() <= (ar * ar + 2 * ar * br + br * br)
                    && are_rects_colliding(
                        at->position.x, 
                        at->position.y,
                        ac->half_width,
                        ac->half_height,
                        at->rotation,
                        bt->position.x, 
                        bt->position.y,
                        bc->half_width,
                        bc->half_height,
                        bt->rotation))
            {
                Vector anew = (bt->velocity * 2 * bw + at->velocity * (aw - bw)) / (aw + bw);
                Vector bnew = (at->velocity * 2 * aw - bt->velocity * (aw - bw)) / (aw + bw);

                at->velocity = anew;
                bt->velocity = bnew;
            }
        }
    }
}

