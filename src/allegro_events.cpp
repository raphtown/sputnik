#include "allegro_events.h"

#include "debug.h"

#include "allegro_display.h"

AllegroEvents::AllegroEvents()
{
    queue = al_create_event_queue();
    SPUTNIK_ASSERT(queue, "Failed to create event queue");
}

AllegroEvents::~AllegroEvents()
{
    al_destroy_event_queue(queue);
}

void AllegroEvents::register_display_source(AllegroDisplay *display)
{
    al_register_event_source(queue, al_get_display_event_source(display->expose()));
}

void AllegroEvents::register_keyboard_source()
{
    ALLEGRO_EVENT_SOURCE *kb_event_source = al_get_keyboard_event_source();
    SPUTNIK_ASSERT(kb_event_source, "Keyboard subsystem not installed");
    al_register_event_source(queue, kb_event_source);
}

bool AllegroEvents::get(ALLEGRO_EVENT *ev)
{
    return al_get_next_event(queue, ev);
}

