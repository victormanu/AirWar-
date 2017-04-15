#include "globalVariables.h"
#include<iostream>
#include <fstream>
DoublyLinkedList *dll = new DoublyLinkedList();
list<_shot> eshot;
list<_enemy> enemies;
/**
 * Definimos el tipo de enemigos, posicion en pantalla y patron de movimiento
 */
void _enemy::init(int _type, int _delay)
{
	int a;
	switch (_type)
	{
	case HELICOPTERO:
		a = rand()%2;
		if (a == 0)
		{
			init(HELICOPTERO, 40 + rand()%200, -20, CURVERIGHT, _delay); // STRAFERIGHT
		}
		else
		{
			init(HELICOPTERO, 400 + rand()%200, -20, CURVELEFT, _delay); // STRAFELEFT
		}
		break;
	case TORRE:
		a = rand()%2;
		if (a == 0)
		{
			init(TORRE, rand()%300, 20, DOWN , _delay);
		}
		else
		{
			init(TORRE, rand()%300, 20, DOWN  , _delay);
		}
		break;
	case TORREM:
		a = rand()%2;
		if (a == 0)
		{
			init(TORREM, 100, 20 + rand()%350, DOWN , _delay);
		}
		else
		{
			init(TORREM, 550, 20 + rand()%350, DOWN  , _delay);
		}
		break;
	case BANSHEE:
		a = rand()%2;
		if (a == 0)
		{
			init(BANSHEE, 40 + rand()%200, -20, STRAFERIGHT, _delay);
		}
		else
		{
			init(BANSHEE, 400 + rand()%200, -20, STRAFELEFT, _delay);
		}
		break;
	case JET:
		a = rand()%2;
		if (a == 0)
		{
			init(JET, 40 + rand()%200, -20, STRAFERIGHT, _delay);
		}
		else
		{
			init(JET, 400 + rand()%200, -20, STRAFELEFT, _delay);
		}
		break;
	case BOMBARDERO:
		a = rand()%2;
		if (a == 0)
		{
			init(BOMBARDERO, 40 + rand()%200, -20, STRAFERIGHT, _delay);
		}
		else
		{
			init(BOMBARDERO, 400 + rand()%200, -20, STRAFELEFT, _delay);
		}
		break;
	case KAMIKAZE:
		a = rand()%2;
		if (a == 0)
		{
			init(KAMIKAZE, 40 + rand()%200, -20, STRAFERIGHT, _delay);
		}
		else
		{
			init(KAMIKAZE, 400 + rand()%200, -20, STRAFELEFT, _delay);
		}
		break;
	}
}

/**
 * Definimos y agregamos los patrones del movimiento
 */
void _enemy::init(int _type, float _x, float _y, int _pattern, int _delay)
{
	exists = true;
	delay = _delay;
	tipo = _type;
	orig_x = x = _x;
	orig_y = y = _y;
	patron = _pattern;
	xv = yv = xa = ya = shotdelay = 0;

	switch(patron)
	{
	case STRAFELEFT:
		yv = 4;
		xv = -2;
		break;
	case STRAFERIGHT:
		yv = 4;
		xv = 2;
		break;
	case CURVELEFT:
		yv = 5 + rand()%3;
		xv = -1;
		ya = 0;
		xa = -0.25;
		break;
	case CURVERIGHT:
		yv = 5 + rand()%3;
		xv = 1;
		ya = 0;
		xa = 0.25;
		break;
	case SINELEFT:
		xv = -5;
		break;
	case SINERIGHT:
		xv = 5;
		break;
	case DOWN:
		yv = 1;
		break;
	case STAY_UP:
		yv = 0;
		break;
	}
}

/**
 * Definimos el movimiento, mas especifico los patrones
 */
void _enemy::move()
{
	switch(patron)
	{
	case STRAFELEFT:
	case STRAFERIGHT:
		x += xv;
		y += yv;
		break;
	case CURVELEFT:
	case CURVERIGHT:
		x += xv;
		y += yv;
		xv += xa;
		yv += ya;
		break;
	case SINELEFT:
	case SINERIGHT:
		x += xv;
		y = orig_y + 50 * sin(x * PI / 180);
		break;
	case DOWN:
		y += yv;
		x = orig_x ;
		break;
	case STAY_UP:
		y += yv;
		x = orig_x + 100 * sin(y * PI / 180);yv = 0;
		break;

	}
}

/**
 * Aqui se toman en cuenta los posibles eventos como las colisiones y la obtencion del puntaje
 */
