/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2024 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#include "../../SDL_internal.h"

#ifdef __profanOS__

#include "SDL_timer.h"
#include <profan/syscall.h>
#include <unistd.h>

static char ticks_started = 0;
static uint32_t start_time_ms = 0;

void SDL_TicksInit(void) {
    if (ticks_started) {
        return;
    }
    ticks_started = 1;
    start_time_ms = c_timer_get_ms();
}

void SDL_TicksQuit(void) {
    ticks_started = 0;
}

Uint64 SDL_GetTicks64(void)
{
    if (!ticks_started) {
        SDL_TicksInit();
    }

    return c_timer_get_ms() - start_time_ms;
}

Uint64 SDL_GetPerformanceCounter(void) {
    return SDL_GetTicks();
}

Uint64 SDL_GetPerformanceFrequency(void) {
    return 1000;
}

void SDL_Delay(Uint32 ms) {
    usleep(ms);
}

#endif /* SDL_TIMER_DUMMY || SDL_TIMERS_DISABLED */

/* vi: set ts=4 sw=4 expandtab: */