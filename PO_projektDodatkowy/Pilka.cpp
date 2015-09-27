#include <cmath>
#include "Pilka.h"
#include <Windows.h>
#include <iostream>


Pilka::Pilka(){
	this->ball_pos_x = 0;
	this->ball_pos_y = 0;
	this->ball_dir_x = -0.10;
	this->ball_dir_y = 2.0;
	this->ball_size = 2;
	this->ball_speed = 2;
}
void Pilka::wykrywaczkolizji(Kontener & nowy){			//collider
	// dodaj parametr w kolejnej klatce
	this->ball_pos_x += this->ball_dir_x * this->ball_speed / 8;
	this->ball_pos_y += this->ball_dir_y * this->ball_speed / 8;
	// Sprawd�, czy nie uderzy�a lewa rakietka:
	if (this->ball_pos_y > nowy.lewa->racket_left_y - nowy.lewa->racket_width / 5 &&
		this->ball_pos_y < nowy.lewa->racket_left_y &&
		fabs(this->ball_pos_x - nowy.lewa->racket_left_x) < nowy.lewa->racket_height / 8 &&
		true){//this->ball_pos_x > nowy.lewa->racket_left_x) { // niepotrzebne
		// ustawia kierunek g�ra-d� w zale�no�ci od tego, kt�r� cz�ci� rakietki uderzymy pi�k�:
		float t = ((float(this->ball_pos_x - nowy.lewa->racket_left_x) / float(nowy.lewa->racket_height / 4)) + 0.1) * 3;
		this->ball_dir_y = fabs(this->ball_dir_y); // odbij w prawo
		this->ball_dir_x = t;
		Beep(512, 25);
	}
	// Sprawd�, czy nie uderzy�a prawa rakietka:
	if (this->ball_pos_y < nowy.prawa->racket_right_y + nowy.prawa->racket_width / 5 &&
		this->ball_pos_y > nowy.prawa->racket_right_y &&
		fabs(this->ball_pos_x - nowy.prawa->racket_right_x) < nowy.prawa->racket_height / 8 &&
		true){//this->ball_pos_x > nowy.prawa->racket_right_x) {
		// ustaw kierunek g�ra-d�
		float t = ((float(this->ball_pos_x - nowy.prawa->racket_right_x) / float(nowy.prawa->racket_height / 4)) + 0.1) * 3;
		this->ball_dir_y = -fabs(this->ball_dir_y); // odbij w lewo
		this->ball_dir_x = t;
		Beep(450, 25);
	}
	// Sprawd�, czy lewy nie przegra�:
	if (this->ball_pos_y < -58) {
		++nowy.prawa->wynik;
		this->ball_pos_x = 0;
		this->ball_pos_y = 0;
		nowy.lewa->racket_left_x = 0;
		nowy.prawa->racket_right_x = 0;
		this->ball_dir_y = fabs(this->ball_dir_y); // podaj pi�k� zwyci�zcy
		this->ball_dir_x = 0;
		Beep(1024, 50);
		Beep(1150, 50);
		Beep(1024, 50);
		Beep(1150, 50);

	}
	// Sprawd�, czy prawy nie przegra�:
	if (this->ball_pos_y > 58) {
		++nowy.lewa->wynik;
		this->ball_pos_x = 0;
		this->ball_pos_y = 0;
		nowy.lewa->racket_left_x = 0;
		nowy.prawa->racket_right_x = 0;
		this->ball_dir_y = -fabs(this->ball_dir_y); // podaj pi�k� zwyci�zcy
		this->ball_dir_x = 0;
		Beep(1024, 50);
		Beep(1150, 50);
		Beep(1024, 50);
		Beep(1150, 50);

	}
	// Sprawd�, czy nie powinna si� odbi� od g�rnej �ciany:
	if (this->ball_pos_x > 46) {
		this->ball_dir_x = -fabs(this->ball_dir_x); // odbij lustrzanie w d�
		Beep(350, 25);

	}
	// Sprawd�, czy nie powinna si� odbi� od dolnej �ciany:
	if (this->ball_pos_x < -46) {
		this->ball_dir_x = fabs(this->ball_dir_x); // odbij lustrzanie w g�r�
		Beep(350, 25);

	}
}


Pilka::~Pilka()
{
}
