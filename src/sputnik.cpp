#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include "debug.h"
#include "sputnik_config.h"

#include "allegro_display.h"
#include "allegro_events.h"
#include "platform.h"
#include "world.h"

#include "collide_component.h"
#include "collide_subsystem.h"
#include "performance_subsystem.h"
#include "physics_subsystem.h"
#include "player_controller_subsystem.h"
#include "player_component.h"
#include "render_subsystem.h"
#include "transform_component.h"
#include "sprite_component.h"

int main(int argc, char **argv)
{
    SPUTNIK_ASSERT(al_init(), "Failed to initialize allegro");
    al_init_font_addon();
    SPUTNIK_ASSERT(al_init_ttf_addon(), "Failed to initialize allegro ttf");
    SPUTNIK_ASSERT(al_init_image_addon(), "Failed to initialize allegro image");
    SPUTNIK_ASSERT(al_init_primitives_addon(), "Failed to initialize allegro primitives");

    SPUTNIK_ASSERT(al_install_keyboard(), "Failed to install keyboard");

    SPUTNIK_ASSERT(al_filename_exists("../assets/ship.png"), "No ship.png");

    AllegroDisplay display(800, 600);
    AllegroEvents events;
    events.register_display_source(&display);
    events.register_keyboard_source();

    World world;
    world.add_subsystem(new PlayerControllerSubsystem(world));
    RenderSubsystem *rs = world.add_subsystem(new RenderSubsystem(world, display));
    world.add_subsystem(new PerformanceSubsystem(world, display));
    world.add_subsystem(new CollideSubsystem(world));
    world.add_subsystem(new PhysicsSubsystem(world));

    const Entity player = world.create();
    CollideComponent *cc = world.add<CollideComponent>(player);
    cc->half_width = 40;
    cc->half_height = 20;
    cc->radius = 40;
    cc->weight = 100;
    world.add<PlayerComponent>(player);

    SpriteComponent *sc = world.add<SpriteComponent>(player);
    sc->filename = new char[100];
    strcpy(sc->filename, "../assets/ship.png");

    world.add<TransformComponent>(player);
    TransformComponent *tc = world.get<TransformComponent>(player);
    tc->position.x = 0;
    tc->position.y = 0;
    
    world.refresh(player);
    rs->track(player);

    const Entity other = world.create();
    CollideComponent *occ = world.add<CollideComponent>(other);
    occ->half_width = 40;
    occ->half_height = 20;
    occ->radius = 40;
    occ->weight = 100;

    TransformComponent *otc = world.add<TransformComponent>(other);
    otc->position.x = 100;
    otc->position.y = 40;
    otc->rotation = 0;

    SpriteComponent *osc = world.add<SpriteComponent>(other);
    osc->filename = new char[100];
    strcpy(osc->filename, "../assets/ship.png");

    world.refresh(other);

    // Since rendering is a subsystem run once every tick one tick = one frame
    unsigned int last = Platform::get_milliseconds();
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
            else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                {
                    quit = true;
                }
            }
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));

        unsigned int now = Platform::get_milliseconds();
        world.process(now - last);
        last = now;

        display.flip();
    }

    return 0;
}

