#pragma once
#include "Rakieta.h"
class RakietaLewa :
	public virtual Rakieta
{
public:
	RakietaLewa();
	
	float racket_left_x;
	float racket_left_y;
	~RakietaLewa();

	friend class Kontener;
	friend class Boisko;
	friend class Pilka;
	friend void rysujPilke(Kontener &);
	friend void ruszPilke(Kontener &);
	friend void setVSync(bool sync);
	friend void WyswietlObraz(void);
	friend void wyswietlWynik(Kontener &);
	friend void podsumowanieGry();
	friend void ObslugaKlawiatury(unsigned char klawisz, int x, int y);
	friend void ObslugaKlawiszySpecjalnych(int klawisz, int x, int y);
	friend void ObsKlawiszySterowania();

};

