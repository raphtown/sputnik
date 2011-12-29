#include "render_subsystem.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "debug.h"

#include "allegro_display.h"
#include "sprite_component.h"
#include "transform_component.h"
#include "world.h"

RenderSubsystem::RenderSubsystem(World &_world, const AllegroDisplay &_display) : 
        Subsystem(_world), display(&_display), history_pos(0)
{
    require<SpriteComponent>();
    require<TransformComponent>();

    for (unsigned int i = 0; i < history_size; i++)
    {
        dt_history[i] = 0;
    }
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

    ALLEGRO_BITMAP *bitmap = al_load_bitmap("../assets/bg.jpg");
    SPUTNIK_ASSERT(bitmap != NULL, "Bitmap is null");

    al_draw_bitmap(bitmap, 
            display->width / 2 - camera_tc->position.x,
            display->height / 2 - camera_tc->position.y,
            0);

    al_destroy_bitmap(bitmap);

    for (std::set<Entity>::const_iterator iter = active.begin(); iter != active.end(); iter++)
    {
        process_entity(camera_tc->position, *iter);
    }

    dt_history[history_pos] = dt;
    history_pos = (history_pos + 1) % history_size;
    for (unsigned int i = history_pos; i < history_pos + history_size; i++)
    {
        unsigned int left = i - history_pos;
        unsigned int height = dt_history[i % history_size];

        ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);
        al_draw_line(20 + left * 2, display->height - 20 - height * 2, 
                20 + left * 2, display->height - 20, color, 0);
    }
}

void RenderSubsystem::track(const Entity &entity)
{
    SPUTNIK_ASSERT(world->has<TransformComponent>(entity), "Need to track a transform component");
    tracking = &entity;
}
