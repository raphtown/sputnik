#ifndef _SUBSYSTEM_H
#define _SUBSYSTEM_H

#include <set>
#include <vector>

#include "world.h"

class Subsystem
{
protected:
    World *world;

    std::vector<bool> interests;
    std::set<Entity> active;

    Subsystem(World *world);
    virtual void process_entity(const Entity &entity) = 0;

    template <class C>
    void require()
    {
        static const unsigned short component_type = world->get_component_type<C>();
        interests[component_type] = true;
    }

public:
    virtual ~Subsystem();

    void changed(const Entity &entity);
    void process();
};

#endif

