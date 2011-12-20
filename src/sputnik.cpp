#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "debug.h"
#include "sputnik_config.h"

#include "allegro_display.h"
#include "allegro_events.h"
#include "world.h"

#include "render_subsystem.h"
#include "transform_component.h"
#include "sprite_component.h"

int main(int argc, char **argv)
{
    SPUTNIK_ASSERT(al_init(), "Failed to initialize allegro");
    SPUTNIK_ASSERT(al_init_image_addon(), "Failed to initialize allegro image");

    SPUTNIK_ASSERT(al_filename_exists("../assets/ship.png"), "No ship.png");

    AllegroDisplay display(640, 480);
    AllegroEvents events;
    events.register_source(&display);

    World world;
    RenderSubsystem rs(&world);
    world.add_subsystem(&rs);

    const Entity player = world.create();
    SpriteComponent *sc = world.add<SpriteComponent>(player);
    sc->filename = new char[100];
    strcpy(sc->filename, "../assets/ship.png");

    world.add<TransformComponent>(player);
    TransformComponent *tc = world.get<TransformComponent>(player);
    tc->x = 30;
    tc->y = 30;
    tc->rotation = 0;
    
    world.refresh(player);

    bool quit = false;
    while (!quit)
    {
        ALLEGRO_EVENT ev;

        while (events.get(&ev))
        {
            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                quit = true;
            }
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));
        rs.process();
        display.flip();
    }

    world.destroy(player);

    return 0;
}

