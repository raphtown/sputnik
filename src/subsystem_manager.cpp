#include "subsystem_manager.h"

SubsystemManager::SubsystemManager() {
}

SubsystemManager::~SubsystemManager() {
}

void SubsystemManager::refresh(const Entity &entity) {
	for (std::vector<Subsystem *>::const_iterator iter = subsystems.begin(); iter != subsystems.end(); iter++) {
		Subsystem *subsystem = *iter;
		subsystem->changed(entity);
	}
}

void SubsystemManager::register_subsystem(Subsystem *subsystem) {
	subsystems.push_back(subsystem);
}