// opengl_zbufor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


/*
(c) Janusz Ganczarski
http://www.januszg.hg.pl
JanuszG@enter.net.pl
*/

#include <GL/glut.h>
#include <stdlib.h>
#include "colors.h"

#include "VectorMath.cpp"

// rozmiary bryły obcinania

const GLdouble left = -2.0;
const GLdouble right = 2.0;
const GLdouble bottom = -2.0;
const GLdouble top = 2.0;
const GLdouble near_ = 3.0;
const GLdouble far_ = 7.0;

// stałe do obsługi menu podręcznego

enum
{
	CUTTING_PLANE, // płaszczyzna przekroju
	POLYGON_OFFSET, // przesunięcie wartości głębi
	EXIT // wyjście
};

// kąt obrotu kuli

GLfloat angle = 0.0;

// kąty obrotu sześcianu

GLfloat rotatex = 0.0;
GLfloat rotatey = 0.0;

// wskaźnik rysowania płaszczyzna przekroju

bool cutting_plane = true;

// wskaźnik przesunięcia wartości głębi

bool polygon_offset = true;

// wskaźnik naciśnięcia lewego przycisku myszki

int button_state = GLUT_UP;

// położenie kursora myszki

int button_x, button_y;

GLint n = 15;
#define GL_PI 3.1415f

GLfloat x, y , angle2;
int iPivot = 1;


void Display()
{
	// kolor tła - zawartość bufora koloru
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// czyszczenie bufora koloru i bufora głębokości
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// wybór macierzy modelowania
	glMatrixMode(GL_MODELVIEW);

	// macierz modelowania = macierz jednostkowa
	glLoadIdentity();

	// przesunięcie układu współrzędnych sześcianu do środka bryły odcinania
	glTranslatef(0, 0, -(near_ + far_) / 2);

	// obroty sześcianu
	glRotatef(rotatex, 1.0, 0, 0);
	glRotatef(rotatey, 0, 1.0, 0);

	// niewielkie powiększenie sześcianu
	glScalef(1.15, 1.15, 1.15);

	// włączenie testu bufora głębokości
	glEnable(GL_DEPTH_TEST);

	// najpierw rysujemy kulę obracającą się wewnątrz sześcianu;
	// z uwagi na celowy brak efektów oświetlenia, obrót kuli
	// podkreśla druga kula w wersji "szkieletowej"
	glPushMatrix();
	angle += 0.2;
	glRotatef(angle, 1.0, 1.0, 0.0);
	glColor3fv(Yellow);
	if (polygon_offset)
		glEnable(GL_POLYGON_OFFSET_FILL);

	glPolygonOffset(1.0, 1.0);
	glutSolidSphere(0.5, 10, 10);
	glColor3fv(Black);
	glutWireSphere(0.5, 10, 10);
	if (polygon_offset)
		glDisable(GL_POLYGON_OFFSET_FILL);

	glPopMatrix();
	

	glEnable(GL_CULL_FACE);

	//glBegin(GL_TRIANGLE_FAN);
	//// Czubek stoka jest wspólnym wierzcho³kiem wszystkich trójk¹tów z wachlarza
	//// wysuniêtym do góry w osi z. W ten sposób zamiast ko³a powstanie sto¿ek.
	//glVertex3f(0.0f, 0.0f, 75.0f);
	//// Wykonujemy obrót w oko³o i oznaczamy w równych odstêpach wierzcho³ki
	//// tworz¹ce wachlarz trójk¹tów.
	//for (angle2 = 0.0f; angle2 <= (2.0f*GL_PI); angle2 += ((GL_PI* 2.0f) / 15.0f))
	//{
	//	// Wyliczenie wspó³rzêdnych x i y kolejnego wierzcho³ka
	//	x = 50.0f*sin(angle2);
	//	y = 50.0f*cos(angle2);
	//	// Wybieranie koloru - zielony lub czerwony
	//	if ((iPivot % 3) == 0)
	//		glColor3f(0.0f, 1.0f, 0.0f);
	//	else if ((iPivot % 2) == 0)
	//		glColor3f(0.2f, 0.1f, 0.7f);
	//	else
	//		glColor3f(1.0f, 0.0f, 0.0f);
	//	// Inkrementacja zmiennej okreœlaj¹cej rodzaj koloru
	//	iPivot++;
	//	// Definiowanie kolejnego wierzcho³ka w wachlarzu trójk¹tów
	//	glVertex2f(x, y);
	//}
	//// Zakoczenie rysowania trójk¹tów sto¿ka
	//glEnd();

	glBegin(GL_TRIANGLE_FAN);
	// œrodek wachlarza znajduje siê na pocz¹tku uk³adu wspó³rzêdnych
	glVertex2f(0.0f, 0.0f);
	for (angle2 = 0.0f; angle2 <= (2.0f*GL_PI); angle2 += ((GL_PI* 2.0f) / 15.0f))
	{
		// Wyliczenie wspó³rzêdnych x i y kolejnego wierzcho³ka
		x = 50.0f*sin(angle2);
		y = 50.0f*cos(angle2);
		// Wybieranie koloru - zielony lub czerwony
		if ((iPivot % 3) == 0)
			glColor3f(0.0f, 1.0f, 0.0f);
		else if ((iPivot % 2) == 0)
			glColor3f(0.2f, 0.1f, 0.7f);
		else
			glColor3f(1.0f, 0.0f, 0.0f);
		// Inkrementacja zmiennej okreœlaj¹cej rodzaj koloru
		iPivot++;
		// Definiowanie kolejnego wierzcho³ka w wachlarzu trójk¹tów
		glVertex2f(x, y);
	}
	// w drugiej kolejności rysujemy wnętrze sześcianu;
	// rysowane są tylko przednie strony wewnętrznych ścian
	// no i nie jest rysowana ściana przednia, w której będzie otwór
	
	glFlush();

	// Wys³anie poleceñ do wykonania
	glutSwapBuffers();
}

