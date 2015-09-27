#pragma once

class Rakieta
{

	friend class Kontener;
	friend class Boisko;
	friend void rysujGraczaI(Kontener &);
	friend void rysujGraczaII(Kontener &);
	friend void rysujPilke(Kontener &);
	friend void ruszPilke(Kontener &);
	friend void wykrywaczkolizji(Kontener &);
	friend void setVSync(bool sync);
	friend void WyswietlObraz(void);
	friend void wyswietlWynik(Kontener &);
public:
	Rakieta();
	
	int racket_width;
	int racket_height;
protected:
	unsigned char wynik;
	virtual ~Rakieta();
};

