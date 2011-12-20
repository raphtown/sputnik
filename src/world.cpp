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
    em->destroy(entity);
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

void World::refresh(const Entity &entity) {
    sm->refresh(entity);
}

