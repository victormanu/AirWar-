#include "globalVariables.h"

_player Halcon_Milenario;

/**
 * Movimiento para el disparo
 */
void _shot::mover()
{
	x += xv;
	y += yv;
}
/**
 * Dibujar el disparo en pantalla
 */
void _shot::dibujar()
{
	mostrar_animaciones(bala_avion[SANE],int(x), int(y), ftofix(atan2(yv, xv) * 128 / PI + 64));
}

bool _shot::offscreen()
{
	if (x < -w) return true;
	if (x > SCREEN_W) return true;
	if (y < -h) return true;
	if (y > SCREEN_H) return true;
	return false;
}


void _player::do_stuff(){

	list<_shot>::iterator it;

	if ((key[KEY_LEFT])){
		xv = -3;
	}
	else if ((key[KEY_RIGHT])){
		xv = 3;
	}
	else{
		xv /= 1.2;
	}
	if ((key[KEY_UP])){
		yv = -3;
	}
	else if ((key[KEY_DOWN]) ){
		yv = 3;
	}else{
		yv /= 1.2;
	}

	if (shotdelay <= 0){
		if ((key[KEY_SPACE])){
			fire();
			play_sample(fuego, 255, 128, 1000, 0);
			shotdelay = 15;
		}
	}else{
		shotdelay--;
	}

	it = pshot.begin();
	while (it != pshot.end()){
		(*it).mover();
		(*it).dibujar();
		if ((*it).offscreen()){
			it = pshot.erase(it);
			it--;
		}
		it++;
	}

	move();
	draw();
}

/**
 * Movimiento del jugador
 */
void _player::move(){
	x += xv;
	y += yv;

	if (x < 0) x = 0;
	if (x + w > SCREEN_W) x = SCREEN_W - w;
	if (y < 0) y = 0;
	if (y + h > SCREEN_H) y = SCREEN_H - h;
}

/**
 * Para bajar la vida del jugador
 */
void _player::take_damage(int damage){
	play_sample(dano_recibido, 255, 128, 1000, 0);
	health -= damage / 2;
}

/**
 * Dibuja el jugador(Avion) en pantalla
 */
void _player::draw(){
	mostrar_enemigos(nave, int(x), int(y));
}

/**
 * Dibuja el disparo
 */
void _player::fire(){
	_shot s;

	switch (shotmode){
	case SHOT_NORMAL:
		s.x = x + w / 2;
		s.y = y + 2;
		s.xv = 0;
		s.yv = -5;
		pshot.push_back(s);
		break;
	case SHOT_DOUBLE:
		s.x = x - 10 + w / 2;
		s.y = y + 2;
		s.xv = 0;
		s.yv = -5;
		pshot.push_back(s);
		s.x = x + 10 + w / 2;
		s.y = y + 2;
		s.xv = 0;
		s.yv = -5;
		pshot.push_back(s);
		break;
	}
}

/**
 *Inicializa el jugador
 */
void _player::init(bool _twoplayer){
	accion = true;
	shotmode = SHOT_NORMAL;
	shotdelay = 0;
	shotdelay2 = 0;
	x = SCREEN_W / 2 - w / 2;
	y = SCREEN_H - h - 20;
	xv = 0;
	yv = 0;
	health = 200;
}
