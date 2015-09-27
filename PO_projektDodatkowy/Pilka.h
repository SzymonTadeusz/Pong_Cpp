#pragma once
#include "Kontener.h"
class Pilka
{
public:
	Pilka();

	float ball_pos_x;
	float ball_pos_y;
	float ball_dir_x;
	float ball_dir_y;
	int ball_size;
	float ball_speed;
	~Pilka();
	void wykrywaczkolizji(Kontener&);	//collider

	friend class Kontener;

	friend void rysujGraczaI(Kontener &);
	friend void rysujGraczaII(Kontener &);
	friend void rysujPilke(Kontener &);
	friend void ruszPilke(Kontener &);
	friend void wykrywaczkolizji(Kontener &);
	friend void setVSync(bool sync);
	friend void WyswietlObraz(void);
	friend void wyswietlWynik(Kontener &);
};
