#include "controller_subsystem.h"

#include "controller_component.h"
#include "transform_component.h"
#include "world.h"

ControllerSubsystem::ControllerSubsystem(World *_world) : 
          Subsystem(_world)
{
    events.register_keyboard_source();

    require<ControllerComponent>();
}

void ControllerSubsystem::process()
{
    ALLEGRO_EVENT ev;
    while (events.get(&ev))
    {
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (ev.keyboard.keycode == ALLEGRO_KEY_W)
            {
                for (std::set<Entity>::const_iterator iter = active.begin(); iter != active.end(); iter++)
                {
                    ControllerComponent *cc = world->get<ControllerComponent>(*iter);
                    cc->key_w = true;
                }
            }
            else if (ev.keyboard.keycode == ALLEGRO_KEY_S)
            {
                for (std::set<Entity>::const_iterator iter = active.begin(); iter != active.end(); iter++)
                {
                    ControllerComponent *cc = world->get<ControllerComponent>(*iter);
                    cc->key_s = true;
                }
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            if (ev.keyboard.keycode == ALLEGRO_KEY_W)
            {
                for (std::set<Entity>::const_iterator iter = active.begin(); iter != active.end(); iter++)
                {
                    ControllerComponent *cc = world->get<ControllerComponent>(*iter);
                    cc->key_w = false;
                }
            }
            else if (ev.keyboard.keycode == ALLEGRO_KEY_S)
            {
                for (std::set<Entity>::const_iterator iter = active.begin(); iter != active.end(); iter++)
                {
                    ControllerComponent *cc = world->get<ControllerComponent>(*iter);
                    cc->key_s = false;
                }
            }
        }
    }
}

