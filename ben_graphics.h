#ifndef BEN_GRAPHICS_H
#define BEN_GRAPHICS_H
#include "string.h"
#include "SDL.h"
#define swap(x,y) do \
	{ unsigned char swap_temp[sizeof(x) == sizeof(y) ? (signed)sizeof(x) : -1]; \
     memcpy(swap_temp,&y,sizeof(x)); \
     memcpy(&y,&x,       sizeof(x)); \
     memcpy(&x,swap_temp,sizeof(x)); \
    } while(0)
void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel );
void draw_line(SDL_Surface *surface, float x1, float y1, float x2, float y2, Uint32 color);
void draw_zero(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_one(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_two(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_three(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_four(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_five(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_six(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_seven(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_eight(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_nine(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_a(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_b(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_c(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_d(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_e(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_f(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_g(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_h(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_i(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_j(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_k(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_l(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_m(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_n(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_o(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_p(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_q(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_r(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_s(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_t(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_u(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_v(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_w(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_x(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_y(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_z(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_rect(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color);
void draw_char(SDL_Surface *surface, char c,int x, int y, int w, int h, Uint32 color);
void draw_string(SDL_Surface *surface,char *string,int x, int y, int w, int h, Uint32 color, int spacing);
#endif
