#ifndef RECTANGLE
#define RECTANGLE

#include <stdio.h>

typedef struct _Rect {
	int x_l, y_l;
	int x_r, y_r;
} Rect;

double getRectArea(Rect* item);
void outRect(Rect* a, FILE* out_stream, const char* color);

#endif