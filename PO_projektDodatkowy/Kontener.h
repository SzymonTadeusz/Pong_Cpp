#include "Rakieta.h"
#include "RakietaLewa.h"
#include "RakietaPrawa.h"
#pragma once


class Kontener{
public:
	RakietaLewa* lewa;
	RakietaPrawa* prawa;
	int doIluPunktow;
	Kontener() { this->lewa = new RakietaLewa(); this->prawa = new RakietaPrawa();}

	friend class Boisko;
	friend class Pilka;
	friend void setVSync(bool sync);
	friend void WyswietlObraz(void);
	friend void wyswietlWynik(Kontener &);
	friend void podsumowanieGry();
	friend void ObslugaKlawiatury(unsigned char klawisz, int x, int y);
	friend void ObslugaKlawiszySpecjalnych(int klawisz, int x, int y);
};