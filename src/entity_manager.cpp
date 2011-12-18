#include "entity_manager.h"

EntityManager::EntityManager(EntityComponentManager *_ecm) : ecm(_ecm), nextId(0) {
}

EntityManager::~EntityManager() {
	for (ComponentTypeMap::iterator iter = components.begin(); iter != components.end(); iter++) {
		EntityComponentMap &components = iter->second;
        for (EntityComponentMap::iterator iter2 = components.begin(); iter2 != components.end(); iter2++) {
            delete(iter2->second);
        }
    }
}

const Entity EntityManager::create() {
    return nextId++;
}

void EntityManager::destroy(const Entity &entity) {
	for (ComponentTypeMap::iterator iter = components.begin(); iter != components.end(); iter++) {
		EntityComponentMap &map = iter->second;

		EntityComponent *component = map[entity];
		if (component) {
			map.erase(entity);

			entities[component->get_component_type()].erase(entity);

			delete component;
		}
    }
}

const Entity EntityManager::get(unsigned int id) {
    return id;
}
