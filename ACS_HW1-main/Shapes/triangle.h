#ifndef TRIANGLE
#define TRIANGLE

#include <stdio.h>

typedef struct _Triangle {
	int x1, y1;
	int x2, y2;
	int x3, y3;
} Triangle;

double getTriangleArea(Triangle* item);
void outTriangle(Triangle* a, FILE* out_stream, const char* color);

#endif