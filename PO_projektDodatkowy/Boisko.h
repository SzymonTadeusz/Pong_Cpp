#include <cstdlib>
#include<stdlib.h>
#include <glut.h>
#include "Kontener.h"
#include"Pilka.h"
#pragma once
class Boisko
{
public:
	Boisko();
	friend class Kontener;
	friend class RakietaLewa;
	friend class RakietaPrawa;
	void rysujObszarGry();
	void rysujGraczaI(Kontener &);
	void rysujGraczaII(Kontener &);
	void rysujPilke(Kontener &, Pilka* pilka);
	void ruszPilke(Kontener &, Pilka *, bool);
	void wyswietlWynik(Kontener &);
	~Boisko();
};

