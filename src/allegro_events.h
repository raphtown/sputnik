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

    void register_source(AllegroDisplay *display);

    bool get(ALLEGRO_EVENT *ev);
};

#endif
