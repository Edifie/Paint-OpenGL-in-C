#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include <gl/glut.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "figura.h"






struct figura {
	float xi, yi;
	float xf, yf;
	float r, g, b;
	char* nome;
	int tipo;
	bool status;
	float rb, gb, bb;
};


// Função que recebe uma figura e acerta o (xf,yf) para garantir que é um quadrado
// Os dois lados ficam iguais ao lado maior.
//--------------------------------------------------SQUARE
void acertaQuadrado(Figura f)
{
	float ladoX = f->xf - f->xi;
	float ladoY = f->yf - f->yi;

	float ladoMaior = MAX(ladoX, ladoY);

	f->xf = f->xi + ladoMaior;
	f->yf = f->yi + ladoMaior;
}

// Esta função garante que ao criar as figuras o ponto (xi,yi) corresponde ao canto inferior esquerdo
// e o ponto (xf,yf) ao canto superior direito
Figura criarFigura(float xi, float yi, float xf, float yf,
	float r, float g, float b, char* nome, int tipo, float rb, float gb, float bb) {
	Figura f;

	f = (Figura)malloc(sizeof(struct figura));
	f->xi = MIN(xi, xf);
	f->yi = MIN(yi, yf);
	f->xf = MAX(xi, xf);
	f->yf = MAX(yi, yf);
	f->r = r;
	f->g = g;
	f->b = b;
	f->tipo = tipo;
	f->bb = bb;
	f->gb = gb;
	f->rb = rb;

	f->nome = (char*)malloc(sizeof(char) * (strlen(nome) + 1));
	strcpy(f->nome, nome);

	//if (f->tipo == QUADRADO || f->tipo == HEXAGONO) acertaQuadrado(f);
	return f;
}


void apagarFigura(Figura f) {
	free(f->nome);
	free(f);
}

void desenhaRetangulo(Figura f)
{
	if (f->status != false) {
		glColor3f(f->r, f->g, f->b);
		glBegin(GL_POLYGON);
		//		glColor3f(f->r, f->g, f->b);
		glVertex2f(f->xi, f->yi);
		//		glColor3f(f->r + 0.1, f->g, f->b);
		glVertex2f(f->xi, f->yf);
		//		glColor3f(f->r, f->g + 0.1, f->b);
		glVertex2f(f->xf, f->yf);
		//		glColor3f(f->r, f->g, f->b + 0.1);
		glVertex2f(f->xf, f->yi);
		glEnd();

		//glColor3f(0,0,0);
		//glBegin(GL_LINE_LOOP);
		//glVertex2f(f->xi, f->yi);
		//glVertex2f(f->xi, f->yf);
		//glVertex2f(f->xf, f->yf);
		//glVertex2f(f->xf, f->yi);
		//glEnd();

		//Boundary
		glColor3f(f->rb, f->gb, f->bb);
		glBegin(GL_LINE_LOOP);
		glVertex2f(f->xi, f->yi);
		glVertex2f(f->xi, f->yf);
		glVertex2f(f->xf, f->yf);
		glVertex2f(f->xf, f->yi);
		glEnd();
	}
}

void desenhaRetanguloLine(Figura f)
{
	if (f->status != false) {
		glColor3f(0, 0, 0);
		glBegin(GL_LINES);
		//		glColor3f(f->r, f->g, f->b);
		glVertex2f(f->xi, f->yi);
		//		glColor3f(f->r + 0.1, f->g, f->b);
		glVertex2f(f->xi, f->yf);
		//		glColor3f(f->r, f->g + 0.1, f->b);
		glVertex2f(f->xf, f->yf);
		//		glColor3f(f->r, f->g, f->b + 0.1);
		glVertex2f(f->xf, f->yi);
		glEnd();

		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(f->xi, f->yi);
		glVertex2f(f->xi, f->yf);
		glVertex2f(f->xf, f->yf);
		glVertex2f(f->xf, f->yi);
		glEnd();
	}
}

void desenhaTriangulo(Figura f)
{
	if (f->status != false) {
		glColor3f(f->r, f->g, f->b);
		glBegin(GL_POLYGON);
		glColor3f(f->r, f->g, f->b);
		glVertex2f(f->xi, f->yi);
		glColor3f(f->r + 0.1, f->g, f->b);
		glVertex2f((f->xi + f->xf) / 2, f->yf);
		glColor3f(f->r, f->g, f->b + 0.1);
		glVertex2f(f->xf, f->yi);
		glEnd();

		//Boundary
		glColor3f(f->rb, f->gb, f->bb);
		glBegin(GL_LINE_LOOP);
		glColor3f(f->rb, f->gb, f->bb);
		glVertex2f(f->xi, f->yi);
		glColor3f(f->rb, f->gb, f->bb);
		glVertex2f((f->xi + f->xf) / 2, f->yf);
		glColor3f(f->rb, f->gb, f->bb);
		glVertex2f(f->xf, f->yi);
		glEnd();
	}
}

