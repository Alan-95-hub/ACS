#include "circle.h"

const double PI = 3.1415926535;

double getCircleArea(Circle* item) {
	double area = item->r * item->r;
	area *= PI;
	return area;
}

void outCircle(Circle* a, FILE* out_stream, const char* color) {
	fprintf(out_stream, "%s circle(x: %d, y: %d, r: %d)\n", color, a->x, a->y, a->r);
}