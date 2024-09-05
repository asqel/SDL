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

/* Being a null driver, there's no event stream. We just define stubs for
   most of the API. */

#include "../../events/SDL_events_c.h"

#include "SDL_nullvideo.h"
#include "SDL_nullevents_c.h"
#include <profan/syscall.h>
#include <profan.h>


static int key_shift_state = 0; // bit 0 is for left 1 right
static uint32_t ab019_array[] = {
    SDLK_a,
    SDLK_b,
    SDLK_c,
    SDLK_d,
    SDLK_e,
    SDLK_f,
    SDLK_g,
    SDLK_h,
    SDLK_i,
    SDLK_j,
    SDLK_k,
    SDLK_l,
    SDLK_m,
    SDLK_n,
    SDLK_o,
    SDLK_p,
    SDLK_q,
    SDLK_r,
    SDLK_s,
    SDLK_t,
    SDLK_u,
    SDLK_v,
    SDLK_w,
    SDLK_x,
    SDLK_y,
    SDLK_z,
    SDLK_0,
    SDLK_1,
    SDLK_2,
    SDLK_3,
    SDLK_4,
    SDLK_5,
    SDLK_6,
    SDLK_7,
    SDLK_8,
    SDLK_9,
};

uint32_t PROFAN_char_to_sdl_key(char c, uint32_t scancode) {
    if (0x01 <= scancode && scancode <= 0x0A)
        return ab019_array[(scancode - 0x01 + 27)];
    if (scancode == 0x0B)
        return SDLK_0;
    if (scancode == 58)
        return SDLK_CAPSLOCK;
    if (c != '\0') {
        if ('A' <= c && c <= 'Z')
            return ab019_array[(c - 'A')];
        if ('a' <= c && c <= 'z')
            return ab019_array[(c - 'a')];
        if ('0' <= c && c <= '9')
            return ab019_array[(c - '0') + 26];
        if (scancode == ' ')
            return SDLK_SPACE;
        switch (c) {
            case '\t': return SDLK_TAB;
            case ',': return SDLK_COMMA;
            case '<': return SDLK_LESS;
            case '>': return SDLK_GREATER;
            case ';': return SDLK_SEMICOLON;
            case ':': return SDLK_COLON;
            case '.': return SDLK_PERIOD;
            case '!': return SDLK_EXCLAIM;
            case '/': return SDLK_SLASH;
            case '%': return SDLK_PERCENT;
            case '\'': return SDLK_QUOTE;
            case '*': return SDLK_ASTERISK;
            case '\\': return SDLK_BACKSLASH;
            case '[': return SDLK_LEFTBRACKET;
            case ']': return SDLK_RIGHTBRACKET;
            case '$': return SDLK_DOLLAR;
            case '=': return SDLK_EQUALS;
            case ')': return SDLK_RIGHTPAREN;
            case '-': return SDLK_MINUS;
            case '`': return SDLK_BACKQUOTE;
            case '#': return SDLK_HASH;
            default: break;
        }
    }
    if (scancode == 0x0E)
        return SDLK_BACKSPACE;
    if (scancode == 0x01)
        return SDLK_ESCAPE;
    if (scancode == 0xC1)
        return SDLK_RETURN;
    if (scancode == 0x38)
        return SDLK_LALT;
    return 0;

}
// only for extended scancode
uint32_t PROFAN_sc_to_sdl_key_spe(uint32_t scancode) {
    switch (scancode) {
        case 0x1D: return SDLK_RCTRL;
        case 0x38: return SDLK_RALT; // alt gr
        case 72: return SDLK_UP;
        case 80: return SDLK_DOWN;
        case 75: return SDLK_LEFT;
        case 77: return SDLK_RIGHT;
        case 71: return SDLK_HOME;
        case 79: return SDLK_END;
        case 83: return SDLK_DELETE;
        case 53: return SDLK_KP_DIVIDE;
        case 0xc1: return SDLK_KP_ENTER;
        default: return 0;
    }
}