void desenhaTrianguloLine(Figura f)
{
	if (f->status != false) {
		glColor3f(0, 0, 0);
		glBegin(GL_LINE_LOOP);
		glColor3f(f->r, f->g, f->b);
		glVertex2f(f->xi, f->yi);
		glColor3f(0, 0, 0);
		glVertex2f((f->xi + f->xf) / 2, f->yf);
		glColor3f(0, 0, 0);
		glVertex2f(f->xf, f->yi);
		glEnd();
	}
}


void desenhaLinha(Figura f)
{
	if (f->status != false) {
		glColor3f(f->r, f->g, f->b);
		glBegin(GL_LINES);
		glVertex2f(f->xi, f->yi);
		glVertex2f(f->xf, f->yf);
		glEnd();
	}
}
void desenhaLinhaLine(Figura f)
{
	if (f->status != false) {
		glColor3f(0, 0, 0);
		glBegin(GL_LINES);
		glVertex2f(f->xi, f->yi);
		glVertex2f(f->xf, f->yf);
		glEnd();
	}
}

void desenhaHexagono(Figura f)
{
	if (f->status != false) {
		// calcula o centro da figura
		float xc = (f->xi + f->xf) / 2;
		float yc = (f->yi + f->yf) / 2;
		// calcula o tamanho da figura (distancia do centro aos pontos)
		float raio = (f->xf - f->xi) / 2;

		glColor3f(f->r, f->g, f->b);
		glBegin(GL_POLYGON);
		glVertex2f(xc + raio, yc);
		glVertex2f(xc + (raio * cos(-3.14 / 3)), yc + (raio * sin(-3.14 / 3))); // -60 graus = -PI/3 radianos
		glVertex2f(xc + (raio * cos(-2 * 3.14 / 3)), yc + (raio * sin(-2 * 3.14 / 3))); // -120 graus = -2/3 * PI radianos
		glVertex2f(xc - raio, yc);
		glVertex2f(xc + (raio * cos(2 * 3.14 / 3)), yc + (raio * sin(2 * 3.14 / 3))); // 120 graus = 2/3 * PI radianos
		glVertex2f(xc + (raio * cos(3.14 / 3)), yc + (raio * sin(3.14 / 3))); // 60 graus = PI/3 radianos
		glEnd();

		//Boundary
		glColor3f(f->rb, f->gb, f->bb);
		glBegin(GL_LINE_LOOP);
		glVertex2f(xc + raio, yc);
		glVertex2f(xc + (raio * cos(-3.14 / 3)), yc + (raio * sin(-3.14 / 3))); // -60 graus = -PI/3 radianos
		glVertex2f(xc + (raio * cos(-2 * 3.14 / 3)), yc + (raio * sin(-2 * 3.14 / 3))); // -120 graus = -2/3 * PI radianos
		glVertex2f(xc - raio, yc);
		glVertex2f(xc + (raio * cos(2 * 3.14 / 3)), yc + (raio * sin(2 * 3.14 / 3))); // 120 graus = 2/3 * PI radianos
		glVertex2f(xc + (raio * cos(3.14 / 3)), yc + (raio * sin(3.14 / 3))); // 60 graus = PI/3 radianos
		glEnd();

	}
}


