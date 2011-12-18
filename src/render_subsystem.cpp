#include "render_subsystem.h"

RenderSubsystem::RenderSubsystem(EntityManager *_em, EntityComponentManager *_ecm) : Subsystem(_em, _ecm) {
}

void RenderSubsystem::processEntity(const Entity &entity) {
	SpriteComponent *sc = em->get<SpriteComponent>(entity);
	TransformComponent *tc = em->get<TransformComponent>(entity);

	ALLEGRO_BITMAP *bitmap = al_load_bitmap(sc->filename);
	al_draw_rotated_bitmap(bitmap, 0, 0, tc->x, tc->y, tc->rotation, 0);
	al_destroy_bitmap(bitmap);
}
