#include "pch.h"
#include "container.h"

Container* newContainer() {
	Container* a = (Container*)malloc(sizeof(Container));

	a->size = 0;
	a->capacity = 1;
	a->arr = (Shape**)malloc(sizeof(Shape*));

	return a;
}

void addItem(Container* a, Shape* item) {
	if (a->size + 1 == a->capacity) {
		a->capacity *= 2;
		Shape** tmp = (Shape**)malloc(sizeof(Shape*) * a->capacity);
		for (int i = 0; i < a->size; i++) {
			tmp[i] = a->arr[i];
		}
		free(a->arr);
		a->arr = tmp;
	}

	a->arr[a->size++] = item;
}

void inputContainer(Container* a, FILE* inp_stream) {
	int type;
	while (fscanf(inp_stream, "%d", &type) != EOF) {
		Shapes shape_type = (Shapes)type;
		Shape* new_shape = NULL;

		int color;
		fscanf(inp_stream, "%d", &color);

		if (shape_type == CIRCLE_) {
			int x, y, r;
			fscanf(inp_stream, "%d %d %d", &x, &y, &r);
			new_shape = createCircle(x, y, r);
		}
		else if (shape_type == RECTANGLE_) {
			int x_l, y_l, x_r, y_r;
			fscanf(inp_stream, "%d %d %d %d", &x_l, &y_l, &x_r, &y_r);
			new_shape = createRect(x_l, y_l, x_r, y_r);
		}
		else if (shape_type == TRIANGLE_) {
			int x1, y1, x2, y2, x3, y3;
			fscanf(inp_stream, "%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3);
			new_shape = createTriangle(x1, y1, x2, y2, x3, y3);
		}

		new_shape->color = (Color)color;
		addItem(a, new_shape);
	}
}

void randomContainer(Container* a, int amount) {
	srand(time(NULL));

	for (int i = 0; i < amount; i++) {
		Color color = (Color)(rand() % 7);
		Shapes type = (Shapes)(rand() % 3);
		Shape* new_shape = NULL;

		if (type == CIRCLE_) {
			int x = rand() % 100;
			int y = rand() % 100;
			int r = rand() % 100;
			new_shape = createCircle(x, y, r);
		}
		if (type == RECTANGLE_) {
			int x_l = rand() % 100;
			int y_l = rand() % 100;
			int x_r = rand() % 100;
			int y_r = rand() % 100;
			new_shape = createRect(x_l, y_l, x_r, y_r);
		}
		if (type == TRIANGLE_) {
			int x1 = rand() % 100;
			int y1 = rand() % 100;
			int x2 = rand() % 100;
			int y2 = rand() % 100;
			int x3 = rand() % 100;
			int y3 = rand() % 100;
			new_shape = createTriangle(x1, y1, x2, y2, x3, y3);
		}

		new_shape->color = color;
		addItem(a, new_shape);
	}
}

void outputContainer(Container* a, FILE* out_stream) {
	for (int i = 0; i < a->size; i++) {
		outShape(a->arr[i], out_stream);
	}
}

void outputStatistics(Container* a, FILE* out_stream) {
	fprintf(out_stream, "Total amount of objects: %d\n", a->size);
}

void swap(Shape* a, Shape* b) {
	Shape c = *a;
	*a = *b;
	*b = c;
}

void processContainer(Container* a) {
	for (int i = 0; i < a->size / 2; i++) {
		int swapFlag = 0;
		for (int j = i; j < a->size - i - 1; j++) {
			if (shapeArea(a->arr[j]) > shapeArea(a->arr[j + 1])) {
				swap(a->arr[j], a->arr[j + 1]);
				swapFlag = 1;
			}
		}

		for (int j = a->size - 2 - i; j > i; j--) {
			if (shapeArea(a->arr[j - 1]) > shapeArea(a->arr[j])) {
				swap(a->arr[j - 1], a->arr[j]);
				swapFlag = 1;
			}
		}

		if (!swapFlag)
			break;
	}
}

void clearContainer(Container* a) {
	for (int i = 0; i < a->size; i++) {
		clearShape(a->arr[i]);
	}

	free(a->arr);
	free(a);
}