void _enemy::eventos()
{
	int d = 0;
	int s;

	if (delay > 0)
	{
		delay--;
		return;
	}

	if ((x < -50) || (y < -50) || (x > 690) || (y > 530))
	{
		exists = 0;
	}

	if (colicion_con_avion())
	{
		exists = 0;
		switch(tipo)
		{
		case HELICOPTERO:
			d = 12;
			break;
		default:
			d = 15;
			break;
		}

		play_sample(explocion, 255, 128, 1000, 0); /// Impactan al Avion con Otra nave
		Halcon_Milenario.take_damage(d);
	}
	else if (un_Disparo())
	{
		exists = 0;

		play_sample(explocion, 255, 128, 1000, 0); ///Disparos impactados del Avion a un Enemigo


		s = Nivel_actual;
		switch(tipo)
		{
		case HELICOPTERO:
			s *= 20;
			break;
		case TORRE:
			s *= 30;
			break;
		case TORREM:
			s *= 40;
			break;
		case BANSHEE:
			s *= 50;
			break;
		case JET:
			s *= 90;
			break;
		case BOMBARDERO:
			s *= 100;
			break;
		case KAMIKAZE:
			s *= 80;
			break;

		}
		if (Halcon_Milenario.accion) s /= 2;
		puntaje_obtenido += s;
	}

	if (shotdelay <= 0)
	{
		disparo();
		shotdelay = 70;
	}
	else
	{
		shotdelay--;
	}

	move();
	dibujar();
}
/**
 * Damos el movimiento y la accion de los disparos
 */
void _enemy::disparo()
{
	float speed;
	float angle = atan2(Halcon_Milenario.y - y, Halcon_Milenario.x - x);
	_shot s;

	switch (tipo)
	{
	case HELICOPTERO:
		speed = 5;
		break;
	case TORRE:
		speed = 3;
		break;
	case TORREM:
		speed = 3;
		break;
	case BANSHEE:
		speed = 5;
		break;
	case JET:
		speed = 6;
		break;
	case BOMBARDERO:
		speed = 4;
		break;
	case KAMIKAZE:
		speed = 6;
		break;
	default:
		speed = 7;
		break;
	}

	s.x = x + 10;
	s.y = y + 10;
	s.xv = speed * cos(angle);
	s.yv = speed * sin(angle);
	eshot.push_back(s);
}

/**
 * Dibujamos en pantalla los enemigos
 */
void _enemy::dibujar(){
	int i = SANE;
	if (Halcon_Milenario.accion)
	{
		i = SANE;
	}

	switch (tipo)
	{
	case HELICOPTERO:
		mostrar_animaciones(enemy1[i], int(x), int(y), ftofix((atan2(yv, xv)) * 128 / PI - 64));
		break;
	case TORRE:
		mostrar_animaciones(enemy2[i], int(x), int(y), ftofix((atan2(yv, xv)) * 128 / PI - 64));
		break;
	case TORREM:
		mostrar_enemigos(enemy3[i], int(x), int(y));
		break;
	case BANSHEE:
		mostrar_animaciones(enemy4[i], int(x), int(y), ftofix((atan2(yv, xv)) * 128 / PI - 64));
		break;
	case JET:
		mostrar_animaciones(enemy5[i], int(x), int(y), ftofix((atan2(yv, xv)) * 128 / PI - 64));
		break;
	case BOMBARDERO:
		mostrar_enemigos(enemy6[i], int(x), int(y));
		break;
	case KAMIKAZE:
		mostrar_animaciones(enemy7[i], int(x), int(y), ftofix((atan2(yv, xv)) * 128 / PI - 64));
		break;
	}
}

/**
 * Para las colisiones con los aviones
 */
bool _enemy::colicion_con_avion(){
	if ((x + 25 > Halcon_Milenario.x) && (x < Halcon_Milenario.x + 25))
	{
		if ((y + 25 > Halcon_Milenario.y) && (y < Halcon_Milenario.y + 25))
		{
			return true;
		}
	}
	return false;
}
/**
 * Colision con un bala
 */
bool _enemy::un_Disparo()
{
	list<_shot>::iterator it;
	it = Halcon_Milenario.pshot.begin();
	while (it != Halcon_Milenario.pshot.end())
	{
		if ((x + 25 > (*it).x) && (x < (*it).x + 5))
		{
			if ((y + 25 > (*it).y) && (y < (*it).y + 7))
			{
				it = Halcon_Milenario.pshot.erase(it);
				it--;
				return true;
			}
		}
		it++;
	}
	return false;
}
/**
 * Genera un nuevo enemigo
 */
