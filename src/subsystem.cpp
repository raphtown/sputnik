#include "subsystem.h"

Subsystem::Subsystem(EntityManager *_em, EntityComponentManager *_ecm) : em(_em), ecm(_ecm), interests(ecm->get_num_components(), false) {
}

Subsystem::~Subsystem() {
}

void Subsystem::process() {
	for (std::set<const Entity>::const_iterator iter = active.begin(); iter != active.end(); iter++) {
		processEntity(*iter);
	}
}
