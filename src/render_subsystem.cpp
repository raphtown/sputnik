#include "render_subsystem.h"

#include <allegro5/allegro.h>

#include "debug.h"

#include "sprite_component.h"
#include "transform_component.h"
#include "world.h"

RenderSubsystem::RenderSubsystem(World *world) : Subsystem(world)
{
}

void RenderSubsystem::process_entity(const Entity &entity)
{
    SpriteComponent *sc = world->get<SpriteComponent>(entity);
    TransformComponent *tc = world->get<TransformComponent>(entity);

    ALLEGRO_BITMAP *bitmap = al_load_bitmap(sc->filename);
    SPUTNIK_ASSERT(bitmap != NULL, "Bitmap is null");

    al_draw_rotated_bitmap(bitmap, al_get_bitmap_width(bitmap) / 2, al_get_bitmap_height(bitmap) / 2, tc->position.x, tc->position.y, tc->rotation, 0);
    al_destroy_bitmap(bitmap);
}

void RenderSubsystem::process(unsigned int dt)
{
    for (std::set<Entity>::const_iterator iter = active.begin(); iter != active.end(); iter++)
    {
        process_entity(*iter);
    }
}

