#include "globalVariables.h"

vector<drawthing> drawqueue;
/**
 *Aqui dibujamos (presemtamos) en pantalla las imagenes o textos
 */
void draw_all()
{
  int i = 0;
  int s = drawqueue.size();
  drawthing t;

  set_window_title("AirWar++");

  while (i < s)
  {
    t = drawqueue[i];
    switch (t.type)
    {
      case MOSTRAR_ENEMIGOS:
        draw_sprite(back_buffer, t.bmp, t.x, t.y);
        break;
      case MOSTRAR_ANIMACIONES:
        rotate_sprite(back_buffer, t.bmp, t.x, t.y, t.angle);
        break;
      case MOSTRAR_TEXTO:
        textout_centre_ex(back_buffer, t.fnt, t.str.c_str(), t.x, t.y, t.color, -1);
        break;
      case MOSTRAR_ESTADIS:
        textout_right_ex(back_buffer, t.fnt, t.str.c_str(), t.x, t.y, t.color, -1);
        break;
      case RECT_LIFE:
        rect(back_buffer, t.x, t.y, t.x + t.w, t.y + t.h, t.color);
        break;
      case RECT_FONDO_LIFE:
        rectfill(back_buffer, t.x, t.y, t.x + t.w, t.y + t.h, t.color);
        break;
      case CLEAR_TO_COLOR:
        clear_to_color(back_buffer, t.color);
        break;
    }
    i++;
  }
  drawqueue.clear();
}

//Metodos para dibujar los objetos en pantalla
void mostrar_enemigos(BITMAP *abitmap, int ax, int ay)
{
  drawthing t;
  t.type = MOSTRAR_ENEMIGOS;
  t.bmp = abitmap;
  t.x = ax;
  t.y = ay;
  drawqueue.push_back(t);
}

void mostrar_animaciones(BITMAP *abitmap, int ax, int ay, fixed aangle)
{
  drawthing t;
  t.type = MOSTRAR_ANIMACIONES;
  t.bmp = abitmap;
  t.x = ax;
  t.y = ay;
  t.angle = aangle;
  drawqueue.push_back(t);
}

void mostrar_texto(FONT *afont, string amessage, int ax, int ay, int acolor)
{
  drawthing t;
  t.type = MOSTRAR_TEXTO;
  t.fnt = afont;
  t.str = amessage;
  t.x = ax;
  t.y = ay;
  t.color = acolor;
  drawqueue.push_back(t);
}

void mostrar_texto_estadisticas(FONT *afont, string amessage, int ax, int ay, int acolor)
{
  drawthing t;
  t.type = MOSTRAR_ESTADIS;
  t.fnt = afont;
  t.str = amessage;
  t.x = ax;
  t.y = ay;
  t.color = acolor;
  drawqueue.push_back(t);
}

void mostrar_rect_vida(int ax, int ay, int bx, int by, int acolor)
{
  drawthing t;
  t.type = RECT_LIFE;
  t.x = ax;
  t.y = ay;
  t.w = bx - ax;
  t.h = by - ay;
  if (t.w < 0) t.w = 0;
  if (t.h < 0) t.h = 0;
  t.color = acolor;
  drawqueue.push_back(t);
}

void mostrar_fondo_vida(int ax, int ay, int bx, int by, int acolor)
{
  drawthing t;
  t.type = RECT_FONDO_LIFE;
  t.x = ax;
  t.y = ay;
  t.w = bx - ax;
  t.h = by - ay;
  if (t.w < 0) t.w = 0;
  if (t.h < 0) t.h = 0;
  t.color = acolor;
  drawqueue.push_back(t);
}

void mostrar_fondo(int acolor)
{
  drawthing t;
  t.type = CLEAR_TO_COLOR;
  t.color = acolor;
  drawqueue.push_back(t);
}
