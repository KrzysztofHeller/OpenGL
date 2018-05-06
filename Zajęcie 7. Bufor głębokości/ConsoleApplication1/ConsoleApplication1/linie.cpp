// opengl_linie_z_halo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


/*
(c) Janusz Ganczarski
http://www.januszg.hg.pl
JanuszG@enter.net.pl
*/

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include "colors.h"

// sta³e do obs³ugi menu podrêcznego

enum
{
	FILL, // obiekt wype³niony
	WIRE, // krawêdzie obiektu
	HALO, // efekt halo
	EXIT // wyjœcie
};

// rozmiary bry³y obcinania

const GLint left = -5;
const GLint right = 5;
const GLint bottom = -5;
const GLint top = 5;
const GLint near_ = -5;
const GLint far_ = 5;

// k¹ty obrotu sceny

GLfloat rotatex = 0.0;
GLfloat rotatey = 0.0;

// wskaŸnik naciœniêcia lewego przycisku myszki

int button_state = GLUT_UP;

// po³o¿enie kursora myszki

int button_x, button_y;

// tryb rysowania

int render_mode = WIRE;

// funkcja generuj¹ca scenê 3D

void DisplayScene()
{
	// kolor t³a - zawartoœæ bufora koloru
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// czyszczenie bufora koloru i bufora g³êbokoœci
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// wybór macierzy modelowania
	glMatrixMode(GL_MODELVIEW);

	// macierz modelowania = macierz jednostkowa
	glLoadIdentity();

	// obroty ca³ej sceny
	glRotatef(rotatex, 1.0, 0.0, 0.0);
	glRotatef(rotatey, 0.0, 1.0, 0.0);

	// w³¹czenie bufora g³êbokoœci
	glEnable(GL_DEPTH_TEST);

	// kolor obiektu
	glColor4fv(Green);

	// narysowanie wybranych elementów sceny
	switch (render_mode)
	{
		// obiekt wype³niony
	case FILL:
		glutSolidSphere(3.0, 15, 15);
		break;

		// rysowanie tylko krawêdzi obiektu
	case WIRE:

		// wy³¹czenie bufora g³êbokoœci
		glDisable(GL_DEPTH_TEST);

		// tryb rysowania wielok¹tów
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		// szerokoœæ linii - linia normalna
		glLineWidth(3.0);

		// narysowanie obiektu
		glutSolidSphere(3.0, 15, 15);

		// tryb rysowania wielok¹tów
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// w³¹czenie testu bufora g³êbokoœci
		glEnable(GL_DEPTH_TEST);
		break;

		// efekt halo
	case HALO:
		// tryb rysowania wielok¹tów
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		// wy³¹czenie zapisu do bufora kolorów
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

		// szerokoœæ linii - linia pogrubiona
		glLineWidth(9.0);

		// narysoanie obiektu
		glutSolidSphere(3.0, 15, 15);

		// w³¹czenie zapisu do bufora g³êbokoœci
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

		// szerokoœæ linii - linia normalna
		glLineWidth(3.0);

		// rodzaj testu bufora g³êbokoœci
		glDepthFunc(GL_LEQUAL);

		// narysowanie obiektu
		glutSolidSphere(3.0, 15, 15);

		// rodzaj testu bufora g³êbokoœci
		glDepthFunc(GL_LESS);

		// tryb rysowania wielok¹tów
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	}

	// skierowanie poleceñ do wykonania
	glFlush();

	// zamiana buforów koloru
	glutSwapBuffers();
}

// zmiana wielkoœci okna

void Reshape(int width, int height)
{
	// obszar renderingu - ca³e okno
	glViewport(0, 0, width, height);

	// wybór macierzy rzutowania
	glMatrixMode(GL_PROJECTION);

	// macierz rzutowania = macierz jednostkowa
	glLoadIdentity();

	// parametry bry³y obcinania
	glOrtho(left, right, bottom, top, near_, far_);

	// generowanie sceny 3D
	DisplayScene();
}

// obs³uga przycisków myszki

void MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		// zapamiêtanie stanu lewego przycisku myszki
		button_state = state;

		// zapamiêtanie po³o¿enia kursora myszki
		if (state == GLUT_DOWN)
		{
			button_x = x;
			button_y = y;
		}
	}
}

// obs³uga ruchu kursora myszki

void MouseMotion(int x, int y)
{
	if (button_state == GLUT_DOWN)
	{
		rotatey += 50 * (right - left) / (float)glutGet(GLUT_WINDOW_WIDTH) *(x - button_x);
		button_x = x;
		rotatex -= 50 * (top - bottom) / (float)glutGet(GLUT_WINDOW_HEIGHT) *(button_y - y);
		button_y = y;
		glutPostRedisplay();
	}
}

// obs³uga menu podrêcznego

void Menu(int value)
{
	switch (value)
	{
		// wybrany tryb rysowania
	case FILL:
	case WIRE:
	case HALO:
		render_mode = value;
		DisplayScene();
		break;

		// wyjœcie
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

	// rozmiary g³ównego okna programu
	glutInitWindowSize(500, 500);

	// utworzenie g³ównego okna programu
	glutCreateWindow("Linie z halo");

	// do³¹czenie funkcji generuj¹cej scenê 3D
	glutDisplayFunc(DisplayScene);

	// do³¹czenie funkcji wywo³ywanej przy zmianie rozmiaru okna
	glutReshapeFunc(Reshape);

	// obs³uga przycisków myszki
	glutMouseFunc(MouseButton);

	// obs³uga ruchu kursora myszki
	glutMotionFunc(MouseMotion);

	// utworzenie podmenu - Tryb rysowania
	int MenuRenderMode = glutCreateMenu(Menu);
#ifdef WIN32

	glutAddMenuEntry("Obiekt wype³niony", FILL);
	glutAddMenuEntry("Krawêdzie obiektu", WIRE);
	glutAddMenuEntry("Efekt halo", HALO);
#else

	glutAddMenuEntry("Obiekt wypelniony", FILL);
	glutAddMenuEntry("Krawedzie obiektu", WIRE);
	glutAddMenuEntry("Efekt halo", HALO);
#endif

	// menu g³ówne
	glutCreateMenu(Menu);
	glutAddSubMenu("Tryb rysowania", MenuRenderMode);

#ifdef WIN32

	glutAddMenuEntry("Wyjœcie", EXIT);
#else

	glutAddMenuEntry("Wyjscie", EXIT);
#endif

	// okreœlenie przycisku myszki obs³uguj¹cego menu podrêczne
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// wprowadzenie programu do obs³ugi pêtli komunikatów
	glutMainLoop();
	return 0;
}