void desenhaHexagonoLine(Figura f)
{
	if (f->status != false) {
		// calcula o centro da figura
		float xc = (f->xi + f->xf) / 2;
		float yc = (f->yi + f->yf) / 2;
		// calcula o tamanho da figura (distancia do centro aos pontos)
		float raio = (f->xf - f->xi) / 2;


		glColor3f(0, 0, 0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(xc + raio, yc);
		glVertex2f(xc + (raio * cos(-3.14 / 3)), yc + (raio * sin(-3.14 / 3))); // -60 graus = -PI/3 radianos
		glVertex2f(xc + (raio * cos(-2 * 3.14 / 3)), yc + (raio * sin(-2 * 3.14 / 3))); // -120 graus = -2/3 * PI radianos
		glVertex2f(xc - raio, yc);
		glVertex2f(xc + (raio * cos(2 * 3.14 / 3)), yc + (raio * sin(2 * 3.14 / 3))); // 120 graus = 2/3 * PI radianos
		glVertex2f(xc + (raio * cos(3.14 / 3)), yc + (raio * sin(3.14 / 3))); // 60 graus = PI/3 radianos
		glEnd();
	}
}

void desenhaRectangle2(Figura f)
{
	if (f->status != false) {
		float centerX = (f->xi + f->xf) / 2;
		/*f->xi = centerX - (0.5*f->xi);
		f->xf = centerX + (0.5 * f->xf);*/
		glColor3f(f->r, f->g, f->b);
		glBegin(GL_POLYGON);
		//		glColor3f(f->r, f->g, f->b);
		glVertex2f(f->xi, f->yi);
		//		glColor3f(f->r + 0.1, f->g, f->b);
		glVertex2f(f->xi, f->yf);
		//		glColor3f(f->r, f->g + 0.1, f->b);
		glVertex2f(f->xf, f->yf);
		//		glColor3f(f->r, f->g, f->b + 0.1);
		glVertex2f(f->xf, f->yi);
		glEnd();


		//glColor3f(0, 0, 0);
		//glBegin(GL_LINE_LOOP);
		//glVertex2f(f->xi, f->yi);
		//glVertex2f(f->xi, f->yf);
		//glVertex2f(f->xf, f->yf);
		//glVertex2f(f->xf, f->yi);
		//glEnd();


		//Boundary
		glColor3f(f->rb, f->gb, f->bb);
		glBegin(GL_LINE_LOOP);
		glVertex2f(f->xi, f->yi);
		glVertex2f(f->xi, f->yf);
		glVertex2f(f->xf, f->yf);
		glVertex2f(f->xf, f->yi);
		glEnd();
	}
}


void desenhaCircle(Figura f)
{
	if (f->status != false) {

		float centerX = (f->xi + f->xf) / 2;
		float centerY = (f->yi + f->yf) / 2;
		float radius = centerX - f->xi;
		glColor3f(f->r, f->g, f->b);
		float PI = 3.14;
		int num_segments = 150;
		int x = centerX;
		int y = centerY;
		glBegin(GL_TRIANGLE_FAN);
		int i;
		int triangleAmount = 20;
		GLfloat twicePi = 2.0f * PI;
		glVertex2f(x, y);
		for (i = 0; i <= triangleAmount; i++) {
			glVertex2f(
				x + (radius * cos(i * twicePi / triangleAmount)),
				y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
		glEnd();



		//Boundary
		glBegin(GL_LINE_LOOP);

		triangleAmount = 20;
		twicePi = 2.0f * PI;
		glColor3f(f->rb, f->gb, f->bb);
		glVertex2f(x, y);
		for (i = 0; i <= triangleAmount; i++) {
			glVertex2f(
				x + (radius * cos(i * twicePi / triangleAmount)),
				y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
		glEnd();
	}

}



void desenhaFigura(Figura f)
{
	switch (f->tipo)
	{
	case LINHA:
		desenhaLinha(f); break;
	case RETANGULO:
		desenhaRectangle2(f); break;
	case QUADRADO:
		desenhaRetangulo(f); break;
	case TRIANGULO:
		desenhaTriangulo(f); break;
	case HEXAGONO:
		desenhaHexagono(f); break;
	case QUADRADO_LINE:
		desenhaRetanguloLine(f); break;
	case TRIANGULO_LINE:
		desenhaTrianguloLine(f); break;
	case LINHA_LINE:
		desenhaLinhaLine(f); break;
	case HEXAGONO_LINE:
		desenhaHexagono(f); break;
	case CIRCLE:
		desenhaCircle(f); break;
	default:
		desenhaRetangulo(f); break;
	}
}

void alteraPos(Figura f, float xi, float yi, float xf, float yf)
{
	f->xi = MIN(xi, xf);
	f->yi = MIN(yi, yf);
	f->xf = MAX(xi, xf);
	f->yf = MAX(yi, yf);

	//if (f->tipo == QUADRADO || f->tipo == HEXAGONO) acertaQuadrado(f);
}

int dentroFigura(Figura f, float x, float y)
{
	return (f->xi <= x && f->xf >= x && f->yi <= y && f->yf >= y);
}

void getCorFigura(Figura f, float* r, float* g, float* b)
{
	*r = f->r;
	*g = f->g;
	*b = f->b;
}



bool getFigure(Figura f, int x, int y)
{
	if (f->xi <= x && f->xf >= x && f->yi <= y && f->yf >= y)
	{
		//Will return true when cursor lies in the figure
		return true;
	}
	else
	{
		//Will return false when cursor is not in the figure 
		return false;
	}
}

void indexDragFigure(Figura f, int x, int y)
{
	//Center Points Calculations
	float xCenter = (f->xf + f->xi) / 2;
	float yCenter = (f->yf + f->yi) / 2;
	//Distance of Center from end Points 
	float xiDist = xCenter - f->xi;
	float xfDist = f->xf - xCenter;

	float yiDist = yCenter - f->yi;
	float yfDist = f->yf - yCenter;

	//Translations
	//New xi xf yi and yf 
	f->xi = (float)x - xiDist;
	f->xf = (float)x + xfDist;

	f->yi = y - yiDist;
	f->yf = y + yfDist;
	xCenter = 0;
	yCenter = 0;
	xiDist = 0;
	xfDist = 0;
	yiDist = 0;
	yfDist = 0;
}



void deleteFig(Figura f)
{
	f->status = false;
	glutPostRedisplay();
}


int getShapeTypo(Figura f)
{
	return f->tipo;
}


void changeColor(Figura f, float r, float g, float b)
{
	f->rb = r;
	f->gb = g;
	f->bb = b;
}