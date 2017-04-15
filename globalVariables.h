#ifndef _MAIN_H
#define _MAIN_H

///Aqui se definen todas las variables que se ocuparan en los otros documentos
///Esto para tener un mayor control y tener un codigo mas organizado

///Bibliotecas a utilizar

#include <allegro.h>
#include <time.h>
#include <list>
#include <string>
#include <vector>
#include <math.h>
#include <string>
#include <ctime>
#include <stdio.h>

using namespace std;

#include "draw.h"
#include "enemy.h"
#include "player.h"

#define PI 3.14159265

//Variables que se utilizan como generales
#define SANE  1

#define QUIT -1
#define MENU  0
#define LOGIC 1
#define DEAD  2

extern int Nivel_actual, puntaje_obtenido;

//Imagenes y sonidos utilizados
extern BITMAP *bullet_menu, *nombre_juego, *vida, *nave, *bala_avion[2], *enemy1[2],
							*bala_enemigos[2], *powerUP2, *powerUP1, *enemy2[2],
							*enemy3[2],*enemy4[2],*enemy5[2],*enemy6[2],*enemy7[2];

extern SAMPLE *recarga, *fuego, *dano_recibido,	*explocion, *nave_abatida;

//Colores que se utilizan para la interfaz
#define BLACK makecol(0, 0, 0)
#define RED makecol(255, 0, 0)
#define GREEN makecol(0, 255, 0)
#define WHITE makecol(255, 255, 255)

#endif
