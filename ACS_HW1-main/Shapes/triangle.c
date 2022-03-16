#include "triangle.h"
#include "pch.h"

double getTriangleArea(Triangle* item) {
	double area = abs((item->x2 - item->x1) * (item->y3 - item->y1) - (item->x3 - item->x1) * (item->y2 - item->y1));
	area *= 0.5;
	return area;
}

void outTriangle(Triangle* a, FILE* out_stream, const char* color) {
	fprintf(out_stream, "%s triangle(x1: %d, y1: %d, x2: %d, y2: %d, x3: %d, y3: %d)\n", color, a->x1, a->y1, a->x2, a->y2, a->x3, a->y3);
}