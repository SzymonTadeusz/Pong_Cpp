#include "Pilka.h"
#include"Boisko.h"
#include<iostream>
#include <windows.h>
using namespace std;

bool flaga = false;			//0 - tryb pauzy, 1 - tryb rozgrywki
bool flag = true;		//flaga istnienia okna rozgrywki
int szer = 640, wys = 480;			//poczatkowe wymiary ekranu
int okno; unsigned int ile;		//nr okna (zarządzane przez Windows) oraz liczba punktow w partii
//Ustawienia widoku początkowego:
GLfloat przyblizenie = 200;
GLfloat rotObsY = 90.0;
GLfloat rotObsX = 60.0;
GLfloat rotObsZ = 0.0;

Kontener & nowy = Kontener();	// powołanie obiektu klasy kontener złożonego z piłki i dwóch rakietek
Boisko boisko = Boisko();
Pilka *pilka = new Pilka();

void UstawParametryWidoku(int szerokosc, int wysokosc);
void ObslugaKlawiatury(unsigned char klawisz, int x, int y);
void ObslugaKlawiszySpecjalnych(int klawisz, int x, int y);
void makedelay(int);
void setVSync(bool sync);
void WyswietlObraz(void);
void podsumowanieGry();


void podsumowanieGry()
{	glutReshapeWindow(szer, wys);
	glutIdleFunc(0);			// przestan renderowac obraz
	glutIconifyWindow();
	flag = false;				//false - okno rozgrywki nie isnieje
	system("cls");				//wyczysc ekran i wyswietl podsumowanie gry
	std::cout << "\n\t\t\t\t PONG" << std::endl << "\t\t\t   Szymon Muszynski" << std::endl << "\t   Praca zaliczeniowa na przedmiot Programowanie Obiektowe";
	cout << "\n\n\n\n\t\t   Mecz zakonczyl sie wynikiem " << (int)nowy.lewa->wynik << " : " << (int)nowy.prawa->wynik << '.' << endl << "\t\t   Aby zakonczyc, zamknij to okno.";
	}

