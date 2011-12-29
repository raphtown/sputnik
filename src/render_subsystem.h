#ifndef _RENDER_SUBSYSTEM_H
#define _RENDER_SUBSYSTEM_H

#include "subsystem.h"

class AllegroDisplay;
class Vector;
class World;

class RenderSubsystem : public Subsystem
{
private:
    const AllegroDisplay *display;
    const Entity *tracking;

    void process_entity(const Vector &camera, const Entity &entity);

public:
    RenderSubsystem(World &world, const AllegroDisplay &display);

    void process(unsigned int dt);
    void track(const Entity &entity);
};

#endif

