#ifndef _WORLD_H
#define _WORLD_H

#include <map>
#include <string>

#include "entity.h"
#include "entity_component_manager.h"
#include "entity_manager.h"

class EntityComponent;
class Subsystem;
class SubsystemManager;

class World
{
private:
    EntityManager *em;
    EntityComponentManager *ecm;
    SubsystemManager *sm;

public:
    World();
    ~World();

    // This method instantiates the component and adds it to the entity.
    // An example call is world.add<TransformComponent>(entity)
    template <class C>
    C *add(const Entity &entity);

    Subsystem *add_subsystem(Subsystem *subsystem);

    const Entity create();
    void destroy(const Entity &entity);

    // This method gets the desired component
    // world.get<TransformComponent>(entity)
    template <class C>
    C *get(const Entity &entity);

    // This method gets the desired component by component type
    const Entity get(unsigned int id);

    template <class C>
    unsigned short get_component_type();

    unsigned int get_num_components();

    // This method returns true if the entity has the given component
    // world.has<TransformComponent>(entity)
    template <class C>
    bool has(const Entity &entity);

    // This method returns true if the entity has the given component by
    // component_type
    bool has(const Entity &entity, unsigned short component_type);

    void refresh(const Entity &entity);
};

template <class C>
C *World::add(const Entity &entity)
{
    static const unsigned short component_type = get_component_type<C>();
    EntityComponent *component = ecm->create(component_type);
    em->add(entity, component);
    return dynamic_cast<C *>(component);
}

template <class C>
C *World::get(const Entity &entity)
{
    static const unsigned short component_type = get_component_type<C>();
    return dynamic_cast<C *>(em->get(entity, component_type));
}

template <class C>
unsigned short World::get_component_type() {
    return ecm->get_id<C>();
}

template <class C>
bool World::has(const Entity &entity)
{
    static const unsigned short component_type = get_component_type<C>();
    return em->has(entity, component_type);
}

#endif

