/******************************/
/* Dilan Taskin 18710		  */
/* Computer Graphics 2020/2021*/
/******************************/


#include <gl/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include "figura.h"
#include <math.h>

#define WINDOW_SIZE 500
#define INSERT 1
#define DELETE 2
const int font = (int)GLUT_BITMAP_9_BY_15;
int w, h;



// array e tamanho máximo para guardar as figuras (bounding boxes)
Figura* figs;
int tam = 20;
int figsCount = 0;

// Estado da aplicação
int tipoFiguraSelecionada = QUADRADO;
int aDesenhar = 0;
int figuraAtiva = -1;
int xUltimo = 0, yUltimo = 0;
int mode = INSERT;

// Palette 
Figura pal[3];
//For Selecting Shapes in The ToolBar tha array store all shapes
Figura selectingShapes[6];


float r = 0.0, g = 0.0, b = 0.0;
int changeB = 0;

int randomFig() {
	int i = rand() % 6;
	switch (i) {
	case 0: return TRIANGULO;
	case 1: return RETANGULO;
	case 2: return LINHA;
	case 4: return QUADRADO;
	case 5: return HEXAGONO;
	case 6: return CIRCLE;
	case 7: return QUADRADO_LINE;
	default: return RETANGULO;
	}
}

void geraFiguraRandom()
{
	int i;

	for (i = 0; i < tam; i++) {
		if (figs[i] == NULL) {
			float xi = rand() % WINDOW_SIZE;
			float yi = rand() % WINDOW_SIZE;
			float xf = rand() % WINDOW_SIZE;
			float yf = rand() % WINDOW_SIZE;

			/*figs[i] = criarFigura(xi, yi, xf, yf,
				rand() / (RAND_MAX + 1.0),
				rand() / (RAND_MAX + 1.0),
				rand() / (RAND_MAX + 1.0),
				"Boundig Box", randomFig());*/

			figsCount++;
			return;
		}
	}
}


//----------------------------------------------Text Rendering-----------------------------------------------------

