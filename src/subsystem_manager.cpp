#include "subsystem_manager.h"

#include "subsystem.h"

SubsystemManager::SubsystemManager()
{
}

SubsystemManager::~SubsystemManager()
{
}

void SubsystemManager::destroyed(const Entity &entity) {
    for (std::vector<Subsystem *>::const_iterator iter = subsystems.begin(); iter != subsystems.end(); iter++)
    {
        Subsystem *subsystem = *iter;
        subsystem->destroyed(entity);
    }
}

void SubsystemManager::process(unsigned int dt)
{
    for (std::vector<Subsystem *>::const_iterator iter = subsystems.begin(); iter != subsystems.end(); iter++)
    {
        (*iter)->process(dt);
    }
}

void SubsystemManager::refresh(const Entity &entity)
{
    for (std::vector<Subsystem *>::const_iterator iter = subsystems.begin(); iter != subsystems.end(); iter++)
    {
        Subsystem *subsystem = *iter;
        subsystem->changed(entity);
    }
}

void SubsystemManager::register_subsystem(Subsystem *subsystem)
{
    subsystems.push_back(subsystem);
}
