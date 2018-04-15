
#include "stdafx.h"
#include <GL/glut.h>
#include <stdlib.h>
#include "materials.h"

// stałe do obsługi menu podręcznego

enum
{
	SOLID,
	WIRE,
	BRASS,                // mosiądz
	BRONZE,               // brąz
	POLISHED_BRONZE,      // polerowany brąz
	CHROME,               // chrom
	COPPER,               // miedź
	POLISHED_COPPER,      // polerowana miedź
	GOLD,                 // złoto
	POLISHED_GOLD,        // polerowane złoto
	PEWTER,               // grafit (cyna z ołowiem)
	SILVER,               // srebro
	POLISHED_SILVER,      // polerowane srebro
	EMERALD,              // szmaragd
	JADE,                 // jadeit
	OBSIDIAN,             // obsydian
	PEARL,                // perła
	RUBY,                 // rubin
	TURQUOISE,            // turkus
	BLACK_PLASTIC,        // czarny plastik
	BLACK_RUBBER,         // czarna guma
	FULL_WINDOW,       // aspekt obrazu - całe okno
	ASPECT_1_1,        // aspekt obrazu 1:1
	EXIT               // wyjście
};

// aspekt obrazu

int aspect = FULL_WINDOW;

// rozmiary bryły obcinania

const GLdouble left = -70.0;
const GLdouble right = 70.0;
const GLdouble bottom = -70.0;
const GLdouble top = 70.0;
const GLdouble near_ = 100.0;
const GLdouble far_ = 150.0;

// współczynnik skalowania

GLfloat scale = 1.0;

// kąty obrotu

GLfloat rotatex = 0.0;
GLfloat rotatey = 0.0;

// przesunięcie

GLfloat translatex = 0.0;
GLfloat translatey = 0.0;

// wskaŸnik naciśnięcia lewego przycisku myszki

int button_state = GLUT_UP;

// poło¿enie kursora myszki

int button_x, button_y;

// funkcja rysująca blok 3x3


const GLfloat *ambient = BrassAmbient;
const GLfloat *diffuse = BrassDiffuse;
const GLfloat *specular = BrassSpecular;
GLfloat shininess = BrassShininess;


bool solid = false;

void obiekt()
{
	if(!solid) glutWireOctahedron();
	else glutSolidOctahedron();

}

void Cube3x3()
{
	obiekt();
	glTranslatef(1.5, 0.0, 0.0);
	obiekt();
	glTranslatef(0.0, -1.5, 0.0);
	obiekt();
	glTranslatef(-1.5, 0.0, 0.0);
	obiekt();
	glTranslatef(-1.5, 0.0, 0.0);
	obiekt();
	glTranslatef(0.0, 1.5, 0.0);
	obiekt();
	glTranslatef(0.0, 1.5, 0.0);
	obiekt();
	glTranslatef(1.5, 0.0, 0.0);
	obiekt();
	glTranslatef(1.5, 0.0, 0.0);
	obiekt();
}

// funkcja rysująca blok 2x2

void Cube2x2()
{
	obiekt();
	glTranslatef(1.5, 0.0, 0.0);
	obiekt();
	glTranslatef(0.0, -1.5, 0.0);
	obiekt();
	glTranslatef(-1.5, 0.0, 0.0);
	obiekt();
	
}

void Dode4x4()
{
	
	glPushMatrix();
	glTranslatef(0.75, -0.75, 0.0);
	Cube2x2();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.75, 2.25, 0.0);
	Cube2x2();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2.25, 2.25, 0.0);
	Cube2x2();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2.25, -0.75, 0.0);
	Cube2x2();
	glPopMatrix();

}
void Dode5x5()
{
	glPushMatrix();
	glTranslatef(1.5, 1.5, 0.0);
	Cube3x3();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.5, -1.5, 0.0);
	Cube2x2();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3.0, 3.0, 0.0);
	Cube2x2();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.5, -1.5, 0.0);
	Cube3x3();
	glPopMatrix();
}

void Dode6x6()
{
	glPushMatrix();
	glTranslatef(2.25, 2.25, 0.0);
	Cube3x3();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(2.25, -2.25, 0.0);
	Cube3x3();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2.25, -2.25, 0.0);
	Cube3x3();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2.25, 2.25, 0.0);
	Cube3x3();
	glPopMatrix();

}

