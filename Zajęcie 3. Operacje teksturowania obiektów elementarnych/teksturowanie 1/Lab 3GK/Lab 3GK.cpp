
#include "stdafx.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glext.h>

// stałe do obsługi menu podręcznego

enum
{
	MAG_FILTER,     // filtr powiększający
	MIN_FILTER,     // filtr pomniejszający
	FULL_WINDOW,    // aspekt obrazu - całe okno
	ASPECT_1_1,     // aspekt obrazu 1:1
	EXIT            // wyjście
};

// aspekt obrazu

int aspect = FULL_WINDOW;

// usunięcie definicji makr near i far

#ifdef near
#undef near
#endif
#ifdef far
#undef far
#endif

// rozmiary bryły obcinania

const GLdouble left = -2.0;
const GLdouble right = 2.0;
const GLdouble bottom = -2.0;
const GLdouble top = 2.0;
const GLdouble near = 3.0;
const GLdouble far = 7.0;

// współczynnik skalowania

GLfloat scale = 1.05;

// identyfikatory list wyświetlania

GLint RECT_LIST;
GLint TEXTURE_256_LIST, TEXTURE_128_LIST, TEXTURE_64_LIST;

// filtr powiększający

GLint mag_filter = GL_NEAREST;

// filtr pomniejszający

GLint min_filter = GL_NEAREST;

// funkcja generująca scenę 3D

void DisplayScene()
{
	// kolor tła - zawartość bufora koloru
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// czyszczenie bufora koloru
	glClear(GL_COLOR_BUFFER_BIT);

	// wybór macierzy modelowania
	glMatrixMode(GL_MODELVIEW);

	// macierz modelowania = macierz jednostkowa
	glLoadIdentity();

	// przesunięcie układu współrzędnych obiektów do środka bryły odcinania
	glTranslatef(0, 0, -(near + far) / 2);

	// skalowanie obiektu - klawisze "+" i "-"
	glScalef(scale, 1.0, 1.0);

	// włączenie teksturowania jednowymiarowego
	glEnable(GL_TEXTURE_1D);

	// tryb upakowania bajtów danych tekstury
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// filtr powiększający
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, mag_filter);

	// filtr pomniejszający
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, min_filter);

	// usunuięcie błędów przy renderingu brzegu tekstury
	if (mag_filter == GL_LINEAR)
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

	// wyświetlenie tekstur
	glCallList(TEXTURE_256_LIST);
	glCallList(TEXTURE_128_LIST);
	glCallList(TEXTURE_64_LIST);

	// skierowanie poleceñ do wykonania
	glFlush();

	// zamiana buforów koloru
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
	if (aspect == ASPECT_1_1)
	{
		// wysokośæ okna większa od wysokości okna
		if (width < height && width > 0)
			glFrustum(left, right, bottom*height / width, top*height / width, near, far);
		else

			// szerokośæ okna większa lub równa wysokości okna
			if (width >= height && height > 0)
				glFrustum(left*width / height, right*width / height, bottom, top, near, far);
	}
	else
		glFrustum(left, right, bottom, top, near, far);

	// generowanie sceny 3D
	DisplayScene();
}

// obsługa klawiatury

void Keyboard(unsigned char key, int x, int y)
{
	// klawisz +
	if (key == '+')
		scale += 0.05;
	else

		// klawisz -
		if (key == '-' && scale > 0.05)
			scale -= 0.05;

	// narysowanie sceny
	DisplayScene();
}

// obsługa menu podręcznego

void Menu(int value)
{
	switch (value)
	{
		// filtr powiększający: GL_NEAREST/GL_LINEAR
	case MAG_FILTER:
		if (mag_filter == GL_NEAREST)
			mag_filter = GL_LINEAR;
		else
			mag_filter = GL_NEAREST;
		DisplayScene();
		break;

		// filtr pomniejszający: GL_NEAREST/GL_LINEAR
	case MIN_FILTER:
		if (min_filter == GL_NEAREST)
			min_filter = GL_LINEAR;
		else
			min_filter = GL_NEAREST;
		DisplayScene();
		break;

		// obszar renderingu - całe okno
	case FULL_WINDOW:
		aspect = FULL_WINDOW;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;

		// obszar renderingu - aspekt 1:1
	case ASPECT_1_1:
		aspect = ASPECT_1_1;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;

		// wyjście
	case EXIT:
		exit(0);
	}
}

// utworzenie list wyświetlania

