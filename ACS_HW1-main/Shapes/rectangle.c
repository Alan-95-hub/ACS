#include "rectangle.h"
#include "pch.h"

double getRectArea(Rect* item) {
	double area = abs(item->x_l - item->x_r);
	area *= abs(item->y_l - item->y_r);
	return area;
}

void outRect(Rect* a, FILE* out_stream, const char* color) {
	fprintf(out_stream, "%s rectangle(x_l: %d, y_l: %d, x_r: %d, y_r: %d)\n", color, a->x_l, a->y_l, a->x_r, a->y_r);
}