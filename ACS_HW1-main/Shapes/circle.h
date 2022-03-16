#ifndef CIRCLE
#define CIRCLE

#include <stdio.h>

typedef struct _Circle {
	int x, y;
	int r;
} Circle;

double getCircleArea(Circle* item);
void outCircle(Circle* a, FILE* out_stream, const char* color);

#endif