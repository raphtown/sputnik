#include "render_subsystem.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "debug.h"

#include "allegro_display.h"
#include "sprite_component.h"
#include "transform_component.h"
#include "world.h"

RenderSubsystem::RenderSubsystem(World &_world, const AllegroDisplay &_display) : 
        Subsystem(_world), display(&_display)
{
    require<SpriteComponent>();
    require<TransformComponent>();

    background = al_load_bitmap("../assets/bg.jpg");
    SPUTNIK_ASSERT(background != NULL, "Bitmap is null");
}

RenderSubsystem::~RenderSubsystem()
{
    al_destroy_bitmap(background);
}

void RenderSubsystem::process_entity(const Vector &camera, const Entity &entity)
{
    SpriteComponent *sc = world->get<SpriteComponent>(entity);
    TransformComponent *tc = world->get<TransformComponent>(entity);

    ALLEGRO_BITMAP *bitmap = al_load_bitmap(sc->filename);
    SPUTNIK_ASSERT(bitmap != NULL, "Bitmap is null");

    float x = tc->position.x - camera.x + display->width / 2;
    float y = tc->position.y - camera.y + display->height / 2;
    al_draw_rotated_bitmap(
            bitmap, 
            al_get_bitmap_width(bitmap) / 2, 
            al_get_bitmap_height(bitmap) / 2, 
            x, 
            y, 
            tc->rotation, 
            0);
    al_destroy_bitmap(bitmap);
}

void RenderSubsystem::process(unsigned int dt)
{
    TransformComponent *camera_tc = world->get<TransformComponent>(*tracking);

    al_draw_bitmap_region(background, 
            camera_tc->position.x - display->width / 2,
            camera_tc->position.y - display->height / 2,
            display->width,
            display->height,
            0,
            0,
            0);

    for (std::set<Entity>::const_iterator iter = active.begin(); iter != active.end(); iter++)
    {
        process_entity(camera_tc->position, *iter);
    }
}

void RenderSubsystem::track(const Entity &entity)
{
    SPUTNIK_ASSERT(world->has<TransformComponent>(entity), "Need to track a transform component");
    tracking = &entity;
}
