#ifndef _RENDER_SUBSYSTEM_H
#define _RENDER_SUBSYSTEM_H

#include "subsystem.h"
#include "vector.h"

class ALLEGRO_BITMAP;
class AllegroDisplay;
class World;

class RenderSubsystem : public Subsystem
{
private:
    const AllegroDisplay *display;
    const Entity *tracking;
    
    ALLEGRO_BITMAP *background;

    void process_entity(const Vector &camera, const Entity &entity);

public:
    RenderSubsystem(World &world, const AllegroDisplay &display);
    ~RenderSubsystem();

    void process(unsigned int dt);
    void track(const Entity &entity);
};

#endif

