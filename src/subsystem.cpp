#include "subsystem.h"

Subsystem::Subsystem(World *_world) : 
          world(_world)
        , interests(std::vector<bool>(_world->get_num_components(), false))
{
}

Subsystem::~Subsystem()
{
}

void Subsystem::changed(const Entity &entity)
{
    unsigned short pos = 0;
    for (std::vector<bool>::const_iterator iter = interests.begin(); iter != interests.end(); iter++)
    {
        if (*iter)
        {
            if (!world->has(entity, pos))
            {
                return;
            }
        }

        pos++;
    }

    active.insert(entity);
}

void Subsystem::process()
{
    for (std::set<Entity>::const_iterator iter = active.begin(); iter != active.end(); iter++)
    {
        process_entity(*iter);
    }
}

