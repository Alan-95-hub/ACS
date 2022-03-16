#include "shape.h"

#include <stdlib.h>

Shape* createCircle(x, y, r) {
	Shape* a = (Shape*)malloc(sizeof(Shape));
	Circle* tmp = (Circle*)malloc(sizeof(Circle));

	tmp->x = x;
	tmp->y = y;
	tmp->r = r;

	a->alternative = tmp;
	a->type = CIRCLE_;
	return a;
}
Shape* createRect(x_l, y_l, x_r, y_r) {
	Shape* a = (Shape*)malloc(sizeof(Shape));
	Rect* tmp = (Rect*)malloc(sizeof(Rect));

	tmp->x_l = x_l;
	tmp->y_l = y_l;
	tmp->x_r = x_r;
	tmp->y_r = y_r;

	a->alternative = tmp;
	a->type = RECTANGLE_;
	return a;
}

Shape* createTriangle(x1, y1, x2, y2, x3, y3) {
	Shape* a = (Shape*)malloc(sizeof(Shape));
	Triangle* tmp = (Triangle*)malloc(sizeof(Triangle));

	tmp->x1 = x1;
	tmp->y1 = y1;
	tmp->x2 = x2;
	tmp->y2 = y2;
	tmp->x3 = x3;
	tmp->y3 = y3;

	a->alternative = tmp;
	a->type = TRIANGLE_;
	return a;
}

void outShape(Shape* a, FILE* out_stream) {
	const char* colors[7] = { "red", "orange", "yellow", "green", "light blue", "blue", "purple" };
	if (a->type == CIRCLE_)
		outCircle(a->alternative, out_stream, colors[a->color]);
	if (a->type == RECTANGLE_)
		outRect(a->alternative, out_stream, colors[a->color]);
	if (a->type == TRIANGLE_)
		outTriangle(a->alternative, out_stream, colors[a->color]);
}

double shapeArea(Shape* a) {
	if (a->type == CIRCLE_)
		return getCircleArea(a->alternative);
	if (a->type == RECTANGLE_)
		return getRectArea(a->alternative);
	if (a->type == TRIANGLE_)
		return getTriangleArea(a->alternative);
}

void clearShape(Shape* item) {
	free(item->alternative);
	free(item);
}