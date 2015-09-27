#pragma once
#include "Rakieta.h"
class RakietaPrawa :
	public virtual Rakieta
{
public:
	RakietaPrawa();

	float racket_right_x;
	float racket_right_y;
	~RakietaPrawa();

	friend class Kontener;
	friend class Boisko;
	friend class Pilka;
	friend void rysujGraczaI(Kontener &);
	friend void rysujGraczaII(Kontener &);
	friend void rysujPilke(Kontener &);
	friend void ruszPilke(Kontener &);
	friend void wykrywaczkolizji(Kontener &);
	friend void setVSync(bool sync);
	friend void WyswietlObraz(void);
	friend void wyswietlWynik(Kontener &);
	friend void podsumowanieGry();
	friend void ObslugaKlawiatury(unsigned char klawisz, int x, int y);
	friend void ObslugaKlawiszySpecjalnych(int klawisz, int x, int y);
	friend void ObsKlawiszySterowania();

};
