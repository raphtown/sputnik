#include "render_subsystem.h"

RenderSubsystem::RenderSubsystem(EntityManager *_em, EntityComponentManager *_ecm) : Subsystem(_em, _ecm)
{
}

void RenderSubsystem::process_entity(const Entity &entity)
{
    SpriteComponent *sc = em->get<SpriteComponent>(entity);
    TransformComponent *tc = em->get<TransformComponent>(entity);

    ALLEGRO_BITMAP *bitmap = al_load_bitmap(sc->filename);
    SPUTNIK_ASSERT(bitmap != NULL, "Bitmap is null");

    al_draw_rotated_bitmap(bitmap, al_get_bitmap_width(bitmap) / 2, al_get_bitmap_height(bitmap) / 2, tc->x, tc->y, tc->rotation, 0);
    al_destroy_bitmap(bitmap);
}