void PROFAN_PumpEvents(_THIS) {
    int scancode = syscall_sc_get();
    SDL_Event ev = {0};
    ev.key.keysym.mod = KMOD_NONE;
    if (key_shift_state & 0)
        ev.key.keysym.mod |= KMOD_LSHIFT; 
    if (key_shift_state & 0b10)
        ev.key.keysym.mod |= KMOD_RSHIFT; 
    while (scancode) {
        if (scancode == 42) { // l ctrl down
            ev.key.keysym.scancode = scancode;
            ev.type = SDL_KEYDOWN;
            ev.key.keysym.sym = SDLK_LCTRL;
            key_shift_state |= 0b01;
            ev.key.keysym.mod |= KMOD_LCTRL;
        }
        else if (scancode == 170) { // l ctrl up
            ev.key.keysym.scancode = scancode;
            ev.type = SDL_KEYUP;
            ev.key.keysym.sym = SDLK_LCTRL;
            key_shift_state &= 0b10;
        }
        if (scancode == 54) { // r ctrl down
            ev.key.keysym.scancode = scancode;
            ev.type = SDL_KEYDOWN;
            ev.key.keysym.sym = SDLK_RCTRL;
            key_shift_state |= 0b10;
            ev.key.keysym.mod |= KMOD_RCTRL;
        }
        else if (scancode == 182) { // r ctrl up
            ev.key.keysym.scancode = scancode;
            ev.type = SDL_KEYUP;
            ev.key.keysym.sym = SDLK_RCTRL;
            key_shift_state &= 0b01;
        }
        else if (scancode == 0xE0) {
            int scancode2 = syscall_sc_get();
            ev.key.keysym.scancode = 0xE000 | scancode2;
            ev.type = scancode2 < 0x80 ? SDL_KEYDOWN : SDL_KEYUP;
            if (scancode2 >= 81)
                scancode2 -= 0x80;
            ev.key.keysym.sym = PROFAN_sc_to_sdl_key_spe(scancode2);
            
        }
        else {
            ev.type = scancode < 0x80 ? SDL_KEYDOWN : SDL_KEYUP;
            if (scancode >= 0x81)
                scancode -= 0x80;
            char c = profan_kb_get_char(scancode, 0);
            ev.key.keysym.scancode = scancode;
            switch (scancode >= 81 ? scancode - 0x80 : scancode) {
                case 0x3B: ev.key.keysym.sym = SDLK_F1; break;
                case 0x3C: ev.key.keysym.sym = SDLK_F2; break;
                case 0x3D: ev.key.keysym.sym = SDLK_F3; break;
                case 0x3E: ev.key.keysym.sym = SDLK_F4; break;
                case 0x3F: ev.key.keysym.sym = SDLK_F5; break;
                case 0x40: ev.key.keysym.sym = SDLK_F6; break;
                case 0x41: ev.key.keysym.sym = SDLK_F7; break;
                case 0x42: ev.key.keysym.sym = SDLK_F8; break;
                case 0x43: ev.key.keysym.sym = SDLK_F9; break;
                case 0x44: ev.key.keysym.sym = SDLK_F10; break;
                case 0x57: ev.key.keysym.sym = SDLK_F11; break;
                case 0x58: ev.key.keysym.sym = SDLK_F12; break;
                case 0x37: ev.key.keysym.sym = SDLK_KP_MULTIPLY; break;
                case 0x47: ev.key.keysym.sym = SDLK_KP_7; break;
                case 0x48: ev.key.keysym.sym = SDLK_KP_8; break;
                case 0x49: ev.key.keysym.sym = SDLK_KP_9; break;
                case 0x4a: ev.key.keysym.sym = SDLK_KP_MINUS; break;
                case 0x4b: ev.key.keysym.sym = SDLK_KP_4; break;
                case 0x4c: ev.key.keysym.sym = SDLK_KP_5; break;
                case 0x4d: ev.key.keysym.sym = SDLK_KP_6; break;
                case 0x4e: ev.key.keysym.sym = SDLK_KP_PLUS; break;
                case 0x4f: ev.key.keysym.sym = SDLK_KP_1; break;
                case 0x50: ev.key.keysym.sym = SDLK_KP_2; break;
                case 0x51: ev.key.keysym.sym = SDLK_KP_3; break;
                case 0x52: ev.key.keysym.sym = SDLK_KP_0; break;
                case 0x53: ev.key.keysym.sym = SDLK_KP_PERIOD; break;
                default: ev.key.keysym.sym = PROFAN_char_to_sdl_key(c, scancode); break;
            }
        }
        int er = SDL_PushEvent(&ev);
        scancode = syscall_sc_get();
    }
}

#endif /* SDL_VIDEO_DRIVER_DUMMY */

/* vi: set ts=4 sw=4 expandtab: */
