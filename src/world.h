#ifndef _WORLD_H
#define _WORLD_H

#include <map>
#include <queue>
#include <set>
#include <utility>

#include "debug.h"

#include "entity.h"
#include "entity_component_manager.h"
#include "entity_manager.h"
#include "subsystem_manager.h"

class EntityComponent;
class Subsystem;

class World
{
private:
    EntityManager *em;
    EntityComponentManager *ecm;
    SubsystemManager *sm;

    std::set<Entity> to_refresh;
    std::set<Entity> to_destroy;
    std::queue<std::pair<Entity, unsigned short> > to_remove;

public:
    World();
    ~World();

    // This method instantiates the component and adds it to the entity.
    // An example call is world.add<TransformComponent>(entity)
    template <class C>
    C *add(const Entity &entity);

    template <class C>
    C *add_subsystem(C *subsystem);

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
    //
    // Adding components is not deferred, so this can return both false and
    // true within the same tick.
    template <class C>
    bool has(const Entity &entity);

    // This method returns true if the entity has the given component by
    // component_type
    bool has(const Entity &entity, unsigned short component_type);

    void process(unsigned int dt);
    void refresh(const Entity &entity);

    template <class C>
    void remove(const Entity &entity);
};

template <class C>
inline C *World::add(const Entity &entity)
{
    static const unsigned short component_type = get_component_type<C>();
    EntityComponent *component = ecm->create(component_type);
    em->add(entity, component);
    to_refresh.insert(entity);
    return dynamic_cast<C *>(component);
}

template <class C>
inline C *World::add_subsystem(C *subsystem) {
    sm->register_subsystem(subsystem);
    return subsystem;
}

template <class C>
inline C *World::get(const Entity &entity)
{
    SPUTNIK_ASSERT(has<C>(entity), "Entity does not have this component");

    static const unsigned short component_type = get_component_type<C>();
    return dynamic_cast<C *>(em->get(entity, component_type));
}

template <class C>
inline unsigned short World::get_component_type() {
    return ecm->get_id<C>();
}

template <class C>
inline bool World::has(const Entity &entity)
{
    static const unsigned short component_type = get_component_type<C>();
    return em->has(entity, component_type);
}

template <class C>
inline void World::remove(const Entity &entity)
{
    static const unsigned short component_type = get_component_type<C>();
    to_remove.push(std::make_pair(entity, component_type));
    to_refresh.insert(entity);
}

#endif