void renderBitmapString(float x, float y, void* font, const char* string) {
	const char* c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

int criaFiguraPos(float xi, float yi, float xf, float yf)
{
	int i;

	for (i = 0; i < tam; i++) {
		if (figs[i] == NULL) {
			figs[i] = criarFigura(xi, yi, xf, yf, r, g, b,
				"Boundig Box", tipoFiguraSelecionada, r, g, b);


			figsCount++;
			return i;
		}
	}
	return -1;
}


void apagaFiguraRandom()
{
	int i;
	int figApagar;

	if (figsCount == 0) return;  // não há nada para apagar

	figApagar = rand() % figsCount;

	for (i = 0; i < tam; i++) {
		if (figs[i] != NULL) {
			if (figApagar == 0) {
				apagarFigura(figs[i]);
				figs[i] = NULL;
				figsCount--;
				break;
			}
			else {
				figApagar--;
			}
		}
	}
}


int pick(int x, int y)
{
	int i;
	for (i = tam - 1; i >= 0; i--)
		if (figs[i] != NULL)
			if (dentroFigura(figs[i], x, y))
				return i;

	return -1;
}

void myInit()
{
	int i;

	srand(time(NULL));  // inicializar os números aleatórios

	figs = (Figura*)malloc(sizeof(Figura) * tam);  // alocar memória para o array
	for (i = 0; i < tam; i++)
		figs[i] = NULL;                            // Definir todas as posições como vazias (ponteiro para NULL)


	//Pallete
	pal[0] = criarFigura(0, 0, 19, 19, 1.0, 0.0, 0.0, "red", QUADRADO, 1.0, 0.0, 0.0);
	pal[1] = criarFigura(20, 0, 39, 19, 0.0, 1.0, 0.0, "green", QUADRADO, 0.0, 1.0, 0.0);
	pal[2] = criarFigura(40, 0, 59, 19, 0.0, 0.0, 1.0, "blue", QUADRADO, 0.0, 0.0, 1.0);
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glColor3f(0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
}


void mydisplay() {
	int i;

	glClear(GL_COLOR_BUFFER_BIT);

	// Para desenhar as figuras percorre-se o array das figs e para as posições que têm figuras (ponteiro != NULL)
	// chama-se a função desenhaFigura
	for (i = 0; i < tam; i++) {
		if (figs[i] != NULL) {
			desenhaFigura(figs[i]);
		}
	}

	for (i = 0; i < 3; i++) {
		desenhaFigura(pal[i]);
	}

	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glLineWidth(0.2);
	glVertex2f(0, 19);
	glVertex2f(w, 19);
	glEnd();

	//pal[0] = criarFigura(0, 0, 19, 19, 1.0, 0.0, 0.0, "red", QUADRADO);
	//float xV = (float)w - 5;
	//float yV = (float)w - 50;
	selectingShapes[0] = criarFigura((w - 150), 0, w - 130, 19, 0.0, 0.0, 0.0, "red", QUADRADO_LINE, 0.0, 0.0, 0.0);
	selectingShapes[1] = criarFigura((w - 120), 0, w - 100, 19, 0.0, 0.0, 0.0, "red", TRIANGULO_LINE, 0.0, 0.0, 0.0);
	selectingShapes[2] = criarFigura((w - 90), 0, w - 70, 19, 0.0, 0.0, 0.0, "red", LINHA_LINE, 0.0, 0.0, 0.0);
	selectingShapes[3] = criarFigura((w - 60), 0, w - 40, 19, 0.0, 0.0, 0.0, "red", HEXAGONO_LINE, 0.0, 0.0, 0.0);
	selectingShapes[4] = criarFigura((w - 30), 0, w - 10, 19, 0.0, 0.0, 0.0, "red", CIRCLE, 0.0, 0.0, 0.0);
	selectingShapes[5] = criarFigura((w - 190), 0, w - 160, 19, 0.0, 0.0, 0.0, "red", RETANGULO_LINE, 0.0, 0.0, 0.0);

	desenhaFigura(selectingShapes[0]);
	desenhaFigura(selectingShapes[1]);
	desenhaFigura(selectingShapes[2]);
	desenhaFigura(selectingShapes[3]);
	desenhaFigura(selectingShapes[4]);
	desenhaFigura(selectingShapes[5]);

	/// Text Rendering Data
	if (r == 1 && g == 0 && b == 0) {
		glPushMatrix();
		//glLoadIdentity();
		glColor3f(0, 0, 0);
		renderBitmapString(w - 250, 490, (void*)font, "Color Selected is:  Red");
		glPopMatrix();
	}
	if (r == 0 && g == 1 && b == 0) {
		glPushMatrix();
		//glLoadIdentity();
		glColor3f(0, 0, 0);
		renderBitmapString(w - 250, 490, (void*)font, "Color Selected is:  Green");
		glPopMatrix();
	}

	if (r == 0 && g == 0 && b == 1) {
		glPushMatrix();
		//glLoadIdentity();
		glColor3f(0, 0, 0);
		renderBitmapString(w - 250, 490, (void*)font, "Color Selected is:  Blue");
		glPopMatrix();
	}

	if (r == 0 && g == 0 && b == 0) {
		glPushMatrix();
		//glLoadIdentity();
		glColor3f(0, 0, 0);
		renderBitmapString(w - 250, 490, (void*)font, "Color Selected is:  Black");
		glPopMatrix();
	}
	if (tipoFiguraSelecionada == TRIANGULO) {
		glPushMatrix();
		//glLoadIdentity();
		glColor3f(0, 0, 0);
		renderBitmapString(w - 210, 470, (void*)font, "Drawing Type: Triangle");
		glPopMatrix();
	}
	if (tipoFiguraSelecionada == QUADRADO) {
		glPushMatrix();
		//glLoadIdentity();
		glColor3f(0, 0, 0);
		renderBitmapString(w - 210, 470, (void*)font, "Drawing Type: Square");
		glPopMatrix();
	}
	if (tipoFiguraSelecionada == LINHA) {
		glPushMatrix();
		//glLoadIdentity();
		glColor3f(0, 0, 0);
		renderBitmapString(w - 210, 470, (void*)font, "Drawing Type: Linha");
		glPopMatrix();
	}
	if (tipoFiguraSelecionada == RETANGULO) {
		glPushMatrix();
		//glLoadIdentity();
		glColor3f(0, 0, 0);
		renderBitmapString(w - 210, 470, (void*)font, "Drawing Type: Rectangle");
		glPopMatrix();
	}
	if (tipoFiguraSelecionada == HEXAGONO) {
		glPushMatrix();
		//glLoadIdentity();
		glColor3f(0, 0, 0);
		renderBitmapString(w - 210, 470, (void*)font, "Drawing Type: Hexagon");
		glPopMatrix();
	}
	if (tipoFiguraSelecionada == CIRCLE) {
		glPushMatrix();
		//glLoadIdentity();
		glColor3f(0, 0, 0);
		renderBitmapString(w - 210, 470, (void*)font, "Drawing Type: Circle");
		glPopMatrix();
	}
	glFlush();
}


void mymouseAreaDesenhoInsert(GLint button, GLint state, GLint x, GLint y)
{
	int i;
	float dx, dy, max;


	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		if (aDesenhar) {
			if (tipoFiguraSelecionada == QUADRADO) {
				dx = (float)fabs((double)(xUltimo - x));
				dy = (float)fabs((double)(yUltimo - y));
				max = MAX(dx, dy);

				alteraPos(figs[figuraAtiva], xUltimo - max, yUltimo - max,
					xUltimo + max, yUltimo + max);
			}
			else if (tipoFiguraSelecionada == RETANGULO)
			{
				alteraPos(figs[figuraAtiva], (xUltimo - 2), yUltimo, (x + 2), y);
			}
			else {
				alteraPos(figs[figuraAtiva], xUltimo, yUltimo, x, y);
			}
			aDesenhar = 0;
		}
		else {
			xUltimo = x;
			yUltimo = y;
			figuraAtiva = criaFiguraPos(x, y, x, y);
			if (figuraAtiva != -1)   // memória (array) não cheia
				aDesenhar = 1;

		}


	glutPostRedisplay();
}


void mymouseAreaDesenhoDelete(GLint button, GLint state, GLint x, GLint y)
{
	/*int i;
	float dx, dy, max;



	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		i = pick(x, y);
		if (i != -1) {
			printf("Apaguei uma figura (%i)\n", i);
			apagarFigura(figs[i]);
			figs[i] = NULL;
			figsCount--;
		}
		else {
			printf("Na posição onde clicou não há figuras!\n");
		}
	}

	glutPostRedisplay();*/
}

void mymouseAreaDesenho(GLint button, GLint state, GLint x, GLint y)
{
	if (mode == INSERT)
		mymouseAreaDesenhoInsert(button, state, x, y);
	else
		mymouseAreaDesenhoDelete(button, state, x, y);
}

void mymouseAreaTools(GLint button, GLint state, GLint x, GLint y)
{
	int i;
	for (i = 0; i < 3; i++)
		if (dentroFigura(pal[i], x, y)) {
			getCorFigura(pal[i], &r, &g, &b);
			printf("Mudei cor...\n");
			return;
		}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		for (i = 0; i < 6; i++)
		{
			bool v = getFigure(selectingShapes[i], x, y);
			if (v == true) {
				int k = getShapeTypo(selectingShapes[i]);
				if (k == 26) {
					tipoFiguraSelecionada = TRIANGULO;
				}
				if (k == 25) {
					tipoFiguraSelecionada = QUADRADO;
				}
				if (k == 27) {
					tipoFiguraSelecionada = LINHA;
				}
				if (k == 28) {
					tipoFiguraSelecionada = RETANGULO;
				}
				if (k == 29) {
					tipoFiguraSelecionada = HEXAGONO;
				}
				if (k == 31) {
					tipoFiguraSelecionada = CIRCLE;
				}
				break;
			}
		}
	}

}

void mymouse(GLint button, GLint state, GLint x, GLint y)
{
	y = WINDOW_SIZE - y;

	dragFigure(button, state, x, y);
	del(button, state, x, y);
	changeBoundary(button, state, x, y);

	if (y >= 20)
		mymouseAreaDesenho(button, state, x, y);
	else
		mymouseAreaTools(button, state, x, y);
}

void moveRatoAreaDesenho(GLint x, GLint y)
{
	float dx, dy, max;

	if (aDesenhar) {
		if (tipoFiguraSelecionada == QUADRADO) {
			dx = (float)fabs((double)(xUltimo - x));
			dy = (float)fabs((double)(yUltimo - y));
			max = MAX(dx, dy);
			alteraPos(figs[figuraAtiva], xUltimo - max, yUltimo - max,
				xUltimo + max, yUltimo + max);
		}
		else {
			alteraPos(figs[figuraAtiva], xUltimo, yUltimo, x, y);
		}

		glutPostRedisplay();
	}
}

int drag = -1;
int indexDrag = 0;
//-------------------------------Get mouse coordinates and then get the figure from that coorinate-----------------
void dragFigure(int button, GLint state, int x, int y)
{
	int i;
	if (button == GLUT_RIGHT_BUTTON)
	{
		//To drag the figure
		if (state == GLUT_DOWN) {
			if (drag == 0)
			{
				for (i = 0; i < figsCount; i++) {
					bool v = getFigure(figs[i], x, y);
					if (v == true)
					{
						indexDrag = i;
						drag = 1;
						break;
					}
				}
				return;
			}

			else
			{
				if (drag == 1) {
					indexDragFigure(figs[indexDrag], x, y);
					drag = -1;
					return;
				}
			}
		}

	}
}



void moveRato(GLint x, GLint y)
{
	y = WINDOW_SIZE - y;

	if (y >= 20)
		moveRatoAreaDesenho(x, y);
}
//Deletes the Figure 
void del(int button, GLint state, int x, int y)
{
	int i;
	if (drag == 2)
	{
		for (i = 0; i < figsCount; i++) {
			bool v = getFigure(figs[i], x, y);
			if (v == true)
			{
				deleteFig(figs[i]);
				drag = -1;
				break;
			}
		}
	}
}
//------------------------------Change Boundary Colour--------------------------------------------------------
void changeBoundary(int button, GLint state, int x, int y)
{
	if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_DOWN && changeB == 1) {
			for (int i = 0; i < figsCount; i++) {
				bool v = getFigure(figs[i], x, y);
				if (v == true)
				{
					changeColor(figs[i], r, g, b);
					changeB = 0;
					break;
				}
			}
			changeB = 0;
		}
	}
}



