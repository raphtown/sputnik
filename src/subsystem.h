#ifndef _SUBSYSTEM_H
#define _SUBSYSTEM_H

#include <set>
#include <vector>

#include "entity_component_manager.h"
#include "entity_manager.h"

class Subsystem {
protected:
	EntityManager *em;
	EntityComponentManager *ecm;

	std::vector<bool> interests;
	std::set<const Entity> active;

	Subsystem(EntityManager *em, EntityComponentManager *ecm);
	virtual void process_entity(const Entity &entity) = 0;

	template <class C>
	void require() {
		static const unsigned short component_type = ecm->get_id<C>();
		interests[component_type] = true;
	}

public:
	virtual ~Subsystem();

	void changed(const Entity &entity);
	void process();
};

#endif
