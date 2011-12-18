#ifndef _SUBSYSTEM_MANAGER_H
#define _SUBSYSTEM_MANAGER_H

#include <vector>

#include "entity_manager.h"
#include "subsystem.h"

class SubsystemManager {
private:
	std::vector<Subsystem *> subsystems;

public:
	SubsystemManager();
	~SubsystemManager();

	void refresh(const Entity &entity);
	void register_subsystem(Subsystem *subsystem);
};

#endif
