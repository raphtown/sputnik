#ifndef _ALLEGRO_EVENTS_H
#define _ALLEGRO_EVENTS_H

#include <allegro5/allegro.h>

class AllegroDisplay;

class AllegroEvents
{
private:
    ALLEGRO_EVENT_QUEUE *queue;

public:
    AllegroEvents();
    ~AllegroEvents();

    void register_display_source(AllegroDisplay *display);
    void register_keyboard_source();

    bool get(ALLEGRO_EVENT *ev);
};

#endif
