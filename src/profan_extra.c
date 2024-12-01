#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <profan/syscall.h>
int64_t __divdi3(int64_t num, int64_t den) {
    return (int64_t) (((int32_t)num) / ((int32_t)den));
}
uint64_t __udivdi3(uint64_t num, uint64_t den) {
    return (uint64_t) (((uint32_t)num) / ((uint32_t)den));
}
uint64_t __umoddi3(uint64_t num, uint64_t den) {
    return (uint64_t) (((uint32_t)num) % ((uint32_t)den));
}
int64_t __moddi3(int64_t num, int64_t den) {
    return (int64_t) (((int32_t)num) % ((int32_t)den));
}


double SDL_uclibc_atan(double x) {
    return atan(x);
}
double SDL_uclibc_atan2(double y, double x) {
    return atan2(y, x);
}
double SDL_uclibc_copysign(double x, double y) {
    return copysign(x, y);
}
double SDL_uclibc_cos(double x) {
    return cos(x);
}
double SDL_uclibc_exp(double x) {
    return exp(x);
}
double SDL_uclibc_fabs(double x) {
    return fabs(x);
}
double SDL_uclibc_floor(double x) {
    return floor(x);
}
double SDL_uclibc_fmod(double x, double y) {
    return fmod(x, y);
}
double SDL_uclibc_log(double x) {
    return log(x);
}
double SDL_uclibc_log10(double x) {
    return log10(x);
}
double SDL_uclibc_pow(double x, double y) {
    return pow(x, y);
}
double SDL_uclibc_scalbn(double x, int n) {
    return scalbln(x, n);
}
double SDL_uclibc_sin(double x) {
    return sin(x);
}
double SDL_uclibc_sqrt(double x) {
    return sqrt(x);
}
double SDL_uclibc_tan(double x) {
    return tan(x);
}

uint32_t *profan_fb;
uint32_t profan_pitch;
uint32_t profan_height;
uint32_t profan_width;

uint32_t *profan_back_fb; // use same pitch/h/w

void __profan_sdl_exit(void);
void __profan_sdl_init(void) {
    setenv("SDL_VIDEODRIVER", "profan_vesa", 1);
    profan_fb = syscall_vesa_fb();
    profan_pitch = syscall_vesa_pitch();
    profan_height = syscall_vesa_height();
    profan_width = syscall_vesa_width();
    profan_back_fb = calloc(profan_pitch * profan_height, 4);
    atexit(&__profan_sdl_exit);
}

void __profan_sdl_exit(void) {
    free(profan_back_fb);
}