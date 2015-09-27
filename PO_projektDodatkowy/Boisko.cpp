#include "Boisko.h"

Boisko::Boisko()
{
}


Boisko::~Boisko()
{
}

void Boisko::rysujGraczaI(Kontener & nowy){				//rysowanie prawej rakietki
	glPushMatrix();
	glColor3f(0, 0, 0.2);
	glScalef((nowy.prawa->racket_height) / 5, 1.5, nowy.prawa->racket_width / 5);
	glTranslatef(nowy.prawa->racket_right_x / 16.5, 0, nowy.prawa->racket_right_y / 2);
	glutSolidCube(1);
	glPopMatrix();
}

void Boisko::rysujGraczaII(Kontener & nowy){			//rysowanie lewej rakietki
	glPushMatrix();
	glColor3f(0, 0.2, 0);
	glScalef(nowy.lewa->racket_height / 5, 1.5, nowy.lewa->racket_width / 5);
	glTranslatef(nowy.lewa->racket_left_x / 16.5, 0, nowy.lewa->racket_left_y / 2);
	glutSolidCube(1);
	glPopMatrix();
}

void Boisko::rysujPilke(Kontener & nowy, Pilka* pilka){				//rysowanie (statycznej) pi³ki
	glPushMatrix();
	glColor3f(0.5, 0, 0);
	glutSolidSphere(pilka->ball_size, 10, 10);
	glPopMatrix();
}

void Boisko::ruszPilke(Kontener & nowy, Pilka *pilka, bool flaga){
	glPushMatrix();
	glTranslatef(pilka->ball_pos_x, 0, pilka->ball_pos_y);
	if (flaga) pilka->wykrywaczkolizji(nowy);
	rysujPilke(nowy,pilka);
	glPopMatrix();

	if (!flaga){
		glColor3f(1, 1, 1);
		glRasterPos3f(20, 0, -8);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'P');
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'a');
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'u');
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'z');
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'a');
	}

	if (!flaga)glutSetWindowTitle("Pong 3D \n- aby wyjœæ z trybu pauzy, wciœnij \'P\'");
	else glutSetWindowTitle("Pong 3D");

}



void Boisko::rysujObszarGry(){			//rysowanie band
	glPushMatrix();
	glColor3f(0, 0, 0);
	glScalef(2, 2, 2);
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, -25, 0);
	glScalef(60, 2, 2);
	glutSolidCube(1);
	glTranslatef(0, 25, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	//glRotatef();
	glScalef(50, 2, 2);
	glTranslatef(0, 0, 15);
	glutSolidCube(1);
	glTranslatef(0, 0, -30);
	glutSolidCube(1);
	glPopMatrix();
	glScalef(0.5, 0.5, 0.5);
	glPopMatrix();
}



void Boisko::wyswietlWynik(Kontener & nowy){
	glPushMatrix();
	glTranslatef(-55, 0, 0);
	glPushMatrix();
	for (int i = 0; i < nowy.lewa->wynik; i++)
	{
		glColor3f(1, 1, 1);
		glTranslatef(0, 0, (-7 * (i % 10)) - 10);
		if (i % 10 == 0 && i != 0) glTranslatef(-7, 0, 0);							//jeœli i=10,20,30..., zjedŸ linijkê ni¿ej
		if ((((nowy.lewa->wynik - nowy.prawa->wynik))>0) &&				//pi³ka setowa, jeœli L.wynik > P.wynik
			nowy.lewa->wynik >= nowy.doIluPunktow - 1)  glColor3f(0.5, 0, 0);			//oraz L.wynik >= doIluPunktow 	
		if (i >= nowy.doIluPunktow - 1 && (((nowy.lewa->wynik - nowy.prawa->wynik))>1))glColor3f(1, 1, 0);
		glutSolidCube(2);
		glTranslatef(0, 0, 7 * (i % 10) + 10);							//powróæ
	}
	glPopMatrix();

	glPushMatrix();
	for (int i = 0; i < nowy.prawa->wynik; i++)
	{
		glColor3f(1, 1, 1);
		glTranslatef(0, 0, (7 * (i % 10)) + 10);
		if (i % 10 == 0 && i != 0) glTranslatef(-7, 0, 0);							//jeœli i=10,20,30..., zjedŸ linijkê ni¿ej
		if ((((nowy.prawa->wynik - nowy.lewa->wynik))>0) &&				//pi³ka setowa, jeœli P.wynik > L.wynik
			nowy.prawa->wynik >= (nowy.doIluPunktow - 1))  glColor3f(0.5, 0, 0);		//oraz P.wynik >= doIluPunktow
		if (i >= nowy.doIluPunktow - 1 && (((nowy.prawa->wynik - nowy.lewa->wynik))>1))glColor3f(1, 1, 0);
		glutSolidCube(2);
		glTranslatef(0, 0, -7 * (i % 10) - 10);							//powróæ
	}
	if ((nowy.lewa->wynik >= nowy.doIluPunktow && ((nowy.lewa->wynik - nowy.prawa->wynik)>1)) || (nowy.prawa->wynik >= nowy.doIluPunktow && ((nowy.prawa->wynik - nowy.lewa->wynik)>1))) podsumowanieGry();
	glPopMatrix();
	glPopMatrix();
}
