#ifndef _ALLEGRO_DISPLAY_H
#define _ALLEGRO_DISPLAY_H

#include <allegro5/allegro.h>

class AllegroDisplay
{
private:
    ALLEGRO_DISPLAY *display;

public:
    const unsigned int width;
    const unsigned int height;

    AllegroDisplay(unsigned int width, unsigned int height);
    ~AllegroDisplay();

    ALLEGRO_DISPLAY *expose();
    void flip();
};

#endif