// zmiana wielkości okna

void Reshape(int width, int height)
{
	// obszar renderingu - całe okno
	glViewport(0, 0, width, height);

	// wybór macierzy rzutowania
	glMatrixMode(GL_PROJECTION);

	// macierz rzutowania = macierz jednostkowa
	glLoadIdentity();

	// parametry bryły obcinania
	glFrustum(left, right, bottom, top, near_, far_);

	// generowanie sceny 3D
	Display();
}

// obsługa klawiszy funkcyjnych i klawiszy kursora

void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
		// kursor w lewo
	case GLUT_KEY_LEFT:
		rotatey -= 1;
		break;

		// kursor w górę
	case GLUT_KEY_UP:
		rotatex -= 1;
		break;

		// kursor w prawo
	case GLUT_KEY_RIGHT:
		rotatey += 1;
		break;

		// kursor w dół
	case GLUT_KEY_DOWN:
		rotatex += 1;
		break;
	}

	// odrysowanie okna
	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

// obsługa przycisków myszki

void MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		// zapamiętanie stanu lewego przycisku myszki
		button_state = state;

		// zapamiętanie położenia kursora myszki
		if (state == GLUT_DOWN)
		{
			button_x = x;
			button_y = y;
		}
	}
}

// obsługa ruchu kursora myszki

void MouseMotion(int x, int y)
{
	if (button_state == GLUT_DOWN)
	{
		rotatey += 30 * (right - left) / glutGet(GLUT_WINDOW_WIDTH) *(x - button_x);
		button_x = x;
		rotatex -= 30 * (top - bottom) / glutGet(GLUT_WINDOW_HEIGHT) *(button_y - y);
		button_y = y;
		glutPostRedisplay();
	}
}

// obsługa menu podręcznego

void Menu(int value)
{
	switch (value)
	{
		// płaszczyzna przekroju
	case CUTTING_PLANE:
		cutting_plane = !cutting_plane;
		Display();
		break;

		// przesunięcie wartości głębi
	case POLYGON_OFFSET:
		polygon_offset = !polygon_offset;
		Display();
		break;

		// wyjście
	case EXIT:
		exit(0);
	}
}

int main(int argc, char * argv[])
{
	// inicjalizacja biblioteki GLUT
	glutInit(&argc, argv);

	// inicjalizacja bufora ramki
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// rozmiary głównego okna programu
	glutInitWindowSize(500, 500);

	// utworzenie głównego okna programu
	glutCreateWindow("Z-bufor");

	// dołączenie funkcji generującej scenę 3D
	glutDisplayFunc(Display);

	// dołączenie funkcji wywoływanej przy zmianie rozmiaru okna
	glutReshapeFunc(Reshape);

	// dołączenie funkcji obsługi klawiszy funkcyjnych i klawiszy kursora
	glutSpecialFunc(SpecialKeys);

	// obsługa przycisków myszki
	glutMouseFunc(MouseButton);

	// obsługa ruchu kursora myszki
	glutMotionFunc(MouseMotion);

	// utworzenie menu podręcznego
	glutCreateMenu(Menu);

	// menu główne
	glutCreateMenu(Menu);
#ifdef WIN32

	glutAddMenuEntry("Płaszczyzna przekroju: rysowana/nierysowana", CUTTING_PLANE);
	glutAddMenuEntry("Przesunięcie wartości głębi: włącz/wyłącz", POLYGON_OFFSET);
	glutAddMenuEntry("Wyjście", EXIT);
#else

	glutAddMenuEntry("Plaszczyzna przekroju: rysowana/nierysowana", CUTTING_PLANE);
	glutAddMenuEntry("Przesuniecie wartosci glebi: wlacz/wylacz", POLYGON_OFFSET);
	glutAddMenuEntry("Wyjscie", EXIT);
#endif

	// określenie przycisku myszki obsługującej menu podręczne
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// dołączenie funkcji wywoływanej podczas "bezczynności" systemu
	glutIdleFunc(Display);

	// wprowadzenie programu do obsługi pętli komunikatów
	glutMainLoop();
	return 0;
}
