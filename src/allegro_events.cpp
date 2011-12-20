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

void AllegroEvents::register_source(AllegroDisplay *display)
{
    al_register_event_source(queue, al_get_display_event_source(display->expose()));
}

bool AllegroEvents::get(ALLEGRO_EVENT *ev)
{
    return al_get_next_event(queue, ev);
}
