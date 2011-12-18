#ifndef _ENTITY_MANAGER_H
#define _ENTITY_MANAGER_H

#include <map>
#include <set>
#include <string>

#include "debug.h"

#include "entity_component.h"
#include "entity_component_manager.h"

typedef unsigned int Entity;

// ComponentTypeMap is map<component name, map<entity, component>>
typedef std::map<Entity, EntityComponent *> EntityComponentMap;
typedef std::map<unsigned short, EntityComponentMap> ComponentTypeMap;

class EntityManager {
private:
	EntityComponentManager *ecm;

	// just make ids sequential
    int nextId;

    ComponentTypeMap components;
	std::map<unsigned short, std::set<const Entity>> entities;

public:
	EntityManager(EntityComponentManager *ecm);
    ~EntityManager();

    const Entity create();
    void destroy(const Entity &entity);
    const Entity get(unsigned int id);

	// This method instantiates the component and adds it to the entity.
	// An example call is entity_manager.add<TransformComponent>(entity)
    template <class C>
    C *add(const Entity &entity) {
		C *component = ecm->create<C>();
		unsigned short component_type = component->get_component_type();

		components[component_type][entity] = component;
		entities[component_type].insert(entity);

		return component;
    }

	// This method gets the desired component 
    template <class C>
    C *get(const Entity &entity) {
		static const unsigned short component_type = ecm->get_id<C>();
        EntityComponent *component = components[component_type][entity];

        return dynamic_cast<C *>(component);
    }

	template <class C>
	const std::set<const Entity> &get_all_with() {
		static const unsigned short component_type = ecm->get_id<C>();
		return entities[component_type];
	}
};

#endif