void enemigo_nuevo(int type)
{
	_enemy e;
	e.init(type);
	dll->insert_front(dll->length()+1,3,e.orig_x,e.orig_y,to_string(type),e);
	enemies.push_back(e);
}
/**
 * Genera un nuevo grupo de enemigos
 */
void nueva_ola_de_enemigos(int type, int num, int delay)
{
	int a, i, p = 0;
	float x = 0, y = 0;
	_enemy e;


	switch (type)
	{
	case HELICOPTERO:
		a = rand()%2;
		if (a == 0)
		{
			p = STRAFERIGHT;
			x = 40 + rand()%200;
			y = -20;
		}
		else
		{
			p = STRAFELEFT;
			x = 400 + rand()%200;
			y = -20;
		}
		break;
	}

	i = 0;
	while (i < num)
	{
		e.init(type, x, y, p, delay * i);
		//cout<<x<<endl;
		dll->insert_front(dll->length()+1,2,x,y,to_string(type),e);
		enemies.push_back(e);
		i++;
	}
}
/**
 * Crea nuevos enemigos
 */
void crear_enemigos(){
	list<_enemy>::iterator it;
	list<_shot>::iterator sit;

	it = enemies.begin();
	while (it != enemies.end())
	{
		(*it).eventos();

		if (((*it).x < -50) || ((*it).x > 690) || ((*it).y < -50) || ((*it).y > 490))
		{
			int Identificador=((dll->delete_back()));
			cout<<Identificador<<endl;
			remove(("ListaDoble"+to_string(Identificador)+".txt").c_str());

			(*it).exists = false;
		}

		if (!(*it).exists)
		{
			it = enemies.erase(it);

			int Identificador=((dll->delete_back()));

			cout<<Identificador<<endl;
			remove(("ListaDoble"+to_string(Identificador)+".txt").c_str());

			it--;
		}
		it++;
	}

	sit = eshot.begin();
	while (sit != eshot.end())
	{
		(*sit).mover();

		if (Halcon_Milenario.accion)
		{
			mostrar_enemigos(bala_enemigos[SANE], int((*sit).x), int((*sit).y));
		}
		else
		{
			mostrar_enemigos(bala_enemigos[SANE], int((*sit).x), int((*sit).y));
		}
		if (((*sit).x + 7 > Halcon_Milenario.x) && ((*sit).x < Halcon_Milenario.x + 25))
		{
			if (((*sit).y + 7 > Halcon_Milenario.y) && ((*sit).y < Halcon_Milenario.y + 25))
			{
				Halcon_Milenario.take_damage(8);
				sit = eshot.erase(sit);
				sit--;
			}
		}
		else if (((*sit).x < -50) || ((*sit).x > 690) || ((*sit).y < -50) || ((*sit).y > 490))
		{

			sit = eshot.erase(sit);
			sit--;
		}

		sit++;
	}
}
Node::Node(int value)       //Parameterized Constructor
{
    data = value;
    next = prev = NULL;
}


DoublyLinkedList::DoublyLinkedList()
{
    head = tail = NULL;
    size = 0;
}

DoublyLinkedList::~DoublyLinkedList()
{
}

void DoublyLinkedList::insert_front(int Identificador,int ataque, float x, float y,string type,struct _enemy temporal)
{
	Node* temp = new Node(Identificador);
    // paginacion
    ofstream myfile;
    myfile.open ("ListaDoble"+to_string(Identificador)+".txt");
    myfile << to_string(temporal.delay)+"\n";
    myfile << to_string(temporal.exists)+"\n";
    myfile << to_string(temporal.orig_x)+"\n";
    myfile << to_string(temporal.orig_y)+"\n";
    myfile << to_string(temporal.patron)+"\n";
    myfile << to_string(temporal.shotdelay)+"\n";
    myfile << to_string(temporal.tipo)+"\n";
    myfile << to_string(temporal.x)+"\n";
    myfile << to_string(temporal.xa)+"\n";
    myfile << to_string(temporal.xv)+"\n";
    myfile << to_string(temporal.y)+"\n";
    myfile << to_string(temporal.ya)+"\n";
    myfile << to_string(temporal.yv)+"\n";

    myfile << to_string(x)+"\n";
    myfile << to_string(y)+"\n";
    myfile << type+"\n";
    myfile.close();

    if (head == NULL)
        head = tail = temp;
    else
    {
        head->prev = temp;
        temp->next = head;
        head = temp;
    }
    size++;
}

