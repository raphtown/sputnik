#include "performance_subsystem.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include "allegro_display.h"
#include "world.h"

PerformanceSubsystem::PerformanceSubsystem(World &_world, const AllegroDisplay &_display) :
    Subsystem(_world), history_pos(0), display(&_display)
{
    for (unsigned int i = 0; i < history_size; i++)
    {
        dt_history[i] = 0;
    }

    font = al_load_ttf_font("../assets/wendy.ttf", -14, 0);
    SPUTNIK_ASSERT(font, "No font loaded");
}

PerformanceSubsystem::~PerformanceSubsystem()
{
}

void PerformanceSubsystem::process(unsigned int dt)
{
    ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);

    unsigned int left = 20;
    unsigned int right = left + history_size;
    unsigned int bottom = display->height - 20;
    unsigned int top = bottom - 200;

    al_draw_rectangle(left, top, right, bottom, color, 0);

    unsigned int max = 0;
    for (unsigned int i = 0; i < history_size; i++)
    {
        if (dt_history[i] > max)
        {
            max = dt_history[i];
        }
    }

    max = (max / 100 + 1) * 100;

    al_draw_text(font, color, left + 1, bottom - 14, 0, "0");
    al_draw_textf(font, color, left + 1, top, 0, "%d", max);

    dt_history[history_pos] = dt;
    history_pos = (history_pos + 1) % history_size;
    for (unsigned int i = history_pos; i < history_pos + history_size; i++)
    {
        unsigned int x = left + i - history_pos;
        unsigned int y = bottom - (1.0f * dt_history[i % history_size]) / max * (bottom - top);

        al_draw_pixel(x, y, color);
    }
}

