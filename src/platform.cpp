#include "platform.h"

#include "debug.h"

#ifdef WIN32

#include <Mmsystem.h>

unsigned int Platform::get_milliseconds()
{
    return timeGetTime();
}

#else

#include <cstddef>
#include <sys/time.h>

unsigned int Platform::get_milliseconds()
{
    timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

#endif