void Dode7x7()
{
	glPushMatrix();
	glTranslatef(2.25, -2.25, 0.0);
	Dode4x4();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.25, 2.25, 0.0);
	Dode4x4();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.0, 3.0, 0.0);
	Cube3x3();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.0, -3.0, 0.0);
	Cube3x3();
	glPopMatrix();



}

void Dode8x8()
{
	glPushMatrix();
	glTranslatef(3.0, 3.0, 0.0);
	Dode4x4();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.0, -3.0, 0.0);
	Dode4x4();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.0, -3.0, 0.0);
	Dode4x4();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.0, 3.0, 0.0);
	Dode4x4();
	glPopMatrix();


}

void Dode9x9()
{
	glPushMatrix();
	glTranslatef(3.75, 3.75, 0.0);
	Dode4x4();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.75, -3.75, 0.0);
	Dode4x4();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.0, -3.0, 0.0);
	Dode5x5();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.0, 3.0, 0.0);
	Dode5x5();
	glPopMatrix();


}
void Dode10x10()
{
	glPushMatrix();
	glTranslatef(3.75, -3.75, 0.0);
	Dode5x5();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.75, 3.75, 0.0);
	Dode5x5();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3.75, -3.75, 0.0);
	Dode5x5();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.75, 3.75, 0.0);
	Dode5x5();
	glPopMatrix();
}

void Dode11x11()
{
	glPushMatrix();
	glTranslatef(3.75, 3.75, 0.0);
	Dode6x6();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.75, -3.75, 0.0);
	Dode6x6();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.5, -4.5, 0.0);
	Dode5x5();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.5, 4.5, 0.0);
	Dode5x5();
	glPopMatrix();
}

void Dode12x12()
{
	glPushMatrix();
	glTranslatef(4.5, 4.5, 0.0);
	Dode6x6();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.5, -4.5, 0.0);
	Dode6x6();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.5, -4.5, 0.0);
	Dode6x6();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.5, 4.5, 0.0);
	Dode6x6();
	glPopMatrix();
}

void Dode13x13()
{
	glPushMatrix();
	glTranslatef(5.25, 5.25, 0.0);
	Dode6x6();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.5, 4.5, 0.0);
	Dode7x7();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.5, -4.5, 0.0);
	Dode7x7();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5.25, -5.25, 0.0);
	Dode6x6();
	glPopMatrix();
}
void Dode14x14()
{
	glPushMatrix();
	glTranslatef(-5.25, 5.25, 0.0);
	Dode7x7();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5.25, -5.25, 0.0);
	Dode7x7();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5.25, -5.25, 0.0);
	Dode7x7();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5.25, 5.25, 0.0);
	Dode7x7();
	glPopMatrix();
}

void Dode15x15()
{
	glPushMatrix();
	glTranslatef(-5.25, 5.25, 0.0);
	Dode8x8();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5.25, -5.25, 0.0);
	Dode8x8();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6.0, -6.0, 0.0);
	Dode7x7();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6.0, 6.0, 0.0);
	Dode7x7();
	glPopMatrix();
}
void Dode16x16()
{
	glPushMatrix();
	glTranslatef(-6.0, 6.0, 0.0);
	Dode8x8();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6.0, -6.0, 0.0);
	Dode8x8();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-6.0, -6.0, 0.0);
	Dode8x8();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6.0, 6.0, 0.0);
	Dode8x8();
	glPopMatrix();
}
// funkcja rysująca piramidę

