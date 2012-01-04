#include "player_controller_subsystem.h"

#include <cmath>

#include "player_component.h"
#include "transform_component.h"
#include "vector.h"
#include "world.h"

PlayerControllerSubsystem::PlayerControllerSubsystem(World &_world) : 
          Subsystem(_world)
{
    events.register_keyboard_source();

    require<PlayerComponent>();
    require<TransformComponent>();

    for (unsigned int i = 0; i < NUM_BUTTONS; i++)
    {
        button_states[i] = false;
    }
}

void PlayerControllerSubsystem::process(unsigned int dt)
{
    ALLEGRO_EVENT ev;
    while (events.get(&ev))
    {
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_W: button_states[MOVE_FORWARD] = true; break;
                case ALLEGRO_KEY_A: button_states[ROTATE_LEFT] = true; break;
                case ALLEGRO_KEY_S: button_states[MOVE_BACKWARD] = true; break;
                case ALLEGRO_KEY_D: button_states[ROTATE_RIGHT] = true; break;
            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch (ev.keyboard.keycode)
            {
                case ALLEGRO_KEY_W: button_states[MOVE_FORWARD] = false; break;
                case ALLEGRO_KEY_A: button_states[ROTATE_LEFT] = false; break;
                case ALLEGRO_KEY_S: button_states[MOVE_BACKWARD] = false; break;
                case ALLEGRO_KEY_D: button_states[ROTATE_RIGHT] = false; break;
            }
        }
    }

    for (std::set<Entity>::const_iterator iter = active.begin(); iter != active.end(); iter++)
    {
        TransformComponent *tc = world->get<TransformComponent>(*iter);

        static const float max_speed = 0.3;
        if (tc->velocity.squaredNorm() > max_speed * max_speed)
        {
            tc->velocity *= 1 / tc->velocity.norm() * max_speed;
        }

        if (button_states[MOVE_FORWARD])
        {
            tc->acceleration(0) += cos(tc->rotation) / 1000;
            tc->acceleration(1) += sin(tc->rotation) / 1000;
        }
        if (button_states[MOVE_BACKWARD])
        {
            tc->acceleration(0) -= cos(tc->rotation) / 1000;
            tc->acceleration(1) -= sin(tc->rotation) / 1000;
        }

        if (button_states[ROTATE_LEFT])
        {
            tc->rotation += 0.1;
        }
        if (button_states[ROTATE_RIGHT])
        {
            tc->rotation -= 0.1;
        }
    }
}

