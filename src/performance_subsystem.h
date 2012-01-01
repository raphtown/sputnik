#ifndef _PERFORMANCE_SYSTEM_H
#define _PERFORMANCE_SYSTEM_H

#include "subsystem.h"

class ALLEGRO_FONT;

class AllegroDisplay;
class World;

class PerformanceSubsystem : public Subsystem
{
private:
    static const unsigned int history_size = 180;
    unsigned int history_pos;
    unsigned int dt_history[history_size];

    const AllegroDisplay *display;

    const ALLEGRO_FONT *font;

public:
    PerformanceSubsystem(World &world, const AllegroDisplay &display);
    ~PerformanceSubsystem();

    void process(unsigned int dt);
};

#endif

