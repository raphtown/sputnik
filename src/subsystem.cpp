#include "subsystem.h"

Subsystem::Subsystem(EntityManager *_em, EntityComponentManager *_ecm) : em(_em), ecm(_ecm), interests(ecm->get_num_components(), false) {
}

Subsystem::~Subsystem() {
}

void Subsystem::changed(const Entity &entity) {
	unsigned short pos = 0;
	for (std::vector<bool>::const_iterator iter = interests.begin(); iter != interests.end(); iter++) {
		if (*iter) {
			if (!em->has(entity, pos)) {
				return;
			}
		}

		pos++;
	}

	active.insert(entity);
}

void Subsystem::process() {
	for (std::set<const Entity>::const_iterator iter = active.begin(); iter != active.end(); iter++) {
		process_entity(*iter);
	}
}