void GenerateDisplayLists()
{
	// generowanie identyfikatora listy wyświetlania
	RECT_LIST = glGenLists(1);

	// lista wyświetlania - prostokąt
	glNewList(RECT_LIST, GL_COMPILE);

	// nało¿enie tekstury na prostokąt
	glBegin(GL_QUADS);
	glTexCoord1f(1.0);
	glVertex2f(1.5, 0.7);
	glTexCoord1f(0.0);
	glVertex2f(-1.5, 0.7);
	glTexCoord1f(0.0);
	glVertex2f(-1.5, -0.7);
	glTexCoord1f(1.0);
	glVertex2f(1.5, -0.7);
	glEnd();

	// koniec listy wyświetlania
	glEndList();

	// sprawdzenie czy implementacja biblioteki obsługuje tekstury o wymiarze 256
	GLint size;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &size);
	if (size < 256)
	{
		printf("Rozmiar tekstur mniejszy od 256");
		exit(0);
	}

	// dane tekstury
	GLubyte texture[256 * 3];

	// przygotowanie danych tekstury RGB
	for (int i = 0; i < 256; i++)
	{
		texture[3 * i + 0] = i;
		texture[3 * i + 1] = i;
		texture[3 * i + 2] = i;
	}

	// generowanie identyfikatora listy wyświetlania
	TEXTURE_256_LIST = glGenLists(1);

	// lista wyświetlania - tekstura o szerokości 256 tekseli
	glNewList(TEXTURE_256_LIST, GL_COMPILE);

	// definiowanie tekstury
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);

	// odło¿enie macierzy modelowania na stos
	glPushMatrix();

	// przesunięcie prostokąta do góry o dwie jednostki
	glTranslatef(0.0, 2.0, 0.0);

	// nało¿enie tekstury na prostokąt
	glCallList(RECT_LIST);

	// zdjęcie macierzy modelowania ze stosu
	glPopMatrix();

	// koniec listy wyświetlania
	glEndList();

	//  przygotowanie danych tekstury LUMINANCE
	for (int i = 0; i < 128; i++)
	{
		texture[i] = i * 2;
	}

	// generowanie identyfikatora listy wyświetlania
	TEXTURE_128_LIST = glGenLists(1);

	// lista wyświetlania - tekstura o szerokości 128 tekseli
	glNewList(TEXTURE_128_LIST, GL_COMPILE);

	// definiowanie tekstury
	glTexImage1D(GL_TEXTURE_1D, 0, GL_LUMINANCE, 128, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, texture);

	// nało¿enie tekstury na prostokąt
	glCallList(RECT_LIST);

	// koniec listy wyświetlania
	glEndList();

	// przygotowanie danych tekstury INTENSITY
	for (int i = 0; i < 64; i++)
	{
		texture[3 * i] = i * 4;
	}

	// generowanie identyfikatora listy wyświetlania
	TEXTURE_64_LIST = glGenLists(1);

	// lista wyświetlania - tekstura o szerokości 64 tekseli
	glNewList(TEXTURE_64_LIST, GL_COMPILE);

	// definiowanie tekstury
	glTexImage1D(GL_TEXTURE_1D, 0, GL_INTENSITY, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);

	// odło¿enie macierzy modelowania na stos
	glPushMatrix();

	// przesunięcie prostokąta do dołu o dwie jednostki
	glTranslatef(0.0, -2.0, 0.0);

	// nało¿enie tekstury na prostokąt
	glCallList(RECT_LIST);

	// zdjęcie macierzy modelowania ze stosu
	glPopMatrix();

	// koniec listy wyświetlania
	glEndList();
}

// sprawdzenie i przygotowanie obsługi wybranych rozszerzeñ

void ExtensionSetup()
{
	// pobranie numeru wersji biblioteki OpenGL
	const char *version = (char*)glGetString(GL_VERSION);

	// odczyt wersji OpenGL
	int major = 0, minor = 0;
	if (sscanf_s(version, "%d.%d", &major, &minor) != 2)
	{
#ifdef WIN32
		printf("Błędny format wersji OpenGL\n");
#else

		printf("Bledny format wersji OpenGL\n");
#endif

		exit(0);
	}

	// sprawdzenie czy jest co najmniej wersja 1.2 OpenGL lub
	// czy jest obsługiwane rozszerzenie GL_SGIS_texture_edge_clamp
	if (!(major > 1 || minor >= 2) &&
		!glutExtensionSupported("GL_SGIS_texture_edge_clamp"))
	{
		printf("Brak rozszerzenia GL_SGIS_texture_edge_clamp!\n");
		exit(0);
	}
}

int main(int argc, char *argv[])
{
	// inicjalizacja biblioteki GLUT
	glutInit(&argc, argv);

	// inicjalizacja bufora ramki
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// rozmiary głównego okna programu
	glutInitWindowSize(500, 500);

	// utworzenie głównego okna programu
	glutCreateWindow("Tekstura 1D");

	// dołączenie funkcji generującej scenę 3D
	glutDisplayFunc(DisplayScene);

	// dołączenie funkcji wywoływanej przy zmianie rozmiaru okna
	glutReshapeFunc(Reshape);

	// dołączenie funkcji obsługi klawiatury
	glutKeyboardFunc(Keyboard);

	// utworzenie podmenu - Aspekt obrazu
	int MenuAspect = glutCreateMenu(Menu);
#ifdef WIN32

	glutAddMenuEntry("Aspekt obrazu - całe okno", FULL_WINDOW);
#else

	glutAddMenuEntry("Aspekt obrazu - cale okno", FULL_WINDOW);
#endif

	glutAddMenuEntry("Aspekt obrazu 1:1", ASPECT_1_1);

	// menu główne
	glutCreateMenu(Menu);

#ifdef WIN32

	glutAddMenuEntry("Filtr powiększający: GL_NEAREST/GL_LINEAR", MAG_FILTER);
	glutAddMenuEntry("Filtr pomniejszający: GL_NEAREST/GL_LINEAR", MIN_FILTER);
	glutAddSubMenu("Aspekt obrazu", MenuAspect);
	glutAddMenuEntry("Wyjście", EXIT);
#else

	glutAddMenuEntry("Filtr powiekszajacy: GL_NEAREST/GL_LINEAR", MAG_FILTER);
	glutAddMenuEntry("Filtr pomniejszajacy: GL_NEAREST/GL_LINEAR", MIN_FILTER);
	glutAddSubMenu("Aspekt obrazu", MenuAspect);
	glutAddMenuEntry("Wyjscie", EXIT);
#endif

	// określenie przycisku myszki obsługującego menu podręczne
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// utworzenie list wyświetlania
	GenerateDisplayLists();

	// sprawdzenie i przygotowanie obsługi wybranych rozszerzeñ
	ExtensionSetup();

	// wprowadzenie programu do obsługi pętli komunikatów
	glutMainLoop();
	return 0;
}
