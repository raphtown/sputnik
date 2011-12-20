#ifndef _ENTITY_COMPONENT_MANAGER_H
#define _ENTITY_COMPONENT_MANAGER_H

#include <map>
#include <string>
#include <typeinfo>

#include "entity_component.h"
#include "sprite_component.h"
#include "transform_component.h"

class EntityComponentManager
{
private:
    unsigned short num_components;

    std::map<unsigned short, EntityComponent *(*)(unsigned short)> creators;
    std::map<std::string, unsigned short> name_to_id;

    void register_components();

public:
    EntityComponentManager();
    ~EntityComponentManager();

    EntityComponent *create(unsigned short id);
    unsigned short get_num_components();

    template <class C>
    C *create()
    {
        static const unsigned short component_id = name_to_id[typeid(C).name()];
        return new C(component_id);
    }

    template <class C>
    unsigned short get_id()
    {
        static const unsigned short component_id = name_to_id[typeid(C).name()];
        return component_id;
    }
};

#endif
