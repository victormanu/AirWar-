#include "globalVariables.h"

volatile int counter;
/**
 * Para aumentar el contador
 */
void update_counter()
{
	counter++;
}

END_OF_FUNCTION(update_counter)

//Declaracion de variables
int Nivel_actual, puntaje_obtenido;// highscore;

unsigned t0, t1; //Para el control del tiempo de Ejecucion


BITMAP *back_buffer;

BITMAP  *bullet_menu, *nombre_juego, *vida, *nave, *bala_avion[2], *enemy1[2],
		*bala_enemigos[2], *powerUP2, *powerUP1, *enemy2[2],
		*enemy3[2],*enemy4[2],*enemy5[2],*enemy6[2],*enemy7[2];

SAMPLE *recarga, *fuego, *dano_recibido, *explocion, *cancion, *nave_abatida;

/**
 * Declaracion de la firmas de los metodos
 */
int menu();
int muerte();
extern int logica();

short init_everything();

/**
 * Encargado de inicializar la logica del juego
 */
int main(){


	short gamestatus;
	bool draw;

	if (init_everything() == 1){
		return 1;
	}

	clear_to_color(back_buffer, BLACK);
	counter = 0;
	gamestatus = MENU;
	draw = false;


	while (gamestatus != QUIT){
		while (counter > 0){
			mostrar_fondo(BLACK);
			switch (gamestatus){
			case MENU:
				gamestatus = menu();
				break;
			case LOGIC:
				gamestatus = logica();
				break;
			case DEAD:
				gamestatus = muerte();
				break;
			}
			draw = true;
			counter--;
		}

		if (draw){
			draw_all();
			blit(back_buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

			draw = false;
		}

		while (counter < 1){
			rest(1);
		}
	} // Fin del Juego



	//pintar_estadisticas(time_playing);

	///Destruye las imagenes
	destroy_bitmap(back_buffer);
	destroy_bitmap(bullet_menu);
	destroy_bitmap(nombre_juego);
	destroy_bitmap(vida);
	destroy_bitmap(nave);
	destroy_bitmap(bala_avion[0]);
	destroy_bitmap(enemy1[0]);
	destroy_bitmap(enemy2[0]);
	destroy_bitmap(enemy3[0]);
	destroy_bitmap(enemy4[0]);
	destroy_bitmap(enemy5[0]);
	destroy_bitmap(enemy6[0]);
	destroy_bitmap(enemy7[0]);
	destroy_bitmap(bala_enemigos[0]);
	destroy_bitmap(powerUP2);
	destroy_bitmap(powerUP1);
	destroy_sample(recarga);
	destroy_sample(fuego);
	destroy_sample(dano_recibido);
	destroy_sample(explocion);
	destroy_sample(cancion);

	allegro_exit();



	return 0;
}
END_OF_MAIN()

short init_everything(){
	allegro_init();
	install_keyboard();
	install_timer();

	srand(time(NULL));

	LOCK_VARIABLE(counter);
	LOCK_FUNCTION(update_counter);

	set_color_depth(16);

	if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0) != 0){
		allegro_message("ERROR GRAFICO AL INICIAR LA APLICACION");
		return 1;
	}

	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	install_int_ex(update_counter, BPS_TO_TIMER(70));

	back_buffer = create_bitmap(640, 480);

	bullet_menu = load_bitmap("imagenes/ammo.bmp", NULL);
	nombre_juego = load_bitmap("imagenes/titulo.bmp", NULL);
	vida = load_bitmap("imagenes/vida.bmp", NULL);
	nave = load_bitmap("imagenes/nave.bmp", NULL);
	bala_avion[SANE] = load_bitmap("imagenes/bala1.bmp", NULL);
	bala_enemigos[SANE] = load_bitmap("imagenes/bala2.bmp", NULL);
	powerUP2 = load_bitmap("imagenes/powerUP2.bmp", NULL);
	powerUP1 = load_bitmap("imagenes/powerUP1.bmp", NULL);

	enemy1[SANE] = load_bitmap("imagenes/helicoptero.bmp", NULL);
	enemy2[SANE] = load_bitmap("imagenes/torre1.bmp", NULL);
	enemy3[SANE] = load_bitmap("imagenes/torre2.bmp", NULL);
	enemy4[SANE] = load_bitmap("imagenes/banshee.bmp", NULL);
	enemy5[SANE] = load_bitmap("imagenes/jet.bmp", NULL);
	enemy6[SANE] = load_bitmap("imagenes/bombardero.bmp", NULL);
	enemy7[SANE] = load_bitmap("imagenes/kamikaze.bmp", NULL);

	recarga = load_sample("sonidos/recarga.wav");
	fuego = load_sample("sonidos/gunshot.wav");
	dano_recibido = load_sample("sonidos/nave_afectada.wav");
	explocion = load_sample("sonidos/explocion.wav");
	cancion = load_sample("sonidos/cancion.wav");
	//nave_abatida = load_sample("sonidos/nave_destruida.wav");

	play_sample(cancion, 255, 128, 1000, 1); // Cancion a lo largo del Juego

	return 0;
}
/**
 * Metodos que son usados para el menu, donde escogemos que opcion queremos
 */
int menu(){
	static short sel = 0, delay = 0;

	mostrar_enemigos(nombre_juego, 120, 40); /// Imagen con el nombre del Juego
	mostrar_texto(font, "Play", 320, 250, WHITE);
	mostrar_texto(font, "Exit", 320, 280, WHITE);

	mostrar_animaciones(bullet_menu, 200, 245 + (sel * 30), 0);

	if (delay <= 0){
		if (key[KEY_UP]){
			sel--;
			if (sel < 0){
				sel = 1;
			}
			delay = 10;
			play_sample(recarga, 255, 128, 1000, 0);
		}
		if (key[KEY_DOWN]){
			sel++;
			if (sel > 1){
				sel = 0;
			}
			delay = 10;
			play_sample(recarga, 255, 128, 1000, 0);
		}
		if (key[KEY_ENTER]){
			delay = 15;
			puntaje_obtenido = 0;
			Nivel_actual = 1;
			switch(sel){
			case 0:
				Halcon_Milenario.init(false);
				return LOGIC;
				break;
			case 1:
				return QUIT;
				break;
			}
		}
		if (key[KEY_ESC]){
			return QUIT;
		}
	}else{
		delay--;
	}
	return MENU;
}

int muerte(){

	static bool first = true;

	if (first){
		Halcon_Milenario.accion = false;
		first = false;
	}

	mostrar_texto(font, "Partida Terminada", 320, 200, WHITE);

	mostrar_texto(font, "..: ESTADISTICAS DEL JUEGO ::.", 320, 230, RED);

	char dato_puntaje[20]; // Capturamos el puntaje alcanzado al final el Juego	 y se imprime
	sprintf(dato_puntaje, "Puntaje: %d", puntaje_obtenido);
	mostrar_texto(font, dato_puntaje, 320, 250, GREEN);

	char dato_tiempo[20]; // Capturamos el jugado al final el Juego	 y se imprime
	sprintf(dato_tiempo, "Tiempo Jugado: %d",0);
	mostrar_texto(font, dato_tiempo, 320, 260, GREEN);

	char dato_nivel[30]; // Capturamos el nivel alcanzado al final el Juego	 y se imprime
	sprintf(dato_nivel, "Maximo Nivel Alcanzado: %d", Nivel_actual);
	mostrar_texto(font, dato_nivel, 320, 270, GREEN);

	if ((key[KEY_ENTER]) || (key[KEY_ESC])){
		first = true;

		return MENU;
	}
	return DEAD;
}
