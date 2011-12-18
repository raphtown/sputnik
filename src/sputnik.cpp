#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "debug.h"
#include "sputnik_config.h"

#include "allegro_display.h"
#include "allegro_events.h"
#include "entity_component_manager.h"
#include "entity_manager.h"
#include "subsystem_manager.h"

#include "render_subsystem.h"
#include "transform_component.h"
#include "sprite_component.h"
 
int main(int argc, char **argv) {
	SPUTNIK_ASSERT(al_init(), "Failed to initialize allegro");
	SPUTNIK_ASSERT(al_init_image_addon(), "Failed to initialize allegro image");

	SPUTNIK_ASSERT(al_filename_exists("../assets/ship.png"), "No ship.png");
 
	AllegroDisplay display(640, 480);
	AllegroEvents events;
	events.register_source(&display);

	EntityComponentManager ecm;
	EntityManager em(&ecm);
	SubsystemManager sm;

	RenderSubsystem rs(&em, &ecm);
	sm.register_subsystem(&rs);

	const Entity player = em.create();
	SpriteComponent *sc = em.add<SpriteComponent>(player);
	sc->filename = new char[100];
	strcpy(sc->filename, "../assets/ship.png");

	em.add<TransformComponent>(player);
	TransformComponent *tc = em.get<TransformComponent>(player);
	tc->x = 30;
	tc->y = 30;
	tc->rotation = 0;

	sm.refresh(player);

	bool quit = false;
	while (!quit) {
		ALLEGRO_EVENT ev;

		while (events.get(&ev)) {
			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				quit = true;
			}
		}

		al_clear_to_color(al_map_rgb(0, 0, 0));
		rs.process();

		display.flip();
	}

	em.destroy(player);
 
	return 0;
}