void Pyramid()
{
	//16x16
	glPushMatrix();
	glTranslatef(1.5, -1.5, 0);
	Dode16x16();
	glPopMatrix();
	//15x15
	glPushMatrix();
	glTranslatef(1.5, -1.5, 2);
	Dode15x15();
	glPopMatrix();
	//14x14
	glPushMatrix();
	glTranslatef(1.5, -1.5, 4);
	Dode14x14();
	glPopMatrix();
	//13x13
	glPushMatrix();
	glTranslatef(1.5, -1.5, 6);
	Dode13x13();
	glPopMatrix();
	//12x12
	glPushMatrix();
	glTranslatef(1.5, -1.5, 8);
	Dode12x12();
	glPopMatrix();
	//11x11
	glPushMatrix();
	glTranslatef(1.5, -1.5, 10);
	Dode11x11();
	glPopMatrix();
	//10x10
	glPushMatrix();
	glTranslatef(1.5, -1.5, 12);
	Dode10x10();
	glPopMatrix();

	//9x9
	glPushMatrix();
	glTranslatef(1.5, -1.5, 14);
	Dode9x9();
	glPopMatrix();

	//8x8
	glPushMatrix();
	glTranslatef(1.5, -1.5, 16);
	Dode8x8();
	glPopMatrix();

	//podstawa 7x7
	glPushMatrix();
	glTranslatef(1.5, -1.5, 18);
	Dode7x7();
	glPopMatrix();


	// podstawa 6x6
	glPushMatrix();
	glTranslatef(1.5, -1.5, 20);
	Dode6x6();
	glPopMatrix();

	// drugi poziom 5x5
	glPushMatrix();
	glTranslatef(1.5, -1.5, 22);
	Dode5x5();
	glPopMatrix();

	// trzeci poziom 4x4
	glPushMatrix();
	glTranslatef(1.5, -1.5, 24);
	Dode4x4();
	glPopMatrix();

	// czwarty poziom 3x3
	glPushMatrix();
	glTranslatef(1.5, -1.5, 26);
	Cube3x3();
	glPopMatrix();

	// piąty poziom 2x2
	glPushMatrix();
	glTranslatef(0.75, -0.75, 28);
	//glTranslatef(-1.0, 1.0, 0.0);
	Cube2x2();
	glPopMatrix();

	// szósty poziom 1x1
	glPushMatrix();
	glTranslatef(1.5, -1.5, 30);
	obiekt();
	glPopMatrix();
}

// funkcja generująca scenę 3D

void Display()
{
	// kolor tła - zawartość bufora koloru
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// czyszczenie bufora koloru
	glClear(GL_COLOR_BUFFER_BIT);

	// wybór macierzy modelowania
	glMatrixMode(GL_MODELVIEW);

	// macierz modelowania = macierz jednostkowa
	glLoadIdentity();

	// włączenie oświetlenia
	glEnable(GL_LIGHTING);

	// włączenie światła GL_LIGHT0 z parametrami domyślnymi
	glEnable(GL_LIGHT0);

	// przesunięcie układu współrzędnych obiektu do środka bryły odcinania
	glTranslatef(0, 0, -(near_ + far_) / 2);

	// przesunięcie obiektu - ruch myszką
	glTranslatef(translatex, translatey, 0.0);

	// skalowanie obiektu - klawisze "+" i "-"
	glScalef(scale, scale, scale);

	// obroty obiektu - klawisze kursora
	glRotatef(rotatex, 1.0, 0, 0);
	glRotatef(rotatey, 0, 1.0, 0);

	// kolor krawędzi obiektu
	glColor3f(0.0, 0.0, 0.0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	// rysowanie piramidy
	Pyramid();

	// skierowanie poleceń do wykonania
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
		// wysokość okna większa od wysokości okna
		if (width < height && width > 0)
			glFrustum(left, right, bottom*height / width, top*height / width, near_, far_);
		else

			// szerokość okna większa lub równa wysokości okna
			if (width >= height && height > 0)
				glFrustum(left*width / height, right*width / height, bottom, top, near_, far_);
	}
	else
		glFrustum(left, right, bottom, top, near_, far_);

	// generowanie sceny 3D
	Display();
}

// obsługa klawiatury

void Keyboard(unsigned char key, int x, int y)
{
	// klawisz +
	if (key == '+')
		scale += 0.1;
	else

		// klawisz -
		if (key == '-' && scale > 0.1)
			scale -= 0.1;

	// odrysowanie okna
	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
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

		// zapamiętanie poło¿enia kursora myszki
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
		translatex += 1.1 *(right - left) / glutGet(GLUT_WINDOW_WIDTH) * (x - button_x);
		button_x = x;
		translatey += 1.1 *(top - bottom) / glutGet(GLUT_WINDOW_HEIGHT) * (button_y - y);
		button_y = y;
		glutPostRedisplay();
	}
}

// obsługa menu podręcznego

