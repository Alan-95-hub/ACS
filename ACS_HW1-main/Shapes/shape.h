#ifndef SHAPE
#define SHAPE 

#include <stdio.h>

#include "circle.h"
#include "rectangle.h"
#include "triangle.h"

typedef enum Shapes {
	CIRCLE_,
	RECTANGLE_,
	TRIANGLE_
} Shapes;

typedef enum Color {
	RED,
	ORANGE,
	YELLOW,
	GREEN,
	LIGHT_BLUE,
	BLUE,
	PURPLE
} Color;

typedef struct _Shape {
	Color color;
	Shapes type;
	void* alternative;
} Shape;

Shape* createCircle(x, y, r);
Shape* createRect(x_l, y_l, x_r, y_r);
Shape* createTriangle(x1, y1, x2, y2, x3, y3);
void outShape(Shape* a, FILE* out_stream);
double shapeArea(Shape* a);
void clearShape(Shape* item);

#endif