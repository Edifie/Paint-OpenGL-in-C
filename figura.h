#include<stdbool.h>
#ifndef __FIGURA_H__
#define __FIGURA_H__

#define MAX(X,Y) (X>Y?X:Y)
#define MIN(X,Y) (X<Y?X:Y)


#define TRIANGULO 20
#define QUADRADO  21
#define LINHA     22
#define RETANGULO 23
#define HEXAGONO  24
#define QUADRADO_LINE 25
#define TRIANGULO_LINE 26 
#define LINHA_LINE     27
#define RETANGULO_LINE 28
#define HEXAGONO_LINE  29
#define CIRCLE_LINE  30
#define CIRCLE  31

typedef struct figura* Figura;

Figura criarFigura(float xi, float yi, float xf, float yf, float r, float g, float b, char* nome, int tipo,
	float rb, float gb, float bb);
void apagarFigura(Figura f);
void desenhaFigura(Figura f);
void alteraPos(Figura f, float xi, float yi, float xf, float yf);
int dentroFigura(Figura f, float x, float y);
void getCorFigura(Figura f, float* r, float* g, float* b);

void dragFigure(int button, GLint state, int x, int y);
bool getFigure(Figura f, int x, int y);
void indexDragFigure(Figura f, int x, int y);
void deleteFig(Figura f);
void del(int button, GLint state, int x, int y);
int getShapeTypo(Figura f);
void changeColor(Figura f, float r, float g, float b);
void changeBoundary(int button, GLint state, int x, int y);
void renderBitmapString(float x, float y, void* font, const char* string);
#endif