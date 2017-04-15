#include "globalVariables.h"


void dibujar_salud();
void do_powerUPs();
int logica();

list<struct_powerUp> powerups;

/**
 * Damos comienzo a la logica del juego
 */
int logica(){
	static bool first = true;
	static unsigned int time = 0;
	char c[40];


	if (first){
		time = 0;
		Nivel_actual = 1;
		enemies.clear();
		eshot.clear();
		first = false;
	}

	time++;
	if (time >= 1000){   //  1800 = 35s
		Nivel_actual++;
		time = 0;
	}
	sprintf(c, "Comenzando Nvl en %d:%02d", ((1000 - time) / 50) / 60, ((1000 - time) / 50) % 60);
	mostrar_texto_estadisticas(font, c, 640, 5, WHITE);
	sprintf(c, "Puntaje: %d", puntaje_obtenido);
	mostrar_texto_estadisticas(font, c, 120, 465, WHITE);
	sprintf(c, "Nivel %d", Nivel_actual);
	mostrar_texto_estadisticas(font, c, 320, 5, WHITE);

	dibujar_salud();
	do_powerUPs();
	Halcon_Milenario.do_stuff();
	crear_enemigos();

	switch(Nivel_actual) //Aqui vamos a aumentar el numero de enemigos
	{
	case 1:
		if (rand()%400 == 0){
			enemigo_nuevo(HELICOPTERO);
		}
		if (rand()%650 == 0){
			enemigo_nuevo(TORRE);
		}

		if (rand()%650==0){
			enemigo_nuevo(BANSHEE);
		}
		break;
	case 2:
		if (rand()%525 == 0){
			nueva_ola_de_enemigos(HELICOPTERO, 3, 35);
		}
		if (rand()%500 == 0){
			enemigo_nuevo(BANSHEE);
		}
		if (rand()%500 == 0){
			enemigo_nuevo(JET);
		}
		break;
	case 3:
		if (rand()%200 == 0){
			nueva_ola_de_enemigos(BANSHEE, 3, 35);
		}
		if (rand()%200 == 0){
			enemigo_nuevo(TORREM);
		}
		if (rand()%200 == 0){
			nueva_ola_de_enemigos(JET, 3, 35);
		}
		break;
	case 4:
		if (rand()%70 == 0){
			enemigo_nuevo(TORREM);
		}
		if (rand()%80 == 0){
			enemigo_nuevo(KAMIKAZE);
		}
		if (rand()%150 == 0){
			nueva_ola_de_enemigos(JET, 5, 15);
		}
		break;
	case 5:
		if (rand()%70 == 0){
			enemigo_nuevo(KAMIKAZE);
		}
		if (rand()%100 == 0)
		{
			nueva_ola_de_enemigos(TORRE, 3, 10);
		}
		if (rand()%50 == 0){
			enemigo_nuevo(BOMBARDERO);
		}
		break;
	default:
		if (rand()%60 == 0){
			enemigo_nuevo(BOMBARDERO);
		}
		if (rand()%120 == 0){
			nueva_ola_de_enemigos(BANSHEE, 5, 10);
		}
		if (rand()%80 == 0){
			enemigo_nuevo(TORRE);
		}
		if (rand()%180 == 0){
			nueva_ola_de_enemigos(HELICOPTERO, 5, 15);
		}
		break;
	}

	if (key[KEY_ESC]){
		first = true;
		Halcon_Milenario.init(false);
		//stop_sample(sweird);
		return MENU;
	}

	if (Halcon_Milenario.health <= 0){
		first = true;
		//stop_sample(sweird);
		return DEAD;
	}

	return LOGIC;
}

//Dibujamos la barra de vida en la pantalla
void dibujar_salud(){
	mostrar_enemigos(vida, 5, 5);
	mostrar_rect_vida(5, 27, 205, 33, WHITE);
	mostrar_fondo_vida(6, 28, 4 + Halcon_Milenario.health, 32, GREEN);
}
//Acciones para que salgan en pantalla los Power Ups
void do_powerUPs(){
	struct_powerUp p;
	list<struct_powerUp>::iterator it;

	if (rand()%400 == 0){
		p.type = rand()%2;
		p.x = 10 + rand()%620;
		p.y = -20;
		p.yv = 4 + rand()%9;
		powerups.push_back(p);
	}

	it = powerups.begin();
	while (it != powerups.end()){
		(*it).y += (*it).yv;
		if ((*it).type == SHOT_PLUS){
			if (Halcon_Milenario.accion){
				mostrar_enemigos(powerUP1, int((*it).x), int((*it).y));
			}else{
				mostrar_enemigos(powerUP2, int((*it).x), int((*it).y));
			}
		}else{
			if (Halcon_Milenario.accion){
				mostrar_enemigos(powerUP2, int((*it).x), int((*it).y));
			}else{
				mostrar_enemigos(powerUP1, int((*it).x), int((*it).y));
			}
		}

		if (((*it).x + 20 > Halcon_Milenario.x) && ((*it).x < Halcon_Milenario.x + 25)){
			if (((*it).y + 20 > Halcon_Milenario.y) && ((*it).y < Halcon_Milenario.y + 25)){
				if ((*it).type == SHOT_PLUS){
					Halcon_Milenario.shotmode++;
					if (Halcon_Milenario.shotmode > SHOT_DOUBLE) {
						Halcon_Milenario.shotmode = SHOT_DOUBLE;
					}
				}else{
					Halcon_Milenario.shotmode--;
					if (Halcon_Milenario.shotmode < SHOT_NORMAL){Halcon_Milenario.shotmode = SHOT_NORMAL;
					}
				}
				powerups.erase(it);
				it--;
			}
		}
		it++;
	}
}
