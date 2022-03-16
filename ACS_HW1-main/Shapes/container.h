#ifndef CONTAINER
#define CONTAINER

#include "shape.h"

typedef struct _Container {
	int size;
	int capacity;

	Shape** arr;
} Container;

Container* newContainer();
void addItem(Container* a, Shape* item);
void inputContainer(Container* a, FILE* inp_stream);
void randomContainer(Container* a, int amount);
void outputContainer(Container* a, FILE* out_stream);
void outputStatistics(Container* a, FILE* out_stream);
void processContainer(Container* a);
void clearContainer(Container* a);

#endif