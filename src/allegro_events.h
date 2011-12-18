#ifndef _ALLEGRO_EVENTS_H
#define _ALLEGRO_EVENTS_H

#include <allegro5/allegro.h>

#include "debug.h"

#include "allegro_display.h"

class AllegroEvents {
private:
	ALLEGRO_EVENT_QUEUE *queue;

public:
	AllegroEvents();
	~AllegroEvents();

	void register_source(AllegroDisplay *display);
	
	bool get(ALLEGRO_EVENT *ev);
};

#endif
