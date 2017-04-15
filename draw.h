#ifndef _draw_h
#define _draw_h

//Defino las variables a utilizar
#define MOSTRAR_ENEMIGOS        0
#define MOSTRAR_ANIMACIONES		1
#define TEXTOUT_EX         		4
#define MOSTRAR_TEXTO  			5
#define MOSTRAR_ESTADIS   		15
#define RECT_LIFE               7
#define RECT_FONDO_LIFE         8
#define CLEAR_TO_COLOR     		14

typedef struct drawthing
{
  short type;
  short x, y, w, h, color;
  fixed angle;  // 0 to 255
  int r;
  short rx, ry;
  string str;
  BITMAP *bmp;
  FONT *fnt;
} drawthing;

extern vector<drawthing> drawqueue;
extern BITMAP *back_buffer;

//Metodos a utilizar por la clase

void mostrar_enemigos(BITMAP *abitmap, int ax, int ay);
void mostrar_animaciones(BITMAP *abitmap, int ax, int ay, fixed aangle);
void mostrar_texto(FONT *afont, string amessage, int ax, int ay, int acolor);
void mostrar_texto_estadisticas(FONT *afont, string amessage, int ax, int ay, int acolor);
void mostrar_rect_vida(int ax, int ay, int bx, int by, int acolor);
void mostrar_fondo_vida(int ax, int ay, int bx, int by, int acolor);
void mostrar_fondo(int acolor);

void draw_all();

#endif
