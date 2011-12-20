#include "allegro_display.h"

#include "debug.h"

AllegroDisplay::AllegroDisplay(unsigned int _width, unsigned int _height) : width(_width), height(_height)
{
    display = al_create_display(width, height);
    SPUTNIK_ASSERT(display, "Failed to create display");

    // sweet allegro bug in allegro 5.0, window gets created offscreen
    al_set_window_position(display, 300, 300);
}

AllegroDisplay::~AllegroDisplay()
{
    al_destroy_display(display);
}

ALLEGRO_DISPLAY *AllegroDisplay::expose()
{
    return display;
}

void AllegroDisplay::flip()
{
    al_flip_display();
}
