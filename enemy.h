#ifndef _ENEMY_H
#define _ENEMY_H

#include "player.h"

//Declarcion de las variables que se utilizan para la implementacion
#define STRAFELEFT  0
#define STRAFERIGHT 1
#define CURVELEFT   2
#define CURVERIGHT  3
#define SINELEFT    4
#define SINERIGHT   5
#define DOWN        6
#define U_UP        7
#define U_DOWN      8
#define STAY_UP     9 //Implemenatacion para el Boss

//Declaracion del tipo de los Enemigos
#define HELICOPTERO  0
#define TORRE        1
#define TORREM       2
#define BANSHEE      3
#define JET      	 4
#define BOMBARDERO   5
#define KAMIKAZE     6

typedef struct _enemy
{
	bool exists;
	short patron, tipo, delay, shotdelay;
	float x, y, xv, yv, xa, ya, orig_y, orig_x;
	
	void eventos();
	void init(int type, int delay = 0);
	void init(int type, float x, float y, int pattern, int delay);
	void move();
	void dibujar();
	void disparo();
	bool colicion_con_avion();
	bool un_Disparo();
} _enemy;

extern list<_shot> eshot;
extern list<_enemy> enemies;

//Metodos a utilizar
void enemigo_nuevo(int type);
void nueva_ola_de_enemigos(int type, int num, int delay);
void crear_enemigos();
struct Node
{
    int data;
    Node* next;
    Node* prev;
    Node(int);
};

class DoublyLinkedList
{
public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void insert_front(int, int , float , float, string, struct _enemy );
    void insert_back(int, int , float , float, string, struct _enemy  );
    int delete_front();
    int delete_back();
    bool is_empty();
    void display();
    int length();
    void search(int);

private:
    Node* head;
    Node* tail;
    int size;

};



#endif