void Menu(int value)
{
	switch (value)
	{
		// materiał - mosiądz
	case BRASS:
		ambient = BrassAmbient;
		diffuse = BrassDiffuse;
		specular = BrassSpecular;
		shininess = BrassShininess;
		Display();
		break;

		// materiał - brąz
	case BRONZE:
		ambient = BronzeAmbient;
		diffuse = BronzeDiffuse;
		specular = BronzeSpecular;
		shininess = BronzeShininess;
		Display();
		break;

		// materiał - polerowany brąz
	case POLISHED_BRONZE:
		ambient = PolishedBronzeAmbient;
		diffuse = PolishedBronzeDiffuse;
		specular = PolishedBronzeSpecular;
		shininess = PolishedBronzeShininess;
		Display();
		break;

		// materiał - chrom
	case CHROME:
		ambient = ChromeAmbient;
		diffuse = ChromeDiffuse;
		specular = ChromeSpecular;
		shininess = ChromeShininess;
		Display();
		break;

		// materiał - miedź
	case COPPER:
		ambient = CopperAmbient;
		diffuse = CopperDiffuse;
		specular = CopperSpecular;
		shininess = CopperShininess;
		Display();
		break;

		// materiał - polerowana miedź
	case POLISHED_COPPER:
		ambient = PolishedCopperAmbient;
		diffuse = PolishedCopperDiffuse;
		specular = PolishedCopperSpecular;
		shininess = PolishedCopperShininess;
		Display();
		break;

		// materiał - złoto
	case GOLD:
		ambient = GoldAmbient;
		diffuse = GoldDiffuse;
		specular = GoldSpecular;
		shininess = GoldShininess;
		Display();
		break;

		// materiał - polerowane złoto
	case POLISHED_GOLD:
		ambient = PolishedGoldAmbient;
		diffuse = PolishedGoldDiffuse;
		specular = PolishedGoldSpecular;
		shininess = PolishedGoldShininess;
		Display();
		break;

		// materiał - grafit (cyna z ołowiem)
	case PEWTER:
		ambient = PewterAmbient;
		diffuse = PewterDiffuse;
		specular = PewterSpecular;
		shininess = PewterShininess;
		Display();
		break;

		// materiał - srebro
	case SILVER:
		ambient = SilverAmbient;
		diffuse = SilverDiffuse;
		specular = SilverSpecular;
		shininess = SilverShininess;
		Display();
		break;

		// materiał - polerowane srebro
	case POLISHED_SILVER:
		ambient = PolishedSilverAmbient;
		diffuse = PolishedSilverDiffuse;
		specular = PolishedSilverSpecular;
		shininess = PolishedSilverShininess;
		Display();
		break;

		// materiał - szmaragd
	case EMERALD:
		ambient = EmeraldAmbient;
		diffuse = EmeraldDiffuse;
		specular = EmeraldSpecular;
		shininess = EmeraldShininess;
		Display();
		break;

		// materiał - jadeit
	case JADE:
		ambient = JadeAmbient;
		diffuse = JadeDiffuse;
		specular = JadeSpecular;
		shininess = JadeShininess;
		Display();
		break;

		// materiał - obsydian
	case OBSIDIAN:
		ambient = ObsidianAmbient;
		diffuse = ObsidianDiffuse;
		specular = ObsidianSpecular;
		shininess = ObsidianShininess;
		Display();
		break;

		// materiał - perła
	case PEARL:
		ambient = PearlAmbient;
		diffuse = PearlDiffuse;
		specular = PearlSpecular;
		shininess = PearlShininess;
		Display();
		break;

		// metariał - rubin
	case RUBY:
		ambient = RubyAmbient;
		diffuse = RubyDiffuse;
		specular = RubySpecular;
		shininess = RubyShininess;
		Display();
		break;

		// materiał - turkus
	case TURQUOISE:
		ambient = TurquoiseAmbient;
		diffuse = TurquoiseDiffuse;
		specular = TurquoiseSpecular;
		shininess = TurquoiseShininess;
		Display();
		break;

		// materiał - czarny plastik
	case BLACK_PLASTIC:
		ambient = BlackPlasticAmbient;
		diffuse = BlackPlasticDiffuse;
		specular = BlackPlasticSpecular;
		shininess = BlackPlasticShininess;
		Display();
		break;

		// materiał - czarna guma
	case BLACK_RUBBER:
		ambient = BlackRubberAmbient;
		diffuse = BlackRubberDiffuse;
		specular = BlackRubberSpecular;
		shininess = BlackRubberShininess;
		Display();
		break;

	case SOLID:
		solid = true;
		Display();
		break;

	case WIRE:
		solid = false;
		Display();
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

int main(int argc, char *argv[])
{
	// inicjalizacja biblioteki GLUT
	glutInit(&argc, argv);

	// inicjalizacja bufora ramki
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// rozmiary głównego okna programu
	glutInitWindowSize(600, 600);

	// utworzenie głównego okna programu
	glutCreateWindow("Stos modelowania");

	// dołączenie funkcji generującej scenę 3D
	glutDisplayFunc(Display);

	// dołączenie funkcji wywoływanej przy zmianie rozmiaru okna
	glutReshapeFunc(Reshape);

	// dołączenie funkcji obsługi klawiatury
	glutKeyboardFunc(Keyboard);

	// dołączenie funkcji obsługi klawiszy funkcyjnych i klawiszy kursora
	glutSpecialFunc(SpecialKeys);

	// obsługa przycisków myszki
	glutMouseFunc(MouseButton);

	// obsługa ruchu kursora myszki
	glutMotionFunc(MouseMotion);

	int MenuMaterial = glutCreateMenu(Menu);


#ifdef WIN32

	glutAddMenuEntry("Mosiądz", BRASS);
	glutAddMenuEntry("Brąz", BRONZE);
	glutAddMenuEntry("Polerowany brąz", POLISHED_BRONZE);
	glutAddMenuEntry("Chrom", CHROME);
	glutAddMenuEntry("Miedź", COPPER);
	glutAddMenuEntry("Polerowana miedź", POLISHED_COPPER);
	glutAddMenuEntry("Złoto", GOLD);
	glutAddMenuEntry("Polerowane złoto", POLISHED_GOLD);
	glutAddMenuEntry("Grafit (cyna z ołowiem)", PEWTER);
	glutAddMenuEntry("Srebro", SILVER);
	glutAddMenuEntry("Polerowane srebro", POLISHED_SILVER);
	glutAddMenuEntry("Szmaragd", EMERALD);
	glutAddMenuEntry("Jadeit", JADE);
	glutAddMenuEntry("Obsydian", OBSIDIAN);
	glutAddMenuEntry("Perła", PEARL);
	glutAddMenuEntry("Rubin", RUBY);
	glutAddMenuEntry("Turkus", TURQUOISE);
	glutAddMenuEntry("Czarny plastik", BLACK_PLASTIC);
	glutAddMenuEntry("Czarna guma", BLACK_RUBBER);
#else

	glutAddMenuEntry("Mosiadz", BRASS);
	glutAddMenuEntry("Braz", BRONZE);
	glutAddMenuEntry("Polerowany braz", POLISHED_BRONZE);
	glutAddMenuEntry("Chrom", CHROME);
	glutAddMenuEntry("Miedz", COPPER);
	glutAddMenuEntry("Polerowana miedz", POLISHED_COPPER);
	glutAddMenuEntry("Zloto", GOLD);
	glutAddMenuEntry("Polerowane zloto", POLISHED_GOLD);
	glutAddMenuEntry("Grafit (cyna z ołowiem)", PEWTER);
	glutAddMenuEntry("Srebro", SILVER);
	glutAddMenuEntry("Polerowane srebro", POLISHED_SILVER);
	glutAddMenuEntry("Szmaragd", EMERALD);
	glutAddMenuEntry("Jadeit", JADE);
	glutAddMenuEntry("Obsydian", OBSIDIAN);
	glutAddMenuEntry("Perla", PEARL);
	glutAddMenuEntry("Rubin", RUBY);
	glutAddMenuEntry("Turkus", TURQUOISE);
	glutAddMenuEntry("Czarny plastik", BLACK_PLASTIC);
	glutAddMenuEntry("Czarna guma", BLACK_RUBBER);
#endif

	int MenuStan = glutCreateMenu(Menu);
	glutAddMenuEntry("Solid", SOLID);
	glutAddMenuEntry("Wire", WIRE);


	// utworzenie podmenu - aspekt obrazu
	int MenuAspect = glutCreateMenu(Menu);

#ifdef WIN32

	glutAddMenuEntry("Aspekt obrazu - całe okno", FULL_WINDOW);
#else

	glutAddMenuEntry("Aspekt obrazu - cale okno", FULL_WINDOW);
#endif
	
	glutAddMenuEntry("Aspekt obrazu 1:1", ASPECT_1_1);

	// menu główne
	glutCreateMenu(Menu);
	glutAddSubMenu("Aspekt obrazu", MenuAspect);
	glutAddSubMenu("Wypełnienie figury", MenuStan);
#ifdef WIN32

	glutAddSubMenu("Materiał", MenuMaterial);
#else

	glutAddSubMenu("Material", MenuMaterial);
#endif
#ifdef WIN32

	glutAddMenuEntry("Wyjście", EXIT);
#else

	glutAddMenuEntry("Wyjscie", EXIT);
#endif

	// określenie przycisku myszki obsługującego menu podręczne
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// wprowadzenie programu do obsługi pętli komunikatów
	glutMainLoop();
	return 0;
}
