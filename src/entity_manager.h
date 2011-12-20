#ifndef _ENTITY_MANAGER_H
#define _ENTITY_MANAGER_H

#include <map>

#include "entity.h"

class EntityComponent;

class EntityManager
{
private:
    // just make ids sequential
    int next_id;

    std::map<Entity, std::map<unsigned short, EntityComponent *> > entities;

public:
    EntityManager();
    ~EntityManager();

    void add(const Entity &entity, EntityComponent *component);
    const Entity create();
    void destroy(const Entity &entity);
    const Entity get(unsigned int id);
    EntityComponent *get(const Entity &entity, unsigned short component_type);
    bool has(const Entity &entity, unsigned short component_type);
};

#endif

