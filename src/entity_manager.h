#ifndef _ENTITY_MANAGER_H
#define _ENTITY_MANAGER_H

#include <map>
#include <set>
#include <string>

#include "debug.h"

#include "entity_component.h"
#include "entity_component_manager.h"

typedef unsigned int Entity;

class EntityComponentManager;

class EntityManager {
private:
	EntityComponentManager *ecm;

	// just make ids sequential
    int nextId;

	std::map<const Entity, std::map<unsigned short, EntityComponent *>> entities;

public:
	EntityManager(EntityComponentManager *ecm);
    ~EntityManager();

    const Entity create();
    void destroy(const Entity &entity);
    const Entity get(unsigned int id);
    bool has(const Entity &entity, unsigned short component_type);

	// This method instantiates the component and adds it to the entity.
	// An example call is entity_manager.add<TransformComponent>(entity)
    template <class C>
    C *add(const Entity &entity) {
		C *component = ecm->create<C>();
		unsigned short component_type = component->get_component_type();

		entities[entity][component_type] = component;

		return component;
    }

	// This method gets the desired component
	// entity_manager.get<TransformComponent>(entity)
    template <class C>
    C *get(const Entity &entity) {
		static const unsigned short component_type = ecm->get_id<C>();
        EntityComponent *component = entities[entity][component_type];

        return dynamic_cast<C *>(component);
    }

	// This method returns true if the entity has the given component
	// entity_manager.has<TransformComponent>(entity)
	template <class C>
	bool has(const Entity &entity) {
		static const unsigned short component_type = ecm->get_id<C>();

		return entities[entity].count(component_type) > 0;
	}
};

#endif