void DoublyLinkedList::insert_back(int Identificador,int ataque, float x, float y,string type,struct _enemy temporal)
{
	Node* temp = new Node(Identificador);
    //Paginacion
    ofstream myfile;
    myfile.open ("ListaDoble"+to_string(Identificador)+".txt");
    myfile << to_string(temporal.delay)+"\n";
    myfile << to_string(temporal.exists)+"\n";
    myfile << to_string(temporal.orig_x)+"\n";
    myfile << to_string(temporal.orig_y)+"\n";
    myfile << to_string(temporal.patron)+"\n";
    myfile << to_string(temporal.shotdelay)+"\n";
    myfile << to_string(temporal.tipo)+"\n";
    myfile << to_string(temporal.x)+"\n";
    myfile << to_string(temporal.xa)+"\n";
    myfile << to_string(temporal.xv)+"\n";
    myfile << to_string(temporal.y)+"\n";
    myfile << to_string(temporal.ya)+"\n";
    myfile << to_string(temporal.yv)+"\n";
    myfile << to_string(x)+"\n";
    myfile << to_string(y)+"\n";
    myfile << type+"\n";
    myfile.close();




    if (tail == NULL)
        head = tail = temp;
    else
    {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
    size++;
}

int DoublyLinkedList::delete_front()
{
    if (!is_empty())
    {
    	Node* temp = head;
        if (head == tail)
        {
            tail = NULL;
        }
        int delValue = temp->data;
        head = head->next;

        delete temp;

        size--;

        //Traer datos de paginacion
        ifstream myfile("ListaDoble"+to_string(delValue)+".txt");
        string Extraction;

        if(!myfile)
        {
            cout<<"Error opening output file"<<endl;
            system("pause");
            //return -1;
        }

        /*cout<<"identificador: "<<delValue<<"\n";
        //identificador=delValue;
        getline(myfile,Extraction,'\n');
        //ataque=Extraction;
        cout<<"ataque: "<<Extraction<<"\n";
        getline(myfile,Extraction,'\n');
        //x=Extraction;
        cout<<"x: "<<Extraction<<"\n";
        getline(myfile,Extraction,'\n');
        //y=Extraction;
        cout<<"y: "<<Extraction<<"\n";
        getline(myfile,Extraction,'\n');

*/



        return delValue;

    }
    return 0;
}

int DoublyLinkedList::delete_back()
{
    if (!is_empty())
    {
    	Node* temp = tail;
        if (head == tail)
        {
            head = NULL;
        }
        int delValue = temp->data;
        tail->next = NULL;
        tail = tail->prev;

        delete temp;

        size--;
        //Traer datos de paginacion
        ifstream myfile("ListaDoble"+to_string(delValue)+".txt");
        string Extraction;

        if(!myfile)
        {
            cout<<"Error opening output file"<<endl;
            system("pause");
            //return -1;
        }

        cout<<"identificador: "<<delValue<<"\n";
        //identificador=delValue;
        getline(myfile,Extraction,'\n');
        //ataque=Extraction;
        cout<<"ataque: "<<Extraction<<"\n";
        getline(myfile,Extraction,'\n');
        //x=Extraction;
        cout<<"x: "<<Extraction<<"\n";
        getline(myfile,Extraction,'\n');
        //y=Extraction;
        cout<<"y: "<<Extraction<<"\n";
        getline(myfile,Extraction,'\n');




        return delValue;

    }
    return 0;
}

bool DoublyLinkedList::is_empty()
{
    if (size <= 0)
    {
        return true;
    }

    return false;
}

void DoublyLinkedList::display()
{
	Node* temp = head;

    cout << "\n\nDisplay in forward order\n";
    while (temp != NULL)
    {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << " NULL";
}

int DoublyLinkedList::length()
{
    return size;
}

void DoublyLinkedList::search(int Identificador)
{
    if (!is_empty())
    {

        //Traer datos de paginacion
        ifstream myfile("ListaDoble"+to_string(Identificador)+".txt");
        string Extraction;

        if(!myfile)
        {
            cout<<"Error opening output file"<<endl;
            system("pause");
            //return -1;
        }

        cout<<"identificador: "<<Identificador<<"\n";
        //identificador=delValue;
        getline(myfile,Extraction,'\n');
        //ataque=Extraction;
        cout<<"ataque: "<<Extraction<<"\n";
        getline(myfile,Extraction,'\n');
        //x=Extraction;
        cout<<"x: "<<Extraction<<"\n";
        getline(myfile,Extraction,'\n');
        //y=Extraction;
        cout<<"y: "<<Extraction<<"\n";
        getline(myfile,Extraction,'\n');




        Node* temp = head;
        while (temp)
        {
            if (temp->data == Identificador)
            {
                cout << "YES! got it." << endl;
                break;
            }
            temp = temp->next;
        }
    }
    else
    {
        cout << "List is empty" << endl;
    }
}
