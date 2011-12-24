#include "world.h"

#include "debug.h"

#include "subsystem.h"
#include "subsystem_manager.h"

World::World() : 
          em(new EntityManager())
        , ecm(new EntityComponentManager())
        , sm(new SubsystemManager())
{
}

World::~World()
{
    delete em;
    delete ecm;
    delete sm;
}

Subsystem *World::add_subsystem(Subsystem *subsystem) {
    sm->register_subsystem(subsystem);
    return subsystem;
}

const Entity World::create()
{
    return em->create();
}

void World::destroy(const Entity &entity)
{
    to_destroy.insert(entity);
}

const Entity World::get(unsigned int id)
{
    return em->get(id);
}

unsigned int World::get_num_components() {
    return ecm->get_num_components();
}

bool World::has(const Entity &entity, unsigned short component_type)
{
    return em->has(entity, component_type);
}

void World::process()
{
    while (!to_remove.empty())
    {
        std::pair<Entity, unsigned short> pair = to_remove.front();
        to_remove.pop();

        em->remove(pair.first, pair.second);
    }

    for (std::set<Entity>::iterator iter = to_refresh.begin(); iter != to_refresh.end(); iter++)
    {
        const Entity &entity = *iter;

        sm->refresh(entity);
    }
    to_refresh.clear();

    for (std::set<Entity>::iterator iter = to_destroy.begin(); iter != to_destroy.end(); iter++)
    {
        const Entity &entity = *iter;

        sm->destroyed(entity);
        em->destroy(entity);
    }
    to_destroy.clear();

    sm->process();
}

void World::refresh(const Entity &entity) {
    to_refresh.insert(entity);
}