void UstawParametryWidoku(int szerokosc, int wysokosc)
{
	glViewport(0, 0, szerokosc, wysokosc);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0,(float)szerokosc / (float)wysokosc, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void WyswietlObraz(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
glPushMatrix();
	glTranslatef(0, 0, -przyblizenie);
	glRotatef(rotObsX, 1, 0, 0);
	glRotatef(rotObsY, 0, 1, 0);
	glRotatef(rotObsZ, 0, 0, 1);
	glColor3f(0.1, 0.1, 0.1);
	glPushMatrix();
	ObsKlawiszySterowania();

	boisko.rysujObszarGry();
	boisko.rysujGraczaI(nowy);
	boisko.rysujGraczaII(nowy);
	boisko.wyswietlWynik(nowy);
	boisko.ruszPilke(nowy,pilka, flaga);

	glPopMatrix();
glPopMatrix();
	glutSwapBuffers();
}

void makedelay(int value){
		WyswietlObraz();
		if (flag){
		glutTimerFunc(1000 / 60, makedelay, 1);
		glutPostRedisplay();
	}
}

void ObsKlawiszySterowania(){
	if (flaga && GetAsyncKeyState(0x57))
		nowy.lewa->racket_left_x = (nowy.lewa->racket_left_x <40) ? nowy.lewa->racket_left_x += 0.40 : nowy.lewa->racket_left_x;
	if (flaga && GetAsyncKeyState(0x53))
		nowy.lewa->racket_left_x = (nowy.lewa->racket_left_x > -40) ? nowy.lewa->racket_left_x -= 0.40 : nowy.lewa->racket_left_x;
	if (flaga && GetAsyncKeyState(VK_NUMPAD8))
		nowy.prawa->racket_right_x = (nowy.prawa->racket_right_x < 40) ? nowy.prawa->racket_right_x += 0.40 : nowy.prawa->racket_right_x;
	if (flaga && GetAsyncKeyState(VK_NUMPAD5))
		nowy.prawa->racket_right_x = (nowy.prawa->racket_right_x > -40) ? nowy.prawa->racket_right_x -= 0.40 : nowy.prawa->racket_right_x;

}

void ObslugaKlawiatury(unsigned char klawisz, int x, int y)
{

	switch (klawisz)
	{
	case '-':
		przyblizenie = (przyblizenie <= 300 && przyblizenie >= 35) ? przyblizenie += 2.0 : przyblizenie;
		break;
	case '+':;
	case '=':
		przyblizenie = (przyblizenie <= 305 && przyblizenie >= 40) ? przyblizenie -= 2.0 : przyblizenie;
		break;
	case 'f':
		if (pilka->ball_speed >= 0.5)pilka->ball_speed -= 0.25;
		break;
	case 'g':
		if (pilka->ball_speed <= 4.75)pilka->ball_speed += 0.25;
		break;
	case 'p':
		flaga = !flaga;
		break;
	case '0':
		rotObsX = 90, rotObsY = 90, rotObsZ = 0;
		break;
	}
	if (klawisz == 27)	exit(1);
	
}

void ObslugaKlawiszySpecjalnych(int klawisz, int x, int y)
{
	switch (klawisz)
	{
	case GLUT_KEY_UP:
		rotObsX = rotObsX + 1.0;
		break;
	case GLUT_KEY_DOWN:
		rotObsX = rotObsX - 1.0;
		break;
	case GLUT_KEY_LEFT:
		rotObsY = rotObsY - 1.0;
		break;
	case GLUT_KEY_RIGHT:
		rotObsY = rotObsY + 1.0;
		break;
	case GLUT_KEY_HOME:
		flaga = false;
		glutIconifyWindow();
		break;
	case GLUT_KEY_PAGE_UP:
		glutFullScreen();
		break;
	case GLUT_KEY_PAGE_DOWN:
		glutReshapeWindow(szer, wys);
		glutPositionWindow(100, 100);
		break;
	}
}

void setVSync(bool sync)
{	typedef BOOL(APIENTRY *PFNWGLSWAPINTERVALPROC)(int);
	PFNWGLSWAPINTERVALPROC wglSwapIntervalEXT = 0;
	const char *extensions = (char*)glGetString(GL_EXTENSIONS);
		if (strstr(extensions, "WGL_EXT_swap_control") == 0) return;
		else{
			wglSwapIntervalEXT = (PFNWGLSWAPINTERVALPROC)wglGetProcAddress("wglSwapIntervalEXT");
			if (wglSwapIntervalEXT)
			wglSwapIntervalEXT(sync);
	}
}

int  main(int argc, char **argv)
{	
	std::cout << "\t\t\t\tPONG 3D" <<std::endl<< "\t\t\t   Szymon Muszynski" << std::endl << "\t   Praca zaliczeniowa na przedmiot Programowanie Obiektowe";
	
	cout << "\n\nSterowanie:\n\n - W, S - sterowanie lewa rakietka\n - NUMPAD 8, NUMPAD 5 - sterowanie prawa rakietka\n - P - tryb pauzy";
	cout << "\n\n - +,- -zmiana przyblizenia widoku\n - Strzalki - zmiana polozenia kamery\n - HOME - minimalizacja okna\n - PGUP, PGDN - pelny ekran/okno \n - ESC - natychmiastowe wyjscie z gry";
	cout << endl<< endl<< "Do ilu punktow chcesz zagrac: ";
	scanf_s("%d", &ile);
	nowy.doIluPunktow = ile;
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(szer, wys);
	okno=glutCreateWindow("Pong 3D");
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1000.0);
	glClearColor(0.4, 0.4, 0.4, 0.0);
	
	glutDisplayFunc(WyswietlObraz);
	// Ustawienie funkcji czekającej - aby nie notować wydajności rzędu 400 FPS, powodującej zupełny brak grywalności
	glutTimerFunc(1000 / 16, makedelay, 1);
	setVSync(true);
	glutReshapeFunc(UstawParametryWidoku);

	glutKeyboardFunc(ObslugaKlawiatury);
	glutSpecialFunc(ObslugaKlawiszySpecjalnych);
	
	glutMainLoop();
	return 0;
}