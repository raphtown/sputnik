#include "entity_component_manager.h"

#include "collide_component.h"
#include "player_component.h"
#include "sprite_component.h"
#include "transform_component.h"

EntityComponentManager::EntityComponentManager() : num_components(0)
{
    register_components();
}

template <class C>
EntityComponent *internal_create(unsigned short type)
{
    return new C(type);
}

void EntityComponentManager::register_components()
{
    creators[num_components] = internal_create<CollideComponent>;
    name_to_id[typeid(CollideComponent).name()] = num_components;
    num_components++;
    
    creators[num_components] = internal_create<PlayerComponent>;
    name_to_id[typeid(PlayerComponent).name()] = num_components;
    num_components++;
    
    creators[num_components] = internal_create<SpriteComponent>;
    name_to_id[typeid(SpriteComponent).name()] = num_components;
    num_components++;

    creators[num_components] = internal_create<TransformComponent>;
    name_to_id[typeid(TransformComponent).name()] = num_components;
    num_components++;
}

EntityComponentManager::~EntityComponentManager()
{
}

EntityComponent *EntityComponentManager::create(unsigned short type)
{
    return creators[type](type);
}

unsigned short EntityComponentManager::get_num_components()
{
    return num_components;
}