void mykey(unsigned char key, int x, int y)
{
	y = WINDOW_SIZE - y;

	if (key == 'x' || key == 'X') exit(0);

	switch (key) {
	case 'q':
	case 'Q':
		tipoFiguraSelecionada = QUADRADO;
		break;
	case 't':
	case 'T':
		tipoFiguraSelecionada = TRIANGULO;
		break;
	case 'h':
	case 'H':
		tipoFiguraSelecionada = HEXAGONO;
		break;
	case 'l':
	case 'L':
		tipoFiguraSelecionada = LINHA;
		break;
	case 'r':
	case 'R':
		tipoFiguraSelecionada = RETANGULO;
		break;
	case 'i':
	case 'I':
		mode = INSERT; break;
	case 'c':
	case 'C':
		tipoFiguraSelecionada = CIRCLE;
		break;
	case 'd':
	case 'D':
		//mode = DELETE; 
		drag = 2;
		break;
	case 'p':
	case 'P':
		//mode = DELETE;
		//dragFigure();
		drag = 0;
		break;
	case 'b':
	case 'B':
		changeB = 1;
		break;
	}

}


void changeSize(int width, int height)
{
	w = width;
	h = height;
}


int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Bounding Boxes");
	glutDisplayFunc(mydisplay);
	glutMouseFunc(mymouse);
	glutKeyboardFunc(mykey);
	glutPassiveMotionFunc(moveRato);


	init();
	glutReshapeFunc(changeSize);
	myInit();

	glutMainLoop();
}
