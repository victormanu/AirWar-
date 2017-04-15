#ifndef _PLAYER_H
#define _PLAYER_H

//Tipos de Disparos
#define SHOT_NORMAL 0
#define SHOT_DOUBLE 1

//Tipos Power Ups
#define SHOT_PLUS  0
#define SHOT_MINUS 1

typedef struct struct_powerUp  ///Struct para los powerUps
{
	float x, y, yv;
	short type;
} _powerup;

typedef struct _shot  /// Struct para las balas
{
	const static int w = 5;
	const static int h = 5;
	
	float x, y, xv, yv;
	
	void mover();
	void dibujar();
	bool offscreen();
} _shot;

typedef struct _player  /// Struct para el Jugador (La Nave)
{
	const static int w = 25;
	const static int h = 25;

	bool accion;
	short shotmode, shotdelay, shotdelay2;
	short health;
	float x, y, xv, yv;
	list<_shot> pshot;
	
	void init(bool _twoplayer);
	void vida_Nueva();
	void do_stuff();
	void move();
	void take_damage(int damage);
	void draw();
	void fire();
	void p2_fire();
} _player;

extern _player Halcon_Milenario;
extern list<struct_powerUp> powerups;

#endif
