#include "ben_graphics.h"
#include "SDL.h"
#include "math.h"

void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel )
{
	if(y < 0 || y >= surface->h || x < 0 || x >= surface->w) return;
    //Convert the pixels to 32 bit 
    Uint32 *pixels = (Uint32 *)surface->pixels;
    
    //Set the pixel
    pixels[ ( y * surface->w ) + x ] = pixel;
}
void draw_line(SDL_Surface *surface, float x1, float y1, float x2, float y2, Uint32 color)
{
	int steep = (fabs(y2 - y1) > fabs(x2 - x1));
	if(steep == 1)
	{
		swap(x1,y1);
		swap(x2,y2);
	}
	if(x1 > x2)
	{
		swap(x1,x2);
		swap(y1,y2);
	}
	const float dx = x2 - x1;
	const float dy = fabs(y2 - y1);
	float error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;
	const int maxX = (int)x2;
	
	int x = (int)x1;
	for(;x < maxX; x++)
	{
		if(steep == 1)
		{
			put_pixel32(surface, y, x, color);
		}
		else
		{
			put_pixel32(surface, x, y, color);
		}
		error -= dy;
		if(error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}
void draw_rect(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color)
{
	draw_line(surface,x,y,x+w,y,color);
	draw_line(surface,x+w,y,x+w,y+w,color);
	draw_line(surface,x+w,y+w,x,y+w,color);
	draw_line(surface,x,y,x,y+w,color);
}
void draw_zero(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color)
{	
	draw_o(surface,x,y,w,h,color);
	
	draw_line(surface,x+w,y,x,y+h,color);//<-across like these slashes
}
void draw_one(SDL_Surface *surface,int x, int y, int w, int h, Uint32 color)
{
	draw_line(surface,x+w/2,y,x+w/2,y+h,color);//left
}
void draw_two(SDL_Surface *surface,int x,int y, int w, int h, Uint32 color)
{
	draw_line(surface,x+w,y,x,y,color);//top
	draw_line(surface,x+w,y,x+w,y+h/2,color);//right
	draw_line(surface,x,y+h/2,x+w,y+h/2,color);//middle
	draw_line(surface,x,y+h/2,x,y+h,color);//left
	draw_line(surface,x,y+h,x+w,y+h,color);//bottom
}
void draw_three(SDL_Surface *surface,int x,int y, int w, int h, Uint32 color)
{
	draw_line(surface,x+w,y,x,y,color);//top
	draw_line(surface,x+w,y,x+w,y+h,color);//right
	draw_line(surface,x,y+h/2,x+w,y+h/2,color);//middle
	draw_line(surface,x,y+h,x+w,y+h,color);//bottom
}
void draw_four(SDL_Surface *surface,int x,int y, int w, int h, Uint32 color)
{
	draw_line(surface,x+w,y,x,y+h/2,color);//top slant
	draw_line(surface,x+w,y,x+w,y+h,color);//right
	draw_line(surface,x,y+h/2,x+w,y+h/2,color);//middle
}
void draw_five(SDL_Surface *surface,int x,int y, int w, int h, Uint32 color)
{
	draw_line(surface,x+w,y,x,y,color);//top
	draw_line(surface,x+w,y+h/2,x+w,y+h,color);//right
	draw_line(surface,x,y+h/2,x+w,y+h/2,color);//middle
	draw_line(surface,x,y,x,y+h/2,color);//left
	draw_line(surface,x,y+h,x+w,y+h,color);//bottom
}
void draw_six(SDL_Surface *surface,int x,int y, int w, int h, Uint32 color)
{
	draw_line(surface,x+w,y,x,y,color);//top
	draw_line(surface,x+w,y+h/2,x+w,y+h,color);//right
	draw_line(surface,x,y+h/2,x+w,y+h/2,color);//middle
	draw_line(surface,x,y,x,y+h,color);//left
	draw_line(surface,x,y+h,x+w,y+h,color);//bottom
}
void draw_seven(SDL_Surface *surface,int x,int y, int w, int h, Uint32 color)
{
	draw_line(surface,x+w,y,x,y,color);//top
	draw_line(surface,x+w,y,x+w,y+h,color);//right
	draw_line(surface,x,y,x,y+h/4,color);//tiny left
}
void draw_eight(SDL_Surface *surface,int x,int y, int w, int h, Uint32 color)
{
	draw_line(surface,x+w,y,x,y,color);//top
	draw_line(surface,x+w,y,x+w,y+h,color);//right
	draw_line(surface,x,y+h/2,x+w,y+h/2,color);//middle
	draw_line(surface,x,y+h,x+w,y+h,color);//bottom
	draw_line(surface,x,y,x,y+h,color);//left
}
void draw_nine(SDL_Surface *surface,int x,int y, int w, int h, Uint32 color)
{
	draw_line(surface,x+w,y,x,y,color);//top
	draw_line(surface,x+w,y,x+w,y+h,color);//right
	draw_line(surface,x,y+h/2,x+w,y+h/2,color);//middle
	draw_line(surface,x,y,x,y+h/2,color);//left
	draw_line(surface,x,y+h,x+w,y+h,color);//bottom
}
void draw_a(SDL_Surface *surface, int x, int y, int w, int h, Uint32 color)
{
	draw_line(surface,x+w/2,y,x+w,y+h,color);//right
	draw_line(surface,x+w/2,y,x,y+h,color);//left
	draw_line(surface,x+w/4,y+h/2,x+3*w/4,y+h/2,color);//middle
}
void draw_b(SDL_Surface *surface,int x,int y, int w, int h,Uint32 color)
{
	draw_line(surface,x,y,x,y+h,color);//left
	draw_line(surface,x+2*w/3,y,x,y,color);//top
	draw_line(surface,x+2*w/3,y,x+w,y+h/8,color);//top slant
	draw_line(surface,x+w,y+h/8,x+w,y+3*h/8,color);//right top
	draw_line(surface,x+2*w/3,y+h/2,x+w,y+3*h/8,color);//middle top slant /
	draw_line(surface,x,y+h/2,x+2*w/3,y+h/2,color);//middle
	draw_line(surface,x+2*w/3,y+h/2,x+w,y+5*h/8,color);//middle bottom slant /
	draw_line(surface,x+w,y+7*h/8,x+w,y+5*h/8,color);//right bottom
	draw_line(surface,x+w,y+7*h/8,x+2*w/3,y+h,color);//bottom slant
	draw_line(surface,x,y+h,x+2*w/3,y+h,color);//bottom
}
void draw_c(SDL_Surface *surface, int x, int y, int w, int h, Uint32 color)
{
	draw_line(surface,x+w,y,x,y,color);//top
	draw_line(surface,x,y,x,y+h,color);//left
	draw_line(surface,x,y+h,x+w,y+h,color);//bottom
}
void draw_d(SDL_Surface *surface,int x,int y, int w, int h,Uint32 color)
{
	draw_line(surface,x,y,x,y+h,color);//left
	draw_line(surface,x+2*w/3,y,x,y,color);//top
	draw_line(surface,x+2*w/3,y,x+w,y+h/8,color);//top slant
	draw_line(surface,x+w,y+h/8,x+w,y+7*h/8,color);//right
	draw_line(surface,x+w,y+7*h/8,x+2*w/3,y+h,color);//bottom slant
	draw_line(surface,x,y+h,x+2*w/3,y+h,color);//bottom
}
void draw_e(SDL_Surface *surface, int x, int y, int w, int h, Uint32 color)
{
	draw_line(surface,x+w,y,x,y,color);//top
	draw_line(surface,x,y,x,y+h,color);//left
	draw_line(surface,x,y+h/2,x+w,y+h/2,color);//middle
	draw_line(surface,x,y+h,x+w,y+h,color);//bottom
}
void draw_f(SDL_Surface *surface, int x, int y, int w, int h, Uint32 color)
{
	draw_line(surface,x+w,y,x,y,color);//top
	draw_line(surface,x,y,x,y+h,color);//left
	draw_line(surface,x,y+h/2,x+w,y+h/2,color);//middle
}
void draw_g(SDL_Surface *surface, int x, int y, int w, int h, Uint32 color)
{
	draw_line(surface,x+w,y,x,y,color);//top
	draw_line(surface,x+w,y+h/2,x+w,y+h,color);//right
	draw_line(surface,x+w/2,y+h/2,x+w,y+h/2,color);//middle
	draw_line(surface,x,y,x,y+h,color);//left
	draw_line(surface,x,y+h,x+w,y+h,color);//bottom
}
void draw_h(SDL_Surface *surface, int x, int y, int w, int h, Uint32 color)
{
	draw_line(surface,x,y,x,y+h,color);//left
	draw_line(surface,x+w,y,x+w,y+h,color);//right
	draw_line(surface,x,y+h/2,x+w,y+h/2,color);//middle
}
void draw_i(SDL_Surface *surface, int x, int y, int w, int h, Uint32 color)
{
	draw_line(surface,x+w,y,x,y,color);//top
	draw_line(surface,x+w/2,y,x+w/2,y+h,color);//middle
	draw_line(surface,x,y+h,x+w,y+h,color);//bottom
}
void draw_j(SDL_Surface *surface, int x, int y, int w, int h, Uint32 color)
{
	draw_line(surface,x+w,y,x,y,color);//top
	draw_line(surface,x,y+h/2,x,y+h,color);//left
	draw_line(surface,x+w/2,y,x+w/2,y+h,color);//middle
	draw_line(surface,x,y+h,x+w/2,y+h,color);//bottom
}
void draw_k(SDL_Surface *surface, int x, int y, int w, int h, Uint32 color)
{
	draw_line(surface,x,y,x,y+h,color);//left
	draw_line(surface,x,y+h/2,x+w,y,color);//top
	draw_line(surface,x,y+h/2,x+w,y+h,color);//bottom
}
void draw_l(SDL_Surface *surface, int x, int y, int w, int h, Uint32 color)
{
	draw_line(surface,x,y,x,y+h,color);//left
	draw_line(surface,x,y+h,x+w,y+h,color);//bottom
}
void draw_m(SDL_Surface *surface, int x, int y, int w, int h, Uint32 color)
{
	draw_line(surface,x+w,y,x+w,y+h,color);//right
	draw_line(surface,x,y,x,y+h,color);//left
	draw_line(surface,x,y,x+w/2,y+h/2,color);//left middle
	draw_line(surface,x+w,y,x+w/2,y+h/2,color);//right middle
}
void draw_n(SDL_Surface *surface, int x, int y, int w, int h, Uint32 color)
{
	draw_line(surface,x+w,y,x+w,y+h,color);//right
	draw_line(surface,x,y,x,y+h,color);//left
	draw_line(surface,x,y,x+w,y+h,color);//middle
}
void draw_o(SDL_Surface *surface, int x, int y, int w, int h, Uint32 color)
{
	draw_line(surface,x,y,x,y+h,color);//left
	draw_line(surface,x,y+h,x+w,y+h,color);//bottom
	draw_line(surface,x,y,x+w,y,color);//top
	draw_line(surface,x+w,y,x+w,y+h,color);//right
}
void draw_p(SDL_Surface *surface, int x, int y, int w, int h, Uint32 color)
{
	draw_line(surface,x,y,x,y+h,color);//left
	draw_line(surface,x,y+h/2,x+w,y+h/2,color);//bottom
	draw_line(surface,x,y,x+w,y,color);//top
	draw_line(surface,x+w,y,x+w,y+h/2,color);//right
}
void draw_q(SDL_Surface *surface, int x, int y, int w, int h, Uint32 color)
{
	draw_o(surface,x,y,w,3*h/4,color);
	draw_line(surface,x+w/2,y+h/2,x+w,y+h,color);//right
	//draw_line(surface,x,y,x+w,y,color);//top
	//draw_line(surface,x+w,y,x+w,y+h/2,color);//left
}
void draw_r(SDL_Surface *surface, int x, int y, int w, int h, Uint32 color)
{
	draw_p(surface,x,y,w,h,color);
	draw_line(surface,x,y+h/2,x+w,y+h,color);//left
}
void draw_s(SDL_Surface *surface,int x,int y, int w, int h,Uint32 color)
{
	draw_line(surface,x+w,y,x,y,color);//top
	draw_line(surface,x+w,y+h/2,x+w,y+h,color);//right
	draw_line(surface,x,y+h/2,x+w,y+h/2,color);//middle
	draw_line(surface,x,y,x,y+h/2,color);//left
	draw_line(surface,x,y+h,x+w,y+h,color);//bottom
	draw_line(surface,x,y+h,x,y+3*h/4,color);//left bottom
	draw_line(surface,x+w,y+h/4,x+w,y,color);//right
}
void draw_t(SDL_Surface *surface, int x, int y, int w, int h, Uint32 color)
{
	draw_line(surface,x+w,y,x,y,color);//top
	draw_line(surface,x+w/2,y,x+w/2,y+h,color);//middle
}
void draw_u(SDL_Surface *surface, int x, int y, int w, int h, Uint32 color)
{
	draw_line(surface,x,y,x,y+h,color);//left
	draw_line(surface,x,y+h,x+w,y+h,color);//bottom
	draw_line(surface,x+w,y,x+w,y+h,color);//right
}
void draw_v(SDL_Surface *surface, int x, int y, int w, int h, Uint32 color)
{
	draw_line(surface,x,y,x+w/2,y+h,color);//left
	draw_line(surface,x+w/2,y+h,x+w,y,color);//right
}
void draw_w(SDL_Surface *surface, int x, int y, int w, int h, Uint32 color)
{
	draw_v(surface,x,y,w/2,h,color);
	draw_v(surface,x+w/2,y,w/2,h,color);
}
void draw_x(SDL_Surface *surface, int x, int y, int w, int h, Uint32 color)
{
	draw_line(surface,x,y,x+w,y+h,color);//left
	draw_line(surface,x,y+h,x+w,y,color);//right
}
void draw_y(SDL_Surface *surface, int x, int y, int w, int h, Uint32 color)
{
	draw_line(surface,x,y,x+w/2,y+h/2,color);//left
	draw_line(surface,x,y+h,x+w,y,color);//right
}
void draw_z(SDL_Surface *surface, int x, int y, int w, int h, Uint32 color)
{
	draw_line(surface,x+w,y,x,y,color);//top
	draw_line(surface,x+w,y,x,y+h,color);//middle
	draw_line(surface,x,y+h,x+w,y+h,color);//bottom
}
void draw_char(SDL_Surface *surface, char c,int x, int y, int w, int h, Uint32 color)
{
	switch(c)
	{
		case '0':	draw_zero(surface,x,y,w,h,color); 			break;
		case '1':	draw_one(surface,x,y,w,h,color); 			break;
		case '2':	draw_two(surface,x,y,w,h,color); 			break;
		case '3':	draw_three(surface,x,y,w,h,color); 			break;
		case '4':	draw_four(surface,x,y,w,h,color); 			break;
		case '5':	draw_five(surface,x,y,w,h,color); 			break;
		case '6':	draw_six(surface,x,y,w,h,color); 			break;
		case '7':	draw_seven(surface,x,y,w,h,color); 			break;
		case '8':	draw_eight(surface,x,y,w,h,color); 			break;
		case '9':	draw_nine(surface,x,y,w,h,color); 			break;
		case 'A':	draw_a(surface,x,y,w,h,color); 				break;
		case 'a':	draw_a(surface,x,y+h/3,w,2*h/3,color); 		break;
		case 'B':	draw_b(surface,x,y,w,h,color); 				break;
		case 'b':	draw_b(surface,x,y+h/3,w,2*h/3,color); 		break;
		case 'C':	draw_c(surface,x,y,w,h,color); 				break;
		case 'c':	draw_c(surface,x,y+h/3,w,2*h/3,color); 		break;
		case 'D':	draw_d(surface,x,y,w,h,color); 				break;
		case 'd':	draw_d(surface,x,y+h/3,w,2*h/3,color); 		break;
		case 'E':	draw_e(surface,x,y,w,h,color); 				break;
		case 'e':	draw_e(surface,x,y+h/3,w,2*h/3,color); 		break;
		case 'F':	draw_f(surface,x,y,w,h,color); 				break;
		case 'f':	draw_f(surface,x,y+h/3,w,2*h/3,color); 		break;
		case 'G':	draw_g(surface,x,y,w,h,color); 				break;
		case 'g':	draw_g(surface,x,y+h/3,w,2*h/3,color); 		break;
		case 'H':	draw_h(surface,x,y,w,h,color); 				break;
		case 'h':	draw_h(surface,x,y+h/3,w,2*h/3,color); 		break;
		case 'I':	draw_i(surface,x,y,w,h,color); 				break;
		case 'i':	draw_i(surface,x,y+h/3,w,2*h/3,color); 		break;
		case 'J':	draw_j(surface,x,y,w,h,color); 				break;
		case 'j':	draw_j(surface,x,y+h/3,w,2*h/3,color); 		break;
		case 'K':	draw_k(surface,x,y,w,h,color); 				break;
		case 'k':	draw_k(surface,x,y+h/3,w,2*h/3,color); 		break;
		case 'L':	draw_l(surface,x,y,w,h,color); 				break;
		case 'l':	draw_l(surface,x,y+h/3,w,2*h/3,color); 		break;
		case 'M':	draw_m(surface,x,y,w,h,color); 				break;
		case 'm':	draw_m(surface,x,y+h/3,w,2*h/3,color); 		break;
		case 'N':	draw_n(surface,x,y,w,h,color); 				break;
		case 'n':	draw_n(surface,x,y+h/3,w,2*h/3,color); 		break;
		case 'O':	draw_o(surface,x,y,w,h,color); 				break;
		case 'o':	draw_o(surface,x,y+h/3,w,2*h/3,color); 		break;
		case 'P':	draw_p(surface,x,y,w,h,color); 				break;
		case 'p':	draw_p(surface,x,y+h/3,w,2*h/3,color); 		break;
		case 'Q':	draw_q(surface,x,y,w,h,color); 				break;
		case 'q':	draw_q(surface,x,y+h/3,w,2*h/3,color); 		break;
		case 'R':	draw_r(surface,x,y,w,h,color); 				break;
		case 'r':	draw_r(surface,x,y+h/3,w,2*h/3,color); 		break;
		case 'S':	draw_s(surface,x,y,w,h,color); 				break;
		case 's':	draw_s(surface,x,y+h/3,w,2*h/3,color); 		break;
		case 'T':	draw_t(surface,x,y,w,h,color); 				break;
		case 't':	draw_t(surface,x,y+h/3,w,2*h/3,color); 		break;
		case 'U':	draw_u(surface,x,y,w,h,color); 				break;
		case 'u':	draw_u(surface,x,y+h/3,w,2*h/3,color); 		break;
		case 'V':	draw_v(surface,x,y,w,h,color); 				break;
		case 'v':	draw_v(surface,x,y+h/3,w,2*h/3,color); 		break;
		case 'W':	draw_w(surface,x,y,w,h,color); 				break;
		case 'w':	draw_w(surface,x,y+h/3,w,2*h/3,color); 		break;
		case 'X':	draw_x(surface,x,y,w,h,color); 				break;
		case 'x':	draw_x(surface,x,y+h/3,w,2*h/3,color); 		break;
		case 'Y':	draw_y(surface,x,y,w,h,color); 				break;
		case 'y':	draw_y(surface,x,y+h/3,w,2*h/3,color); 		break;
		case 'Z':	draw_z(surface,x,y,w,h,color); 				break;
		case 'z':	draw_z(surface,x,y+h/3,w,2*h/3,color); 		break;
		case '\n':												break;
		case '\0':	return;
	}
}
void draw_string(SDL_Surface *surface,char *string,int x, int y, int w, int h, Uint32 color, int spacing)
{
	if(string == NULL) { return; }
	int i;
	for(i = 0; i < strlen(string); i++)
	{
		draw_char(surface,string[i],x,y,w,h,color);
		if(string[i] == '\n')
		{
			y += h + spacing;
		}
		x += w + spacing;
	}
}













