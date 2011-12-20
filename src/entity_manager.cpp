#include "entity_manager.h"

#include "debug.h"

#include "entity_component.h"

EntityManager::EntityManager() : next_id(0)
{
}

EntityManager::~EntityManager()
{
    for (std::map<Entity, std::map<unsigned short, EntityComponent *> >::iterator iter = entities.begin(); iter != entities.end(); iter++)
    {
        std::map<unsigned short, EntityComponent *> &components = iter->second;
        for (std::map<unsigned short, EntityComponent *>::iterator iter2 = components.begin(); iter2 != components.end(); iter2++)
        {
            delete(iter2->second);
        }
    }
}

void EntityManager::add(const Entity &entity, EntityComponent *component) {
    entities[entity][component->get_component_type()] = component;
}

const Entity EntityManager::create()
{
    return next_id++;
}

void EntityManager::destroy(const Entity &entity)
{
    std::map<unsigned short, EntityComponent *> &components = entities[entity];

    for (std::map<unsigned short, EntityComponent *>::iterator iter = components.begin(); iter != components.end(); iter++)
    {
        delete iter->second;
    }

    entities.erase(entity);
}

const Entity EntityManager::get(unsigned int id)
{
    return id;
}

EntityComponent *EntityManager::get(const Entity &entity, unsigned short component_type) {
    return entities[entity][component_type];
}

bool EntityManager::has(const Entity &entity, unsigned short component_type)
{
    return entities[entity].count(component_type) > 0;
}

